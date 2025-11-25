cmake_minimum_required(VERSION 3.10)
project(dsa_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source subfolders
set(SUBDIRS arrays maps sets graphs trees)

foreach(subdir ${SUBDIRS})
    file(GLOB SOURCES "${subdir}/*.cpp")
    foreach(src ${SOURCES})
        get_filename_component(name ${src} NAME_WE)
        add_executable(${name} ${src})
        set_target_properties(${name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${subdir}"
        )
    endforeach()
endforeach()
