#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include "Passenger.h"
#include "Bus.h"

template <typename x>
class QNode {
public:
	x _Pointer_Object; //pointer to the object of the passenger
	int Priority;
	QNode<x>* Next;
	QNode() { Next = nullptr; }
	//QNode(const x& obj, QNode<x>* nextptr);
	QNode(x obj, int priority);
	void setPtrObj(x pointer_object);
	x getPtrObj() const;
	void setNext(QNode<x>* NextPtr);
	QNode<x>* getNext() const;
	void setPriority(int priority);
	int getPriority() const;
};

template <typename x>
void QNode<x>::setPriority(int priority) { this->Priority = priority; }
template <typename x>
int QNode<x>::getPriority() const { return Priority; }

//template<typename x>
//QNode<x>::QNode(const x& obj, QNode<x>* nextptr) {
//	this->_Pointer_Object_Passenger = obj;
//	this->Next = nextptr;
//}

template <typename x>
void QNode<x>::setPtrObj(x pointer_object) {
	this->_Pointer_Object = pointer_object;
}
template <typename x>
QNode<x>::QNode(x obj, int priority) {
	this->_Pointer_Object = obj;
	this->Priority = priority;
	this->Next = nullptr;
}

template <typename x>
x QNode<x>::getPtrObj() const { return _Pointer_Object; }

template <typename x>
void QNode<x>::setNext(QNode<x>* NextPtr) { Next = NextPtr; }

template <typename x>
QNode<x>* QNode<x>::getNext() const { return Next; }

//------------------------------------------------------------------------------------------------------------------------
//the queue implemented using linked list

template <typename x>
class Queue {
private:
	QNode<x>* Front;
	QNode<x>* Rear;
public:
	Queue() { Front = Rear = nullptr; }
	virtual bool Is_Empty() const = 0;
	virtual bool Peek(x obj)  const = 0;
	virtual void enQueue(x obj, int priority) = 0; //takes a pointer of the object of the passenger class as a parameter 
	virtual x deQueue() = 0;
	virtual void Print_Queue() const = 0;
	virtual int Count() const = 0;
	virtual bool Find(x obj) = 0;
};


class PriorityQueuePassenger : public Queue<Passenger*> {
private:

public:
	QNode<Passenger*>* Front;
	QNode<Passenger*>* Rear;
	PriorityQueuePassenger() {
		Front = Rear = nullptr;
	}
	bool Is_Empty() const override { return (Front == nullptr); }
	bool Peek(Passenger* obj) const override {
		if (Is_Empty()) { return false; }
		obj = Front->getPtrObj();
		return true;
	}
	void enQueue(Passenger* obj, int priority) override {
		//if the linked list is empty then it will only be one element therefore the front and rare are equal
		QNode<Passenger*>* NewNode = new QNode<Passenger*>(obj, priority);
		//the queue is empty or the new node has high prioriy than the front
		//then the new node hayeb2a fel front
		if (Is_Empty() || priority > this->Front->getPriority()) {
			NewNode->setNext(this->Front);
			this->Front = NewNode;
		}
		else {
			QNode<Passenger*>* CurPtr = this->Front;
			//hafdal adawar fel queue lhad ma ala2y heta ll node
			while (CurPtr->getNext() && priority <= CurPtr->getNext()->getPriority()) {
				CurPtr = CurPtr->getNext();
			}
			NewNode->setNext(CurPtr->getNext());
			CurPtr->setNext(NewNode);
		}
	}
	Passenger* deQueue() override {
		if (Is_Empty()) { std::cout << "Queue is Empty" << std::endl; } //the queue is empty
		Passenger* Passenger_Object = Front->getPtrObj();
		QNode<Passenger*>* DELETED = Front;
		if (Front == Rear) { Front = Rear = nullptr; }
		else {
			Front = Front->getNext();
		}
		delete DELETED;
		return Passenger_Object;
	}
	void Print_Queue() const override {
		std::cout << "\nPrinting Queue contents:\n";
		QNode<Passenger*>* ptr = Front;
		std::cout << "[ ";
		while (ptr)
		{
			std::cout << ptr->getPtrObj()->getId() << ", ";
			ptr = ptr->getNext();
		}
		std::cout << "]";
	}
	Passenger** get_array_passengers() const {
		int number_passengers = Count();
		Passenger** array = new Passenger * [number_passengers];
		QNode<Passenger*>* Ptr = Front;
		int count = 0;
		while (Ptr) {
			array[count] = Ptr->getPtrObj();
			count++;
			Ptr = Ptr->getNext();
		}
		return array;
	}

