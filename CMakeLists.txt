# ----------------------------------------
# BUILD BATCH FOR WINDOWS
# ----------------------------------------
cmake_minimum_required(VERSION "3.24.1")
project("FileCrypt")

# ----------------------------------------
# VARIABLES
# ----------------------------------------
file(GLOB_RECURSE SRC "src/*.cpp" "src/*.h")

# ----------------------------------------
# BUILD
# ----------------------------------------
add_executable("build" ${SRC})
