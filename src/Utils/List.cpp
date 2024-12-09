/*
Implementation of a doubly linked list

iterating the list

for (node<type> *n = l.begin(); n != l.end(); n = n->next())
{
    ...
}

*/

#include "List.h"

template <typename type>
node<type>* node<type>::next() const
{
    if (this == origin->tail)
        return nullptr;

    return next_node;
}

template <typename type>
node<type>* node<type>::prev() const
{
    if (this == origin->head)
        return nullptr;

    return prev_node;
}

template <typename type>
list<type>::list()
{
    size = 0;

    head = new node<type>({}, nullptr, nullptr, this);
    tail = new node<type>({}, nullptr, nullptr, this);

    head->next_node = tail;
    head->prev_node = nullptr;

    tail->next_node = nullptr;
    tail->prev_node = head;
}

template <typename type>
list<type>::list(const list<type> &other)
{
    size = 0;

    head = new node<type>({}, nullptr, nullptr, this);
    tail = new node<type>({}, nullptr, nullptr, this);

    head->next_node = tail;
    head->prev_node = nullptr;

    tail->next_node = nullptr;
    tail->prev_node = head;

    push_back_list(other);
}

template <typename type>
list<type>::~list()
{
    clear();
    delete head;
    delete tail;
}

template <typename type>
void list<type>::operator= (const list<type> &other)
{
    clear();
    push_back_list(other);
}

template <typename type>
void list<type>::push_back(type elem)
{
    node<type> *new_node = new node<type>(elem, tail, tail->prev_node, this);

    tail->prev_node->next_node = new_node;
    tail->prev_node = new_node;

    size++;
}

template <typename type>
void list<type>::push_back(node<type> *n)
{
    if (n == nullptr || n->origin == this || n->origin != nullptr)
        return;
    
    n->origin = this;

    tail->prev_node->next_node = n;
    tail->prev_node = n;

    size++;
}

template <typename type>
void list<type>::push_front(type elem)
{
    node<type> *new_node = new node<type>(elem, head->next_node, head, this);

    head->next_node = new_node;
    new_node->next_node->prev_node = new_node;

    size++;
}

template <typename type>
void list<type>::push_front(node<type> *n)
{
    if (n == nullptr || n->origin == this || n->origin != nullptr)
        return;
    
    n->origin = this;

    head->next_node = n;
    n->next_node->prev_node = n;

    size++;
}

template <typename type>
void list<type>::push_back_list(const list<type> &other)
{
    if (other.empty())
        return;

    node<type> *n = other.begin();
    while (n != other.end())
    {
        push_back(n->elem);
        n = n->next_node;
    }
}

template <typename type>
void list<type>::push_front_list(const list &other)
{
    if (other.empty())
        return;
    
    node<type> *n = other.end()->prev_node;
    while (n != other.begin()->prev_node)
    {
        push_front(n->elem);
        n = n->prev_node;
    }
}

template <typename type>
void list<type>::push_back_transfer_list(list<type> &other)
{
    if (other.empty())
        return;

    // Update the origin of the nodes being transferred
    node<type> *n = other.begin();
    while (n != other.end())
    {
        n->origin = this;
        n = n->next_node;
    }

    tail->prev_node->next_node = other.head->next_node;
    other.head->next_node->prev_node = tail->prev_node;

    tail->prev_node = other.tail->prev_node;
    other.tail->prev_node->next_node = tail;

    size += other.size;
    
    // Clear other list
    other.head->next_node = other.tail;
    other.tail->prev_node = other.head;
    other.size = 0;        
}

template <typename type>
void list<type>::push_front_transfer_list(list<type> &other)
{
    if (other.empty())
        return;
    
    // Update the origin of the nodes being transferred
    node<type> *n = other.begin();
    while (n != other.end())
    {
        n->origin = this;
        n = n->next_node;
    }

    head->next_node->prev_node = other.tail->prev_node;
    other.tail->prev_node->next_node = head->next_node;

    head->next_node = other.head->next_node;
    other.head->next_node->prev_node = head;

    size += other.size;
    
    // Clear other list
    other.head->next_node = other.tail;
    other.tail->prev_node = other.head;
    other.size = 0;        
}

template <typename type>
type list<type>::pop_back()
{
    if (size == 0)
        return {};
    
    node<type> *temp = tail->prev_node;
    type elem = temp->elem;

    tail->prev_node = tail->prev_node->prev_node;
    tail->prev_node->next_node = tail;
    size--;
    
    delete temp;
    return elem;
}

template <typename type>
type list<type>::pop_front()
{
    if (size == 0)
        return {};
    
    node<type> *temp = head->next_node;
    type elem = temp->elem;

    head->next_node = head->next_node->next_node;
    head->next_node->prev_node = head;
    size--;
    
    delete temp;
    return elem;
}

template <typename type> 
node<type>* list<type>::pop_node(node<type> *n)
{
    if (n == nullptr || n == head || n == tail || !in_list(n))
        return nullptr;
    
    n->prev_node->next_node = n->next_node;
    n->next_node->prev_node = n->prev_node;
    n->origin = nullptr;
    size--;
    
    return n;
}

template <typename type>
void list<type>::remove(type elem)
{
    for (node<type> *i = begin(); i != end();)
    {
        if (i->elem == elem)
        {
            node<type> *temp = i;
            i = i->next_node;
            
            temp->prev_node->next_node = temp->next_node;
            temp->next_node->prev_node = temp->prev_node;

            delete temp;
            size--;
        }
        else
            i = i->next_node;
    }
}

template <typename type>
void list<type>::clear()
{
    while (size > 0)
    {
        pop_front();
    }
}