cmake_minimum_required(VERSION 3.13)

#add_compile_definitions(QESP_NO_UDEV)
#add_compile_definitions(__linux__)
aux_source_directory (. DIR_SERIALPORT_SRCS)
aux_source_directory (../../qextserialport/src DIR_EXTSERIALPORT_SRCS)
add_library (serialport ${DIR_SERIALPORT_SRCS} ${DIR_EXTSERIALPORT_SRCS})
