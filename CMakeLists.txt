cmake_minimum_required(VERSION 3.0)

project(Koperasi C)

# Include directories for header files
include_directories(includes)

# Set source
set(
    AUTH
    src/auth/auth.data.c 
    src/auth/auth.service.c
)

set(
    ITEM
    src/item/item.data.c 
    src/item/item.service.c
)

# Add the executable
add_executable(migrator src/migrator/migrator.c src/helper/helper.c)
add_executable(main ${AUTH} ${ITEM} src/helper/helper.c src/main.c)

# Link header files to the executable
target_include_directories(migrator PUBLIC includes)
