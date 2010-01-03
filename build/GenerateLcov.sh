#!

# Lancer le test
# lcov --directory ../output/temp/posix-gcc/coverage/sources/wordgrid/ --zerocounters
lcov --directory ../output/temp/posix-gcc/coverage/sources/wordgrid/ --capture --output-file ../output/coverage/tests.info
genhtml ../output/coverage/tests.info


