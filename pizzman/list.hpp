/**
 * @file list.hpp
 * @brief List class declaration
 */

#ifndef LIST_H
#define LIST_H

#include <cstdlib>
#include <stdexcept>

/**
 * @class List template class
 * @brief Reimplementing the template of a guarded list with its typical methods
 * Other spicy methods included
 */
template<typename T>
class List {
    /**
     * @struct ListItem
     * @brief ListItem structure for a list
     */
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

        iterator& operator++() {
            if (actual != NULL) {
                actual = actual->next;
                if (actual->next == NULL)
                    actual = NULL;
            }
            return (*this);
        }

        iterator operator++(int) {
            iterator temp = (*this);
            operator++();
            return temp;
        }

        T& operator*() {
            if (actual != NULL)
                return actual->data;
            else
                throw std::out_of_range("This iterator does not point to anything.");
        }

        T* operator->() {
            if (actual != NULL)
                return &actual->data;
            else
                throw std::out_of_range("This iterator does not point to anything.");
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

    /**
     * @brief returns the number of list items in list
     * @return number
     */
    size_t size() const {
        return number;
    }

    /**
     * @brief inserts an item into the list (at the tail)
     */
    void insert(const T& data) {
        tail->data = data;
        tail->next = new ListItem;
        tail = tail->next;
        number++;
    }

    /**
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

    /**
     * @brief method is useful only for heterogeneous stores (List<X*>)
     * Upon comparing, the method dereferences both of the items in order to
     * Work with the dedicated operator== between the two items.
     * @see pizza.h, order.h, topping.h, profile.h's operator==
     * @return an iterator with the found item
     */
    iterator find_p(const T& data) {
        for (iterator iter = begin(); iter != end(); ++iter) {
            if (*(*iter) == (*data))
                return iter;
        }
        return iterator();
    }

    /**
     * @brief Typical begin()
     * @return iterator with head item
     */
    iterator begin() const {
        return iterator(*this);
    }

    /**
     * @brief Typical end()
     * @return iterator with sentinel (blank) item
     */
    iterator end() const {
        return iterator();
    }

    /**
     * @brief an interesting method that works similarly as find_p
     * Iterates through list to find the searched "indexed" item
     * @return an iterator with the found item
     * @exception if overindexing happens
     */
    iterator operator[](const size_t& index) {
        if (index >= size()) {
            throw std::out_of_range("Out of range indexing of List");
        }
        else {
            size_t i = 0;
            for (iterator iter = begin(); iter != end(); ++iter, ++i) {
                if (i == index)
                    return iter;
            }
        }
        return iterator();
    }
};

#endif // LIST_H
