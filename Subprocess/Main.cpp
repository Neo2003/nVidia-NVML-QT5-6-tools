#include <unistd.h>
#include <QCoreApplication>
#include <QObject>
#include <iostream>
#include <QSocketNotifier>
#include <QLibrary>
#include "../include/nvml.h"

typedef nvmlReturn_t (*Init)();
typedef nvmlReturn_t (*Shutdown)();
typedef nvmlReturn_t (*DeviceGetHandleByIndex)(unsigned int, nvmlDevice_t*);
typedef nvmlReturn_t (*DeviceSetFanSpeed)(nvmlDevice_t,unsigned int,unsigned int);

class nvwrite : public QObject
{
    Q_OBJECT

    public:
        nvwrite( QObject* parent = 0 ) : QObject( parent )
        {
            QSocketNotifier *n1 = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read); //, this);
            connect(n1, SIGNAL(activated(int)), this, SLOT(onMainApplicationSignal()));
            
            QLibrary nvmlLib("libnvidia-ml.so.1");
            Init nvmlInit = (Init)nvmlLib.resolve("nvmlInit_v2");
            nvmlShutdown = (Shutdown)nvmlLib.resolve("nvmlShutdown");
            nvmlDeviceGetHandleByIndex = (DeviceGetHandleByIndex)nvmlLib.resolve("nvmlDeviceGetHandleByIndex_v2");
            nvmlDeviceSetFanSpeed =(DeviceSetFanSpeed)nvmlLib.resolve("nvmlDeviceSetFanSpeed_v2");
            
            nvmlInit();
        }
        ~nvwrite()
        {
            nvmlShutdown();
        }
    private:
        DeviceGetHandleByIndex nvmlDeviceGetHandleByIndex;
        DeviceSetFanSpeed nvmlDeviceSetFanSpeed;
        Shutdown nvmlShutdown;
        void setFan(unsigned int cardnb, unsigned int fannb, unsigned int value)
        {
            nvmlDevice_t card;
            nvmlDeviceGetHandleByIndex(cardnb,&card);
            nvmlDeviceSetFanSpeed(card,fannb,value);
        }

    signals:
        void interProcessSignal();
        void finished();

    public slots:
        void finish()
        {
            exit(0);
        }
        void onMainApplicationSignal()
        {
            std::string command;
            std::cin >> command;
            QString received = QString::fromStdString(command);
            QStringList list = received.split(",", Qt::SkipEmptyParts);
            if (list[0]== "V") // ventilation format "V,card,fan,value"
            {
                unsigned int cardnb = list[1].toInt();;
                unsigned int fannb = list[2].toInt();;
                unsigned int value = list[3].toInt();;
                setFan(cardnb, fannb, value);
            }
            else if (command=="quit")
            {
                emit finished();
            }            
        }
};

int main(int argc, char *argv[]) {
    QCoreApplication::setSetuidAllowed(true); // Allow application to be run as root or sudo

    QCoreApplication app( argc, argv );
    nvwrite writer;

    QObject::connect(&writer, SIGNAL(finished()), &writer, SLOT(finish())); 
    return app.exec();
}
#include "Main.moc"
