// Copyright (c) 2025 Soviet-Cat
// See LICENSE.md for details

#ifdef WINDOWS
    #ifdef EXPORTS
        #define KRATOS __declspec(dllexport)
    #else
        #define KRATOS __declspec(dllimport)
    #endif
#else
    #define KRATOS
#endif