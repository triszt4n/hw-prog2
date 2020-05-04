/**
 * @file list.h
 */

#ifndef LIST_H
#define LIST_H

#include <cstdlib>
#include <stdexcept>



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
    };

    /**
     * @brief This recursive function solves freeing of every element
     */
    void clearRec(ListItem* item) {
        if (item != NULL) {
            clearRec(item->next);
            delete item;
        }
    }

    ListItem* head;
    ListItem* tail;
    size_t number;
public:
    class iterator {
        ListItem* actual;
    public:
        iterator(): actual(NULL) { }

        iterator(const List& l): actual(l.head) {
            if (actual->next == NULL)
                    actual = NULL;
        }

        iterator(const iterator& i): actual(i.getActual()) { }

        ~iterator() { delete actual; }

        iterator& operator++() {
            if (actual != NULL) {
                actual = actual->next;
                if (actual->next == NULL)
                    actual = NULL;
            }
            return *this;

        }

        iterator operator++(int) {
            iterator temp(*this);
            operator++();
            return temp;
        }

        T& operator*() {
            if (actual == NULL)
                throw std::out_of_range("List is empty.");
            else
                return actual->data;
        }

        ListItem* getActual() const {
            return actual;
        }

        bool operator==(const iterator& rhs) const {
            return (rhs.getActual() == actual);
        }

        bool operator!=(const iterator& rhs) const {
            return (rhs.getActual() != actual);
        }
    };

    List(): number(0) { head = tail = new ListItem; }
    ~List() { clear(); }

    size_t size() const {
        return number;
    }
    T& getFirst() const {
        return head->data;
    }

    void insert(const T& data) {
        tail->data = data;
        tail->next = new ListItem;
        tail = tail->next;
        number++;
    }
    void clear() {
        clearRec(head);
    }

    iterator find(const T& data) const {
        for (iterator i = begin(); i != end(); ++i) {
            if (*i == data)
                return i;
        }

        return iterator();
    }
    iterator begin() const {
        return iterator(*this);
    }
    iterator end() const {
        return iterator();
    }

    T& operator[](size_t index) {
        iterator iter = begin();
        for (size_t i = 0; i < index; ++i) {
            if (iter == end())
                throw std::out_of_range("Error at indexing of list.");
            else
                ++iter;
        }
        return *iter;
    }

    T operator[](size_t index) const {
        iterator iter = begin();
        for (size_t i = 0; i < index; ++i) {
            if (iter == end())
                throw std::out_of_range("Error at indexing of list.");
            else
                ++iter;
        }
        return *iter;
    }
};

#endif // LIST_H
