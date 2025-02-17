#
# Arm SCP/MCP Software
# Copyright (c) 2021, Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

set(CMAKE_ASM_COMPILER
    clang-11
    CACHE FILEPATH "Path to the assembler.")
set(CMAKE_C_COMPILER
    clang-11
    CACHE FILEPATH "Path to the C compiler.")
set(CMAKE_CXX_COMPILER
    clang-11
    CACHE FILEPATH "Path to the C++ compiler.")

set(CMAKE_OBJCOPY
    llvm-objcopy-11
    CACHE FILEPATH "Path to objcopy tool.")