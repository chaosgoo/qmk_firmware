// Copyright 2022 chaosgoo (@chaosgoo)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define VENDOR_ID 0x626c  // rs
#define PRODUCT_ID 0x0062 // 100
#define DEVICE_VER 0x0001 // rev 1
// #define MANUFACTURER goo
// #define PRODUCT r720

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
#ifdef PS2_DRIVER_USART
#define PS2_CLOCK_PIN   D5
#define PS2_DATA_PIN    D2

/* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
/* set DDR of CLOCK as input to be slave */
#define PS2_USART_INIT() do {   \
    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
    UCSR1C = ((1 << UMSEL10) |  \
              (3 << UPM10)   |  \
              (0 << USBS1)   |  \
              (3 << UCSZ10)  |  \
              (0 << UCPOL1));   \
    UCSR1A = 0;                 \
    UBRR1H = 0;                 \
    UBRR1L = 0;                 \
} while (0)
#define PS2_USART_RX_INT_ON() do {  \
    UCSR1B = ((1 << RXCIE1) |       \
              (1 << RXEN1));        \
} while (0)
#define PS2_USART_RX_POLL_ON() do { \
    UCSR1B = (1 << RXEN1);          \
} while (0)
#define PS2_USART_OFF() do {    \
    UCSR1C = 0;                 \
    UCSR1B &= ~((1 << RXEN1) |  \
                (1 << TXEN1));  \
} while (0)
#define PS2_USART_RX_READY      (UCSR1A & (1<<RXC1))
#define PS2_USART_RX_DATA       UDR1
#define PS2_USART_ERROR         (UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1)))
#define PS2_USART_RX_VECT       USART1_RX_vect
#endif
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 16

#define DIODE_DIRECTION ROW2COL

#define DEBOUNCE 5

#define ROW_A F0
#define ROW_B D4
#define ROW_C F4
#define ROW_D F1
#define ROW_E F5
#define ROW_F F6
#define ROW_G D0
#define ROW_H D1

#define SHR_LATCH C6
#define SHR_CLOCK C7
#define SHR_DATA F7

#define LED_CAPS_LOCK_PIN B6
#define LED_NUM_LOCK_PIN B0

// #define ROW_A PD1
// #define ROW_B PD0
// #define ROW_C PD4
// #define ROW_D PC6
// #define ROW_E PD7
// #define ROW_F PE6
// #define ROW_G PB4
// #define ROW_H PB5

// #define SHR_LATCH PF5
// #define SHR_CLOCK PF4
// #define SHR_DATA PF6


#define SHR_ROWS { ROW_A, ROW_B, ROW_C, ROW_D, ROW_E, ROW_F, ROW_G, ROW_H }