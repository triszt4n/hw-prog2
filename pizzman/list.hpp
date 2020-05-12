/**
 * @file list.h
 */

#ifndef LIST_H
#define LIST_H

#include <cstdlib>
#include <stdexcept>
#include "profile.h"

/**
 * @class List
 * @brief Reimplementing the template of a guarded list with its typical methods
 */
template<typename T>
class List {
    struct ListItem {
        T data;
        ListItem* next;
        ListItem(ListItem* p = NULL): next(p) { }

        ListItem& operator=(const ListItem);
    };

    ListItem* head;
    ListItem* tail;
    size_t number;

    List(const List&);
    List& operator=(const List&);
public:
    /**
     * @class List::iterator
     * @brief lovely iterator for our List
     */
    class iterator {
        ListItem* actual;
    public:
        iterator(): actual(NULL) { }

        iterator(const List& l): actual(l.head) {
            if (actual->next == NULL)
                actual = NULL;
        }

        iterator(const iterator& iter) {
            *this = iter;
        }

        void operator=(const iterator& rhs) {
            actual = rhs.getActual();
        }

        ListItem* getActual() const {
            return actual;
        }

        ~iterator() { delete actual; }

        iterator& operator++() {
            if (actual != NULL) {
                actual = actual->next;
                if (actual->next == NULL)
                    actual = NULL;
            }
            return (*this);
        }

        iterator& operator++(int) {
            iterator temp = (*this);
            operator++();
            return temp;
        }

        T& operator*() {
            if (actual != NULL)
                return actual->data;
            else
                throw std::out_of_range("List is empty.");
        }

        T* operator->() {
            if (actual != NULL)
                return &actual->data;
            else
                throw std::out_of_range("List is empty.");
        }


        bool operator==(const iterator& rhs) const {
            return (rhs.actual == actual);
        }

        bool operator!=(const iterator& rhs) const {
            return (rhs.actual != actual);
        }
    };

    List(): number(0) { head = tail = new ListItem(); }
    ~List() {
        clear();
        delete head;
    }

    size_t size() const {
        return number;
    }

    /**
     * @fn insert(T)
     * @brief inserts an item into the list (at the tail)
     */
    void insert(const T& data) {
        tail->data = data;
        tail->next = new ListItem;
        tail = tail->next;
        number++;
    }

    /**
     * @fn clear()
     * @brief frees all the items in list
     */
    void clear() {
        ListItem* item;
        while ((item = head) != NULL) {
            head = item->next;
            delete item;
        }
        head = tail = new ListItem();
        number = 0;
    }

    // DEPRECATED: DIDN'T USE IT EVER
    /**
     * @fn find_p(T): iterator
     * @brief method assumes T is a pointer itself, finds element in list
     * Uses indirection to access operator== of any specific type (Profile, Pizza, Topping, Order)
     * @return an iterator with the found item
     */
    iterator find_p(const T& data) {
        for (iterator i = begin(); i != end(); ++i) {
            if (*(*i) == (*data))
                return i;
        }
        return iterator();
    }

    /// Typical begin()
    iterator begin() const {
        return iterator(*this);
    }

    /// Typical end()
    iterator end() const {
        return iterator();
    }

    /// Interesting indexing operator
    T operator[](const size_t& index) {
        T found;
        size_t i = 0;
        for (iterator iter = begin(); iter != end(); ++iter) {
            if (i == index)
                return *iter;
            ++i;
        }
        return found;
    }
};

#endif // LIST_H
