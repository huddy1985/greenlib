SET(EXECUTABLE "greensocket_simple_b_transport_hierarchy_bind")

add_executable(${EXECUTABLE} simple_b_transport_top.cpp
  ../simple_b_transport/simple_b_gs_master.cpp
  ../common/simple_b_gs_secure_slave.cpp
  ../common/simple_b_gs_slave.cpp
  ../common/simple_b_gs_secure_adapter.cpp
)

target_link_libraries(${EXECUTABLE} ${SystemC_LIBRARIES} pthread)

add_dependencies(compile_test ${EXECUTABLE})

add_test(NAME COMPILATION:_${EXECUTABLE}
         COMMAND  sh -c "./${EXECUTABLE} > executable_output.txt")
add_test(NAME TEMPLATE:_${EXECUTABLE}
         COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/test.cmake)
add_test_compare(DIFF:_${EXECUTABLE}
	executable_output.template ${CMAKE_CURRENT_SOURCE_DIR}/expected_output.template)
