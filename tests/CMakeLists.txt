
function(iaq_test test_name)
    set(TEST_EXECUTABLE run_${test_name})
    set(TEST_SOURCE ${test_name}.cpp)

    add_executable(${TEST_EXECUTABLE} ${TEST_SOURCE})
    target_include_directories(${TEST_EXECUTABLE} PRIVATE ${PROJECT_SOURCE_DIR}/include)
    # CMake 3.20 and upstream GTest define GTest::gtest, older versions define GTest::GTest
    if (TARGET GTest::gtest)
        target_link_libraries(${TEST_EXECUTABLE} GTest::gtest GTest::gtest_main ${PROJECT_NAME}_static)
    else ()
        target_link_libraries(${TEST_EXECUTABLE} GTest::GTest GTest::Main ${PROJECT_NAME}_static)
    endif ()
    # 由于gtest是由GCC5.1之前版本编译的， 而被测试的程序是由更高版本编译器编译， 
    # 所以如果需要LIBCXX_USE_CXX11_ABI=0来兼容旧版本libstdc++，否则LIBCXX_USE_CXX11_ABI=1则链接新版本libstdc++
    target_compile_definitions(${TEST_EXECUTABLE} PRIVATE _GLIBCXX_USE_CXX11_ABI=0)
    add_test(${test_name} ${TEST_EXECUTABLE})
endfunction()




macro(subdirlist result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*.cpp)
    set(dirlist "")
    foreach(child ${children})
        if(NOT IS_DIRECTORY ${curdir}/${child})
            STRING(REGEX REPLACE "(.*)\.cpp" "\\1" FILE_NAME ${child})
            list(APPEND dirlist ${FILE_NAME})
        endif()
    endforeach(child ${children})
    set(${result} ${dirlist})
endmacro(subdirlist result curdir)

subdirlist(tests ${CMAKE_CURRENT_SOURCE_DIR})
foreach(test ${tests})
    iaq_test(${test})
endforeach(test ${tests})
