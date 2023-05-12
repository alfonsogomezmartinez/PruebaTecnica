# CMake generated Testfile for 
# Source directory: /home/alfonso/Escritorio/PruebaTecnicaIkerlan
# Build directory: /home/alfonso/Escritorio/PruebaTecnicaIkerlan/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(UnitTests "runUnitTests")
set_tests_properties(UnitTests PROPERTIES  _BACKTRACE_TRIPLES "/home/alfonso/Escritorio/PruebaTecnicaIkerlan/CMakeLists.txt;12;add_test;/home/alfonso/Escritorio/PruebaTecnicaIkerlan/CMakeLists.txt;0;")
subdirs("lib/googletest")
