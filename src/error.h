#pragma once

#define ERROR_PROMPT "ERROR: "

#define ERROR_INVALID(what) ERROR_PROMPT "invalid " what
#define ERROR_ALLOC ERROR_PROMPT "failed memory allocation"
#define ERROR_ZERO_POINTER_FREE ERROR_PROMPT "trying to free a zeroed pointer"
