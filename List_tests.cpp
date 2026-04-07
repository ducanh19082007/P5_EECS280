#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

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
    it = it;  // self-assignment

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
        ASSERT_EQUAL(list.back(), 20 - i - 2);
    }
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_EQUAL(list.front(), 0);
    for (int i = 0; i < 20; ++i) {
        list.push_back(0);
        ASSERT_EQUAL(list.size(), i + 1);
        ASSERT_EQUAL(list.back(), i);
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

TEST_MAIN()
