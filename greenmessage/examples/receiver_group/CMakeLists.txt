SET(EXECUTABLE "greenmessage_receiver_group")

add_executable(${EXECUTABLE} system.cpp
  sender.cpp
  receiver.cpp
)
target_link_libraries(${EXECUTABLE} ${SystemC_LIBRARIES} pthread)

add_dependencies(compile_test ${EXECUTABLE})

add_test(NAME COMPILATION:_${EXECUTABLE}
         COMMAND  sh -c "./${EXECUTABLE} > executable_output.txt")
add_test_compare(DIFF:_${EXECUTABLE}
	executable_output.txt ${CMAKE_CURRENT_SOURCE_DIR}/expected_output.txt)
