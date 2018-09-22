#include "include.hh"

#include "tests_tuple.cc"
#include "tests_color.cc"
#include "tests_canvas.cc"
#include "tests_matrix.cc"
#include "tests_matrix_transformations.cc"
#include "tests_ray.cc"
#include "tests_sphere.cc"
#include "tests_intersection.cc"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
