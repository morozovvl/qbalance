cmake_minimum_required(VERSION 3.13)

aux_source_directory (. DIR_REPORT_SRCS)
add_library (report ${DIR_REPORT_SRCS})