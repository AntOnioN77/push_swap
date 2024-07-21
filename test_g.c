#include <stdio.h>
#include <assert.h>
#include "circularArray.h" // Make sure this path is correct

// Test Setup
t_ciar *setup_test(int items) {
    return ciar_int_init(items);
}

// Test Teardown
void teardown_test(t_ciar *arr) {
    ciar_free(arr);
}

// Test Initialization
void test_init() {
    t_ciar *arr = setup_test(5);
    assert(arr != NULL);
    assert(arr->slots == 6); // Because of the implementation detail
    teardown_test(arr);
    printf("test_init passed\n");
}

// Test Add and Pop
void test_add_pop() {
    t_ciar *arr = setup_test(2);
    add(arr, 1);
    add(arr, 2);
    assert(pop(arr) == OK);
    assert(arr->fill == 1);
    teardown_test(arr);
    printf("test_add_pop passed\n");
}

// Test Rotate
void test_rotate() {
    t_ciar *arr = setup_test(2);
    add(arr, 1);
    add(arr, 2);
    rotate(arr);
    assert(arr->buff[arr->top] == 1); // Assuming OK means successful operation
    teardown_test(arr);
    printf("test_rotate passed\n");
}

// Test Reverse Rotate
void test_reverse_rotate() {
    t_ciar *arr = setup_test(2);
    add(arr, 1);
    add(arr, 2);
    reverse_rotate(arr);
    assert(arr->buff[prev_index(arr->top, arr->slots)] == 2);
    teardown_test(arr);
    printf("test_reverse_rotate passed\n");
}

// Main function to run tests
int main() {
    test_init();
    test_add_pop();
    test_rotate();
    test_reverse_rotate();
    printf("All tests passed!\n");
    return 0;
}