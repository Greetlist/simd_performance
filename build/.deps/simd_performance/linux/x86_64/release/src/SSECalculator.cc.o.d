{
    depfiles_gcc = "SSECalculator.o: src/SSECalculator.cc\
",
    files = {
        "src/SSECalculator.cc"
    },
    values = {
        "/usr/bin//gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++17",
            "-DNDEBUG"
        }
    }
}