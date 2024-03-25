#pragma once
#include <cassert>

// Dynamic queue - list implementation
class DynamicQueue
{
private:
	class QueueNode
	{
		friend class DynamicQueue;
		int value;
		QueueNode* next;

		QueueNode(int value, QueueNode* next = nullptr)
		{
			this->value = value;
			this->next = next;
		}
	};

	// These track the front and rear of the queue
	QueueNode* front;
	QueueNode* rear;

public:
	// Constructor and destructor
	DynamicQueue()
	{
		front = rear = nullptr;
	}
	
	~DynamicQueue()
	{
		Clear();
	}

	void Enqueue(int value)
	{
		if (IsEmpty())
		{
			front = new QueueNode(value);
			rear = front;
		}
		else
		{
			rear->next = new QueueNode(value);		// Creates the new node at the end of rear
			rear = rear->next;						// Moves to the new rear node
		}
	}

	int Dequeue()
	{
		assert(!IsEmpty());
		int value = front->value;
		QueueNode* temp = front;
		front = front->next;
		delete temp;
		return value;
	}

	bool IsEmpty() const
	{
		return (front == nullptr);
	}

	void Clear()
	{
		while (!IsEmpty())
		{
			Dequeue();
		}
	}
};
