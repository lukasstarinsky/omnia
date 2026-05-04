set(SOURCES
        AssetManager.cpp
        AssetRegistry.cpp
        ModelImporter.cpp
        ShaderCompiler.cpp
        ShaderImporter.cpp
        TextureImporter.cpp
)

find_package(Stb REQUIRED)
find_package(unofficial-shaderc CONFIG REQUIRED)
set(THIRD_PARTY_LIBS unofficial::shaderc::shaderc)

omnia_lib(LibAsset
        SOURCES ${SOURCES}
        LIBS LibCore
        THIRD_PARTY ${THIRD_PARTY_LIBS}
        INCLUDE_DIRS PRIVATE ${Stb_INCLUDE_DIR}
)