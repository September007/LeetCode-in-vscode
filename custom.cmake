if(LEETCODE_PROBLEM_SOURCES STREQUAL "")
    set(LEETCODE_PROBLEM_SOURCES "${CMAKE_SOURCE_DIR}" CACHE STRING "")
endif()
message(STATUS "hardcode LEETCODE_PROBLEM_SOURCES:${LEETCODE_PROBLEM_SOURCES}")