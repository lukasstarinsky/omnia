add_library(LibGraphics INTERFACE)

target_include_directories(LibGraphics INTERFACE
        $<BUILD_INTERFACE:${OMNIA_SOURCE_DIR}/Libraries>
)
