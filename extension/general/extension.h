#ifndef EXTENSION_H
#define EXTENSION_H

#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"

#if defined(_WIN32)
  #define WindowsDllExport(name) extern PGDLLEXPORT Datum name(PG_FUNCTION_ARGS);
#else
  #define WindowsDllExport(name)
#endif

#define PG_FUNC_0(NAME, RETURN_TYPE, PG_RETURN_TYPE) \
WindowsDllExport(pg_ ## NAME);\
PG_FUNCTION_INFO_V1(pg_ ## NAME);\
Datum pg_ ## NAME(PG_FUNCTION_ARGS) {\
    RETURN_TYPE result = NAME();\
    PG_RETURN_ ## PG_RETURN_TYPE(result);\
}

#define PG_FUNC_1(NAME, RETURN_TYPE, PG_RETURN_TYPE, ARG0_TYPE, PG_ARG0_TYPE) \
WindowsDllExport(pg_ ## NAME);\
PG_FUNCTION_INFO_V1(pg_ ## NAME); \
Datum pg_ ## NAME(PG_FUNCTION_ARGS) { \
    if(PG_ARGISNULL(0)){\
        PG_RETURN_NULL();\
    }\
    ARG0_TYPE arg0 = (ARG0_TYPE) PG_GETARG_ ## PG_ARG0_TYPE(0);\
    RETURN_TYPE result = NAME(arg0);\
    PG_RETURN_ ## PG_RETURN_TYPE(result);\
}

#define PG_FUNC_2(NAME, RETURN_TYPE, PG_RETURN_TYPE, ARG0_TYPE, PG_ARG0_TYPE, ARG1_TYPE, PG_ARG1_TYPE) \
WindowsDllExport(pg_ ## NAME);\
PG_FUNCTION_INFO_V1(pg_ ## NAME);\
Datum pg_ ## NAME(PG_FUNCTION_ARGS) {\
    if(PG_ARGISNULL(0) || PG_ARGISNULL(1)){\
        PG_RETURN_NULL();\
    }\
    ARG0_TYPE arg0 = (ARG0_TYPE) PG_GETARG_ ## PG_ARG0_TYPE(0);\
    ARG1_TYPE arg1 = (ARG1_TYPE) PG_GETARG_ ## PG_ARG1_TYPE(1);\
    RETURN_TYPE result = NAME(arg0, arg1);\
    PG_RETURN_ ## PG_RETURN_TYPE(result);\
}

#define PG_FUNC_2_POINTER(NAME, ARG0_TYPE, PG_ARG0_TYPE, ARG1_TYPE, PG_ARG1_TYPE) \
WindowsDllExport(pg_ ## NAME);\
PG_FUNCTION_INFO_V1(pg_ ## NAME);\
Datum pg_ ## NAME(PG_FUNCTION_ARGS) {\
    if(PG_ARGISNULL(0) || PG_ARGISNULL(1)){\
        PG_RETURN_NULL();\
    }\
    ARG0_TYPE arg0 = (ARG0_TYPE) PG_GETARG_ ## PG_ARG0_TYPE(0);\
    ARG1_TYPE arg1 = (ARG1_TYPE) PG_GETARG_ ## PG_ARG1_TYPE(1);\
    void* result = NAME(arg0, arg1);\
    if(result==NULL){\
        PG_RETURN_NULL();\
    }\
    PG_RETURN_POINTER(result);\
}

#define PG_FUNC_3(NAME, RETURN_TYPE, PG_RETURN_TYPE, ARG0_TYPE, PG_ARG0_TYPE, ARG1_TYPE, PG_ARG1_TYPE, ARG2_TYPE, PG_ARG2_TYPE) \
WindowsDllExport(pg_ ## NAME);\
PG_FUNCTION_INFO_V1(pg_ ## NAME);\
Datum pg_ ## NAME(PG_FUNCTION_ARGS) {\
    if(PG_ARGISNULL(0) || PG_ARGISNULL(1) || PG_ARGISNULL(2)){\
        PG_RETURN_NULL();\
    }\
    ARG0_TYPE arg0 = (ARG0_TYPE) PG_GETARG_ ## PG_ARG0_TYPE(0);\
    ARG1_TYPE arg1 = (ARG1_TYPE) PG_GETARG_ ## PG_ARG1_TYPE(1);\
    ARG2_TYPE arg2 = (ARG2_TYPE) PG_GETARG_ ## PG_ARG2_TYPE(2);\
    RETURN_TYPE result = NAME(arg0, arg1, arg2);\
    PG_RETURN_ ## PG_RETURN_TYPE(result);\
}

#define PG_TRAPEZOIDAL_FUNCTION(NAME) \
WindowsDllExport(pg_ ## NAME);\
PG_FUNCTION_INFO_V1(pg_##NAME);\
Datum pg_##NAME(PG_FUNCTION_ARGS) {\
    trapezoidal_function *f = NAME();\
    PG_RETURN_POINTER(f);\
}


#endif
