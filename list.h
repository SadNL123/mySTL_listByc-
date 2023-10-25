#pragma once
#include<iostream>
using namespace std;

template<class type>
class list
{
private:
	class node
	{
	public:
		type value;
		node* nextElementAddress;
		node* lastElementAddress;
		node(type v,node* lastA,node* nextA)
		{
			value = v;
			nextElementAddress = nextA;
			lastElementAddress = lastA;
		}
	};
	node* firstPostion;
	node* lastPostion;
	int list_size;
public:

	class iterator
	{
	public:
		node* ite;
		iterator()
		{

		}
		iterator& operator=(node* postion)
		{
			ite = postion;
			return *this;
		}

		iterator& operator++()
		{
			
			this->ite = this->ite->nextElementAddress;
			return *this;
		}
		type& operator*()
		{
			return ite->value;
		}
		iterator& operator--()
		{
			
			this->ite = this->ite->lastElementAddress;
			return *this;
		}
		bool operator!=(iterator ano)
		{
			if (this->ite == ano.ite)
			{
				return false;
			}
			else
				return true;
		}
	};
	list()
	{
		firstPostion = NULL;
		lastPostion = NULL;
		list_size = 0;
	}
	~list()
	{
		node* currentPostion = firstPostion;
		while (currentPostion != NULL)
		{
			node* nextNode = currentPostion->nextElementAddress;
			delete currentPostion;
			currentPostion = nextNode;
		}
	}
	void push_back(type v)
	{
		if (list_size==0)
		{
			node* temp = new node(v, NULL, NULL);
			firstPostion = temp;
			lastPostion = temp;
			list_size++;
		}
		else
		{
			node* temp = new node(v,lastPostion, NULL);
			(*lastPostion).nextElementAddress = temp;
			lastPostion = temp;
			list_size++;
		}
	}
	void push_front(type v)
	{
		if (list_size == 0)
		{
			node* temp = new node(v, NULL, NULL);
			firstPostion = temp;
			lastPostion = temp;
			list_size++;
		}
		else
		{
			node* temp = new node(v, NULL, firstPostion);
			firstPostion->lastElementAddress = temp;
			firstPostion = temp;
			list_size++;
		}
	}
	
	type front()
	{
		return (*firstPostion).value;
	}
	type back()
	{
		return (*lastPostion).value;
	}

	void clear() 
	{
		node* currentPostion = firstPostion;
		while (currentPostion != NULL)
		{
			node* nextNode = currentPostion->nextElementAddress;
			delete currentPostion;
			currentPostion = nextNode;
		}
		firstPostion = NULL;
		lastPostion = NULL;
		list_size = 0;
	}
	
	iterator begin()
	{
		iterator temp;
		temp.ite = firstPostion;
		return temp;
	}
	iterator end()
	{
		iterator temp;
		temp.ite = lastPostion->nextElementAddress;
		return temp;
	}
	void pop_back()
	{
		if (list_size == 0)
		{
			return;
		}
		else if (list_size == 1)
		{
			delete firstPostion;
			firstPostion = NULL;
			lastPostion = NULL;
			list_size--;
			return;
		}
		lastPostion->lastElementAddress->nextElementAddress = NULL;
		node* temp = lastPostion->lastElementAddress;
		delete lastPostion;
		lastPostion = temp;
		list_size--;
		return;
	}
	void pop_front()
	{
		if (list_size == 0)
		{
			return;
		}
		else if (list_size == 1)
		{
			delete firstPostion;
			firstPostion = NULL;
			lastPostion = NULL;
			list_size--;
			return;
		}
		firstPostion->nextElementAddress->lastElementAddress = NULL;
		node* temp = firstPostion->nextElementAddress;
		delete firstPostion;
		firstPostion = temp;
		list_size--;
		return;
	}


	node* search(type ele)
	{
		node* temp = firstPostion;
		while (1)
		{
			if (temp == lastPostion->nextElementAddress)
			{
				return NULL;
			}
			else
			{
				if (temp->value == ele)
				{
					return temp;
				}
				else
				{
					temp = temp->nextElementAddress;
				}
			}
		}
	}

	void erase(iterator begin, iterator end)
	{
		node* target1 = begin.ite;
		node* target2 = end.ite;
		if (target1 == NULL || target2 == NULL)
		{
			return;
		}
		else
		{
			if (target1 == firstPostion&&target2!=lastPostion)
			{
				firstPostion = target2->nextElementAddress;
			}
			else if (target2 == lastPostion && target1 != firstPostion)
			{
				lastPostion = target1->lastElementAddress;
			}
			else if(target2==lastPostion&&target1==firstPostion)
			{
				clear();
				return;
			}
			target1->lastElementAddress->nextElementAddress = target2->nextElementAddress;
			target2->nextElementAddress->lastElementAddress = target1->lastElementAddress;
			node* temp = target1;
			while (1)
			{
				if (temp == end.ite->nextElementAddress)
					break;
				node* newtemp = temp->nextElementAddress;
				delete temp;
				list_size--;
				temp = newtemp;
			}
		}
	}




	void erase(iterator pos)
	{
		node* target = pos.ite;
		if (target == NULL)
			return;
		else if (target == firstPostion)
		{
			firstPostion = firstPostion->nextElementAddress;
		}
		else if (target == lastPostion)
		{
			lastPostion = lastPostion->lastElementAddress;
		}
		else {
			target->lastElementAddress->nextElementAddress = target->nextElementAddress;
			target->nextElementAddress->lastElementAddress = target->lastElementAddress;
			delete target;
			list_size--;
			return;
		}
	}
	void remove(type ele)
	{
		node* target = search(ele);
		if (target == NULL)
			return;
		else
		{
			target->lastElementAddress->nextElementAddress = target->nextElementAddress;
			target->nextElementAddress->lastElementAddress = target->lastElementAddress;
			delete target;
			return;
			list_size--;
		}
	}
	void insert(iterator pos, type ele)
	{
		node* target = pos.ite;
		if (target == NULL)
		{
			return;
		}
		else
		{
			node* temp = new node(ele, target->lastElementAddress, target);
			list_size++;
			target->lastElementAddress->nextElementAddress = temp;
			target->lastElementAddress = temp;
		}
	}
	int size()
	{
		return list_size;
	}
};
