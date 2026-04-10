#include "List.hpp"
#include "unit_test_framework.hpp"
 
using namespace std;
 
// Add your test cases here

TEST(test_iterator_after_erase) {
    List<int> list;
    for (int i = 0; i < 3; ++i) list.push_back(i);

    auto it = list.begin();
    auto erased = it;
    ++it;

    list.erase(erased);

    ASSERT_EQUAL(*it, 1); // should still be valid
}  

TEST(test_erase_begin) {
    List<int> list;
    for (int i = 0; i < 3; ++i) list.push_back(i); // 0 1 2

    auto it = list.erase(list.begin());

    ASSERT_EQUAL(*it, 1);
    ASSERT_EQUAL(list.front(), 1);
}

TEST(test_erase_last) {
    List<int> list;
    for (int i = 0; i < 3; ++i) list.push_back(i);

    auto it = list.begin();
    ++it; ++it; // last element

    auto result = list.erase(it);

    ASSERT_TRUE(result == list.end());
}

TEST(test_insert_begin) {
    List<int> list;
    list.push_back(2);

    auto it = list.insert(list.begin(), 1);

    ASSERT_EQUAL(*it, 1);
    ASSERT_EQUAL(list.front(), 1);
}

TEST(test_insert_end) {
    List<int> list;
    list.push_back(1);

    auto it = list.insert(list.end(), 2);

    ASSERT_EQUAL(*it, 2);
    ASSERT_EQUAL(list.back(), 2);
}

TEST(test_erase_begin) {
    List<int> list;
    for (int i = 0; i < 3; ++i) list.push_back(i); // 0 1 2

    auto it = list.erase(list.begin());

    ASSERT_EQUAL(*it, 1);
    ASSERT_EQUAL(list.front(), 1);
}

TEST(test_const_iterator_read) {
    const List<int> list = [] {
        List<int> temp;
        temp.push_back(42);
        return temp;
    }();

    auto it = list.begin();
    ASSERT_EQUAL(*it, 42);
}

TEST(test_erase_last) {
    List<int> list;
    for (int i = 0; i < 3; ++i) list.push_back(i);

    auto it = list.begin();
    ++it; ++it; // last element

    auto result = list.erase(it);

    ASSERT_TRUE(result == list.end());
}

TEST(test_copy_constructors){
    List<int> list1;
    for (int i = 0; i < 5; ++i) {
        list1.push_back(i);
    }
    List<int> list2(list1);
    ASSERT_EQUAL(list1.size(), list2.size());
    for (auto it1 = list1.begin(), it2 = list2.begin(); it1 != list1.end(); ++it1, ++it2) {
        ASSERT_EQUAL(*it1, *it2);
    }

    
}
 
TEST(test_iterator_erase_return) {
    List<int> list;
    for (int i = 0; i < 3; ++i) list.push_back(i); // 0 1 2
 
    List<int>::Iterator it = list.begin();
    ++it; // points to 1
 
    List<int>::Iterator next = list.erase(it);
 
    ASSERT_EQUAL(*next, 2);
}
 
TEST(test_iterator_insert) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);
 
    List<int>::Iterator it = list.begin();
    ++it; // points to 3
    ASSERT_EQUAL(*it, 3);
    ASSERT_EQUAL(*list.begin(), 1);
    ASSERT_EQUAL(*(++list.begin()), 3);
 
    List<int>::Iterator inserted = list.insert(it, 2);
 
    ASSERT_EQUAL(*inserted, 2);
    ASSERT_EQUAL(*list.begin(), 1);
    ASSERT_EQUAL(*(++list.begin()), 2);
    ASSERT_EQUAL(*(++(++list.begin())), 3);
 
    // Check full list
    int expected = 1;
    for (auto i = list.begin(); i != list.end(); ++i) {
        ASSERT_EQUAL(*i, expected++);
    }
}
 
TEST(test_iterator_arrow_operator) {
    struct Test {
        int x;
    };
 
    List<Test> list;
    list.push_back({10});
 
    List<Test>::Iterator it = list.begin();
    ASSERT_EQUAL(it->x, 10);
 
    it->x = 20;
    ASSERT_EQUAL(list.front().x, 20);
}
 
