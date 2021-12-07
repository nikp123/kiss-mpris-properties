add_executable(demo main.c)

target_link_libraries(demo      PRIVATE kiss-mpris)
target_include_directories(demo PRIVATE ../src/)

