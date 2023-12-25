#include <iostream>
#include "Event.h"
#include "Node.h"

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H
using namespace std;



template<typename t>
class LinkedQueue
{
    Node<t>* backptr;
    Node<t>* frontptr;
public:
    LinkedQueue()
    {
        backptr = nullptr;
        frontptr = nullptr;
    }
    void Print_Queue_events() {
        std::cout << "\nPrinting Queue contents:\n";
        Node<t>* ptr = frontptr;

        while (ptr)
        {
            cout << "I am in the print que function " << endl;
            cout << "event is  " << ptr->getvalue()->get_event_type() << endl;
            cout << " type is  " << ptr->getvalue()->get_type_of_passenger() << endl;
            cout << " special  " << ptr->getvalue()->get_special_type() << endl;
            cout << " id is  " << ptr->getvalue()->get_id() << endl;
            cout << "start station is  " << ptr->getvalue()->get_sstation() << endl;
            cout << "l station is  " << ptr->getvalue()->get_l_station() << endl;
            cout << "hour is  " << ptr->getvalue()->get_hour() << endl;
            cout << " minute is  " << ptr->getvalue()->get_minute() << endl << '\n';
            cout << endl;
            ptr = ptr->getnext();
        }
    }
    Node<t>* getfront()
    {
        return frontptr;
    }
    Node<t>* getback()
    {
        return backptr;
    }
    bool isEmpty() const
    {
        return frontptr == nullptr;
    }

    bool isEmptyNext() const
    {
        return frontptr->getnext() == nullptr;
    }

    bool enqueue(t item)
    {
        Node<t>* newnode = new Node<t>(item);
        if (isEmpty()) frontptr = backptr = newnode;
        else backptr->setnext(newnode);

        backptr = newnode;
        return true;
    }
    t dequeue()
    {
        Node<t>* ptr = frontptr;
        if (isEmpty()) return ptr->getvalue();
        frontptr = frontptr->getnext();
        if (frontptr == nullptr) backptr = nullptr;
        t temp = ptr->getvalue();

        delete ptr;
        return temp;
    }

    t peek_Event() const
    {
        t item;
        if (isEmpty()) return nullptr;
        item = frontptr->getvalue();

        return item;
    }
    t peek_Next_Event() const
    {
        t item;
        if (isEmptyNext()) return nullptr;
        item = frontptr->getnext()->getvalue();
        return item;
    }

    bool peek(t item) const
    {
        if (isEmpty()) return false;
        item = frontptr->getvalue();
        return true;
    }
    ~LinkedQueue() { }
};

#endif
