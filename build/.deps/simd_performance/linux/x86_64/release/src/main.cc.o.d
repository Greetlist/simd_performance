{
    values = {
        "/usr/bin//gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++17",
            "-msse",
            "-DNDEBUG"
        }
    },
    files = {
        "src/main.cc"
    },
    depfiles_gcc = "main.o: src/main.cc src/BaseCalculator.h src/SSECalculator.h\
"
}