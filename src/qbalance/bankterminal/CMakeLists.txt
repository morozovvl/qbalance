cmake_minimum_required (VERSION 2.6)
set (PROJECTNAME bankterminal)

project (${PROJECTNAME})

find_package (Qt4 REQUIRED)
set (SOURCE_ROOT ./)
aux_source_directory (${SOURCE_ROOT} SOURCES)

# Указываем пути, где искать заголовочники, дополнительно к стандартным путям.
#include_directories( "/my/addition/path/to/headers" "${SOURCE_ROOT}" )

# Устанавливаем путь, куда будет скопирован исполняемый файл при выполнении
# команды 'make install'.
#set( INSTALL_PATH /usr/local/bin/ )

# Указываем пути, где искать сторонние динамически библиотеки. Эти пути будут
# просмотрены в дополнение к умолчальными системным путям.
#link_directories( "/my/addition/path/to/lib" )

# Перечисляем необходимые сторонние динамические библиотеки и сохраняем
# их список в переменной REQUIRED_LIBRARIES.
# Поиск этих библиотек будет произведён как по стандартным системным путям, 
# так и по указанным выше (с помощью функции link_directories).
#set( REQUIRED_LIBRARIES
#		my_addition_lib
#		boost_thread 
#		boost_system )

# Устанавливаем флаги компилятора (причём никаких скрытых флагов, только эти).
#set( CMAKE_CXX_FLAGS "-O0 -Wall -pedantic -std=c++0x" ) 

# Собираем исполняемый файл с именем my_program.
#set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)
#set(LIBRARY_OUTPUT_PATH ${dir} )
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/plugins)
add_library (${PROJECTNAME} MODULE ${SOURCES})

# Компонуем собранную программу с необходимыми динамическими библиотеками.
#target_link_libraries( ${BIN} ${REQUIRED_LIBRARIES} )

# Установка. Это действие будет активировано при выполнении команды 'make install'.
#install
#( TARGETS ${BIN} DESTINATION ${INSTALL_PATH} )