TEST(test_iterator_dereference) {
    List<int> list;
    list.push_back(42);
 
    List<int>::Iterator it = list.begin();
    ASSERT_EQUAL(*it, 42);
 
    *it = 100;
    ASSERT_EQUAL(list.front(), 100);
}
 
TEST(test_iterator_decrement_from_end) {
    List<int> list;
    for (int i = 0; i < 3; ++i) list.push_back(i);
 
    List<int>::Iterator it = list.end();
 
    it--;
    ASSERT_EQUAL(*it, 2);
    ASSERT_TRUE(it != list.end());
 
    --it;
    ASSERT_EQUAL(*it, 1);
    ASSERT_TRUE(it != list.end());
}
 
TEST(test_iterator_increment) {
    List<int> list;
    for (int i = 0; i < 3; ++i) list.push_back(i);
 
    List<int>::Iterator it = list.begin();
 
    ASSERT_EQUAL(*it, 0);
 
    ++it;
    ASSERT_EQUAL(*it, 1);
    ASSERT_TRUE(it != list.end());
 
    it++;
    ASSERT_EQUAL(*it, 2);
    ASSERT_TRUE(it != list.end());
 
    ++it;
    ASSERT_TRUE(it == list.end());
    ASSERT_EQUAL(it, list.end());
}
 
TEST(test_iterator_assignment_to_default) {
    List<int> list;
    list.push_back(5);
 
    List<int>::Iterator it = list.begin();
    List<int>::Iterator def;
 
    it = def;
 
    ASSERT_TRUE(it == def);
}
 
TEST(test_iterator_assignment_self) {
    List<int> list;
    list.push_back(10);
 
    List<int>::Iterator it = list.begin();
    //it = it;  // self-assignment
 
    ASSERT_EQUAL(*it, 10);
}
 
TEST(test_iterator_assignment_default) {
    List<int>::Iterator it1;
    List<int>::Iterator it2;
 
    it1 = it2;
 
    ASSERT_TRUE(it1 == it2);
}
 
TEST(test_iterator_CALCULATION_assignment_operator) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
 
    // Assign begin iterator
    List<int>::Iterator it1 = list.begin();
    List<int>::Iterator it2;
 
    it2 = it1;  // assignment
 
    ASSERT_TRUE(it1 == it2);
    ASSERT_FALSE(it1 != it2);
 
    // Move one iterator, ensure they diverge
    ++it1;
    ASSERT_FALSE(it1 == it2);
    ASSERT_TRUE(it1 != it2);
 
    // Assign again after movement
    it2 = it1;
    ASSERT_TRUE(it1 == it2);
 
    // Assign end iterator
    List<int>::Iterator end_it = list.end();
    it1 = end_it;
 
    ASSERT_TRUE(it1 == list.end());
}
 
TEST(test_iterator_comparative_equal_operator) {
    List<int> list_1;
    List<int> list_2;
 
    for (int i = 0; i < 5; ++i) {
        list_1.push_back(i);
        list_2.push_back(i);
    }
 
    // Same list, same position
    List<int>::Iterator it1 = list_1.begin();
    List<int>::Iterator it2 = list_1.begin();
    ASSERT_TRUE(it1 == it2);
    ASSERT_FALSE(it1 != it2);
 
    // Same list, different position
    ++it2;
    ASSERT_FALSE(it1 == it2);
    ASSERT_TRUE(it1 != it2);
 
    // Different lists, same value (should NOT be equal)
    List<int>::Iterator it3 = list_2.begin();
    ASSERT_FALSE(it1 == it3);
    ASSERT_TRUE(it1 != it3);
 
    // End iterators (same list)
    List<int>::Iterator end1 = list_1.end();
    List<int>::Iterator end2 = list_1.end();
    ASSERT_TRUE(end1 == end2);
    ASSERT_FALSE(end1 != end2);
 
    // End iterators (different lists)
    List<int>::Iterator end3 = list_2.end();
    ASSERT_FALSE(end1 == end3);
}
 
TEST(test_iterator_another_comparative_equal_operator) {
    // Default-constructed iterators
    List<int>::Iterator list_1;
    List<int>::Iterator list_2;
 
    ASSERT_TRUE(list_1 == list_2);
    ASSERT_FALSE(list_1 != list_2);
 
    // Default vs real iterator
    List<int> list;
    list.push_back(10);
 
    List<int>::Iterator it = list.begin();
 
    ASSERT_FALSE(list_1 == it);
    ASSERT_TRUE(list_1 != it);
 
    // Iterator compared with itself
    ASSERT_TRUE(it == it);
    ASSERT_FALSE(it != it);
}
 
