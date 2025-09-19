/**
 * @file syscall.c
 * @author Lu Yongping (Lucas@hiwonder.com)
 * @brief 标准库桩函数的重定向
 * @version 0.1
 * @date 2023-05-12
 *
 * @copyright Copyright (c) 2023
 *
 */


#include <stdio.h>
#include "usart.h"
//#include "SEGGER_RTT.h"  // Disabled SEGGER_RTT

// Disable semihosting for different compilers
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
    __asm(".global __use_no_semihosting");
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 5000000)
    #pragma import(__use_no_semihosting)
#elif defined(__GNUC__)
    // GNU GCC: Override system calls to disable semihosting
    extern void initialise_monitor_handles(void);
#else
    #warning "Unknown compiler - semihosting may not be properly disabled"
#endif


char *_sys_command_string(char *cmd, int len){
    return NULL;
}


void _sys_exit(int return_code) {
    while (1)
        ;
}

void ttywrch (int ch) {
}

int stdin_getchar (void)
{
    return 0;
}

int stderr_putchar (int ch)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 0xFFFF);
    //SEGGER_RTT_Write(0, &ch, 1);
    return ch;
}

int stdout_putchar (int ch)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 0xFFFF);
    //SEGGER_RTT_Write(0, &ch, 1);
    return (ch);
}

// Additional system calls for GNU GCC newlib
#ifdef __GNUC__
int _write(int file, char *ptr, int len)
{
    for (int i = 0; i < len; i++) {
        stdout_putchar(*ptr++);
    }
    return len;
}

int _read(int file, char *ptr, int len)
{
    return 0;
}

int _close(int file)
{
    return -1;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _fstat(int file, void *st)
{
    return 0;
}

int _isatty(int file)
{
    return 1;
}
#endif


