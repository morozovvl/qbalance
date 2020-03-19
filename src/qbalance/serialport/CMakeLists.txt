set(PROJECTNAME serialport)
aux_source_directory (. DIR_SERIALPORT_SRCS)
aux_source_directory (../../qextserialport/src DIR_EXTSERIALPORT_SRCS)
add_library (${PROJECTNAME} ${DIR_SERIALPORT_SRCS} ${DIR_EXTSERIALPORT_SRCS})


