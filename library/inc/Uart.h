/*
 * Copyright 2013 OpenMote Technologies, S.L.
 */

/**
 *
 * @file       Uart.h
 * @author     Pere Tuset-Peiro (peretuset@openmote.com)
 * @version    v0.1
 * @date       May, 2014
 * @brief
 * @ingroup
 *
 */

#ifndef UART_H_
#define UART_H_

#include "interrupt.h"
#include "ioc.h"
#include "uart.h"
#include "sys_ctrl.h"

#include "hw_ioc.h"
#include "hw_ints.h"
#include "hw_types.h"
#include "hw_uart.h"

class Gpio;

typedef void (*callback_t)(void);

class Uart
{

friend class InterruptHandler;

public:
    Uart(uint32_t peripheral_, uint32_t base_, uint32_t clock_, uint32_t interrupt_, Gpio * rx_, uint32_t rx_ioc_, Gpio * tx_, uint32_t tx_ioc_);
    void enable(uint32_t baudrate_, uint32_t config_, uint32_t mode);
    void sleep(void);
    void wakeup(void);
    uint32_t getBase(void);
    void setRxCallback(callback_t callback_);
    void setTxCallback(callback_t callback_);
    uint8_t readByte(void);
    uint8_t readByte(uint8_t * buffer, uint8_t len);
    void writeByte(uint8_t byte);
    void writeByte(uint8_t * buffer, uint8_t len);
    void interruptEnable(void);
    void interruptDisable(void);
protected:
    void interruptHandler(void);
private:
    void interruptHandlerRx();
    void interruptHandlerTx();
private:
    uint32_t peripheral;
    uint32_t base;
    uint32_t clock;
    uint32_t interrupt;
    uint32_t baudrate;
    uint32_t config;
    uint32_t mode;
    Gpio * rx;
    Gpio * tx;
    callback_t rx_callback = nullptr;
    callback_t tx_callback = nullptr;
};

#endif /* UART_H_ */
