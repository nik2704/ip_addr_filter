cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_address VERSION ${PROJECT_VERSION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

add_executable(ip_address_flt main.cpp)
add_library(ip_address IPaddress.cpp)
target_link_libraries(ip_address_flt PRIVATE ip_address)

set_target_properties(ip_address_flt ip_address PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_address
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_address_flt PRIVATE
    ip_address
)

if(WITH_BOOST_TEST)
    find_package(Boost REQUIRED COMPONENTS unit_test_framework)

    # Добавляем исполняемый файл для тестов
    add_executable(test_utils tests/test_utils.cpp)
    add_executable(test_ip_address tests/test_ip_address.cpp)
    add_executable(test_list tests/test_list.cpp)
    add_executable(test_ip_filter tests/test_ip_filter.cpp)

    # Линкуем Boost с исполняемым файлом
    target_link_libraries(test_utils Boost::unit_test_framework)
    target_link_libraries(test_ip_address PRIVATE Boost::unit_test_framework ip_address)
    target_link_libraries(test_list PRIVATE Boost::unit_test_framework ip_address)
    target_link_libraries(test_ip_filter PRIVATE Boost::unit_test_framework ip_address)

    # Устанавливаем параметры компилятора
    set_target_properties(test_utils PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(test_ip_address PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(test_list PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(test_ip_filter PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    target_include_directories(test_utils PRIVATE ${Boost_INCLUDE_DIRS})
    target_include_directories(test_ip_address PRIVATE ${Boost_INCLUDE_DIRS})
    target_include_directories(test_list PRIVATE ${Boost_INCLUDE_DIRS})
    target_include_directories(test_ip_filter PRIVATE ${Boost_INCLUDE_DIRS})

    # Регистрация теста в CTest
    enable_testing()
    add_test(NAME test_utils COMMAND test_utils)
    add_test(NAME test_ip_address COMMAND test_ip_address)
    add_test(NAME test_list COMMAND test_list)
    add_test(NAME test_ip_filter COMMAND test_list)
endif()

if (MSVC)
    target_compile_options(ip_address_flt PRIVATE
        /W4
    )
    target_compile_options(ip_address PRIVATE
        /W4
    )
    if(WITH_BOOST_TEST)
        target_compile_options(test_utils PRIVATE
            /W4
        )
        target_compile_options(test_ip_address PRIVATE
            /W4
        )
        target_compile_options(test_list PRIVATE
            /W4
        )
        target_compile_options(test_ip_filter PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(ip_address_flt PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_address PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_BOOST_TEST)
        target_compile_options(test_utils PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
        target_compile_options(test_ip_address PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
        target_compile_options(test_list PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
        target_compile_options(test_ip_filter PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    
    endif()
endif()

install(TARGETS ip_address_flt RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
