#define SHR_LATCH 21
#define SHR_CLOCK 20
#define SHR_DATA 19


#define ROW_A 15
#define ROW_B 14
#define ROW_C 13
#define ROW_D 12
#define ROW_E 11
#define ROW_F 10
#define ROW_G 9
#define ROW_H 8

#define MATRIX_ROWS 8
#define MATRIX_COLS 16

#define SHR_COLS \
  { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 }

static uint8_t read_rows(void);
static void select_col(uint8_t col);
static void unselect_cols();

static void shift_pulse(void);
static void shift_out_single(uint8_t value);
static void shift_out(uint16_t value);
void print_b(void *pointer, size_t size);
static const uint16_t col_values[16] = SHR_COLS;


static uint8_t matrix[MATRIX_ROWS];
static uint8_t matrix_debouncing[MATRIX_ROWS];

int cols[8] = {
  15, 14, 13, 12, 11, 10, 9, 8
};
int rows[16] = {
  8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 26
};
int pins[24] = {
  8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 26, 27, 28, 2, 3, 4, 5, 6, 7
};
void resetRows(int status) {
  for (int r = 0; r < 8; r++) {
    digitalWrite(rows[r], status);
  }
}

void resetCols(int status) {
  for (int c = 0; c < 16; c++) {
    digitalWrite(cols[c], status);
  }
}

void scan() {
  for (int c = 0; c < 16; c++) {
    resetCols(HIGH);
    digitalWrite(cols[c], LOW);
    for (int r = 0; r < 8; r++) {
      if (digitalRead(rows[r]) == LOW) {
        Serial.print("Cols.Pin");
        Serial.print(cols[c]);
        Serial.print("\t Rows.Pin");
        Serial.print(rows[r]);
        Serial.print("\t\tCol ");
        Serial.print(c);
        Serial.print("\t Row ");
        Serial.print(r);
        Serial.println();
        digitalWrite(25, HIGH);
        delay(500);
        digitalWrite(25, LOW);
      }
    }
  }
}


void setup() {
  Serial.begin(115200);
  // for (int c = 0; c < 16; c++) {
  //   pinMode(cols[c], OUTPUT);
  // }
  for (int r = 0; r < 8; r++) {
    pinMode(rows[r], INPUT);
  }
  pinMode(25, OUTPUT);
  pinMode(SHR_DATA, OUTPUT);
  pinMode(SHR_LATCH, OUTPUT);
  pinMode(SHR_CLOCK, OUTPUT);
}

void matrixScan() {
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    select_col(col);

    Serial.print("Select Col.");
    Serial.print(col);
    Serial.print(" get ");
    uint8_t rows = read_rows();
    Serial.print(rows, BIN);
    Serial.println();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      bool prev_bit = matrix_debouncing[row] & (1 << col);
      bool curr_bit = rows & (1 << row);
      if (prev_bit != curr_bit) {
      }
    }
    // unselect_cols();
    delay(100);
  }
}


void loop() {
  matrixScan();
}

static inline void shift_pulse(void) {
  digitalWrite(SHR_CLOCK, HIGH);
  digitalWrite(SHR_CLOCK, LOW);
}

static void shift_out_single(uint8_t value) {
  for (uint8_t i = 0; i < 8; i++) {
    if (value & 0b10000000) {
      digitalWrite(SHR_DATA, HIGH);
    } else {
      digitalWrite(SHR_DATA, LOW);
    }

    shift_pulse();
    value = value << 1;
  }
}

static void shift_out(uint16_t value) {
  digitalWrite(SHR_LATCH, LOW);
  uint8_t first_byte = (value >> 8) & 0xFF;
  uint8_t second_byte = (uint8_t)(value & 0xFF);

  shift_out_single(first_byte);
  shift_out_single(second_byte);
  if (value != 0) {
    Serial.print("Shift Out:");
    Serial.print(first_byte, BIN);
    // print_b(&first_byte, sizeof(first_byte));
    Serial.print(" ");
    Serial.print(second_byte, BIN);
    // print_b(&second_byte, sizeof(second_byte));
    Serial.print(". ");
  }
  digitalWrite(SHR_LATCH, HIGH);
}


static void select_col(uint8_t col) {
  // SHIFT out columns 0 to 15

  shift_out(col_values[col]);
}

static void unselect_cols() {
  shift_out(0);
}


static uint8_t read_rows(void) {
  uint8_t rowsValue = (digitalRead(ROW_H) << 7) | (digitalRead(ROW_G) << 6) | (digitalRead(ROW_F) << 5) | (digitalRead(ROW_E) << 4) | (digitalRead(ROW_D) << 3) | (digitalRead(ROW_C) << 2) | (digitalRead(ROW_B) << 1) | (digitalRead(ROW_A));

  return rowsValue;
}

void print_b(void *pointer, size_t size) {
  unsigned long data = *((unsigned long *)pointer);
  int length = size * 8;
  int counter = 0;
  while (length-- > 0) {
    Serial.print((data >> length) & 0x1);
      counter++;
    if (counter % 8 == 0) {
      Serial.print(" ");
    }
  }
}