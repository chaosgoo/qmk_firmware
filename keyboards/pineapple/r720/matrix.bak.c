#include <stdbool.h>
#include "matrix.h"
#include "quantum.h"
#include "stdlib.h"
#include "print.h"

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

#define OUTPUT_SHR 1
// #define OUTPUT_COLROWINFO 1
static const int row_values[8] = {ROW_B, ROW_A, ROW_C, ROW_D, ROW_E, ROW_F, ROW_G, ROW_H};
// 按照74hc165的pin顺序,映射出来的KSO顺序
static const uint16_t realIndex[16] = {1, 13, 5, 2, 7, 0, 3, 9, 15, 14, 12, 10, 4, 8, 6, 11};
static uint8_t        debouncing    = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint16_t read_rows(void);
static void     select_row(uint8_t col);
static void     unselect_row(uint8_t col);
static void     unselect_rows(void);
static uint16_t arrangeU16Binary(uint16_t data, const uint16_t array[]);

__attribute__((weak)) void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__((weak)) void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

inline uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

void matrix_init(void) {
    setPinOutput(ROW_A);
    setPinOutput(ROW_B);
    setPinOutput(ROW_C);
    setPinOutput(ROW_D);
    setPinOutput(ROW_E);
    setPinOutput(ROW_F);
    setPinOutput(ROW_G);
    setPinOutput(ROW_H);

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        writePinHigh(row_values[i]);
    }

    setPinOutput(SHR_LATCH);
    setPinOutput(SHR_CLOCK);
    setPinInput(SHR_DATA);
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i]            = 0;
        matrix_debouncing[i] = 0;
    }
    unselect_rows();
    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        unselect_rows();
        select_row(row);
        uint16_t rows = read_rows();
        if (rows != 0) {
            uprintf("row = %d,", row);
        }
        unselect_row(row);
        for (uint16_t col = 0; col < MATRIX_COLS; col++) {
            bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1 << col);
            bool curr_bit = rows & (1 << col);
            if (prev_bit != curr_bit) {
                matrix_debouncing[col] ^= ((matrix_row_t)1 << col);
                debouncing             = DEBOUNCE;
            }
        }
    }
    // _delay_ms(1000);
    if (debouncing) {
        if (--debouncing) {
            _delay_us(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }
    matrix_scan_quantum();
    return 1;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & ((matrix_row_t)1 << col));
}

inline matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
    uprint("\nr/c 0123456789ABCDEF\n");
}

uint8_t matrix_key_count(void) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop32(matrix[i]);
    }
    return count;
}

static uint16_t read_rows(void) {
    uint16_t _data = 0;
    writePinLow(SHR_LATCH);
    _delay_us(10);
    writePinHigh(SHR_LATCH);
    for (int i = 0; i < 16; i++) {
        writePinLow(SHR_CLOCK);
        _delay_us(10);
        _data <<= 1;
        int pinResult = !readPin(SHR_DATA);
        _data         = _data | pinResult;
        writePinHigh(SHR_CLOCK);
    }
    _data = arrangeU16Binary(_data, realIndex);
#if defined(OUTPUT_SHR)
    if (_data != 0) {
        for (int i = 0; i < 16; i++) {
            if (_data & (1 << i)) {
                uprintf("%d\n", i);
            }
        }
    }
#endif // OUTPUT_SHR
    return _data;
}

/**
 * @brief 选择指定Row
 * @param col 待选择的Row
 **/
static void select_row(uint8_t col) {
    writePinLow(row_values[col]);
    _delay_us(10);
}

/**
 * @brief 取消选择指定Row
 * @param col 待取消的Row
 **/
static void unselect_row(uint8_t col) {
    writePinHigh(row_values[col]);
    _delay_us(10);
}

/**
 * @brief 取消选择所有Row
 **/
static void unselect_rows(void) {
    for (int i = 0; i < 8; i++) {
        writePinHigh(row_values[i]);
    }
}

/**
 * @brief 由于我的74HC165的输出顺序和矩阵键盘的顺序对应.
 * 所以本函数进行重新排列,重新排列后的bit顺序和键盘IO序号对应
 **/
static uint16_t arrangeU16Binary(uint16_t data, const uint16_t array[]) {
    uint16_t arrange = 0;
    for (int i = 0; i < 16; i++) {
        uint16_t cBit = 1 << i;
        if ((data & cBit) != 0) {
            arrange |= (1 << array[i]);
        }
    }
    return arrange;
}


// 5,10->4,2
//