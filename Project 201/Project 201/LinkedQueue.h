#include <iostream>
#include "Event.h"

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H
using namespace std;


class Node_Queue
{
private:
    Event* value;
    Node_Queue* next;

public:
    Node_Queue()
    {
        next = nullptr;
    }
    Node_Queue(Event* newvalue)
    {
        value = newvalue;
        next = nullptr;
    }
    void setvalue(Event* newvalue)
    {
        value = newvalue;

    }
    void setnext(Node_Queue* newptr)
    {
        next = newptr;
    }
    Event* getvalue()
    {
        return value;
    }

    void getit()
    {
        cout << value;
    }

    Node_Queue* getnext() const
    {
        return next;
    }
};



class LinkedQueue
{
    Node_Queue* backptr;
    Node_Queue* frontptr;
public:
    LinkedQueue()
    {
        backptr = nullptr;
        frontptr = nullptr;
    }
    void Print_Queue_events() {
        std::cout << "\nPrinting Queue contents:\n";
        Node_Queue* ptr = frontptr;

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
    Node_Queue* getfront()
    {
        return frontptr;
    }
    Node_Queue* getback()
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

    bool enqueue(Event* item)
    {
        Node_Queue* newnode = new Node_Queue(item);
        if (isEmpty()) frontptr = backptr = newnode;
        else backptr->setnext(newnode);

        backptr = newnode;
        return true;
    }
    Event* dequeue()
    {
        Node_Queue* ptr = frontptr;
        if (isEmpty()) return ptr->getvalue();
        frontptr = frontptr->getnext();
        if (frontptr == nullptr) backptr = nullptr;
        Event* temp = ptr->getvalue();

        delete ptr;
        return temp;
    }

    Event* peek_Event() const
    {
        Event* item;
        if (isEmpty()) return nullptr;
        item = frontptr->getvalue();

        return item;
    }
    Event* peek_Next_Event() const
    {
        Event* item;
        if (isEmptyNext()) return nullptr;
        item = frontptr->getnext()->getvalue();
        return item;
    }

    bool peek(Event* item) const
    {
        if (isEmpty()) return false;
        item = frontptr->getvalue();
        return true;
    }
    ~LinkedQueue() { }
};

#endif
