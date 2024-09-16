
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtCore/QTimer>
#include <QtCharts>
#include <QChartView>
#include <QListIterator>
#include <QAbstractAxis>
#include <QtMath>
#include "ui_NvControl.h"
#include "../include/nvml.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

private:
    QTimer *tUpdate;
    QQueue<int> TempQueue;
    QQueue<int> FanQueue;
    QQueue<float> WattQueue;
    QChart *chart;
    QChartView *chartView;
    QValueAxis *axisTemp;
    QValueAxis *axisWatt;
    float MinPower, MaxPower;
    int MinTemp, MaxTemp;
    const int iNbPoints = 200;
    QLabel *StatusLabel;
    int prevTemp;
    QTimer *tDownLag;
    int fanvalue, fanoldvalue;
    QProcess *nvmlCmd;
    
    typedef int (*Init)();
    typedef int (*DeviceGetHandleByIndex)(unsigned int, nvmlDevice_t*);
    typedef int (*DeviceGetTemperature)(nvmlDevice_t,nvmlTemperatureSensors_t,unsigned int*);
    typedef int (*DeviceGetPowerUsage)(nvmlDevice_t,unsigned int*);
    
    DeviceGetHandleByIndex nvmlDeviceGetHandleByIndex;
    DeviceGetTemperature nvmlDeviceGetTemperature;
    DeviceGetPowerUsage nvmlDeviceGetPowerUsage;
    
    nvmlDevice_t card;
    
public slots:
    void UpdateData();
    int ComputeFan(int valTemperature);

private slots:
    bool LoadNVMLLibrary();
    
    unsigned int GetTemperature();
    float GetPower();
    
public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();
};

#endif
