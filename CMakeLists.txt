cmake_minimum_required(VERSION 3.10)
project(BudgetWebApp)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    include
    external/crow/include
    external/asio/asio/include
)          # For your own headers

add_executable(budget_app
    src/main.cpp
    src/IncomeBaseline.cpp
)