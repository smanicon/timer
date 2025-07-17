function(generate_main_test TARGET_NAME)
    # Obtenir les sources du target
    get_target_property(SRCS ${TARGET_NAME} SOURCES)

    if(NOT SRCS)
        message(FATAL_ERROR "Target ${TARGET_NAME} has no sources")
    endif()

    set(TEST_NAMES "")

    foreach(FILE ${SRCS})
      if(FILE MATCHES "\\.c$")
        file(READ ${FILE} CONTENTS)
        string(REPLACE "\n" ";" LINES "${CONTENTS}")

        foreach(LINE ${LINES})
          string(STRIP "${LINE}" LINE) 
          if(LINE MATCHES "^\\s*//" OR LINE MATCHES "^\\s*#define")
            continue()
          endif()

          string(REGEX MATCH "^[ \t]*TEST\\(([^)]+)\\)" MATCHED_LINE "${LINE}")
          if(MATCHED_LINE)
            string(REGEX REPLACE "^[ \t]*TEST\\(([^)]+)\\)" "\\1" TEST_NAME ${MATCHED_LINE})
            list(APPEND TEST_NAMES ${TEST_NAME})
          endif()
        endforeach()
      endif()
    endforeach()

    if(TEST_NAMES STREQUAL "")
        message(WARNING "No TEST(...) found in target ${TARGET_NAME}")
    endif()

    # Générer le fichier C
    set(GENERATED_FILE "${CMAKE_BINARY_DIR}/${TARGET_NAME}_generated_main.c")
    file(WRITE ${GENERATED_FILE} "#include \"unity.h\"\n\n")

    foreach(TEST_FN ${TEST_NAMES})
      file(APPEND ${GENERATED_FILE} "void ${TEST_FN}();\n")
    endforeach()

    file(APPEND ${GENERATED_FILE} "\n")
    file(APPEND ${GENERATED_FILE} "int main(void) {\n")
    file(APPEND ${GENERATED_FILE} "    UNITY_BEGIN();\n")

    foreach(TEST_FN ${TEST_NAMES})
      file(APPEND ${GENERATED_FILE} "    RUN_TEST(${TEST_FN});\n")
    endforeach()

    file(APPEND ${GENERATED_FILE} "    return UNITY_END();\n")
    file(APPEND ${GENERATED_FILE} "}\n")

    # Ajouter le fichier généré aux sources
    target_sources(${TARGET_NAME} PRIVATE ${GENERATED_FILE})
endfunction()
