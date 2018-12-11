cmake_minimum_required(VERSION 3.13)

aux_source_directory (. DIR_SERIALPORT_SRCS)
aux_source_directory (../../qextserialport/src DIR_EXTSERIALPORT_SRCS)
add_library (serialport ${DIR_SERIALPORT_SRCS} ${DIR_EXTSERIALPORT_SRCS})