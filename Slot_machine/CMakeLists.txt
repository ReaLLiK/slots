# CMakeList.txt: проект CMake для Slot_machine; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Slot_machine "Slot_machine.cpp" "Slot_machine.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Slot_machine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
