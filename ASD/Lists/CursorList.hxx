/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CursorList.hxx
 * Author: fresh222
 *
 * Created on November 17, 2018, 4:41 PM
 */

#ifndef CURSORLIST_H
#define CURSORLIST_H

#include <iostream>
#include <list>

using position_t = int;

class CursorList
{

	struct node
	{
		int x;
		int next;
	};

	node *arr;
	int current_size;
	int arr_size;
	int head; // indeks pierwszego wezla
	int next_free;

public:
	CursorList() : head(-1), arr_size(15), current_size(0), next_free(0)
	{

		arr = new node [arr_size];
		for (int i = 0 ; i < arr_size; i++)
		{
			arr[i].next = i + 1;
			arr[i].x = -5;	
		}
	}

    CursorList(int N) : head(-1), arr_size(N), current_size(0), arr (new node [arr_size]), next_free(0)
	{
		arr = new node [arr_size];
		for (int i = 0 ; i < arr_size; i++)
		{
			arr[i].next = i + 1;
			arr[i].x = -5;	
		}
    

	}

void push_front(int x)
    {	 
	if (current_size == 0)
        {
            int free = next_free; // kolejny wolny wezel
            next_free = arr[next_free].next;   
        
            arr[free].x = x;
            arr[free].next = -1;
            
            head = free;
            current_size++;
            
        }
    
        else if (current_size < arr_size)
        {
            int free = next_free; // kolejny wolny wezel
            next_free = arr[next_free].next;    
        
            arr[free].x = x;
            arr[free].next = head;
            
            head = free;
            current_size++;
        }
    }
    
    int pop_front()
    {

        if (current_size == 1)
        {
            int ret_val = arr[head].x;
            int lastfree_pos;
            int freeiter = next_free;
            
            arr[head].x = -6;
            arr[head].next = -1;
            
            while (freeiter != arr_size) // wpisywanie wolnego wezla na koniec listy
            {
  
                lastfree_pos = freeiter;
                freeiter = arr[freeiter].next;
            }
            
            arr[lastfree_pos].next = head;
            arr[head].next = arr_size;
            
            head = -1;
            current_size--;
            
            return ret_val;
        }
    
        else
        {
            int ret_val = arr[head].x;
            int next_pos = arr[head].next;
            int lastfree_pos;
            int freeiter = next_free;
		              

            arr[head].x = -7;
            //arr[head].next = -1;
            
            while (freeiter != arr_size) // wpisywanie wolnego wezla na koniec
            {
  
                lastfree_pos = freeiter;
                freeiter = arr[freeiter].next;
            }
            
            arr[lastfree_pos].next = head;
            arr[head].next = arr_size;
            
            head = next_pos;
            current_size--;
                    
            return ret_val;
        }
    }
    
    void push_back(int x)
    {


        if (current_size == 0)
        {
            push_front(x);
        }
        
        else if (current_size < arr_size)
        {
            int free = next_free; // kolejny wolny wezel
            next_free = arr[next_free].next;      
            
            int next_pos = head;
            
            while (arr[next_pos].next != -1)
            {
               // prev_pos = next_pos
                next_pos = arr[next_pos].next;
            }
            
            arr[free].x = x;
            arr[free].next = -1;
        
            arr[next_pos].next = free;
            current_size++;
        }
    }
    
    int pop_back()
    {

        if (current_size == 1)
        {
            return pop_front();
        }
        
        else
        {
            int prev_pos = head;
            int next_pos = arr[head].next;
            int lastfree_pos;
            int freeiter = next_free;
            
            while (arr[next_pos].next != -1)
            {
                prev_pos = next_pos;
                next_pos = arr[next_pos].next;
            }
        
            int ret_val = arr[next_pos].x;
            
            while (freeiter != arr_size) // adding node to free list
            {
  
                lastfree_pos = freeiter;
                freeiter = arr[freeiter].next;
            }
            
            arr[lastfree_pos].next = next_pos;
            arr[next_pos].next = arr_size;
            
            arr[next_pos].x = -8;
            //arr[next_pos].next = -1;
            
            arr[prev_pos].next = -1;
            
		current_size--;

            return ret_val;
        }
        
    }

    position_t find (int x)
    {
	if(current_size == 0)
		return -1;


	//test();
        int next = head;

        while (arr[next].next != -1)
        {
            if (arr[next].x == x)
                return next;
	
            next = arr[next].next;
        }

        return -1;
    }

    position_t erase(position_t pos)
    {

        if (pos == head)
        {
            pop_front();
            return head;
        }

        int next = head;
        int last_pos;

        while( arr[next].next != -1)
        {
            if (arr[next].next == pos)
            {
                arr[last_pos].next = arr[next].next;
                arr[next].next = -1;
                arr[next].x = 0;

                current_size--;
                return arr[last_pos].next;
            }

            last_pos = next;
            next = arr[next].next;
        }

        return -1;
    }

    position_t insert(position_t pos, int x)
    {
        int free = next_free;
        next_free = arr[next_free].next;    
        
        int next = head;
        int last_pos;

        while (arr[next].next != -1)
        {
            if (arr[next].next == pos)
            {
                arr[free].x = x;
                arr[free].next = arr[next].next;

                arr[last_pos].next = free;

                current_size++;
                free++;

                return arr[next].next;
            }
		last_pos = next;
            next = arr[next].next;
        }
        return -1;
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

    void test()
	{
        std::cout << "head = " << head << "\nfree = " << next_free << "\n";
		for (int i = 0; i < arr_size; i++)
		{
			std::cout << "[" << i << "]" << "   " << arr[i].x << " " << arr[i].next << "\n";
		
			//if (arr[i].next == -1 && i > head)
			//	break;
		}
	}

};


#endif // CURSORLIST_H


