#include <QLibrary>
#include "include/nvml.h"

struct X {
   static const char* brand[];
};
const char* X::brand[] = {"UNKNOWN","QUADRO","TESLA","NVS","GRID","GEFORCE","TITAN","NVIDIA_VAPPS","NVIDIA_VPC","NVIDIA_VCS","NVIDIA_VWS","NVIDIA_CLOUD_GAMING","QUADRO_RTX","NVIDIA_RTX","NVIDIA","GEFORCE_RTX","TITAN_RTX"};

typedef int (*Init)();
typedef int (*GetDeviceCount)(unsigned int*);
typedef int (*DeviceGetHandleByIndex)(unsigned int, nvmlDevice_t*);
typedef int (*DeviceGetName)(nvmlDevice_t,char*,int);
typedef int (*DeviceGetTemperature)(nvmlDevice_t,nvmlTemperatureSensors_t,unsigned int*);
typedef int (*DeviceGetPowerUsage)(nvmlDevice_t,unsigned int*);
typedef int (*DeviceGetNumFans)(nvmlDevice_t,unsigned int*);
typedef int (*DeviceGetFanSpeed)(nvmlDevice_t,unsigned int,unsigned int*);
typedef int (*DeviceSetFanControlPolicy)(nvmlDevice_t,unsigned int,nvmlFanControlPolicy_t);
typedef int (*DeviceSetFanSpeed)(nvmlDevice_t,unsigned int,unsigned int);
typedef int (*DeviceGetNumGpuCores)(nvmlDevice_t,unsigned int*);
typedef int (*DeviceGetClock)(nvmlDevice_t,nvmlClockType_t,nvmlClockId_t,unsigned int*);
typedef int (*DeviceGetBrand)(nvmlDevice_t,nvmlBrandType_t);
typedef int (*DeviceGetCurrPcieLinkGeneration)(nvmlDevice_t,unsigned int*);
typedef int (*DeviceGetCurrPcieLinkWidth)(nvmlDevice_t,unsigned int*);
typedef int (*DeviceGetGpuMaxPcieLinkGeneration)(nvmlDevice_t,unsigned int*);
typedef int (*DeviceGetMemoryInfo)(nvmlDevice_t,nvmlMemory_t*);
typedef int (*DeviceGetGpcClkMinMaxVfOffset)(nvmlDevice_t,int*,int*);
typedef int (*DeviceGetMemClkMinMaxVfOffset)(nvmlDevice_t,int*,int*);
typedef int (*DeviceGetPowerManagementLimit)(nvmlDevice_t,unsigned int*);
typedef int (*DeviceGetMemClkVfOffset)(nvmlDevice_t,int*);
typedef int (*DeviceGetGpcClkVfOffset)(nvmlDevice_t,int*);

