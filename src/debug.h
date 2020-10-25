#pragma once

#include "chunk.h"
#include "common.h"

void debug_disassemble_chunk(Chunk const* chunk, char const* name);
size_t debug_disassemble_instruction(Chunk const* chunk, size_t offset);
