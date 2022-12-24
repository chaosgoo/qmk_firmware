#include <stdbool.h>
#include "matrix.h"
#include "quantum.h"
#include "stdlib.h"
#include "print.h"

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

// #define OUTPUT_SHR 1
// #define OUTPUT_COLROWINFO 1
static const int row_values[8] = {ROW_B, ROW_A, ROW_C, ROW_D, ROW_E, ROW_F, ROW_G, ROW_H};
// 按照74hc165的pin顺序,映射出来的KSO顺序
static const uint16_t realIndex[16] = {1, 13, 5, 2, 7, 0, 3, 9, 15, 14, 12, 10, 4, 8, 6, 11};

static uint16_t read_rows(void);
static void     select_row(uint8_t col);
static void     unselect_row(uint8_t col);
static void     unselect_rows(void);
static uint16_t arrangeU16Binary(uint16_t data, const uint16_t array[]);

void matrix_init_custom(void) {
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
    unselect_rows();
    matrix_init_quantum();
}

bool matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    matrix_row_t current_row_value = 0;
    writePinLow(SHR_LATCH);
    select_row(current_row);
    matrix_output_select_delay();
    writePinHigh(SHR_LATCH);
    uint16_t read_result = read_rows();
    /* For each octet of columns... */
    // for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index += 8) {

    //     if (read_result >= 0) {
    //         /* only if SPI read successful: populate the matrix row with the
    //            state of the 8 consecutive column bits */
    //         current_row_value |= ((matrix_row_t)read_result << col_index);
    //     }
    // }
    current_row_value |= ((matrix_row_t)read_result);

    /* Unselect row & wait for all columns signals to go high. */
    unselect_row(current_row);
    matrix_output_unselect_delay(current_row, current_row_value != 0);

    /* Update row in matrix. */
    if (current_row_value != current_matrix[current_row]) {
        current_matrix[current_row] = current_row_value;
        return true;
    }

    return false;
}

bool matrix_scan_custom(matrix_row_t curr_matrix[]) {
    bool changed = false;

    /* set row, read cols */
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= matrix_read_cols_on_row(curr_matrix, current_row);
    }

    return changed;
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
    // _data = 0;
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