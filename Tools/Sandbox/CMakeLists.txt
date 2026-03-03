add_executable(Sandbox
        Main.cpp
)

target_link_libraries(Sandbox PRIVATE
        Common
        LibCore
)

add_dependencies(Sandbox
        LibCore
)