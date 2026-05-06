set(SOURCES
        Input.cpp
)

set(THIRD_PARTY_LIBS)

if (WIN32)
    list(APPEND SOURCES
            Win32/UUIDWin32.cpp
            Win32/WindowWin32.cpp
    )
    list(APPEND THIRD_PARTY_LIBS Rpcrt4)
endif ()

omnia_lib(LibPlatform
        SOURCES ${SOURCES}
        THIRD_PARTY PRIVATE ${THIRD_PARTY_LIBS}
)
