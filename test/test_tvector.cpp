#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(v);

	ASSERT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(v);

	ASSERT_NE(&v[0], &v1[0]);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	ASSERT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;

	ASSERT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	for (int i = 0; i < v.size(); i++)
		v[i] = i;

	ASSERT_ANY_THROW(v[-2]);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	for (int i = 0; i < v.size(); i++)
		v[i] = i;

	ASSERT_ANY_THROW(v[6]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index_using_at)
{
	TDynamicVector<int> v(4);
	for (int i = 0; i < v.size(); i++)
		v[i] = i;

	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index_using_at)
{
	TDynamicVector<int> v(4);
	for (int i = 0; i < v.size(); i++)
		v[i] = i;

	ASSERT_ANY_THROW(v.at(6));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(v);

	v = v;

	ASSERT_EQ(v1, v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(4);

	v1 = v;

	ASSERT_EQ(v1, v);
}

TEST(TDynamicVector, assign_operator_change_vector_size_more_original_vec)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(7);

	size_t sz = v1.size();
	v = v1;

	ASSERT_EQ(v.size(), sz);
}

TEST(TDynamicVector, assign_operator_change_vector_size_less_original_vec)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(3);

	size_t sz = v1.size();
	v = v1;

	ASSERT_EQ(v.size(), sz);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(10);

	v1 = v;

	ASSERT_EQ(v1, v);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(v);

	ASSERT_EQ(v == v1, true);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(4);

	ASSERT_EQ(v == v, true);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(5);

	ASSERT_EQ(v != v1, true);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(4);
	v = v + 10;
	ASSERT_EQ(v[0], 10);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(4);
	v = v - 10;
	ASSERT_EQ(v[0], -10);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(4);
	for (int i = 0; i < v.size(); i++)
		v[i] = 1;
	v = v * 2;
	ASSERT_EQ(v[2], 2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(4);
	for (int i = 0; i < v.size(); i++) {
		v[i] = 1;
		v1[i] = 2;
	}
	//std::cout << v << std::endl;
	//std::cout << v1 << std::endl;
	TDynamicVector<int> v2(std::move(v + v1));

	ASSERT_EQ(v * 3, v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(5);

	ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(4);
	for (int i = 0; i < v.size(); i++) {
		v[i] = 5;
		v1[i] = 1;
	}
	//std::cout << v << std::endl;
	//std::cout << v1 << std::endl;
	TDynamicVector<int> v2(std::move(v - v1));

	ASSERT_EQ(v1 * 4, v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(5);

	ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(4);
	for (int i = 0; i < v.size(); i++) {
		v[i] = 2;
		v1[i] = 3;
	}
	int tmp = 24;

	ASSERT_EQ(tmp, v * v1);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(5);
	ASSERT_ANY_THROW(v * v1);
}

TEST(TDynamicVector, can_move_semantic)
{
	TDynamicVector<int> v(5);
	int tmp = (int)&v;
	TDynamicVector<int> v1(std::move(v));


	ASSERT_NE(tmp, (int)&v1);
}

TEST(TDynamicVector, can_move_semantic_operator)
{
	TDynamicVector<int> v(5);
	int tmp = (int)&v;
	TDynamicVector<int> v1 = std::move(v);

	ASSERT_NE(tmp, (int)&v1);

}