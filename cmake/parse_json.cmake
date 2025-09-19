function(parse_json json_file json_key output_var)
    file(STRINGS ${json_file} json_content)

    foreach(line IN LISTS json_content)
        string(REGEX REPLACE "^[ \t\r\n]+" "" line ${line})
        string(REGEX REPLACE ",$" "" line ${line})

        if(line STREQUAL "")
            continue()
        endif()

        if(line MATCHES "\"([^\"]+)\":[ \t]*\"([^\"]+)\"")
            set(key ${CMAKE_MATCH_1})
            set(value ${CMAKE_MATCH_2})
            if(key STREQUAL ${json_key})
                set(result ${value})
                break()
            endif()
        endif()
    endforeach()

    set(${output_var} ${result} PARENT_SCOPE)
endfunction()
