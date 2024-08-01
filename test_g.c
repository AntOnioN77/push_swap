#include <stdio.h>
#include <assert.h>
#include "circularArray.h" // Make sure this path is correct
#include <string.h>

//imprimir stack
void print_stack(t_ciar *arr)
{
	if (arr->fill == 0)
		return ;
	int index = arr->back;
	while (index != arr->top)
	{
		printf("%d\n", arr->buff[index]);
		index = prev_index(index, arr->slots);
	}
	printf("%d\n", arr->buff[index]);
}

int check_stack(t_ciar *arr, int *expected, int size)
{
	int index;
	int i = 0;
	int level_top;

	if (arr->fill < 1)
		{
			if(size == 0)
				{
					printf("OK\n");
					return (0);
				}
			printf("Empty stack, size %d???", size);
			return (1);
		}
	index = arr->back;
	level_top = get_level(arr, arr->top);
	while (get_level(arr, index) >= level_top)
	{
		if ((i + 1) > size)
		{
			printf("distance between top and back is greater than size \n");
			return (1);
		}
		if (arr->buff[index] != expected[i])
		{
			printf("Not OK\n");
			printf("Difference in position arr[%d]\n", i);
			return (1);
		}
		index = prev_index(index, arr->slots);
		i++;
	}
	if (i < size)
	{
		printf("distance between top and back is less than size \n");
		return (1);
	}
	printf("OK\n");
	return (0);
}

// Test Setup
t_ciar *setup_test(int items)
{
    return init_ciar(items);
}

