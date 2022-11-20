cmake_minimum_required(VERSION 3.10)

project(LeetCode)

include_directories(include)

aux_source_directory(. srcs)

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
    string(REGEX REPLACE "(\.\/)([0-9]+)(.*)" "\\2" name ${src} )
    add_executable(${name} ${src})
endforeach()
