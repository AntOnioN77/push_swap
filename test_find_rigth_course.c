// test_find_right_course.c
#include <assert.h>
#include <string.h>
#include <limits.h>

#include "circular_array.h"


// Test functions
void test_find_place_for() {
    t_ciar stack_a;
    int array[] = {1, 3, 5, 7, 9};
    stack_a.fill = 5;
    stack_a.array = array;

    assert(find_place_for(&stack_a, 4) == 2);
    assert(find_place_for(&stack_a, 10) == 0);
    assert(find_place_for(&stack_a, 0) == 0);
}

void test_init_course() {
    t_course course;
    init_course(&course);

    assert(course.steps == INT_MAX);
    assert(course.rr == 0);
    assert(course.rrr == 0);
    assert(course.ra == 0);
    assert(course.rb == 0);
    assert(course.rra == 0);
    assert(course.rrb == 0);
    assert(course.pa == 0);
}

void test_run_sync_rotate() {
    t_course course;
    t_place deeper = {5, 'a'};
    t_place higher = {2, 'a'};

    run_sync_rotate(deeper, higher, &course);

    assert(course.steps == 6);
    assert(course.rr == 2);
    assert(course.rrr == 0);
    assert(course.ra == 3);
    assert(course.rb == 0);
    assert(course.rra == 0);
    assert(course.rrb == 0);
    assert(course.pa == 1);
}

int main() {
    test_find_place_for();
    test_init_course();
    test_run_sync_rotate();

    printf("All tests passed!\n");
    return 0;
}