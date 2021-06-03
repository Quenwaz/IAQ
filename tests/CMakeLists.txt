
function(iaq_test test_name)
    set(TEST_EXECUTABLE run_${test_name})
    set(TEST_SOURCE ${test_name}.cpp)

    add_executable(${TEST_EXECUTABLE} ${TEST_SOURCE})
    target_include_directories(${TEST_EXECUTABLE} PRIVATE ${CURL_INCLUDE_DIRS})
    # CMake 3.20 and upstream GTest define GTest::gtest, older versions define GTest::GTest
    if (TARGET GTest::gtest)
        target_link_libraries(${TEST_EXECUTABLE} GTest::gtest GTest::gtest_main ${PROJECT_NAME}_static)
    else ()
        target_link_libraries(${TEST_EXECUTABLE} GTest::GTest GTest::Main ${PROJECT_NAME}_static)
    endif ()
    add_test(${test_name} ${TEST_EXECUTABLE})
endfunction()


iaq_test(str2float_test)