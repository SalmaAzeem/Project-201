#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include "Passenger.h"
#include<iostream>
using namespace std;

template<typename t>
class LinkedList
{
private:
    Node<t>* head;

public:

    LinkedList() { head = nullptr; }
    LinkedList(Node<t>* a)
    {
        head = a;
    }
    ~LinkedList()
    {
        DeleteAll();
    }
    Node<t>* gethead() {
        return head;
    }
    void sethead(t value)
    {
        head->setvalue(value);
    }
    Node<t>* GetNodeInPlace(int place) {
        Node<t>* ptr = this->head;
        if (ptr != nullptr)
            for (int i = 0; i < place; i++)   ptr = ptr->getnext();
        return ptr;
    }

    void insertend(t item) {
        Node<t>* newNode = new Node<t>(item);
        Node<t>* ptr = this->head;
        if (ptr == nullptr)
        {
            this->head = newNode;
        }
        else
        {
            while (ptr->getnext() != nullptr)
            {
                ptr = ptr->getnext();
            }

            ptr->setnext(newNode);
        }

    }
    void insertNode(Node<t>* a) {
        Node<t>* ptr = this->head;
        if (ptr == nullptr)
        {
            this->head = a;
        }
        else
        {
            while (ptr->getnext() != nullptr)
            {
                ptr = ptr->getnext();
            }

            ptr->setnext(a);
        }
    }

    bool InsertSortedDesc(Passenger* obj)
    {
        Node<t>* newNode = new Node<t>(obj);
        Node<t>* ptr = this->head;

        if (this->head == nullptr || obj->getLeaveStationId() > ptr->getvalue()->getLeaveStationId())
        {
            newNode->setnext(this->head);
            this->head = newNode;
            return true;
        }

        while (ptr != nullptr)
        {
            if (ptr->getnext() == nullptr || (ptr->getvalue()->getLeaveStationId() > obj->getLeaveStationId() && (ptr->getnext() == nullptr || obj->getLeaveStationId() > ptr->getnext()->getvalue()->getLeaveStationId())))
            {
                newNode->setnext(ptr->getnext());
                ptr->setnext(newNode);
                return true;
            }
            else {
                ptr = ptr->getnext();
            }
        }
        return true;
    }

    bool InsertSorted(Passenger* obj)
    {
        Node<t>* newNode = new Node<t>(obj);
        Node<t>* ptr = this->head;

        if (this->head == nullptr || obj->getLeaveStationId() < ptr->getvalue()->getLeaveStationId())
        {
            newNode->setnext(this->head);
            this->head = newNode;
            return true;
        }

        while (ptr != nullptr)
        {
            if (ptr->getnext() == nullptr || (ptr->getvalue()->getLeaveStationId() < obj->getLeaveStationId() && (ptr->getnext() == nullptr || obj->getLeaveStationId() < ptr->getnext()->getvalue()->getLeaveStationId())))
            {
                newNode->setnext(ptr->getnext());
                ptr->setnext(newNode);
                return true;
            }
            else {
                ptr = ptr->getnext();
            }
        }
        return true;
    }
    bool Find(t item) {
        Node<t>* ptr = this->head;
        bool there;
        while (ptr != nullptr)
        {
            if (ptr->getvalue() == item)  there = true;
            ptr = ptr->getnext();

        }
        delete ptr;
        return there;
    }


    void RecPrint(Node<t>* ptr) {
        cout << "I am in RecPrint" << endl;
        if (ptr == nullptr) return;
        cout << (ptr->getvalue()) << "\t";
        RecPrint(ptr->getnext());
        return;
    }

    void RecPrint() {
        RecPrint(this->head);
    }



    bool DeleteNode(t item) {
        bool found = this->Find(item);

        if (!found) return false;


        if (item == this->head->getvalue())
        {
            this->head = this->head->getnext();
            return true;
        }
        else {

            Node<t>* ptr = this->head;
            while (ptr->getnext()->getvalue() != item)
            {
                ptr = ptr->getnext();
            }

            Node<t>* temp = ptr->getnext();
            ptr->setnext(ptr->getnext()->getnext());
            delete temp;
            return true;
        }
    }

    void DeleteAll() {
        Node<t>* P = head;
        while (head)
        {
            P = head->getnext();
            delete head;
            head = P;
        }
    }

};


#endif
