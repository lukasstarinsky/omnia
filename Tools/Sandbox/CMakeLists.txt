set(SOURCES
        Main.cpp
)

omnia_app(Sandbox
        SOURCES ${SOURCES}
        LIBS LibCore LibGraphics
)