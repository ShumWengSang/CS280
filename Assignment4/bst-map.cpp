#pragma once
#include <iostream>
#include "bst-map.h"
	namespace CS280
{
	// static data members
	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator
		CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::end_it = CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator(nullptr);

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const
		CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::const_end_it = CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const(
			nullptr);

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::Node* BSTmap<KEY_TYPE, VALUE_TYPE>::MakeNode(KEY_TYPE k,
		VALUE_TYPE val, BSTmap<KEY_TYPE, VALUE_TYPE>::Node* p, BSTmap<KEY_TYPE, VALUE_TYPE>::Node* l, BSTmap<KEY_TYPE, VALUE_TYPE>::Node* r, int h, int b)
	{
		++this->size_;
		return new Node(k, val, p, h, b, l, r);
	}

	// Node stuff
	template<typename KEY_TYPE, typename VALUE_TYPE>
	CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node::Node(KEY_TYPE k, VALUE_TYPE val, BSTmap::Node* p, int h, int b,
		BSTmap::Node* l,
		BSTmap::Node* r) : key(k), value(val), height(h), balance(b),
		parent(p),
		left(l), right(r)
	{

	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	KEY_TYPE const& CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node::Key() const
	{
		return key;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	VALUE_TYPE& CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::Node::Value()
	{
		return value;
	}


	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::Node* BSTmap<KEY_TYPE, VALUE_TYPE>::Node::last()
	{

		Node* node = this;
		while (node && node->right != nullptr)
			node = node->right;
		return node;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::Node* BSTmap<KEY_TYPE, VALUE_TYPE>::Node::first()
	{
		Node* node = this;
		while (node && node->left != nullptr)
			node = node->left;
		return node;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::Node*
		BSTmap<KEY_TYPE, VALUE_TYPE>::Node::decrement()
	{
		// Predecessor Function

		Node* predecessor;
		// If we have a left sub-tree
		if (this->left)
		{
			predecessor = this->left->last();
		}
		else
		{
			// Last right turn taken should be predecessors
			predecessor = FindPredecessor();
		}
		return predecessor;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::Node* BSTmap<KEY_TYPE, VALUE_TYPE>::Node::increment()
	{
		// Successor function.

		if (this->right) // IF right pointer is not null
		{
			// Find the minimum in the sub-tree at right side.
			// Sub tree is leftest
			return this->right->first();
		}
		else // If Right is null...
		{
			return FindSuccesor();
		}
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::Node* BSTmap<KEY_TYPE, VALUE_TYPE>::Node::FindSuccesor()
	{
		// Go up to parent
		Node* localparent = this->parent;
		if (localparent == nullptr)
			return localparent;

		// Check where we came from
		if (localparent->right == this) // If from right side.
		{
			return localparent->FindSuccesor();
		}
		else // We came from left side.
		{
			return localparent;
		}
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::Node*&
		BSTmap<KEY_TYPE, VALUE_TYPE>::Node::findNode(Node* node)
	{
		if (node->parent->right == node)
			return node->parent->right;
		else
			return node->parent->left;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	void BSTmap<KEY_TYPE, VALUE_TYPE>::Node::ShallowCopy(Node* lhs, Node* rhs)
	{
		lhs->balance = rhs->balance;
		lhs->height = rhs->height;
		lhs->key = rhs->key;
		lhs->value = rhs->value;
		lhs->left = rhs->left;
		lhs->right = rhs->right;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::Node*
		BSTmap<KEY_TYPE, VALUE_TYPE>::Node::FindPredecessor()
	{
		// Go up to parent
		Node* localparent = this->parent;
		if (localparent == nullptr)
			return localparent;

		// Check where we came from
		if (localparent->right == this) // If from right side.
		{
			return localparent;
		}
		else // We came from left side.
		{
			return localparent->FindPredecessor();
		}
	}

	//in implementation file 
	//method's name and return value have to be fully qualified with
	//all required namespace and class names (like CS280::BSTmap<KEY_TYPE,VALUE_TYPE>::BSTmap)
	//but the argument list does not have to be:
	//function argument list automatically falls into the method's namespace (Koenig lookup)


	////////////////////////////////////////////////////////////
	// typename is used to help compiler to parse
	template <typename KEY_TYPE, typename VALUE_TYPE>
	void BSTmap<KEY_TYPE, VALUE_TYPE>::Clear(BSTmap_iterator node)
	{
		if (node->left)
			Clear(node->left);
		if (node->right)
			Clear(node->right);
		delete node.p_node;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap()
	{
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap(const BSTmap& rhs)
	{
		size_ = 0;
		pRoot = Copy(rhs.pRoot, nullptr);

		// Todo: Copy constructor
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	BSTmap<KEY_TYPE, VALUE_TYPE>& BSTmap<KEY_TYPE, VALUE_TYPE>::operator=(const BSTmap& rhs)
	{
		size_ = 0;
		if (pRoot)
		{
			Clear(pRoot);
		}
		pRoot = Copy(rhs.pRoot, nullptr);
		return *this;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	BSTmap<KEY_TYPE, VALUE_TYPE>::~BSTmap()
	{
		if (pRoot)
			Clear(pRoot);
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	unsigned int BSTmap<KEY_TYPE, VALUE_TYPE>::size()
	{
		return this->size_;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	VALUE_TYPE& BSTmap<KEY_TYPE, VALUE_TYPE>::operator[](KEY_TYPE const& key)
	{
		return emplaceFind(pRoot, end_it, key);
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator
		CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::begin()
	{
		if (pRoot)
			return BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator(pRoot->first());
		else
			return end_it;
	}


	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator BSTmap<KEY_TYPE, VALUE_TYPE>::end()
	{
		return end_it;
	}


	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const
		BSTmap<KEY_TYPE, VALUE_TYPE>::begin() const
	{
		if (pRoot)
			return BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const(pRoot->first());
		else
			return const_end_it;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const
		BSTmap<KEY_TYPE, VALUE_TYPE>::end() const
	{
		return const_end_it;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const BSTmap<KEY_TYPE, VALUE_TYPE>::find(
		KEY_TYPE const& key) const
	{
		if (pRoot)
		{
			return BSTmap_iterator_const(find(pRoot, key).p_node);
		}
		return BSTmap<KEY_TYPE, VALUE_TYPE>::const_end_it;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator BSTmap<KEY_TYPE, VALUE_TYPE>::find(KEY_TYPE const& key)
	{
		// Check for root
		if (pRoot)
		{
			return find(pRoot, key);
		}
		return BSTmap<KEY_TYPE, VALUE_TYPE>::end_it;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::BSTmap_iterator(Node* p) : p_node(p)
	{

	}

	// Assignment operator.
	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator&
		BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator=(const BSTmap_iterator& rhs)
	{
		// We do a shallow copy
		this->p_node = rhs.p_node;
		return *this;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator&
		BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator++()
	{
		// Todo: Fix this
		 // Use succesor
		p_node = p_node->increment();
		return *this;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator
		BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator++(int)
	{
		BSTmap_iterator copy(*this);
		++(*this); // or operator++();
		return copy;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::Node&
		BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator*()
	{
		return *(this->p_node);
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::Node*
		BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator->()
	{
		return p_node;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	bool BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator!=(const BSTmap::BSTmap_iterator& rhs)
	{
		return p_node != rhs.p_node;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	bool BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator::operator==(const BSTmap::BSTmap_iterator& rhs)
	{
		return p_node == rhs.p_node;
	}


	template<typename KEY_TYPE, typename VALUE_TYPE>
	BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const::BSTmap_iterator_const(Node* p) :
		p_node(p)
	{

	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const&
		BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const::operator=(const BSTmap_iterator_const& rhs)
	{
		p_node = rhs;
	}
	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const&
		BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const::operator++()
	{
		// pre increment
		p_node = p_node->increment();
		return *this;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const
		BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const::operator++(int)
	{
		// TODO: Post increment
		BSTmap_iterator_const copy(*this);
		++(*this); // or operator++();
		return copy;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::Node const&
		BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const::operator*()
	{
		return *p_node;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::Node const*
		BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const::operator->()
	{
		return p_node;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	bool BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const::operator!=(const BSTmap_iterator_const& rhs)
	{
		return p_node != rhs.p_node;
	}
	template<typename KEY_TYPE, typename VALUE_TYPE>
	bool BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator_const::operator==(const BSTmap_iterator_const& rhs)
	{
		return p_node == rhs.p_node;
	}


	////////////////////////////////////////////////////////////
	// do not change this code from here to the end of the file
	/* figure out whether node is left or right child or root
	 * used in print_backwards_padded
	 */
	template<typename KEY_TYPE, typename VALUE_TYPE>
	char BSTmap<KEY_TYPE, VALUE_TYPE>::getedgesymbol(const Node* node) const
	{
		const Node* parent = node->parent;
		if (parent == nullptr) return '-';
		else return (parent->left == node) ? '\\' : '/';
	}

	/* this is another "ASCII-graphical" print, but using
	 * iterative function.
	 * Left branch of the tree is at the bottom
	 */
	template<typename KEY_TYPE, typename VALUE_TYPE>
	std::ostream& operator<<(std::ostream& os, BSTmap<KEY_TYPE, VALUE_TYPE> const& map)
	{
		map.print(os);
		return os;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	void CS280::BSTmap<KEY_TYPE, VALUE_TYPE>::print(std::ostream& os, bool print_value) const
	{
		if (pRoot)
		{
			BSTmap<KEY_TYPE, VALUE_TYPE>::Node* b = pRoot->last();
			while (b)
			{
				int depth = getdepth(b);
				int i;
				/* printf(b); */

				char edge = getedgesymbol(b);
				switch (edge)
				{
				case '-':
					for (i = 0; i < depth; ++i) std::printf("       ");
					os << b->key;
					if (print_value) { os << " -> " << b->value; }
					os << std::endl;
					break;
				case '\\':
					for (i = 0; i < depth; ++i) std::printf("       ");
					os << edge << std::endl;
					for (i = 0; i < depth; ++i) std::printf("       ");
					os << b->key;
					if (print_value) { os << " -> " << b->value; }
					os << std::endl;
					break;
				case '/':
					for (i = 0; i < depth; ++i) std::printf("       ");
					os << b->key;
					if (print_value) { os << " -> " << b->value; }
					os << std::endl;
					for (i = 0; i < depth; ++i) std::printf("       ");
					os << edge << std::endl;
					break;
				}
				b = b->decrement();
			}
		}
		std::printf("\n");
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::BSTmap_iterator
		BSTmap<KEY_TYPE, VALUE_TYPE>::find(BSTmap_iterator root, KEY_TYPE const& key)
	{
		if (!root.p_node)
			return this->end_it;
		else if (key < root->Key())
			return find(root->left, key);
		else if (root->Key() < key)
			return find(root->right, key);
		else
			return root;

	}
	template<typename KEY_TYPE, typename VALUE_TYPE>
	VALUE_TYPE& BSTmap<KEY_TYPE, VALUE_TYPE>::emplaceFind(Node*& curretNode, BSTmap_iterator parent, KEY_TYPE const& key)
	{
		// Base case
		if (curretNode == nullptr)
		{
			curretNode = MakeNode(key, VALUE_TYPE{}, parent.p_node);
			return curretNode->Value();
		}
		// Case that we found

		if (key < curretNode->Key())
			return emplaceFind(curretNode->left, curretNode, key);
		else if (curretNode->Key() < key)
			return emplaceFind(curretNode->right, curretNode, key);
		else
			return curretNode->Value();
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	int BSTmap<KEY_TYPE, VALUE_TYPE>::getdepth(Node* node) const
	{
		// Depth is distance to root.
		Node* newNode = node;
		int result = 0;
		while (newNode != nullptr)
		{
			newNode = newNode->parent;
			++result;
		}
		return --result;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	void BSTmap<KEY_TYPE, VALUE_TYPE>::erase(BSTmap_iterator it)
	{
    if (it == end_it)
			return;
		DeleteNode(it.p_node);
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	void BSTmap<KEY_TYPE, VALUE_TYPE>::DeleteNode(Node* node)
	{
		// If node is a leaf node.
		if (!node->left && !node->right)
		{
			if (node != pRoot)
			{
				// Set our parents to nullptrs
				Node*& leftOrRight = Node::findNode(node);
				leftOrRight = nullptr;
			}
			else
			{
				pRoot = nullptr;
			}
			DestroyNode(node);
		}
		// Two children
		else if (node->left && node->right)
		{
			Node* successor = node->decrement();
			// node copy successor
			node->Value() = successor->Value();
			node->key = successor->key;
			DeleteNode(successor);
		}
		// If node only has one option
		else
		{
			Node* child = (node->left) ? node->left : node->right;

			if (node != pRoot)
			{
				// Set our parents to child
				Node*& leftOrRight = Node::findNode(node);
				leftOrRight = child;
				child->parent = node->parent;
			}
			else
			{
				pRoot = child;
			}
			DestroyNode(node);
		}
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	void BSTmap<KEY_TYPE, VALUE_TYPE>::DestroyNode(Node* node)
	{
		delete node;
		size_--;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename BSTmap<KEY_TYPE, VALUE_TYPE>::Node*
		BSTmap<KEY_TYPE, VALUE_TYPE>::Copy(BSTmap::Node* root, BSTmap::Node* parent)
	{
		// Base case
		if (!root)
			return nullptr;
		Node* newNode = MakeNode(root->key, root->value, parent);
		newNode->left = Copy(root->left, newNode);
		newNode->right = Copy(root->right, newNode);
		return newNode;
	}
}