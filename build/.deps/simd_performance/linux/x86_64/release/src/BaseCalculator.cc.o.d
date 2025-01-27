{
    files = {
        "src/BaseCalculator.cc"
    },
    depfiles_gcc = "BaseCalculator.o: src/BaseCalculator.cc src/BaseCalculator.h\
",
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