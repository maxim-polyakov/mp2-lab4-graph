#include <gtest.h>
#include "stack.h"



TEST(Stack, can_create_stack){
	Stack<double> *s;
	ASSERT_NO_THROW(s = new Stack<double>());
}

TEST(Stack, can_create_copied_stack){
	Stack<char> s1;
	s1.Push(3);
	s1.Push(2);
	ASSERT_NO_THROW(Stack<char> s2(s1));
}

TEST(Stack, copied_stack_is_equal_to_sourse_one){
	Stack<char> s1;
	s1.Push(3);
	Stack<char> s2(s1);
	EXPECT_EQ(s1.Peek(), s2.Peek());
}

TEST(Stack, copied_list_has_its_own_memory){
	Stack<char> s1;
	s1.Push(1);
	s1.Push(2);
	Stack<char> s2(s1);
	s2.Put();
	s2.Push(3);
	EXPECT_NE(s1.Peek(), s2.Peek());
}

TEST(Stack, IsEmpty_returns_1_when_stack_is_empty){
	Stack<char> s;
	EXPECT_EQ(1, s.IsEmpty());
}

TEST(Stack, IsEmpty_returns_0_when_stack_isnt_empty){
	Stack<char> s;
	s.Push(1);
	EXPECT_EQ(0, s.IsEmpty());
}

TEST(Stack, IsFull_returns_0_when_stack_isnt_full){
	Stack<char> s;
	s.Push(1);
	EXPECT_EQ(0, s.IsFull());
}

TEST(Stack, can_push_new_element){
	Stack<char> s;
	ASSERT_NO_THROW(s.Push(1));
}

TEST(Stack, throws_when_try_pop_element_when_stack_is_empty){
	Stack<char> s;
	ASSERT_ANY_THROW(s.Put());
}

TEST(Stack, can_pop_element_from_no_empty_stack){
	Stack<char> s;
	s.Push(1);
	ASSERT_NO_THROW(s.Put());
}

TEST(Stack, poped_element_is_equal_to_pushed_one){
	Stack<char> s;
	s.Push(1);
	EXPECT_EQ(1, s.Put());
}

TEST(Stack, throws_when_try_look_element_when_stack_is_empty){
	Stack<char> s;
	ASSERT_ANY_THROW(s.Peek());
}

TEST(Stack, can_look_element_from_no_empty_stack){
	Stack<char> s;
	s.Push(1);
	ASSERT_NO_THROW(s.Peek());
}

TEST(Stack, looked_element_is_equal_to_pushed_one){
	Stack<char> s;
	s.Push(1);
	EXPECT_EQ(1, s.Peek());
}

