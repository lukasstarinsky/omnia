set(SOURCES
        Awaitable.cpp
        Scheduler.cpp
        ThreadPool.cpp
)

omnia_lib(LibConcurrency
        SOURCES ${SOURCES}
)