// Test Teardown
void teardown_test(t_ciar *arr)
{
    free_ciar(arr);
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


// Test get_back
void test_get_back1() {
    t_ciar *arr = setup_test(2);
    add(arr, 1);
    add(arr, 2);
    
    assert(get_back(arr) == 1);
    teardown_test(arr);
    printf("test_get_back1 passed\n");
}

void test_get_back2() {
    t_ciar *arr = setup_test(3);
    add(arr, 1);
	add(arr, 7);
    add(arr, 2);
	rotate(arr);
    
    assert(get_back(arr) == 2);
    teardown_test(arr);
    printf("test_get_back2 passed\n");
}

void test_get_back3() {
    t_ciar *arr = setup_test(3);
    add(arr, 1);
	add(arr, 7);
    add(arr, 2);
	rotate(arr);
	rotate(arr);
    
    assert(get_back(arr) == 7);
    teardown_test(arr);
    printf("test_get_back3 passed\n");
}

// Test get_top
void test_get_top1() {
    t_ciar *arr = setup_test(3);
    add(arr, 1);
	add(arr, 7);
    add(arr, 2);
    
    assert(get_top(arr) == 2);
    teardown_test(arr);
    printf("test_get_top1 passed\n");
}

void test_get_top2() {
    t_ciar *arr = setup_test(3);
    add(arr, 1);
	add(arr, 7);
    add(arr, 2);
	reverse_rotate(arr);
    
    assert(get_top(arr) == 1);
    teardown_test(arr);
    printf("test_get_top2 passed\n");
}

void test_get_top3() {
    t_ciar *arr = setup_test(3);
    add(arr, 1);
	add(arr, 7);
    add(arr, 2);
	reverse_rotate(arr);
	reverse_rotate(arr);
    
    assert(get_top(arr) == 7);
    teardown_test(arr);
    printf("test_get_top3 passed\n");
}
void test_get_top4() {
    t_ciar *arr = setup_test(3);
    add(arr, 1);
	add(arr, 7);
    add(arr, 2);
	reverse_rotate(arr);
	reverse_rotate(arr);
    reverse_rotate(arr); 

    assert(get_top(arr) == 2);
    teardown_test(arr);
    printf("test_get_top4 passed\n");
}

// Test Rotate
void test_rotate1() {
    t_ciar *arr = setup_test(2);
    add(arr, 1);
    add(arr, 2);
    rotate(arr);
    assert(arr->buff[arr->top] == 1); // Assuming OK means successful operation
    teardown_test(arr);
    printf("test_rotate1 passed\n");
}

void test_rotate2() {
    t_ciar *arr = setup_test(2);
    add(arr, 1);
    add(arr, 2);
    rotate(arr);
	rotate(arr);
    assert(arr->buff[arr->top] == 2);
    teardown_test(arr);
    printf("test_rotate2 passed\n");
}

// Test Reverse Rotate
void test_reverse_rotate1() {
    t_ciar *arr = setup_test(2);
    add(arr, 1);
    add(arr, 2);
    reverse_rotate(arr);
    assert(get_top(arr) == 1);
    teardown_test(arr);
    printf("test_reverse_rotate1 passed\n");
}

void test_reverse_rotate2() {
    t_ciar *arr = setup_test(3);
    add(arr, 1);
    add(arr, 2);
	add(arr, 3);
    reverse_rotate(arr);
    assert(get_top(arr) == 1);
    teardown_test(arr);
    printf("test_reverse_rotate2 passed\n");
}

void test_reverse_rotate3() {
    t_ciar *arr = setup_test(2);
    add(arr, 1);
    add(arr, 2);
    reverse_rotate(arr);
	reverse_rotate(arr);
    assert(get_top(arr) == 2);
    teardown_test(arr);
    printf("test_reverse_rotate3 passed\n");
}

void test_reverse_rotate4() {
    t_ciar *arr = setup_test(2);
    add(arr, 1);
    add(arr, 2);
    reverse_rotate(arr);
	reverse_rotate(arr);
	reverse_rotate(arr);
    assert(get_top(arr) == 1);
    teardown_test(arr);
    printf("test_reverse_rotate4 passed\n");
}
/*
void test_push()
{
	t_ciar *arr = setup_test();
}
*/
void test_tomaniadd()
{
	int i;
	t_ciar *arr = setup_test(2); //el array solo contendra 2 numeros
	
	add(arr, 1);
	add(arr, 2);
	add(arr, 3);
	add(arr, 4);
	
	i = 4;
	while (i > 0)
	{
		assert(get_top(arr) );
		//printf("test_tomaniadd %d\n", get_top(arr));
		rotate(arr);
		i--;
	}
	teardown_test(arr);
    printf("test_tomaniadd passed\n");
}

void	test_push()
{
	t_ciar *arr;
	t_ciar *brr;
	//-----------------{back, x, x}
	int expected_a[] = {1,2,3};
	int expected_b[] = {0,0,0};

	printf("-0-0-0-0-0-0----- test_push ------0-0-0-0-0-0\n");
	arr = init_ciar(3);
	brr = init_ciar(3);
	add(arr, 1);
	add(arr, 2);
	add(arr, 3);
	
	rotate(arr);
	rotate(arr);
	rotate(arr);

	printf("\n	estado inicial\n");
	printf("--stack A--\n");
	print_stack(arr);
	assert(check_stack(arr, expected_a, 3) == 0);
	printf("--stack B--\n");
	print_stack(brr);
	assert(check_stack(brr, expected_b, 0) == 0);
	printf("stacks A y B tienen el numero de elementos esperados y en el orden correcto\n");

	printf("\n	push1:\n");
	push(arr, brr);
	memcpy(expected_a,(int[]){1,2,0}, sizeof(expected_a));
	memcpy(expected_b,(int[]){3,0,0}, sizeof(expected_a));
	printf("--stack A--\n");
	print_stack(arr);
	assert(check_stack(arr, expected_a, 2) == 0);
	printf("--stack B--\n");
	print_stack(brr);
	assert(check_stack(brr, expected_b, 1) == 0);
	printf("stacks A y B tienen el numero de elementos esperados y en el orden correcto\n");

	printf("\n	push2:\n");
	push(arr, brr);
	memcpy(expected_a,(int[]){1,0,0}, sizeof(expected_a));
	memcpy(expected_b,(int[]){3,2,0}, sizeof(expected_a));
	printf("--stack A--\n");
	print_stack(arr);
	assert(check_stack(arr, expected_a, 1) == 0);
	printf("--stack B--\n");
	print_stack(brr);
	assert(check_stack(brr, expected_b, 2) == 0);
	printf("stacks A y B tienen el numero de elementos esperados y en el orden correcto\n");

	printf("\n	push3:\n");
	push(arr, brr);
	memcpy(expected_a,(int[]){0,0,0}, sizeof(expected_a));
	memcpy(expected_b,(int[]){3,2,1}, sizeof(expected_a));
	printf("--stack A--\n");
	print_stack(arr);
	assert(check_stack(arr, expected_a, 0) == 0);
	printf("--stack B--\n");
	print_stack(brr);
	assert(check_stack(brr, expected_b, 3) == 0);
	printf("stacks A y B tienen el numero de elementos esperados y en el orden correcto\n");
	teardown_test(arr);
}

void test_swap() {
		t_ciar *arr = setup_test(3);
		add(arr, 1);
		add(arr, 2);
		add(arr, 3);
		
		swap(arr);
		assert(get_top(arr) == 2);
		assert(get_back(arr) == 1);
		assert(arr->buff[prev_index(arr->top, arr->slots) == 3]);
		
		teardown_test(arr);
		printf("test_swap passed\n");
	}

	

// Main function to run tests
int main() {
    test_init();
    test_add_pop();
    test_rotate1();
	test_rotate2();
	test_reverse_rotate1();
	test_reverse_rotate2();
	test_reverse_rotate3();
	test_reverse_rotate4();
	test_get_back1();
	test_get_back2();
	test_get_back3();
	test_get_top1();
	test_get_top2();
	test_get_top3();
	test_get_top4();
	test_push();
	test_tomaniadd();
	test_swap();
    printf("All tests passed!\n");
    return 0;
}