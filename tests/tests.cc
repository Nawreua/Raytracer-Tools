#include "include.hh"

#include "tests_tuple.cc"
#include "tests_color.cc"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
