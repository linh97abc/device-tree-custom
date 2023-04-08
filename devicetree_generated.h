#ifndef __DEVICETREE_GENERATED_H__
#define __DEVICETREE_GENERATED_H__

#define CONFIG_PIN1 1
#define CONFIG_PIN2 2
// Device uart_win32
#define DT_INST_0_uart_win32_P_devID UART_WIN32_0
#define DT_INST_0_uart_win32_P_compatible uart_win32
#define DT_INST_0_uart_win32_P_baudrate 115200
#define DT_INST_0_uart_win32_P_status okay

#define DT_INST_1_uart_win32_P_devID UART_WIN32_1
#define DT_INST_1_uart_win32_P_compatible uart_win32
#define DT_INST_1_uart_win32_P_baudrate 921600
#define DT_INST_1_uart_win32_P_status okay

#define DT_INST_uart_win32_NUM_INSTANCES 2

#define DT_FOREACH_OKAY_INST_uart_win32(fn) fn(0) fn(1)

// Device uart_mock
#define DT_INST_0_uart_mock_P_devID UART_MOCK_0
#define DT_INST_0_uart_mock_P_compatible uart_mock
#define DT_INST_0_uart_mock_P_baudrate 115200
#define DT_INST_0_uart_mock_P_status okay

#define DT_INST_uart_mock_NUM_INSTANCES 1

#define DT_FOREACH_OKAY_INST_uart_mock(fn) fn(0)

// Device gpio_mock
#define DT_INST_0_gpio_mock_P_devID GPIO_MOCK_0
#define DT_INST_0_gpio_mock_P_compatible gpio_mock
#define DT_INST_0_gpio_mock_P_pins CONFIG_PIN1 | \
CONFIG_PIN2
#define DT_INST_0_gpio_mock_P_status okay

#define DT_INST_gpio_mock_NUM_INSTANCES 1

#define DT_FOREACH_OKAY_INST_gpio_mock(fn) fn(0)

enum DeviceID_t {
    UART_WIN32_0,
    UART_WIN32_1,
    UART_MOCK_0,
    GPIO_MOCK_0
};

#endif
