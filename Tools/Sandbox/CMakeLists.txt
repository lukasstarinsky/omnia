set(SOURCES
        Main.cpp
)

omnia_app(Sandbox
        SOURCES ${SOURCES}
        LIBS LibUI LibRHI LibAsset LibRenderer
)
add_dependencies(Sandbox CopyResources)