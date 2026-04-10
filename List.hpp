#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 List/Editor Project
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return first == nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const {
    return ls_size;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    assert(first != nullptr);
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    assert(last != nullptr);
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    Node *p_new = new Node;
    p_new->datum = datum;
    p_new->prev = nullptr;
    p_new->next = first;

    if (first){
      first->prev = p_new;
    }

    if (first == nullptr) {
      last = p_new;
    }
    first = p_new;
    ls_size++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    Node *p_new = new Node;
    p_new->datum = datum;
    p_new->next = nullptr;
    p_new->prev = last;

    if (last) {
      last->next = p_new;
    }

    if (empty()) {
      first = last = p_new;
    } else {
      last->next = p_new;
      p_new->prev = last;
    }
    ls_size++;
    last = p_new;
  }

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
      assert(!empty());

      Node* to_delete = first;
      first = first->next; //go back to the first ones

      if (first) {
        first->prev = nullptr; 
      } else {
        last = nullptr;
      }

      delete to_delete;
      ls_size-=1;
  }

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(!empty());

    Node* to_delete = last;
    last = last->prev;
    
    if (last != nullptr) {
      last->next = nullptr;
    } else {
      first = nullptr;
    }
    delete to_delete;
    ls_size -= 1;
  }

  //MODIFIES: invalidates all iterators to the removed elements
  //EFFECTS:  removes all items from the list
  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.
  List() : first(nullptr), last(nullptr) {}; //default constructor

  ~List() { //destructor
    clear();
  }

  List(const List &other) : first (nullptr), last(nullptr) { //copy constructor
    copy_all(other);
  }

  List & operator=(const List &other) {
    if (this == &other) {
      return *this;
    }
    clear();
    copy_all(other);
    return *this;
  }

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    for (Node *np = other.first; np ; np = np->next) {
      push_back(np->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int ls_size = 0;      // number of elements in the list

public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.
    Iterator(List<T> *list = nullptr) : list_ptr(list), node_ptr(nullptr) {};



    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.
    ~Iterator() { //destructor
      list_ptr = nullptr;
      node_ptr = nullptr; 
    }

  // copy constructor
    Iterator(const Iterator &other)
        : list_ptr(other.list_ptr), node_ptr(other.node_ptr) {};
 
    Iterator & operator=(const Iterator &other) { //overloaded assignment operator
      if (this != &other) {
        list_ptr = other.list_ptr;
        node_ptr = other.node_ptr;
      }
      return *this;
    }


    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.

    bool operator==(const Iterator &other) const {
      return list_ptr == other.list_ptr && node_ptr == other.node_ptr;
    }

    bool operator!=(const Iterator &other) const {
      return !(*this == other);
    }

    T& operator*() const {
      assert(list_ptr);
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator& operator++() { // for when i++
      assert(list_ptr);
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    Iterator operator++(int /*dummy*/) {
      assert(list_ptr);
      assert(node_ptr);
      Iterator copy = *this;
      node_ptr = node_ptr->next;
      return copy;
    }



    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      assert(*this != list_ptr->begin());
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &operator*();
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here


    // add any friend declarations here
    friend class List;


    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np) : list_ptr(lp), node_ptr(np) {}

  

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(this, first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator(this, nullptr);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i) {
    assert(i.list_ptr == this);
    assert(i.node_ptr);

    Node *to_delete = i.node_ptr;
    Node *to_return = nullptr;

    if (to_delete == first) {
      first = to_delete->next;
      if (first) {
          first->prev = nullptr;
      } else {
        last = nullptr;
      }
      to_return = first;
    }
    else if (to_delete == last) {
      last = to_delete->prev;
      if (last) {
        last->next = nullptr;
      } else {
        first = nullptr;
      }
      to_return = last;
    }
    else {
      to_delete->prev->next = to_delete->next;
      to_delete->next->prev = to_delete->prev;
      to_return = to_delete->next;
    }
    ls_size--;
    delete to_delete;
    return Iterator(this, to_return);
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
Iterator insert(Iterator i, const T &datum) {
    assert(i.list_ptr == this);
    
    Node *p_insert = new Node;
    p_insert->datum = datum;

    if (i.node_ptr == nullptr) {
        // inserting at end
        p_insert->next = nullptr;
        p_insert->prev = last;
        if (last) last->next = p_insert;
        else first = p_insert;
        last = p_insert;
        ls_size++;
        return Iterator(this, p_insert);
    }

    p_insert->next = i.node_ptr;
    p_insert->prev = i.node_ptr->prev;
    if (i.node_ptr->prev != nullptr) {
        i.node_ptr->prev->next = p_insert;
    } else {
        first = p_insert;
    }
    i.node_ptr->prev = p_insert;
    ls_size++;
    return Iterator(this, p_insert);
}
};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line;
