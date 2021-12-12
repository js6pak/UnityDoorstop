#include "../crt.h"

#define DEFINE_CALLS

#define CAT2(start, middle, end) start##middle##end
#define CAT(start, middle, end) CAT2(start, middle, end)
#define STR2(A) #A
#define STR(A) STR2(A)
#define HEADER2(A) A.h
#define HEADER(A) HEADER2(A)

#define IMPORT_LIB STR(HEADER(IMPORT_PREFIX))
#define LOADER_FUNC_NAME CAT(load_, IMPORT_PREFIX, _funcs)

#define DEF_CALL(retType, name, ...) typedef retType (*name##_t)(__VA_ARGS__);
#include IMPORT_LIB
#undef DEF_CALL

struct {
#define DEF_CALL(retType, name, ...) name##_t name;
#include IMPORT_LIB
#undef DEF_CALL
} IMPORT_PREFIX;

static inline void LOADER_FUNC_NAME(void *lib) {
#define DEF_CALL(retType, name, ...)                                           \
    IMPORT_PREFIX.name = (name##_t)dlsym(lib, STR(CAT(IMPORT_PREFIX, _, name)));
#include IMPORT_LIB
#undef DEF_CALL
}

#undef DEFINE_CALLS