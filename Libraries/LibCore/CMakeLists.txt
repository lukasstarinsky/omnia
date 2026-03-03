set(SOURCES )

if(WIN32)
    list(APPEND SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/Win32Window.cpp
    )
endif()

omnia_lib(LibCore
        SOURCES ${SOURCES}
)
