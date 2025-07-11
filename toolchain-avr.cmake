# avr-toolchain.cmake
# Toolchain pour programmer un ATmega328P avec avr-gcc

# Microcontrôleur cible
set(MCU "atmega328p" CACHE STRING "AVR MCU")
set(F_CPU "16000000UL" CACHE STRING "CPU frequency")

# Spécifie que nous croisons
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

# Chemins des outils AVR
find_program(AVR_CC avr-gcc)
find_program(AVR_CXX avr-g++)
find_program(AVR_OBJCOPY avr-objcopy)
find_program(AVR_SIZE_TOOL avr-size)
find_program(AVRDUDE avrdude)

# Définit les outils utilisés
set(CMAKE_C_COMPILER ${AVR_CC})
set(CMAKE_CXX_COMPILER ${AVR_CXX})
set(CMAKE_OBJCOPY ${AVR_OBJCOPY})
set(CMAKE_SIZE ${AVR_SIZE_TOOL})

# Flags de compilation
set(CMAKE_C_FLAGS_INIT "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-mmcu=${MCU}")


# Pas de standard C++ requis ici
set(CMAKE_C_STANDARD 99)
