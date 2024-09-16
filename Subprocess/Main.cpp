#include <unistd.h>
#include <QCoreApplication>
#include <QObject>
#include <iostream>
#include <QSocketNotifier>
#include <QLibrary>
#include "../include/nvml.h"

typedef int (*Init)();
typedef int (*GetDeviceCount)(unsigned int*);
typedef int (*DeviceGetHandleByIndex)(unsigned int, nvmlDevice_t*);
typedef int (*DeviceGetName)(nvmlDevice_t,char*,int);
typedef int (*DeviceGetTemperature)(nvmlDevice_t,nvmlTemperatureSensors_t,unsigned int*);
typedef int (*DeviceSetFanControlPolicy)(nvmlDevice_t,unsigned int,nvmlFanControlPolicy_t);
typedef int (*DeviceSetFanSpeed)(nvmlDevice_t,unsigned int,unsigned int);

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
            nvmlDeviceGetHandleByIndex = (DeviceGetHandleByIndex)nvmlLib.resolve("nvmlDeviceGetHandleByIndex_v2");
            nvmlDeviceGetTemperature =(DeviceGetTemperature)nvmlLib.resolve("nvmlDeviceGetTemperature");
            nvmlDeviceSetFanSpeed =(DeviceSetFanSpeed)nvmlLib.resolve("nvmlDeviceSetFanSpeed_v2");
            nvmlDeviceSetFanControlPolicy =(DeviceSetFanControlPolicy)nvmlLib.resolve("nvmlDeviceSetFanControlPolicy");
            
            nvmlInit();
        }

    private:
        DeviceGetHandleByIndex nvmlDeviceGetHandleByIndex;
        DeviceGetTemperature nvmlDeviceGetTemperature;
        DeviceSetFanSpeed nvmlDeviceSetFanSpeed;
        DeviceSetFanControlPolicy nvmlDeviceSetFanControlPolicy;
        
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
