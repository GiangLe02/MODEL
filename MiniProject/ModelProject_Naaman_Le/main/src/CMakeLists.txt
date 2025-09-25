# Nesrine Naaman & Nguyen Huong Giang LE

# Add an executable target
add_library(mylibrary main.c function.c inverse.c LU.c multiply_matrices.c)

target_include_directories(mylibrary PUBLIC ${PROJECT_SOURCE_DIR}/include)