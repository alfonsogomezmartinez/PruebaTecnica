# CMake generated Testfile for 
# Source directory: /home/alfonso/Escritorio/PruebaTecnica
# Build directory: /home/alfonso/Escritorio/PruebaTecnica/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(UnitTests "runUnitTests")
set_tests_properties(UnitTests PROPERTIES  _BACKTRACE_TRIPLES "/home/alfonso/Escritorio/PruebaTecnica/CMakeLists.txt;15;add_test;/home/alfonso/Escritorio/PruebaTecnica/CMakeLists.txt;0;")
subdirs("lib/googletest")
