#pragma once
#include <vector>


template<typename T>
class node
{
private:
	T data_;
	node* parent_;
	node* left_;
	node* right_;
public:
	node(T data, node* parent = nullptr, node* left = nullptr, node* right = nullptr) : 
		data_(data), parent_(parent), left_(left), right_(right) {}
	node(const node&) = default;
	node(node&& n) noexcept;
	node& operator=(node&& n) noexcept;
	node& operator=(const node&) = delete;
	~node();

	T get_data();
	void set_data(T d);

	node* get_left() const;
	node* get_right() const;
	node* get_parent() const;
	node* get_deep_left();
	node* get_deep_right();

	void set_left(node* left);
	void set_right(node* right);
	void set_parent(node* parent);

	bool is_left();

	void swap(node<T>* n);
	void clear();
};

template <typename T>
node<T>::node(node&& n) noexcept
{
	std::swap(parent_, n->parent_);
	std::swap(left_, n->left_);
	std::swap(right_, n->right_);
	std::swap(data_, n->data_);
}

template <typename T>
node<T>& node<T>::operator=(node&& n) noexcept
{
	std::swap(parent_, n->parent_);
	std::swap(left_, n->left_);
	std::swap(right_, n->right_);
	std::swap(data_, n->data_);
	return this;
}

template <typename T>
node<T>::~node()
{
	delete left_;
	delete right_;
}

template <typename T>
T node<T>::get_data()
{
	return data_;
}

template <typename T>
void node<T>::set_data(T d)
{
	data_ = d;
}

template <typename T>
node<T>* node<T>::get_left() const
{
	return left_;
}

template <typename T>
node<T>* node<T>::get_right() const
{
	return right_;
}

template <typename T>
node<T>* node<T>::get_parent() const
{
	return  parent_;
}

template <typename T>
node<T>* node<T>::get_deep_left()
{
	if (left_) return left_->get_deep_left();
	return this;
}

template <typename T>
node<T>* node<T>::get_deep_right()
{
	if (right_) return  right_->get_deep_right();
	return this;
}

template <typename T>
void node<T>::set_left(node* left)
{
	left_ = left;
}

template <typename T>
void node<T>::set_right(node* right)
{
	right_ = right;
}

template <typename T>
void node<T>::set_parent(node* parent)
{
	parent_ = parent;
}

template <typename T>
bool node<T>::is_left()
{
	return parent_->get_left() == this;
}

template <typename T>
void node<T>::swap(node<T>* n)
{
	std::swap(parent_, n->parent_);
	std::swap(left_, n->left_);
	std::swap(right_, n->right_);
}

template <typename T>
void node<T>::clear()
{
	left_ = nullptr;
	right_ = nullptr;
	parent_ = nullptr;
}
