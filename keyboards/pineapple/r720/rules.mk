# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
CUSTOM_MATRIX = lite
CONSOLE_ENABLE = yes          # Console for debug
COMMAND_ENABLE = yes          # Commands for debug and configuration
# PICO_BARE_METAL = no          # Commands for debug and configuration
SRC += matrix.c


PS2_MOUSE_ENABLE = yes
PS2_ENABLE = yes
PS2_DRIVER = usart