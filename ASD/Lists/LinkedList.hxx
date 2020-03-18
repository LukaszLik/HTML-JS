#include <iostream>

using position_t = struct node*;


	struct node
	{
		int x;
		node* prev;
		node* next;
	};


class LinkedList
{
	// <---------------->>>
	node* head; // -------->>>
	node* tail; // <----------
	int current_size;

	public:

	LinkedList() : current_size(0), head(nullptr), tail(nullptr)
	{}

	~LinkedList()
	{
		while (current_size > 0)
		{
			pop_front();
		}
	}

	void push_front (int x)
	{
		if (current_size == 0)
		{
			node* new_node = new node;
			new_node -> x = x;

			new_node -> next = tail;
			new_node -> prev = nullptr;

			if (tail != nullptr)
			{
				tail -> prev = new_node;
			}			

			tail = new_node;
			head = new_node;
			current_size++;
		}
		
		else
		{
			node* new_node = new node;
			new_node -> x = x;

			new_node -> next = tail;
			tail -> prev = new_node;
			new_node -> prev = nullptr;

			tail = new_node;
			current_size++;
		}
	}

	void push_back(int x)
	{
		if (current_size == 0)
		{
			push_front(x);
		}
		
		else
		{
			node* new_node = new node;
			new_node -> x = x;

			new_node -> next = nullptr;
			new_node -> prev = head;
			
			head -> next = new_node;

			head = new_node;
			current_size++;
		}

	}
	
	int pop_front()
	{
		if (current_size > 1)
		{
			node* old_node = tail;
		
			tail = old_node -> next;
			tail -> prev = nullptr;

			int val = old_node -> x;
			delete old_node;
			
			current_size--;

			//if (size == 0)
			//	tail = nullptr;
			
			return val;
		}
	
		if (current_size == 1)
		{
			int val = tail -> x;
			
			delete tail;

			tail = nullptr;
			head = nullptr;
			
			current_size--;

			return val;
		}
	}

	int pop_back()
	{
		if (current_size > 1)
		{
			node* old_node = head;

			head = old_node -> prev;
			head -> next = nullptr;

			int val = old_node -> x;

			delete old_node;

			current_size--;

			return val;
		}

		else if (current_size == 1)
		{
			pop_front();
		}

	}

	position_t find(int x)
	{
		node* current_node = tail;

		while (current_node != nullptr)
		{
			if (current_node -> x == x)
				return current_node;

			current_node = current_node -> next;
		}

		return nullptr;
	}

	position_t erase (position_t pos)
	{
		(pos -> next) -> prev = pos -> prev;
		(pos -> prev) -> next = pos -> next;
		
		current_size--;
		delete pos;
		return pos -> prev;
	}
	
	position_t insert (position_t pos, int x)
	{
		node* new_node = new node;

		new_node -> x = x;
		
		if ((pos -> next) == nullptr)
		{
			pos -> next = new_node;
			new_node -> prev = pos;	
			new_node -> next = nullptr;
			head = new_node;
		}		

		else
		{
			new_node -> prev = pos;
			new_node -> next = (pos -> next);
			
			(pos -> next) -> prev = new_node;
			pos -> next = new_node;
		}	

		current_size++;

		return new_node;
	}

	int size()
	{
		return current_size;
	}

	bool empty()
	{
		if (size() == 0)
			return true;

		else
			return false;
	}

};