TEST(test_iterator_nonempty_list) {
    List<int> list;
    for (List<int>::Iterator i = list.begin(); i != list.end(); ++i) {
        list.push_back(*i);
    }
    List<int>::Iterator it = list.begin();
    for (List<int>::Iterator i = list.begin(); i != list.end(); ++i) {
        ASSERT_TRUE(it != list.end());
        ASSERT_EQUAL(*it, *i);
    }
    ASSERT_TRUE(it == list.end());
 
    for (List<int>::Iterator i = list.begin(); i != list.end(); ++i) {
        list.pop_back();
    }
 
    ASSERT_TRUE(list.empty());
 
    for (List<int>::Iterator i = list.begin(); i != list.end(); ++i) {
        ASSERT_TRUE(i == list.end());
    }
 
    
}
 
TEST(test_iterator_empty_list) {
    List<int> list;
    List<int>::Iterator it = list.begin();
    ASSERT_TRUE(it == list.end());
    ASSERT_FALSE(it != list.end());
}
 
TEST(test_iterator_init) {
    List<int> list;
 
    List<int>::Iterator it1;              // default
    List<int>::Iterator it2 = list.begin();
    List<int>::Iterator it3 = list.end();
 
    // Self equality
    ASSERT_TRUE(it1 == it1);
    ASSERT_TRUE(it2 == it2);
    ASSERT_TRUE(it3 == it3);
 
    ASSERT_FALSE(it1 != it1);
    ASSERT_FALSE(it2 != it2);
    ASSERT_FALSE(it3 != it3);
 
    // Default vs list iterators
    ASSERT_TRUE(it1 != it2);
    ASSERT_TRUE(it1 != it3);
 
    // 🔥 KEY FIX: empty list => begin == end
    ASSERT_TRUE(it2 == it3);
    ASSERT_FALSE(it2 != it3);
}
 
TEST(test_size_empty) {
    List<int> list;
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
    list.push_back(42);
    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.size(), 1);
    list.pop_back();
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
}
 
TEST(test_size_push_front) {
    List<int> list;
    ASSERT_EQUAL(list.size(), 0);
    list.push_front(42);
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(list.front(), 42);
    ASSERT_EQUAL(list.back(), 42);
    list.pop_front();
    ASSERT_EQUAL(list.size(), 0);
}
 
TEST(teset_empty) {
    List<int> list;
    ASSERT_TRUE(list.empty());
    list.push_back(42);
    ASSERT_FALSE(list.empty());
    list.pop_back();
    ASSERT_TRUE(list.empty());
}
 
TEST(test_front_back) {
    List<int> list;
    list.push_back(42);
    ASSERT_EQUAL(list.front(), 42);
    ASSERT_EQUAL(list.back(), 42);
    list.push_front(73);
    ASSERT_EQUAL(list.front(), 73);
    ASSERT_EQUAL(list.back(), 42);
}
 
TEST(test_clear) {
    List<int> list;
 
    for (int i = 0; i < 130; ++i) {
        list.push_back(i);
        ASSERT_EQUAL(list.size(), i + 1);
        ASSERT_EQUAL(list.back(), i);
        ASSERT_EQUAL(list.front(), 0);
    }
 
    list.clear();
 
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_TRUE(list.empty());
 
    ASSERT_TRUE(list.begin() == list.end());
}
 
TEST(test_clear_empty) {
    List<int> list;
 
    list.clear();  // should not crash
 
    ASSERT_TRUE(list.empty());
    ASSERT_TRUE(list.begin() == list.end());
}
 
