#cmake_minimum_required(VERSION 3.13)

aux_source_directory (. DIR_STARTUP_SRCS)
add_library (startup ${DIR_STARTUP_SRCS})