int main(int argc, char *argv[])
{
    QLibrary nvmlLib("libnvidia-ml.so.1");
        
    Init nvmlInit = (Init)nvmlLib.resolve("nvmlInit_v2");
    GetDeviceCount nvmlGetDeviceCount = (GetDeviceCount)nvmlLib.resolve("nvmlDeviceGetCount_v2");
    DeviceGetHandleByIndex nvmlDeviceGetHandleByIndex = (DeviceGetHandleByIndex)nvmlLib.resolve("nvmlDeviceGetHandleByIndex_v2");
    DeviceGetName nvmlDeviceGetName = (DeviceGetName)nvmlLib.resolve("nvmlDeviceGetName");
    DeviceGetTemperature nvmlDeviceGetTemperature = (DeviceGetTemperature)nvmlLib.resolve("nvmlDeviceGetTemperature");
    DeviceGetPowerUsage nvmlDeviceGetPowerUsage = (DeviceGetPowerUsage)nvmlLib.resolve("nvmlDeviceGetPowerUsage");
    DeviceGetNumFans nvmlDeviceGetNumFans = (DeviceGetNumFans)nvmlLib.resolve("nvmlDeviceGetNumFans");
    DeviceGetFanSpeed nvmlDeviceGetFanSpeed = (DeviceGetFanSpeed)nvmlLib.resolve("nvmlDeviceGetFanSpeed_v2");
    DeviceSetFanSpeed nvmlDeviceSetFanSpeed = (DeviceSetFanSpeed)nvmlLib.resolve("nvmlDeviceSetFanSpeed_v2");
    DeviceSetFanControlPolicy nvmlDeviceSetFanControlPolicy = (DeviceSetFanControlPolicy)nvmlLib.resolve("nvmlDeviceSetFanControlPolicy");
    DeviceGetNumGpuCores nvlmDeviceGetNumGpuCores = (DeviceGetNumGpuCores)nvmlLib.resolve("nvmlDeviceGetNumGpuCores");
    DeviceGetClock nvmlDeviceGetClock = (DeviceGetClock)nvmlLib.resolve("nvmlDeviceGetClock");
    DeviceGetBrand nvlmDeviceGetBrand = (DeviceGetBrand)nvmlLib.resolve("nvmlDeviceGetBrand");
    DeviceGetCurrPcieLinkGeneration nvmlDeviceGetCurrPcieLinkGeneration = (DeviceGetCurrPcieLinkGeneration)nvmlLib.resolve("nvmlDeviceGetCurrPcieLinkGeneration");
    DeviceGetCurrPcieLinkWidth nvmlDeviceGetCurrPcieLinkWidth = (DeviceGetCurrPcieLinkWidth)nvmlLib.resolve("nvmlDeviceGetCurrPcieLinkWidth");
    DeviceGetGpuMaxPcieLinkGeneration nvmlDeviceGetGpuMaxPcieLinkGeneration = (DeviceGetGpuMaxPcieLinkGeneration)nvmlLib.resolve("nvmlDeviceGetGpuMaxPcieLinkGeneration");
    DeviceGetMemoryInfo nvmlDeviceGetMemoryInfo = (DeviceGetMemoryInfo)nvmlLib.resolve("nvmlDeviceGetMemoryInfo");
    DeviceGetGpcClkMinMaxVfOffset nvmlDeviceGetGpcClkMinMaxVfOffset = (DeviceGetGpcClkMinMaxVfOffset)nvmlLib.resolve("nvmlDeviceGetGpcClkMinMaxVfOffset");
    DeviceGetMemClkMinMaxVfOffset nvmlDeviceGetMemClkMinMaxVfOffset = (DeviceGetMemClkMinMaxVfOffset)nvmlLib.resolve("nvmlDeviceGetMemClkMinMaxVfOffset");
    DeviceGetPowerManagementLimit nvmlDeviceGetPowerManagementLimit = (DeviceGetPowerManagementLimit)nvmlLib.resolve("nvmlDeviceGetPowerManagementLimit");
    DeviceGetMemClkVfOffset nvmlDeviceGetMemClkVfOffset = (DeviceGetMemClkVfOffset)nvmlLib.resolve("nvmlDeviceGetMemClkVfOffset");
    DeviceGetGpcClkVfOffset nvmlDeviceGetGpcClkVfOffset = (DeviceGetGpcClkVfOffset)nvmlLib.resolve("nvmlDeviceGetGpcClkVfOffset");
    
    nvmlInit();
        
    unsigned int cardCount;
    nvmlGetDeviceCount(&cardCount);
    qDebug(QString::asprintf("Card Count: %u",cardCount).toStdString().c_str());
        
    for (unsigned int i=0;i<cardCount;i++)
    {
        nvmlDevice_t card;
        nvmlDeviceGetHandleByIndex(i,&card);
        char cardName[NVML_DEVICE_NAME_BUFFER_SIZE];
        nvmlDeviceGetName(card, cardName, NVML_DEVICE_NAME_BUFFER_SIZE);
        qDebug(QString::asprintf("Card %u name: %s",i,cardName).toStdString().c_str());
        nvmlBrandType_t brd;
        nvlmDeviceGetBrand(card,brd);
        qDebug(QString::asprintf("Card %u is of kind %s (%u)",i,X::brand[brd],brd).toStdString().c_str());
        nvmlMemory_t *meminfo = new nvmlMemory_t;
        nvmlDeviceGetMemoryInfo(card,meminfo);
        qDebug(QString::asprintf("Card %u has %u GB memory (%u MB used, %u MB free)",i,meminfo->total/1024/1024/1024,meminfo->used/1024/1024,meminfo->free/1024/1024).toStdString().c_str());
        unsigned int pcigen,pcimaxgen,pciwidth;
        nvmlDeviceGetCurrPcieLinkGeneration(card,&pcigen);
        nvmlDeviceGetCurrPcieLinkWidth(card,&pciwidth);
        nvmlDeviceGetGpuMaxPcieLinkGeneration(card,&pcimaxgen);
        qDebug(QString::asprintf("Card %u is operating on PCIe Gen%u (Max Gen%u) %u lines width",i,pcigen,pcimaxgen,pciwidth).toStdString().c_str());
        unsigned int coreNb;
        nvlmDeviceGetNumGpuCores(card, &coreNb);
        qDebug(QString::asprintf("Card %u has %u CUDA cores",i,coreNb).toStdString().c_str());
        unsigned int temp;
        nvmlDeviceGetTemperature(card,NVML_TEMPERATURE_GPU,&temp);
        qDebug(QString::asprintf("Card %u die temperature: %u°C",i,temp).toStdString().c_str());
        unsigned int power;
        nvmlDeviceGetPowerUsage(card,&power);
        float wpower = float(power)/1000.0f;
        qDebug(QString::asprintf("Card %u power usage: %.2f W (%u mW)",i,wpower,power).toStdString().c_str());
        unsigned int clockDie,clockRam;
        nvmlDeviceGetClock(card,NVML_CLOCK_GRAPHICS,NVML_CLOCK_ID_CURRENT,&clockDie);
        nvmlDeviceGetClock(card,NVML_CLOCK_MEM,NVML_CLOCK_ID_CURRENT,&clockRam);
        qDebug(QString::asprintf("Card %u die clock %u Mhz, RAM clock %u Mhz",i,clockDie,clockRam).toStdString().c_str());
        unsigned int numfans;
        nvmlDeviceGetNumFans(card,&numfans);
        qDebug(QString::asprintf("Card %u has %u fans",i,numfans).toStdString().c_str());
        for (unsigned int j=0;j<numfans;j++)
        {
            unsigned int fanspeed;
            nvmlDeviceGetFanSpeed(card,j,&fanspeed);
            qDebug(QString::asprintf("  Card %u fan %u speed: %u%",i,j,fanspeed).toStdString().c_str());
        }
        int memMin, memMax, gpcMin, gcpMax;
        nvmlDeviceGetMemClkMinMaxVfOffset(card,&memMin,&memMax);
        nvmlDeviceGetGpcClkMinMaxVfOffset(card,&gpcMin,&gcpMax);
        qDebug(QString::asprintf("Card %u clock allowed offsets:\n  RAM min %i, RAM max %i\n  GPC min %i, GPC max %i",i,memMin,memMax,gpcMin,gcpMax).toStdString().c_str());
        int offsetMem, offsetGPC;
        nvmlDeviceGetMemClkVfOffset(card,&offsetMem);
        nvmlDeviceGetGpcClkVfOffset(card,&offsetGPC);
        qDebug(QString::asprintf("Card %u current offset RAM %i, GPC %i",i,offsetMem,offsetGPC).toStdString().c_str());
        unsigned int plimit;
        nvmlDeviceGetPowerManagementLimit(card,&plimit);
        qDebug(QString::asprintf("Card %u power limit: %u W",i,plimit/1000).toStdString().c_str());
    }
}
