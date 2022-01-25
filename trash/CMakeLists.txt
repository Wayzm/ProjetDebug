






Makefile better for this kind of project





###cmake_minimum_required(VERSION 3.10)

project("Debug")

set(CMAKE_CXX_STANDARD 17)


add_compile_options(
                    -Ofast
                    -mavx2
                    )


include_directories("include/")

###
add_library(Tools src/tools.c)


###
add_executable(Debug src/main.c)
