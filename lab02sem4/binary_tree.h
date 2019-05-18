#pragma once
#include "node.h"
#include <string>
#include <iostream>
#include <list>

template<typename T>
class binary_tree
{
private:
	node<T>* delete_node(node<T>* n);
	void counter(int c, int& count, std::list<T>& l, node<T>* node);
	void counter(std::list<T>& l, node<T>* node);
	node<T>* head_;
public:
	void add(T data);
	std::list<T> counting(int c);
	binary_tree(const binary_tree&) = delete;
	binary_tree(binary_tree&&) = delete;
	binary_tree& operator=(binary_tree&&) = delete;
	binary_tree& operator=(const binary_tree&) = delete;

	std::list<T> all();

    binary_tree(node<T>* n = nullptr) : head_(n){}
	~binary_tree();
};

template <typename T>
std::list<T> binary_tree<T>::all()
{
	std::list<T> l;

	counter(l, head_);

	return l;
}

template <typename T>
binary_tree<T>::~binary_tree()
{
	delete head_;
}

template <typename T>
void binary_tree<T>::add(T data)
{
	node<T>* tmp = head_, *p = nullptr;
	if (!tmp)
	{
		head_ = new node<T>(data);
		return;
	}

	while (true)
	{
		if (data < tmp->get_data())
		{
			if (tmp->get_left())
			{
				tmp = tmp->get_left();
				continue;
			}
			tmp->set_left(new node<T>(data, tmp, p));
			return;
		}
		if (data > tmp->get_data())
		{
			if (tmp->get_right())
			{
				tmp = tmp->get_right();
				continue;
			}
			tmp->set_right(new node<T>(data, tmp, p));
			return;
		}
		if (data == tmp->get_data()) return;
		p = tmp;
	}
}

template <typename T>
std::list<T> binary_tree<T>::counting(int c)
{
	int count = 0;
	std::list<T> l;

	counter(c, count, l, head_);

	return l;
}

template <typename T>
void binary_tree<T>::counter(int c, int& count, std::list<T>& l, node<T>* node)
{
    if (!node) return;

	counter(c, count, l, node->get_left());
	++count;
	if (count%c == 0) 
	{
		l.push_back(node->get_data());
		node = delete_node(node);
	}
	if (node) counter(c, count, l, node->get_right());
}

template <typename T>
void binary_tree<T>::counter(std::list<T>& l, node<T>* node)
{
	if (!node) return;
	counter(l, node->get_left());
	l.push_back(node->get_data());
	counter(l, node->get_right());
}

template <typename T>
node<T>* binary_tree<T>::delete_node(node<T>* n)
{
	if (!n) return nullptr;
	if (!(n->get_left() || n->get_right()))
	{
		if (n->get_parent())
		{
			if (n->is_left())
			{
				n->get_parent()->set_left(nullptr);
			}
			else
			{
				n->get_parent()->set_right(nullptr);
			}
		}
		else
		{
			head_ = nullptr;
		}
		delete n;
		return nullptr;
	}

	if (static_cast<bool>(n->get_left()) ^ static_cast<bool>(n->get_right()))
	{
		node<T>* p = n->get_parent(), *removed_node;
        if (n->get_left())
		{
			removed_node = n->get_left();
		}
        else
		{
			removed_node = n->get_right();
		}
		if (p)
		{
			if (n->is_left()) p->set_left(removed_node);
			else p->set_right(removed_node);
			
		}
		else
		{
			head_ = removed_node;
		}
		removed_node->set_parent(p);
		n->clear();
		delete n;
		return removed_node;
    }

	if (n->get_left() && n->get_right())
	{
		if (!n->get_right()->get_left())
		{
			node<T>* tmp = n->get_right();
			n->set_data(tmp->get_data());
			n->set_right(tmp->get_right());
			tmp->clear();
			delete tmp;
			return n;
		}
		else
		{
			node<T>* tmp = n->get_right()->get_deep_left();
			n->set_data(tmp->get_data());
			delete_node(tmp);
			return n;
		}
	}
	return nullptr;
}
