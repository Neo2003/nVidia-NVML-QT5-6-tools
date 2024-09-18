#include <QLibrary>
#include "include/nvml.h"

struct X {
   static const char* brand[];
};
const char* X::brand[] = {"UNKNOWN","QUADRO","TESLA","NVS","GRID","GEFORCE","TITAN","NVIDIA_VAPPS","NVIDIA_VPC","NVIDIA_VCS","NVIDIA_VWS","NVIDIA_CLOUD_GAMING","QUADRO_RTX","NVIDIA_RTX","NVIDIA","GEFORCE_RTX","TITAN_RTX"};

typedef nvmlReturn_t (*Init_v2)();
typedef nvmlReturn_t (*Shutdown)();
typedef nvmlReturn_t (*GetDeviceCount)(unsigned int*);
typedef nvmlReturn_t (*DeviceGetHandleByIndex)(unsigned int, nvmlDevice_t*);
typedef nvmlReturn_t (*DeviceGetName)(nvmlDevice_t,char*,int);
typedef nvmlReturn_t (*DeviceGetTemperature)(nvmlDevice_t,nvmlTemperatureSensors_t,unsigned int*);
typedef nvmlReturn_t (*DeviceGetPowerUsage)(nvmlDevice_t,unsigned int*);
typedef nvmlReturn_t (*DeviceGetNumFans)(nvmlDevice_t,unsigned int*);
typedef nvmlReturn_t (*DeviceGetFanSpeed)(nvmlDevice_t,unsigned int,unsigned int*);
typedef nvmlReturn_t (*DeviceSetFanControlPolicy)(nvmlDevice_t,unsigned int,nvmlFanControlPolicy_t);
typedef nvmlReturn_t (*DeviceSetFanSpeed)(nvmlDevice_t,unsigned int,unsigned int);
typedef nvmlReturn_t (*DeviceGetNumGpuCores)(nvmlDevice_t,unsigned int*);
typedef nvmlReturn_t (*DeviceGetClock)(nvmlDevice_t,nvmlClockType_t,nvmlClockId_t,unsigned int*);
typedef nvmlReturn_t (*DeviceGetBrand)(nvmlDevice_t,nvmlBrandType_t);
typedef nvmlReturn_t (*DeviceGetCurrPcieLinkGeneration)(nvmlDevice_t,unsigned int*);
typedef nvmlReturn_t (*DeviceGetCurrPcieLinkWidth)(nvmlDevice_t,unsigned int*);
typedef nvmlReturn_t (*DeviceGetGpuMaxPcieLinkGeneration)(nvmlDevice_t,unsigned int*);
typedef nvmlReturn_t (*DeviceGetMemoryInfo)(nvmlDevice_t,nvmlMemory_t*);
typedef nvmlReturn_t (*DeviceGetGpcClkMinMaxVfOffset)(nvmlDevice_t,int*,int*);
typedef nvmlReturn_t (*DeviceGetMemClkMinMaxVfOffset)(nvmlDevice_t,int*,int*);
typedef nvmlReturn_t (*DeviceGetPowerManagementLimit)(nvmlDevice_t,unsigned int*);
typedef nvmlReturn_t (*DeviceGetMemClkVfOffset)(nvmlDevice_t,int*);
typedef nvmlReturn_t (*DeviceGetGpcClkVfOffset)(nvmlDevice_t,int*);
typedef nvmlReturn_t (*SystemGetDriverVersion)(char*,unsigned int);
typedef nvmlReturn_t (*SystemGetNVMLVersion)(char*,unsigned int);
typedef nvmlReturn_t (*DeviceGetEncoderCapacity)(nvmlDevice_t,nvmlEncoderType_t,unsigned int*);

int main(int argc, char *argv[])
{
    QLibrary nvmlLib("libnvidia-ml.so.1");
        
    Init_v2 nvmlInit_v2 = (Init_v2)nvmlLib.resolve("nvmlInit_v2");
    Shutdown nvmlShutdown = (Shutdown)nvmlLib.resolve("nvmlShutdown");
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
    SystemGetDriverVersion nvmlSystemGetDriverVersion = (SystemGetDriverVersion)nvmlLib.resolve("nvmlSystemGetDriverVersion");
    SystemGetNVMLVersion nvmlSystemGetNVMLVersion = (SystemGetNVMLVersion)nvmlLib.resolve("nvmlSystemGetNVMLVersion");
    DeviceGetEncoderCapacity nvmlDeviceGetEncoderCapacity = (DeviceGetEncoderCapacity)nvmlLib.resolve("nvmlDeviceGetEncoderCapacity");

    nvmlInit_v2();

    char driverVersion[NVML_SYSTEM_DRIVER_VERSION_BUFFER_SIZE];
    nvmlSystemGetDriverVersion(driverVersion, NVML_SYSTEM_DRIVER_VERSION_BUFFER_SIZE);
    qDebug(QString::asprintf("Driver version: %s",driverVersion).toStdString().c_str());
    char nvmlVersion[NVML_SYSTEM_NVML_VERSION_BUFFER_SIZE];
    nvmlSystemGetNVMLVersion(nvmlVersion,NVML_SYSTEM_NVML_VERSION_BUFFER_SIZE);
    qDebug(QString::asprintf("NVML version: %s",nvmlVersion).toStdString().c_str());
    
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
        qDebug(QString::asprintf("Card %u has %llu GB memory (%llu MB used, %llu MB free)",i,meminfo->total/1024/1024/1024,meminfo->used/1024/1024,meminfo->free/1024/1024).toStdString().c_str());
        unsigned int pcigen,pcimaxgen,pciwidth;
        nvmlDeviceGetCurrPcieLinkGeneration(card,&pcigen);
        nvmlDeviceGetCurrPcieLinkWidth(card,&pciwidth);
        nvmlDeviceGetGpuMaxPcieLinkGeneration(card,&pcimaxgen);
        qDebug(QString::asprintf("Card %u is operating on PCIe Gen%u (Max Gen%u) %u lines width",i,pcigen,pcimaxgen,pciwidth).toStdString().c_str());
        unsigned int coreNb;
        nvlmDeviceGetNumGpuCores(card, &coreNb);
        qDebug(QString::asprintf("Card %u has %u CUDA cores",i,coreNb).toStdString().c_str());
        unsigned int encoderCapacityH264, encoderCapacityHEVC, encoderCapacityAV1;
        nvmlDeviceGetEncoderCapacity(card, nvmlEncoderType_t::NVML_ENCODER_QUERY_H264, &encoderCapacityH264);
        nvmlDeviceGetEncoderCapacity(card, nvmlEncoderType_t::NVML_ENCODER_QUERY_HEVC, &encoderCapacityHEVC);
        nvmlDeviceGetEncoderCapacity(card, nvmlEncoderType_t::NVML_ENCODER_QUERY_AV1, &encoderCapacityAV1);
        encoderCapacityH264 = (encoderCapacityH264 > 100) ? 0 : encoderCapacityH264;
        encoderCapacityHEVC = (encoderCapacityHEVC > 100) ? 0 : encoderCapacityHEVC;
        encoderCapacityAV1 = (encoderCapacityAV1 > 100) ? 0 : encoderCapacityAV1;
        qDebug(QString::asprintf("Card %u encoder capacity\n  H264: %u%, HEVC: %u%, AV1: %u%",i,encoderCapacityH264,encoderCapacityHEVC,encoderCapacityAV1).toStdString().c_str());
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

        delete(meminfo);
    }

    nvmlShutdown();
    return(0);
}
