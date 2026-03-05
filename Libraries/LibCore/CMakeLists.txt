set(SOURCES
)

if (WIN32)
    list(APPEND SOURCES
            Win32Window.cpp
    )
endif ()

omnia_lib(LibCore
        SOURCES ${SOURCES}
)
