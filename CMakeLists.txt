cmake_minimum_required(VERSION 3.8)
project(CodeCollection)

set(CMAKE_CXX_STANDARD 11)


include_directories(include/)

set(CODECOLLECTION_SOURCE
        include/codecollection/TwoState/TwoStateArray.hpp
        include/codecollection/TwoState/TwoState.hpp
        include/codecollection/TwoState/TwoStateCommon.hpp)


option(CODECOLLECTION_BUILD_TESTS "Determines whether to build tests." ON)

if (CODECOLLECTION_BUILD_TESTS)
    enable_testing()


#        Adding ccsource here enables some header only files to be parsed correctly by clion
    set(CODECOLLECTION_TEST_SOURCE
            ${CODECOLLECTION_SOURCE}
            test/TestBase.cpp test/TwoStateTest.cpp)


    if (NOT TARGET Catch)
        include(ExternalProject)
        set(GB_FETCH_EXTERNAL_CATCH
                URL https://github.com/philsquared/Catch/archive/master.zip)


        ExternalProject_Add(Catch-External
                PREFIX ${CMAKE_BINARY_DIR}/ext/Catch
                ${GB_FETCH_EXTERNAL_CATCH}
                CONFIGURE_COMMAND ""
                BUILD_COMMAND ""
                INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ext/Catch/src/Catch-External/single_include/catch.hpp
                ${CMAKE_BINARY_DIR}/ext/Catch/include/catch.hpp
                )

        add_library(Catch INTERFACE)
        add_dependencies(Catch Catch-External)
        target_include_directories(Catch INTERFACE ${CMAKE_BINARY_DIR}/ext/Catch/include/)
    endif ()

    add_executable(codecollection_test ${CODECOLLECTION_TEST_SOURCE})
    target_link_libraries(codecollection_test Catch)
endif ()
