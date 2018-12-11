cmake_minimum_required(VERSION 3.13)

aux_source_directory (. DIR_KERNEL_SRCS)
add_library (kernel ${DIR_KERNEL_SRCS})
