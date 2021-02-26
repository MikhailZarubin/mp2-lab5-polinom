#include"gtest.h"
#include<algorithm>
#include"../Polinom/Polinom.h"

TEST(Monom, can_create_monom)
{
	ASSERT_NO_THROW(TMonom m);
}
TEST(Monom, monom_fields_are_initialized_by_default)
{
	TMonom m;
	int error = 0;
	if (m.x != 0 || m.y != 0 || m.z != 0 || m.coeff != 1.0)
		error++;
	EXPECT_EQ(0, error);
}
TEST(Monom, can_compare_the_monoms)
{
	TMonom m1, m2;
	ASSERT_NO_THROW(m1 == m2);
	ASSERT_NO_THROW(m1 < m2);
	ASSERT_NO_THROW(m1 > m2);
}
TEST(Monom, monoms_are_compared_correctly)
{
	TMonom m1(1,1,1,1.0), m2(1,2,1,1.0);
	EXPECT_EQ(true, m1 < m2);
	EXPECT_EQ(true, m2 > m1);
	m1.y = 2;
	EXPECT_EQ(true, m1 == m2);
}
TEST(Monom, monom_can_be_assigned_to)
{
	TMonom m1, m2;
	ASSERT_NO_THROW(m1 = m2);
}
TEST(Monom, monoms_are_assigned_correctly)
{
	TMonom m1, m2(1, 2, 3, 4.0);
	m1 = m2;
	int error = 0;
	if (m1.x !=1 || m1.y != 2 || m1.z != 3 || m1.coeff != 4.0)
		error++;
	EXPECT_EQ(0, error);
}
TEST(Monom, monoms_can_be_multiplied_by_each_other)
{
	TMonom m1, m2;
	ASSERT_NO_THROW(m1=m1* m2);
}
TEST(Monom, monoms_multiplying_by_each_other_is_done_correctly)
{
	TMonom m1(1,2,3,4.0), m2(4,3,2,1.0);
	m1 = m1 * m2;
	int error = 0;
	if (m1.x != 5 || m1.y != 5 || m1.z != 5 || m1.coeff != 4.0)
		error++;
	EXPECT_EQ(0, error);
}
TEST(Monom, monoms_can_be_multiplied_by_a_number)
{
	TMonom m;
	ASSERT_NO_THROW(m= m*5.0);
}
TEST(Monom, monoms_multiplying_by_a_number_is_done_correctly)
{
	TMonom m(1,2,3,4.0);
	m = m * 5.0;
	int error = 0;
	if (m.x != 1 || m.y != 2 || m.z != 3 || m.coeff != 20.0)
		error++;
	EXPECT_EQ(0, error);
}
TEST(Polinom, can_create_polinom)
{
	ASSERT_NO_THROW(TPolinom l);
}
TEST(Polinom, can_copy_empty_polinom)
{
	TPolinom l;
	ASSERT_NO_THROW(TPolinom p(l));
}
TEST(Polinom, can_copy_no_empty_polinom)
{
	TPolinom l;
	TMonom m(2, 4, 8, 3.14);
	l.InsMonom(m);
	ASSERT_NO_THROW(TPolinom p(l));
}
TEST(Polinom, the_ñopied_polinom_has_its_own_memory)
{
	TPolinom l;
	TMonom m(2, 4, 8, 3.14);
	l.InsMonom(m);
	TPolinom p(l);
	p.DelFirst();
	EXPECT_EQ(1, l.Get_Size());
}
TEST(Polinom, can_insert_monom_in_empty_polinom)
{
	TPolinom p;
	TMonom m;
	ASSERT_NO_THROW(p.InsMonom(m));
}
TEST(Polinom, can_insert_monom_in_no_empty_polinom)
{
	TPolinom p;
	TMonom tmp(1, 0, 1, 1.5);
	p.InsMonom(tmp);
	TMonom m;
	ASSERT_NO_THROW(p.InsMonom(m));
}
TEST(Polinom, can_compare_empty_polinom)
{
	TPolinom p1, p2, p3;
	ASSERT_NO_THROW(p1 = p2 = p3);
}
TEST(Polinom, can_compare_no_empty_polinom_the_same_sizes)
{
	TPolinom p1, p2, p3;
	TMonom m;
	p1.InsMonom(m);
	m.x=5;
	p2.InsMonom(m);
	m.y = 5;
	p3.InsMonom(m);
	ASSERT_NO_THROW(p1 = p2 = p3);
}
TEST(Polinom, can_compare_no_empty_polinom_the_different_sizes)
{
	TPolinom p1, p2;
	TMonom m;
	p2.InsMonom(m);
	ASSERT_NO_THROW(p1 = p2);
	p1.DelFirst();
	ASSERT_NO_THROW(p2 = p1);
}
TEST(Polinom, can_adiition_empty_polinom)
{
	TPolinom p1, p2;
	ASSERT_NO_THROW(p1 += p2);
}
TEST(Polinom, can_adiition_no_empty_polinom_the_same_sizes)
{
	TPolinom p1, p2;
	TMonom tmp(1, 0, 1, 1.5);
	p1.InsMonom(tmp);
	tmp.x = 2;
	p2.InsMonom(tmp);
	ASSERT_NO_THROW(p1 += p2);
}
TEST(Polinom, can_adiition_no_empty_polinom_the_different_sizes)
{
	TPolinom p1, p2;
	TMonom tmp(1, 0, 1, 1.5);
	p1.InsMonom(tmp);
	tmp.x = 2;
	p2.InsMonom(tmp);
	tmp.y = 3;
	p2.InsMonom(tmp);
	ASSERT_NO_THROW(p1 += p2);
}
TEST(Polinom, when_adding_the_polinoms_the_opposite_valued_monoms_will_be_destroyed)
{
	TPolinom p1, p2;
	TMonom tmp(1, 1,2,1.0);
	p1.InsMonom(tmp);
	tmp.coeff = -tmp.coeff;
	p2.InsMonom(tmp);
	ASSERT_NO_THROW(p1 += p2);
	EXPECT_EQ(0, p1.Get_Size());
}
TEST(Polinom, can_multiplication_empty_polinom)
{
	TPolinom p1, p2;
	ASSERT_NO_THROW(TPolinom p = p1 * p2);
}
TEST(Polinom, can_multiplication_no_empty_polinom_the_same_sizes)
{
	TPolinom p1, p2;
	TMonom tmp(1, 0, 1, 1.5);
	p1.InsMonom(tmp);
	tmp.x = 2;
	p2.InsMonom(tmp);
	TPolinom p;
	ASSERT_NO_THROW(p = p1 * p2);
}
TEST(Polinom, can_multiplication_no_empty_polinom_the_different_sizes)
{
	TPolinom p1, p2;
	TMonom tmp(1, 0, 1, 1.5);
	p1.InsMonom(tmp);
	tmp.x = 2;
	p2.InsMonom(tmp);
	tmp.y = 3;
	p2.InsMonom(tmp);
	TPolinom p;
	ASSERT_NO_THROW(p = p1 * p2);
}