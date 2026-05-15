set(SOURCES
        Scheduler.test.cpp
)

omnia_test(LibConcurrency
        SOURCES ${SOURCES}
        LIBS LibConcurrency
)