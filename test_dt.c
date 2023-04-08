#include "devicetree.h"
#define DT_DRV_COMPAT uart_win32

#if DT_NUM_INST_STATUS_OKAY() > 0
#include <stdio.h>
#include <version.h>
#define DEVID 1

#define DEVICE_TEST_INIT(n) static int baudrate_ ## n = DT_INST_PROP(n, baudrate);

DT_INST_FOREACH_STATUS_OKAY(DEVICE_TEST_INIT)

int main()
{
    printf("Version: %s, Device num: %d\n", BUILD_VERSION, DT_NUM_INST_STATUS_OKAY());
    return 0;
}

#endif