TEST(test_size_pushback_popback) {
    List<int> list;
    ASSERT_EQUAL(list.size(), 0);
    list.push_back(42);
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(list.back(), 42);
    ASSERT_EQUAL(list.front(), 42);
    list.pop_back();
    for (int i = 0; i < 20; ++i) {
        list.push_back(i);
        ASSERT_EQUAL(list.size(), i + 1);
        ASSERT_EQUAL(list.back(), i);
        ASSERT_EQUAL(list.front(), 0);
    }
    ASSERT_EQUAL(list.front(), 0);
    ASSERT_EQUAL(list.size(), 20);
    
    for (int i = 0; i < 20; ++i) {
        list.pop_back();
        ASSERT_EQUAL(list.size(), 20 - i - 1);
        if (!list.empty()) {
            ASSERT_EQUAL(list.back(), 20 - i - 2);
        }
    }
    ASSERT_EQUAL(list.size(), 0);
    for (int i = 0; i < 20; ++i) {
        list.push_back(0);
        ASSERT_EQUAL(list.size(), i + 1);
        ASSERT_EQUAL(list.back(), 0);
    }
    ASSERT_EQUAL(list.size(), 20);
    ASSERT_EQUAL(list.front(), 0);
}
 
TEST(test_push_front) {
    List<int> list;
    list.push_front(42);
    ASSERT_EQUAL(list.front(), 42);
    ASSERT_EQUAL(list.back(), 42);
    list.push_front(73);
    ASSERT_EQUAL(list.front(), 73);
    ASSERT_EQUAL(list.back(), 42);
}
// Tests assignment operator according to hint
// Must declare list2 first, then assign on a separate line
TEST(test_assignment_operator_basic) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    List<int> list2;  // default constructed first
    list2 = list1;    // now uses operator=, not copy ctor
    //thoroughly check that = actually works
    ASSERT_EQUAL(list2.size(), list1.size());
    List<int>::Iterator it1 = list1.begin();
    List<int>::Iterator it2 = list2.begin();
    while (it1 != list1.end()) {
        ASSERT_EQUAL(*it1, *it2);
        ++it1; ++it2;
    }
}

// Assigning to a non-empty list (must clear old data first)
TEST(test_assignment_operator_overwrite) {
    List<int> list1;
    list1.push_back(10);
    list1.push_back(20);

    List<int> list2;
    list2.push_back(99);
    list2.push_back(88);
    list2.push_back(77);  // list2 has MORE elements than list1

    list2 = list1;  // should replace 99, 88, 77 with 10, 20

    ASSERT_EQUAL(list2.size(), 2);
    ASSERT_EQUAL(list2.front(), 10);
    ASSERT_EQUAL(list2.back(), 20);
}

// Assigning empty list to non-empty (must fully clear)
TEST(test_assignment_operator_assign_empty) {
    List<int> list1;  // empty

    List<int> list2;
    list2.push_back(1);
    list2.push_back(2);

    list2 = list1;  // list2 should now be empty

    ASSERT_TRUE(list2.empty());
    ASSERT_EQUAL(list2.size(), 0);
    ASSERT_TRUE(list2.begin() == list2.end());
}

// Assigning non-empty to empty list
TEST(test_assignment_operator_to_empty) {
    List<int> list1;
    list1.push_back(5);
    list1.push_back(6);

    List<int> list2;  // empty

    list2 = list1;

    ASSERT_EQUAL(list2.size(), 2);
    ASSERT_EQUAL(list2.front(), 5);
    ASSERT_EQUAL(list2.back(), 6);
}

// Self-assignment must not corrupt the list
TEST(test_assignment_operator_self) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list = list;  // self-assignment

    ASSERT_EQUAL(list.size(), 3);
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 3);
}

// modifying list2 after assignment must not affect list1
TEST(test_assignment_operator_deep_copy) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2;
    list2 = list1;

    list2.push_back(3);  // modify list2
    list2.pop_front();   // modify list2

    // list1 must be unchanged
    ASSERT_EQUAL(list1.size(), 2);
    ASSERT_EQUAL(list1.front(), 1);
    ASSERT_EQUAL(list1.back(), 2);
}

// Chained assignment: list3 = list2 = list1
TEST(test_assignment_operator_chained) {
    List<int> list1;
    list1.push_back(7);
    list1.push_back(8);

    List<int> list2;
    List<int> list3;

    list3 = list2 = list1;  // chained

    ASSERT_EQUAL(list2.size(), 2);
    ASSERT_EQUAL(list2.front(), 7);
    ASSERT_EQUAL(list3.size(), 2);
    ASSERT_EQUAL(list3.front(), 7);
}
TEST_MAIN()
 
