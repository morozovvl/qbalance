# ***************************************************************************
# Implemented using http://blog.inventic.eu/2012/08/qt-and-google-breakpad/
# as a the reference.
#
# Get Google Breakpad here: https://code.google.com/p/google-breakpad/
#
# The required breakpad sources have been copied into /src in order to make
# integration with the application smooth and easy.
#
# To use source from Google Breakpad SVN checkout instead, change src
# to path where it was checked out. 
#
# ***************************************************************************

HEADERS += crashhandler.h
SOURCES += crashhandler.cpp

INCLUDEPATH += ../../google-breakpad/

# Windows
win32:HEADERS += common/windows/string_utils-inl.h
win32:HEADERS += src/common/windows/guid_string.h
win32:HEADERS += src/client/windows/handler/exception_handler.h
win32:HEADERS += src/client/windows/common/ipc_protocol.h
win32:HEADERS += src/google_breakpad/common/minidump_format.h
win32:HEADERS += src/google_breakpad/common/breakpad_types.h
win32:HEADERS += src/client/windows/crash_generation/crash_generation_client.h
win32:HEADERS += src/common/scoped_ptr.h
win32:SOURCES += src/client/windows/handler/exception_handler.cc
win32:SOURCES += src/common/windows/string_utils.cc
win32:SOURCES += src/common/windows/guid_string.cc
win32:SOURCES += src/client/windows/crash_generation/crash_generation_client.cc

# Linux
unix:HEADERS += src/client/linux/minidump_writer/cpu_set.h
unix:HEADERS += src/client/linux/minidump_writer/proc_cpuinfo_reader.h
unix:HEADERS += src/client/linux/handler/exception_handler.h
unix:HEADERS += src/client/linux/crash_generation/crash_generation_client.h
unix:HEADERS += src/client/linux/handler/minidump_descriptor.h
unix:HEADERS += src/client/linux/minidump_writer/minidump_writer.h
unix:HEADERS += src/client/linux/minidump_writer/line_reader.h
unix:HEADERS += src/client/linux/minidump_writer/linux_dumper.h
unix:HEADERS += src/client/linux/minidump_writer/linux_ptrace_dumper.h
unix:HEADERS += src/client/linux/minidump_writer/directory_reader.h
unix:HEADERS += src/client/linux/log/log.h
unix:HEADERS += src/client/minidump_file_writer-inl.h
unix:HEADERS += src/client/minidump_file_writer.h
unix:HEADERS += src/common/linux/linux_libc_support.h
unix:HEADERS += src/common/linux/eintr_wrapper.h
unix:HEADERS += src/common/linux/ignore_ret.h
unix:HEADERS += src/common/linux/file_id.h
unix:HEADERS += src/common/linux/memory_mapped_file.h
unix:HEADERS += src/common/linux/safe_readlink.h
unix:HEADERS += src/common/linux/guid_creator.h
unix:HEADERS += src/common/linux/elfutils.h
unix:HEADERS += src/common/linux/elfutils-inl.h
unix:HEADERS += src/common/linux/elf_gnu_compat.h
unix:HEADERS += src/common/using_std_string.h
unix:HEADERS += src/common/memory.h
unix:HEADERS += src/common/basictypes.h
unix:HEADERS += src/common/memory_range.h
unix:HEADERS += src/common/string_conversion.h
unix:HEADERS += src/common/convert_UTF.h
unix:HEADERS += src/google_breakpad/common/minidump_format.h
unix:HEADERS += src/google_breakpad/common/minidump_size.h
unix:HEADERS += src/google_breakpad/common/breakpad_types.h
unix:HEADERS += src/common/scoped_ptr.h
unix:HEADERS += src/third_party/lss/linux_syscall_support.h
unix:SOURCES += src/client/linux/crash_generation/crash_generation_client.cc
unix:SOURCES += src/client/linux/handler/exception_handler.cc
unix:SOURCES += src/client/linux/handler/minidump_descriptor.cc
unix:SOURCES += src/client/linux/minidump_writer/minidump_writer.cc
unix:SOURCES += src/client/linux/minidump_writer/linux_dumper.cc
unix:SOURCES += src/client/linux/minidump_writer/linux_ptrace_dumper.cc
unix:SOURCES += src/client/linux/log/log.cc
unix:SOURCES += src/client/minidump_file_writer.cc
unix:SOURCES += src/common/linux/linux_libc_support.cc
unix:SOURCES += src/common/linux/file_id.cc
unix:SOURCES += src/common/linux/memory_mapped_file.cc
unix:SOURCES += src/common/linux/safe_readlink.cc
unix:SOURCES += src/common/linux/guid_creator.cc
unix:SOURCES += src/common/linux/elfutils.cc
unix:SOURCES += src/common/string_conversion.cc
unix:SOURCES += src/common/convert_UTF.c
#breakpad app need debug info inside binaries
unix:QMAKE_CXXFLAGS+=-g
