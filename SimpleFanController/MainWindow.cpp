#include "MainWindow.h"
#include <QLibrary>
#include <unistd.h>

bool MainWindow::LoadNVMLLibrary()
{
    QLibrary nvmlLib("libnvidia-ml.so.1");
    
    Init nvmlInit = (Init)nvmlLib.resolve("nvmlInit_v2");
    nvmlShutdown = (Shutdown)nvmlLib.resolve("nvmlShutdown");
    nvmlDeviceGetHandleByIndex = (DeviceGetHandleByIndex)nvmlLib.resolve("nvmlDeviceGetHandleByIndex_v2");
    nvmlDeviceGetTemperature = (DeviceGetTemperature)nvmlLib.resolve("nvmlDeviceGetTemperature");
    nvmlDeviceGetPowerUsage = (DeviceGetPowerUsage)nvmlLib.resolve("nvmlDeviceGetPowerUsage");
    
    nvmlInit();
    nvmlDeviceGetHandleByIndex(0,&card);
    return true;
}


unsigned int MainWindow::GetTemperature()
{
    unsigned int temp;
    nvmlDeviceGetTemperature(card,NVML_TEMPERATURE_GPU,&temp);
    return temp;
}

float MainWindow::GetPower()
{
    unsigned int power;
    nvmlDeviceGetPowerUsage(card,&power);
    float wpower = float(power)/1000.0f;
    return wpower;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this); // this sets up GUI
    
    nvmlCmd = new QProcess(this); // start subprocess
    QString exec = "./nvmlCmd";
    QStringList params;
    nvmlCmd->start(exec, params);
    nvmlCmd->waitForStarted();
    
    // Use a timer to auto refresh data.
    tUpdate = new QTimer( this );
    connect( tUpdate,  SIGNAL( timeout() ), this, SLOT( UpdateData() ) );
    tUpdate->start(2000);

    chart = new QChart();
    chart->setTitle("Power (red), temperature (blue) and fan (green)");
    chart->legend()->hide();
    axisTemp = new QValueAxis();
    axisTemp->setRange(30, 85);//25,80
    axisTemp->setTickCount(12);
    axisTemp->setLabelsColor(Qt::blue);
    chart->addAxis(axisTemp,Qt::AlignRight);
    
    axisWatt = new QValueAxis();
    axisWatt->setRange(20, 350);//0,350
    axisWatt->setTickCount(12);
    axisWatt->setLabelsColor(Qt::red);
    chart->addAxis(axisWatt,Qt::AlignLeft);
    
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    this->setCentralWidget(chartView);
    
    StatusLabel = new QLabel("");
    statusBar()->addWidget(StatusLabel);
    
    MinPower = 1000;
    MaxPower = 0;
    MinTemp = 1000;
    MaxTemp = 0;
    fanoldvalue = 0;
    for (int i=1;i<iNbPoints;i++)
    {
        TempQueue.enqueue(20);
        WattQueue.enqueue(-10);
        FanQueue.enqueue(0);
    }
    prevTemp = 0;
    tDownLag = new QTimer( this );
    LoadNVMLLibrary();
}

MainWindow::~MainWindow()
{
    nvmlCmd->write("quit\n"); // ask subprocess to end
    nvmlShutdown();
    delete tUpdate;
    delete axisTemp;
    delete chart;
    delete chartView;
}

int MainWindow::ComputeFan(int valTemperature)
{
    int fan = qCeil(std::min(std::max(45, int((12.0/7.0)*valTemperature-(200.0/7.0))), 100)); // fan curve
    if (fanoldvalue > fan && fanoldvalue - fan > 6 && fanoldvalue <= 100)
    {
        fan = fanoldvalue - 6;
    }
    nvmlCmd->write(QString::asprintf("V,0,0,%u\n",fan).toStdString().c_str()); // ask V:ventilation, card 0, fan 0, speed
    nvmlCmd->write(QString::asprintf("V,0,1,%u\n",fan).toStdString().c_str()); // ask V:ventilation, card 0, fan 1, speed
    return fan;
}

void MainWindow::UpdateData()
{
    int TempValue = GetTemperature();
    
    TempQueue.enqueue(TempValue);
    if (TempQueue.size() > iNbPoints)
        TempQueue.dequeue();
    MinTemp = std::min(TempValue, MinTemp);
    MaxTemp = std::max(TempValue, MaxTemp);
    
    QLineSeries *serie = new QLineSeries();

    int id=0;
    QListIterator<int> i(TempQueue);
    while (i.hasNext())
        serie->append(id++, i.next());
    
    chart->removeAllSeries();
    chart->addSeries(serie);
    serie->attachAxis(axisTemp);
    QPen penT(Qt::blue);
    serie->setPen(penT);

    float WattValue = GetPower();
    WattQueue.enqueue(WattValue);
    if (WattQueue.size() > iNbPoints)
        WattQueue.dequeue();
    MinPower = std::min(WattValue, MinPower);
    MaxPower = std::max(WattValue, MaxPower);
    
    serie = new QLineSeries();
    id=0;
    QListIterator<float> j(WattQueue);
    while (j.hasNext())
        serie->append(id++, j.next());
    
    chart->addSeries(serie);
    serie->attachAxis(axisWatt);
    QPen penW(Qt::red);
    serie->setPen(penW);
    
    if (TempValue>prevTemp)
    {
        fanoldvalue = fanvalue;
        fanvalue = ComputeFan(TempValue);
        tDownLag->stop();
    }
    else if (tDownLag->isActive())
    {   if (tDownLag->remainingTime()<2000)
        {
            tDownLag->stop();
            fanoldvalue = fanvalue;
            fanvalue = ComputeFan(TempValue);
        }
        //else // nothing
    }
    else if (prevTemp>=TempValue)
    {       
        tDownLag->start(21500);
    }
    FanQueue.enqueue(fanvalue);
    if (FanQueue.size() > iNbPoints)
        FanQueue.dequeue();
    
    serie = new QLineSeries();
    id=0;
    QListIterator<int> k(FanQueue);
    while (k.hasNext())
        serie->append(id++, k.next());
    chart->addSeries(serie);
    serie->attachAxis(axisTemp);
    QPen penF(Qt::green);
    serie->setPen(penF);
    
    prevTemp = TempValue;
    QString s_output = QString::asprintf(" Temp: %u°C, Power draw %0.1fW -> Fan: %u%% | Min: %u°C, %0.1fW | Max: %u°C, %0.1fW   ", TempValue, WattValue, fanvalue, MinTemp, MinPower, MaxTemp, MaxPower);
    StatusLabel->setText(s_output);
    StatusLabel->repaint();
}
