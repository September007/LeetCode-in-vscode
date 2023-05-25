cmake_minimum_required(VERSION 3.15)

project(LeetCode)

# HardCode LEETCODE_PROBLEM_SOURCES
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/custom.cmake)
    include(${CMAKE_CURRENT_LIST_DIR}/custom.cmake)
endif()

option(ENABLE_REFER "生成 embeded/* 中的引用型的调试目标，其将包含提交文件" ON)
option(ENABLE_SAVE_TESTS "auto save tests file when corresponded problem source file is deleted,\
this will also enable auto loading tests instead of generate new when a old problem source file \
is showing again" ON)
option(LEETCODE_PROBLEM_SOURCES "LeetCode 插件指定的源文件的位置, vscode-setting: leetcode.workspaceFolder" "${CMAKE_CURRENT_LIST_DIR}")
set(TESTS_SAVE_DIR "${CMAKE_CURRENT_LIST_DIR}/history-tests")
set(REFER_TARGET_SUFFIX "-")
set(RTS ${REFER_TARGET_SUFFIX}) # short alias

# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
include_directories(include)

message(STATUS "LEETCODE_PROBLEM_SOURCES:${LEETCODE_PROBLEM_SOURCES}")
aux_source_directory("${LEETCODE_PROBLEM_SOURCES}" srcs)

add_compile_definitions(LOCAL)

add_subdirectory(extern/googletest EXCLUDE_FROM_ALL)

function(cxx_exe name src)
    add_executable(${name} ${src})
    target_link_libraries(${name} PRIVATE GTest::gtest)

    if(ENABLE_REFER)
        # src ./xxx.cpp PURE_PATH: xxx.cpp
        string(SUBSTRING ${src} 2 -1 PURE_PATH)
        set(CPP_SOURCE_FILE ${PURE_PATH})

        if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/embeded/${name}.cpp)
            if(ENABLE_SAVE_TESTS AND EXISTS ${TESTS_SAVE_DIR}/${name}.cpp)
                file(COPY ${TESTS_SAVE_DIR}/${name}.cpp DESTINATION ${CMAKE_CURRENT_LIST_DIR}/embeded)
                message("COPY ${TESTS_SAVE_DIR}/${name}.cpp DESTINATION ${CMAKE_CURRENT_LIST_DIR}/embeded")
            else()
                configure_file(${CMAKE_CURRENT_LIST_DIR}/embeded/template.cpp ${CMAKE_CURRENT_LIST_DIR}/embeded/${name}.cpp)
            endif()
        endif()

        add_executable(${name}${RTS} ${CMAKE_CURRENT_LIST_DIR}/embeded/${name}.cpp)
        target_link_libraries(${name}${RTS} PRIVATE GTest::gtest)
        target_compile_definitions(${name}${RTS} PRIVATE EMBEDED_TARGET)
    endif()
endfunction()

# the existing problem file will trigger adding targets
foreach(src ${srcs})
    # src is like   ./4.balahbalah.cpp

    # cmake does not allow chinesename target name?
    # string(LENGTH ${src} name_total_len)
    # math(EXPR name_len ${name_total_len}-6 )
    # string(SUBSTRING ${src} 2 ${name_len} name_raw)
    # string(REPLACE "." "_" name ${name_raw})

    # this work but too lonnnnnnnnnnnnnnnngy
    # string(LENGTH ${src} name_total_len)
    # string(SUBSTRING ${src} 2 -1 name)
    # string(FIND ${name} "." dot_position)
    # string(SUBSTRING ${name} 0 ${dot_position} name)

    # https://cmake.org/cmake/help/latest/command/string.html#regex-replace
    # split ${src} to 3 part  ---./  4  .balahbalah.cpp--- and only reserve the serial numeber
    get_filename_component(fileName "${src}" NAME)

    # message("src: ${src}")
    # message("name: ${fileName}")
    string(REGEX REPLACE "([0-9]+)(.*)" "\\1" name "${fileName}")
    cxx_exe(${name} ${src})
endforeach()

# the existing problem test file will trigger problem file checking
# once problem file is not founded, we will move the tests file to the TESTS_SAVE_DIR
if(ENABLE_SAVE_TESTS)
    aux_source_directory(embeded TESTS)
else()
    set(TESTS)
endif()

foreach(TEST ${TESTS})
    string(REGEX REPLACE "(embeded\/)([0-9]*)(.*)" "\\2" serial ${TEST})

    if(NOT "${serial}") # embeded/template.cpp
        continue()
    endif()

    # "" is parameter to fit the request of at least one input paramter of string-regex-match
    string(REGEX MATCH ".*\/${serial}\..*" thisMatch ${srcs} "")
    message("TEST:${TEST}|serial:${serial}")

    if("${thisMatch}" STREQUAL "")
        if(NOT IS_DIRECTORY "${TESTS_SAVE_DIR}")
            file(MAKE_DIRECTORY "${TESTS_SAVE_DIR}")
        endif()

        file(RENAME ${TEST} ${TESTS_SAVE_DIR}/${serial}.cpp)
        message("file(RENAME ${TEST} ${TESTS_SAVE_DIR}/${serial}.cpp)")
    endif()
endforeach()
