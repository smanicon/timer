cmake_minimum_required(VERSION 3.15)
project(tm1638_timer_project C ASM)

# Fichiers source
file(GLOB SOURCES "src/*.c")

add_executable(${PROJECT_NAME}.elf ${SOURCES})

target_compile_options(${PROJECT_NAME}.elf PRIVATE
  -mmcu=${MCU} -DF_CPU=${F_CPU} -O3 -Wall
)
target_link_options(${PROJECT_NAME}.elf PRIVATE
  -mmcu=${MCU} -O3
)


# Génère le .hex et .eep à la compilation
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
  COMMAND ${CMAKE_OBJCOPY} -O ihex -j .eeprom --change-section-lma .eeprom=0 ${PROJECT_NAME}.elf ${PROJECT_NAME}.eep
  COMMENT "Création des fichiers .hex et .eep"
)

# Cible pour flasher
add_custom_target(flash
  COMMAND ${AVRDUDE} -c usbasp -p m328p -U flash:w:${PROJECT_NAME}.hex:i
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${PROJECT_NAME}.elf
  COMMENT "Flash du microcontrôleur avec avrdude"
)
