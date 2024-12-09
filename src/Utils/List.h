/*
iterating the list

for (node<type> *n = l.begin(); n != l.end(); n = n->next())
{
    ...
}

*/

#include <memory>
#include <stdexcept>

template <typename type>
class list;

template <typename type>
class node
{
    private:
        node<type> *next_node;
        node<type> *prev_node;
        list<type> *origin;
    
        friend class list<type>;

    public:
        type elem;

        node(type elem, node *next, node *prev, list<type> *origin) : elem(elem), next_node(next), prev_node(prev), origin(origin) {}

        /* Returns the next node of `n` */
        node<type>* next() const;

        /* Returns the previous node of `n` */
        node<type>* prev() const;
};

template <typename type>
class list
{
    private:
        size_t size;
        node<type> *head;
        node<type> *tail;

        friend class node<type>;

    public:
        list();
        list(const list<type> &other);
        ~list();

        void operator= (const list<type> &other);

        /* Returns the size of the list */
        size_t get_size() const { return size; }

        /* Returns true if the list is empty, else returns false */
        bool empty() const { return size == 0; }

        /* Returns true if the node is part of the list, else returns */
        bool in_list(const node<type> *n) const { return n->origin == this; }

        /* Returns the first element of the list */
        node<type>* begin() const { return head->next_node; }

        /* Returns the tail (after the last element) of the list */
        node<type>* end() const { return tail; }

        /* Insert `elem` to the end of the list */
        void push_back(type elem);
        
        /* 
         * inserts `n` to the end of the list
         * `n` must not be part of any list, including this
         */
        void push_back(node<type> *n);

        /* Insert `elem` to the begining of the list */
        void push_front(type elem);

        /*
         * inserts `n` to the begining of the list
         * `n` must not be part of any list, including this
         */
        void push_front(node<type> *n);
        
        /* Insert copies of `other`'s elements to the end of this list */
        void push_back_list(const list<type> &other);

        /* Insert copies of the `other`'s elements to the begining of this list */
        void push_front_list(const list &other);

        /* 
         * Insert the elements of `other`'s elements to the end of this list
         * and empties `other`
         */
        void push_back_transfer_list(list<type> &other);

        /* 
         * Insert the elements of `other`'s elements to the begining of this list
         * and empties `other`
         */
        void push_front_transfer_list(list<type> &other);

        /* Removes the last element */
        type pop_back();

        /* Removes the first element */
        type pop_front();

        /* 
         * Removes `n` if it belongs to this list 
         * `n` must be manually deleted by the user 
         */
        node<type>* pop_node(node<type> *n);

        /* Removes all the occurences of `elem` */
        void remove(type elem);

        /* Removes all the elements */
        void clear();
};