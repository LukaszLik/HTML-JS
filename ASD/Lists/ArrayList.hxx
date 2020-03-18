#include <iostream>
#include <cstdlib>

using position_t = int;

class ArrayList
{
	int *arr;
	int arr_size;
	int current_size;
	


public:
	ArrayList() : arr_size(10), current_size(0)
	{
		arr = new int [arr_size];
	}

	ArrayList (int N) : arr_size(N), current_size(0)
	{
		arr = new int [arr_size];	
	}

	void push_front (int x) // inserts element at the begining
	{	
		if (current_size > 0)
		{
			for (int i = current_size - 1; i >= 0; i--)
				arr[i+1] = arr[i]; 

			arr[0] = x;
			
			current_size++;
		}
		
		else
		{
			arr[0] = x; // if current_size == 0
			current_size++;
		}
	}	

	int pop_front()
	{
		int return_val;
		int temp;
		
		if (current_size == 0)
		{
			exit(-2);
		}

		if (current_size > 1)
		{
			return_val = arr[0];
			
			for (int i = 0; i < current_size; i++)
				arr[i] = arr[i+1];
			
			current_size--;

			return return_val;
		}
		
		else
		{
			current_size--;
			return arr[0];
		}	
	}

	void push_back(int x)
	{
		arr[current_size] = x;
		current_size++;
	}

	int pop_back()
	{
		
		if (current_size == 0)
		{
			exit(-2);
		}
		
		else
		{
			current_size--;
			return arr[current_size];
		}
	}

	position_t find (int x)
	{
		for (int i = 0; i < current_size; i++)
			if (arr[i] == x)
				return i;

		return -1;
	}

	position_t erase (position_t pos)
	{
		for (int i = pos; i < current_size - 1; i++)
			arr[i] = arr[i+1];
		
		current_size--;
		return pos;
	}

	position_t insert (position_t pos, int x)
	{
		for (int i = current_size - 1; i > pos; i--)
			arr[i+1] = arr[i];
		
		arr[pos] = x;
		current_size++;
		return pos;
	}

	int size()
	{
		return current_size;
	}

	bool empty()
	{
		if (size() == 0)
			return true;
		
		return false;
	}

};
