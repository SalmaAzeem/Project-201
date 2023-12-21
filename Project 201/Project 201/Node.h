#pragma once
#ifndef NODE_H
#define NODE_H

#include<iostream>
using namespace std;

template<typename t>
class Node
{
private:
    t value;
    Node<t>* next;

public:
    Node()
    {
        next = nullptr;
    }
    Node(t newvalue)
    {
        value = newvalue;
        next = nullptr;
    }
    void setvalue(t newvalue)
    {
        value = newvalue;

    }
    void setnext(Node<t>* newptr)
    {
        next = newptr;
    }
    t getvalue()
    {
        return value;
    }
    Node<t>* getnext() const
    {
        return next;
    }
};

#endif
