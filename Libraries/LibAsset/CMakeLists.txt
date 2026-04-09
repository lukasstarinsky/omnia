set(SOURCES
        ImportManager.cpp
        ModelImporter.cpp
        TextureImporter.cpp
)

omnia_lib(LibAsset
        SOURCES ${SOURCES}
)
