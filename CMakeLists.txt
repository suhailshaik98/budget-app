cmake_minimum_required(VERSION 3.10)
project(BudgetWebApp)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

include_directories(
    ${PQXX_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include           # For your own headers
    ${CMAKE_SOURCE_DIR}/external/crow/include
    ${CMAKE_SOURCE_DIR}/external/asio/asio/include
)

link_directories(${PQXX_LIBRARY_DIRS})

add_executable(budget_app
    src/executable/main.cpp
    src/database/database_module.cpp      # Add the database_module.cpp here
    src/moneyflow/InitialAccountSetup.cpp
    src/moneyflow/Transaction_Manager.cpp
)

target_link_libraries(budget_app PRIVATE ${PQXX_LIBRARIES})
