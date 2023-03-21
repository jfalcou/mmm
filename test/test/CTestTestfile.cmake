# CMake generated Testfile for 
# Source directory: /home/gravil/workspace/TER/mmm/test
# Build directory: /home/gravil/workspace/TER/mmm/test/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unit.system.context.exe "/usr/bin/mpiexec" "-n" "4" "/home/gravil/workspace/TER/mmm/test/unit/unit.system.context.exe")
set_tests_properties(unit.system.context.exe PROPERTIES  WORKING_DIRECTORY "/home/gravil/workspace/TER/mmm/test/unit" _BACKTRACE_TRIPLES "/home/gravil/workspace/TER/mmm/cmake/make_unit.cmake;59;add_test;/home/gravil/workspace/TER/mmm/cmake/make_unit.cmake;76;setup_location;/home/gravil/workspace/TER/mmm/cmake/make_unit.cmake;86;make_unit;/home/gravil/workspace/TER/mmm/test/CMakeLists.txt;9;glob_unit;/home/gravil/workspace/TER/mmm/test/CMakeLists.txt;0;")
add_test(unit.system.datatype.exe "/usr/bin/mpiexec" "-n" "4" "/home/gravil/workspace/TER/mmm/test/unit/unit.system.datatype.exe")
set_tests_properties(unit.system.datatype.exe PROPERTIES  WORKING_DIRECTORY "/home/gravil/workspace/TER/mmm/test/unit" _BACKTRACE_TRIPLES "/home/gravil/workspace/TER/mmm/cmake/make_unit.cmake;59;add_test;/home/gravil/workspace/TER/mmm/cmake/make_unit.cmake;76;setup_location;/home/gravil/workspace/TER/mmm/cmake/make_unit.cmake;86;make_unit;/home/gravil/workspace/TER/mmm/test/CMakeLists.txt;9;glob_unit;/home/gravil/workspace/TER/mmm/test/CMakeLists.txt;0;")
add_test(unit.entity.distribuable_sequence.exe "/usr/bin/mpiexec" "-n" "4" "/home/gravil/workspace/TER/mmm/test/unit/unit.entity.distribuable_sequence.exe")
set_tests_properties(unit.entity.distribuable_sequence.exe PROPERTIES  WORKING_DIRECTORY "/home/gravil/workspace/TER/mmm/test/unit" _BACKTRACE_TRIPLES "/home/gravil/workspace/TER/mmm/cmake/make_unit.cmake;59;add_test;/home/gravil/workspace/TER/mmm/cmake/make_unit.cmake;76;setup_location;/home/gravil/workspace/TER/mmm/cmake/make_unit.cmake;86;make_unit;/home/gravil/workspace/TER/mmm/test/CMakeLists.txt;10;glob_unit;/home/gravil/workspace/TER/mmm/test/CMakeLists.txt;0;")
