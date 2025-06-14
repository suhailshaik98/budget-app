cmake_minimum_required(VERSION 3.10)
project(BudgetWebApp)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/crow/include
    ${CMAKE_SOURCE_DIR}/external/asio/asio/include
)          # For your own headers

add_executable(budget_app
    src/executable/main.cpp
    src/moneyflow/IncomeBaseline.cpp
)