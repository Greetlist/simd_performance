{
    depfiles_gcc = "AVXCalculator.o: src/AVXCalculator.cc\
",
    files = {
        "src/AVXCalculator.cc"
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