cmake_minimum_required(VERSION 3.15)
project(GMM_Model)

# Find GSL
find_package(GSL REQUIRED)

# Define the executable and all source files
add_executable(mosquito_sim
    src/Mosquito_Stage_2.cpp 
    src/add_mosqs_function.cpp 
    src/read_variables_from_csv.cpp
)

# TELL CMAKE ABOUT THE INCLUDE FOLDER
target_include_directories(mosquito_sim PRIVATE include)

# Link GSL
target_link_libraries(mosquito_sim PRIVATE GSL::gsl)