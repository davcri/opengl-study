add_library(Math math.cpp)
target_include_directories(
    Math INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS Math DESTINATION lib)
install(FILES math.h DESTINATION include)