	int Count() const override {
		int count{};
		QNode<Passenger*>* CurPtr = Front;
		if (Is_Empty()) { return 0; }
		while (CurPtr) {
			count++;
			CurPtr = CurPtr->getNext();
		}
		return count;
	}
	bool Find(Passenger* obj) {
		QNode<Passenger*>* Ptr = Front;
		bool available = false;
		while (Ptr != nullptr) {
			if (Ptr->getPtrObj()->getId() == obj->getId()) {
				available = true;
			}
			Ptr = Ptr->getNext();
		}
		delete Ptr;
		return available;
	}

	bool Leave_Passenger(Passenger* obj) {
		bool available = Find(obj);
		if (!available) { return false; }
		if (obj->getId() == Front->getPtrObj()->getId()) {
			Front = Front->getNext();
		}
		else {
			QNode<Passenger*>* Ptr = Front;
			while (Ptr->getNext()->getPtrObj()->getId() != obj->getId()) {
				Ptr = Ptr->getNext();
			}
			QNode<Passenger*>* Temp = Ptr->getNext();
			Ptr->setNext(Ptr->getNext()->getNext());
			delete Temp;
			return true;
		}
	}
	//bool Leave_Passenger(Passenger* obj) {
	//	if (!Front) { return false; } //the queue is empty
	//	QNode<Passenger*>* CurPtr = Front;
	//	QNode<Passenger*>* DeletePtr = new QNode<Passenger*>;
	//	while (CurPtr) {
	//		if (CurPtr->getNext()->getPtrObj()->getId() == obj->getId()) {
	//			if (CurPtr == Front) { deQueue(); }
	//			else {
	//				DeletePtr = CurPtr->getNext();
	//				CurPtr->setNext(CurPtr->getNext()->getNext());
	//				delete DeletePtr;
	//				//DeletePtr = nullptr;
	//				return true;
	//				}
	//			}
	//			CurPtr = CurPtr->getNext();
	//		}
	//		return false;
	//}
	~PriorityQueuePassenger() {
		while (!Is_Empty()) { deQueue(); }
	}
};


class BusQueue : public Queue<Bus*> {
private:
	QNode<Bus*>* Front;
	QNode<Bus*>* Rear;
public:
	BusQueue() { Front = Rear = nullptr; }
	bool Is_Empty() const override { return (Front == nullptr); }
	bool Peek(Bus* obj) const override {
		if (Is_Empty()) { return false; }
		obj = Front->getPtrObj();
		return true;
	}
	void enQueue(Bus* BusObj, int priority) override {
		//if the linked list is empty then it will only be one element therefore the front and rare are equal
		QNode<Bus*>* NewNode = new QNode<Bus*>(BusObj, priority);
		//the queue is empty or the new node has high prioriy than the front
		//then the new node hayeb2a fel front
		if (Is_Empty() || priority > this->Front->getPriority()) {
			NewNode->setNext(this->Front);
			this->Front = NewNode;
		}
		else {
			QNode<Bus*>* CurPtr = this->Front;
			//hafdal adawar fel queue lhad ma ala2y heta ll node
			while (CurPtr->getNext() && priority <= CurPtr->getNext()->getPriority()) {
				CurPtr = CurPtr->getNext();
			}
			NewNode->setNext(CurPtr->getNext());
			CurPtr->setNext(NewNode);
		}
	}
	Bus* deQueue() override {
		if (Is_Empty()) { std::cout << "The Queue is empty." << "\n"; } //the queue is empty
		Bus* Bus_Object = Front->getPtrObj();
		QNode<Bus*>* DELETED = Front;
		if (Front == Rear) { Front = Rear = nullptr; }
		else {
			Front = Front->getNext();
		}
		delete DELETED;
		return Bus_Object;
	}
	void Print_Queue() const override {
		std::cout << "\nPrinting Queue contents:\n";
		QNode<Bus*>* ptr = Front;
		std::cout << "[ ";
		while (ptr)
		{
			std::cout << ptr->getPtrObj()->getId() << ", "; //-------------edit: add the id of the bus so it won't print the address of the pointer----------------
			ptr = ptr->getNext();
		}
		std::cout << "]";
	}

	int Count() const override {
		int count{};
		QNode<Bus*>* CurPtr = Front;
		if (Is_Empty()) { return 0; }
		while (CurPtr) {
			count++;
			CurPtr = CurPtr->getNext();
		}
		return count;
	}
	bool Find(Bus* obj) {
		QNode<Bus*>* Ptr = Front;
		bool available;
		while (Ptr != nullptr) {
			if (Ptr->getPtrObj() == obj) {
				available = true;
			}
			Ptr = Ptr->getNext();
		}
		delete Ptr;
		return available;
	}
	Bus* Peek_Bus() const
	{
		Bus* Bus;
		if (Is_Empty()) { return nullptr; }
		Bus = Front->getPtrObj();
		return Bus;
	}
};

#endif // !QUEUE
