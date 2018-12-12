add_contract(contactbook contactbook ${CMAKE_CURRENT_SOURCE_DIR}/src/contactbook.cpp)
target_include_directories(contactbook.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(contactbook.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
