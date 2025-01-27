{
    files = {
        "src/main.cc"
    },
    values = {
        "/usr/bin//gcc",
        {
            "-m64",
            "-g",
            "-O0",
            "-std=c++17",
            "-msse"
        }
    },
    depfiles_gcc = "main.o: src/main.cc src/BaseCalculator.h src/SSECalculator.h\
"
}