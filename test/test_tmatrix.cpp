#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(m);

	ASSERT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(m);

	ASSERT_NE(&m[0][0], &m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);

	ASSERT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);
	m[1][1] = 100;
	ASSERT_EQ(m[1][1], 100);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);

	ASSERT_ANY_THROW(m[-1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);

	ASSERT_ANY_THROW(m[6][1]);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(m);

	m = m;

	ASSERT_EQ(m, m1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(5);

	m = m1;

	ASSERT_EQ(m, m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_bigger_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(7);

	size_t sz = m1.size();
	m = m1;

	ASSERT_EQ(m.size(), sz);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_less_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(3);

	size_t sz = m1.size();
	m = m1;

	ASSERT_EQ(m.size(), sz);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(m1);

	m = m1;

	ASSERT_EQ(m, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(m);

	ASSERT_EQ(m == m1, true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(5);

	ASSERT_EQ(m == m, true);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(6);

	ASSERT_EQ(m != m1, true);
}

TEST(TDynamicMatrix, can_multiply_scalar_by_matrix)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(m);

	for (int i = 0; i < m.size(); i++)
		for (int j = 0; j < m.size(); j++) {
			m[i][j] = 1;
			m1[i][j] = 3;
		}

	ASSERT_EQ(m * 3, m1);
}

TEST(TDynamicVector, can_multiply_vector_to_matrix) {
	TDynamicMatrix<int> m(3);
	TDynamicVector<int> v(3);

	for (int i = 0; i < m.size(); i++) {
		v[i] = i;
		for (int j = 0; j < m.size(); j++)
			m[i][j] = i + j;
	}

	TDynamicVector<int> v1 = m * v;

	ASSERT_EQ(5 == v1[0] && 8 == v1[1] && 11 == v1[2], 1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);

	for (int i = 0; i < m.size(); i++)
		for (int j = 0; j < m.size(); j++) {
			m[i][j] = 1;
			m1[i][j] = 2;
			m2[i][j] = 3;
		}

	ASSERT_EQ(m + m1, m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(4);
	TDynamicMatrix<int> m1(5);

	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);

	for (int i = 0; i < m.size(); i++)
		for (int j = 0; j < m.size(); j++) {
			m[i][j] = 1;
			m1[i][j] = 2;
			m2[i][j] = 3;
		}

	ASSERT_EQ(m2 - m1, m);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(4);
	TDynamicMatrix<int> m1(5);

	ASSERT_ANY_THROW(m - m1);
}


TEST(TDynamicMatrix, can_multiply_matrix_to_matrix_equal_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);
	
	for (int i = 0; i < m.size(); i++)
		for (int j = 0; j < m.size(); j++) {
			m[i][j] = 1;
			m1[i][j] = 2;
			m2[i][j] = 10;
		}
	
	ASSERT_EQ(m * m1, m2);
}

TEST(TDynamicMatrix, cant_multiply_matrix_to_matrix_different_size)
{
	TDynamicMatrix<int> m(4);
	TDynamicMatrix<int> m1(5);

	ASSERT_ANY_THROW(m * m1);
}
