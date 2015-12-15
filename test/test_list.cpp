#include <gtest.h>
#include "list.h"

TEST(List, can_create_list){
	List<char> *list;
	ASSERT_NO_THROW(list = new List<char>());
}

TEST(List, can_create_copied_list) {
	List<char> list1;
	list1.InsertLast(1);
	ASSERT_NO_THROW(List<char> list2(list1));
}
TEST(List, copied_list_is_equal_to_sourse_one){

	List<char> list1;
	list1.InsertLast(1);
	List<char> list2(list1);
	EXPECT_EQ(list2.getFirst()->key, 1);
};

TEST(List, can_print_list) {
	List<char> list1;
	list1.InsertLast(25);
	ASSERT_NO_THROW(list1.Print());
}

TEST(List, can_print_empty_list) {
	List<char> list1;
	ASSERT_NO_THROW(list1.Print());
}

TEST(List, can_insert_last_element) {
	List<char> list;
	list.InsertFirst(2);
	ASSERT_NO_THROW(list.InsertLast(5));
}

TEST(List, can_insert_last_element_when_list_is_empty) {
	List<char> list;
	ASSERT_NO_THROW(list.InsertLast(5));
}

TEST(List, list_after_insertion_last_peek_right) {
	List<char> list;
	list.InsertLast(5);
	EXPECT_EQ(5, list.getFirst()->key);
}

TEST(List, list_after_insertion_first_peek_right) {
	List<char> list;
	list.InsertFirst(5);
	EXPECT_EQ(list.getFirst()->key, 5);
}