#pragma once
#include <iostream>
#include <algorithm>
namespace CS280
{
	// static data members
	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator
		CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::end_it = CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator(nullptr);

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const
		CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::const_end_it = CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const(
			nullptr);

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::Node* AVLmap<KEY_TYPE, VALUE_TYPE>::MakeNode(KEY_TYPE k,
		VALUE_TYPE val, AVLmap<KEY_TYPE, VALUE_TYPE>::Node* p, AVLmap<KEY_TYPE, VALUE_TYPE>::Node* l, AVLmap<KEY_TYPE, VALUE_TYPE>::Node* r, int h, int b)
	{
		++this->size_;
		return new Node(k, val, p, h, b, l, r);
	}

	// Node stuff
	template<typename KEY_TYPE, typename VALUE_TYPE>
	CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node::Node(KEY_TYPE k, VALUE_TYPE val, AVLmap::Node* p, int h, int b,
		AVLmap::Node* l,
		AVLmap::Node* r) : key(k), value(val), height(h), balance(b),
		parent(p),
		left(l), right(r)
	{

	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	KEY_TYPE const& CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node::Key() const
	{
		return key;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	VALUE_TYPE& CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node::Value()
	{
		return value;
	}


	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::Node* AVLmap<KEY_TYPE, VALUE_TYPE>::Node::last()
	{

		Node* node = this;
		while (node && node->right != nullptr)
			node = node->right;
		return node;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::Node* AVLmap<KEY_TYPE, VALUE_TYPE>::Node::first()
	{
		Node* node = this;
		while (node && node->left != nullptr)
			node = node->left;
		return node;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::Node*
		AVLmap<KEY_TYPE, VALUE_TYPE>::Node::decrement()
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
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::Node* AVLmap<KEY_TYPE, VALUE_TYPE>::Node::increment()
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
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::Node* AVLmap<KEY_TYPE, VALUE_TYPE>::Node::FindSuccesor()
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
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::Node*&
		AVLmap<KEY_TYPE, VALUE_TYPE>::findNode(Node* node)
	{
		if (!node->parent)
			return pRoot;
		if (node->parent->right == node)
			return node->parent->right;
		else
			return node->parent->left;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	void AVLmap<KEY_TYPE, VALUE_TYPE>::Node::ShallowCopy(Node* lhs, Node* rhs)
	{
		lhs->balance = rhs->balance;
		lhs->height = rhs->height;
		lhs->key = rhs->key;
		lhs->value = rhs->value;
		lhs->left = rhs->left;
		lhs->right = rhs->right;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::Node*
		AVLmap<KEY_TYPE, VALUE_TYPE>::Node::FindPredecessor()
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


	template <typename KEY_TYPE, typename VALUE_TYPE>
	int AVLmap<KEY_TYPE, VALUE_TYPE>::Node::GetHeight()
	{
		return height;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	int AVLmap<KEY_TYPE, VALUE_TYPE>::Node::GetBalance()
	{
		return balance;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	void AVLmap<KEY_TYPE, VALUE_TYPE>::Node::SetHeight(int h)
	{
		height = h;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	void AVLmap<KEY_TYPE, VALUE_TYPE>::Node::SetBalance(int b)
	{
		balance = b;
	}
	
	template <typename KEY_TYPE, typename VALUE_TYPE>
	int AVLmap<KEY_TYPE, VALUE_TYPE>::Node::CalcHeightFull(Node* node)
	{
		using namespace std;
		if (node == NULL)
			return 0;

		// find the height of each subtree
		int lh = CalcHeightFull(node->left);
		int rh = CalcHeightFull(node->right);

		node->SetHeight(max(lh, rh));
		
		return 1 + max(lh, rh);
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	void AVLmap<KEY_TYPE, VALUE_TYPE>::Node::CalcNodeStatsCheap(Node* node)
	{
		using namespace std;
		if (node == NULL)
			return;

		CalcHeightCheap(node);
		CalcBalanceCheap(node);

	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	void AVLmap<KEY_TYPE, VALUE_TYPE>::Node::CalcHeightCheap(Node* node)
	{
		using namespace std;
		// find the height of each subtree
		int lh = node->left ? node->left->GetHeight() : 0;
		int rh = node->right ? node->right->GetHeight() : 0;

		
		// Nothing
		if (!node->left && !node->right)
			node->SetHeight(0);
		else 
			node->SetHeight(max(lh, rh) + 1);
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	void AVLmap<KEY_TYPE, VALUE_TYPE>::Node::CalcBalanceCheap(Node* node)
	{
		int lh = node->left ? node->left->GetHeight() + 1: 0;
		int rh = node->right ? node->right->GetHeight() + 1: 0;
		
		node->SetBalance(lh - rh);
	}

	
	//in implementation file 
	//method's name and return value have to be fully qualified with
	//all required namespace and class names (like CS280::AVLmap<KEY_TYPE,VALUE_TYPE>::AVLmap)
	//but the argument list does not have to be:
	//function argument list automatically falls into the method's namespace (Koenig lookup)


	////////////////////////////////////////////////////////////
	// typename is used to help compiler to parse
	template <typename KEY_TYPE, typename VALUE_TYPE>
	void AVLmap<KEY_TYPE, VALUE_TYPE>::Clear(AVLmap_iterator node)
	{
		if (node->left)
			Clear(node->left);
		if (node->right)
			Clear(node->right);
		delete node.p_node;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap()
	{
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap(const AVLmap& rhs)
	{
		size_ = 0;
		pRoot = Copy(rhs.pRoot);

		// Todo: Copy constructor
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	AVLmap<KEY_TYPE, VALUE_TYPE>& AVLmap<KEY_TYPE, VALUE_TYPE>::operator=(const AVLmap& rhs)
	{
		size_ = 0;
		if (pRoot)
		{
			Clear(pRoot);
		}
		pRoot = Copy(rhs.pRoot);
		return *this;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	AVLmap<KEY_TYPE, VALUE_TYPE>::~AVLmap()
	{
		if (pRoot)
			Clear(pRoot);
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	unsigned int AVLmap<KEY_TYPE, VALUE_TYPE>::size()
	{
		return this->size_;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	VALUE_TYPE& AVLmap<KEY_TYPE, VALUE_TYPE>::operator[](KEY_TYPE const& key)
	{
		bool isInsertion = false;
		VALUE_TYPE& returnVal = emplaceFind(pRoot, end_it, key, isInsertion);
		// If we were inserting
		if(isInsertion)
		{
			// Now we have to do some balancing.
			while(insertionPtrs.size() != 0)
			{
				Node* y = insertionPtrs[0];
				insertionPtrs.pop_front();
				
				// Update balance and height
				Node::CalcNodeStatsCheap(y);

				// Do balancing algo if less or eq to 1
				//
				Node*& node = findNode(y);
				
				if(node->GetBalance() > 1 && node->left->GetBalance() >= 0) // RR
				{
					RotateRight(node);
				}
				else if(node->GetBalance() < -1 && node->right->GetBalance() <= 0)  // LL
				{
					RotateLeft(node);
				}
				else if(node->GetBalance() > 1 && node->left->GetBalance() < 0) // RL
				{
					RotateLeft(node->left);
					RotateRight(node);
				}
				else if(node->GetBalance() < -1 && node->right->GetBalance() > 0) //LR
				{
					RotateRight(node->right);
					RotateLeft(node);
				}
			}
		}
		insertionPtrs.clear();
		return returnVal;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator
		CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::begin()
	{
		if (pRoot)
			return AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator(pRoot->first());
		else
			return end_it;
	}


	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator AVLmap<KEY_TYPE, VALUE_TYPE>::end()
	{
		return end_it;
	}


	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const
		AVLmap<KEY_TYPE, VALUE_TYPE>::begin() const
	{
		if (pRoot)
			return AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const(pRoot->first());
		else
			return const_end_it;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const
		AVLmap<KEY_TYPE, VALUE_TYPE>::end() const
	{
		return const_end_it;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const AVLmap<KEY_TYPE, VALUE_TYPE>::find(
		KEY_TYPE const& key) const
	{
		if (pRoot)
		{
			return AVLmap_iterator_const(find(pRoot, key).p_node);
		}
		return AVLmap<KEY_TYPE, VALUE_TYPE>::const_end_it;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator AVLmap<KEY_TYPE, VALUE_TYPE>::find(KEY_TYPE const& key)
	{
		// Check for root
		if (pRoot)
		{
			return find(pRoot, key);
		}
		return AVLmap<KEY_TYPE, VALUE_TYPE>::end_it;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::AVLmap_iterator(Node* p) : p_node(p)
	{

	}

	// Assignment operator.
	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator&
		AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator=(const AVLmap_iterator& rhs)
	{
		// We do a shallow copy
		this->p_node = rhs.p_node;
		return *this;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator&
		AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator++()
	{
		// Todo: Fix this
		 // Use succesor
		p_node = p_node->increment();
		return *this;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator
		AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator++(int)
	{
		AVLmap_iterator copy(*this);
		++(*this); // or operator++();
		return copy;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::Node&
		AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator*()
	{
		return *(this->p_node);
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::Node*
		AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator->()
	{
		return p_node;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	bool AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator!=(const AVLmap::AVLmap_iterator& rhs)
	{
		return p_node != rhs.p_node;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	bool AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator==(const AVLmap::AVLmap_iterator& rhs)
	{
		return p_node == rhs.p_node;
	}


	template<typename KEY_TYPE, typename VALUE_TYPE>
	AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::AVLmap_iterator_const(Node* p) :
		p_node(p)
	{

	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const&
		AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator=(const AVLmap_iterator_const& rhs)
	{
		p_node = rhs;
	}
	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const&
		AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator++()
	{
		// pre increment
		p_node = p_node->increment();
		return *this;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const
		AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator++(int)
	{
		// TODO: Post increment
		AVLmap_iterator_const copy(*this);
		++(*this); // or operator++();
		return copy;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::Node const&
		AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator*()
	{
		return *p_node;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::Node const*
		AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator->()
	{
		return p_node;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	bool AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator!=(const AVLmap_iterator_const& rhs)
	{
		return p_node != rhs.p_node;
	}
	template<typename KEY_TYPE, typename VALUE_TYPE>
	bool AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator==(const AVLmap_iterator_const& rhs)
	{
		return p_node == rhs.p_node;
	}


	////////////////////////////////////////////////////////////
	// do not change this code from here to the end of the file
	/* figure out whether node is left or right child or root
	 * used in print_backwards_padded
	 */
	template<typename KEY_TYPE, typename VALUE_TYPE>
	char AVLmap<KEY_TYPE, VALUE_TYPE>::getedgesymbol(const Node* node) const
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
	std::ostream& operator<<(std::ostream& os, AVLmap<KEY_TYPE, VALUE_TYPE> const& map)
	{
		map.print(os);
		return os;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	void CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::print(std::ostream& os, bool print_value) const
	{
		if (pRoot)
		{
			AVLmap<KEY_TYPE, VALUE_TYPE>::Node* b = pRoot->last();
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
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator
		AVLmap<KEY_TYPE, VALUE_TYPE>::find(AVLmap_iterator root, KEY_TYPE const& key)
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
	VALUE_TYPE& AVLmap<KEY_TYPE, VALUE_TYPE>::emplaceFind(Node*& curretNode, 
		AVLmap_iterator parent, KEY_TYPE const& key, bool& inserted)
	{
		// Base case
		if (curretNode == nullptr)
		{
			inserted = true;
			curretNode = MakeNode(key, VALUE_TYPE{}, parent.p_node);
			return curretNode->Value();
		}
		insertionPtrs.push_front(curretNode);
		if (key < curretNode->Key())
			return emplaceFind(curretNode->left, curretNode, key, inserted);
		else if (curretNode->Key() < key)
			return  emplaceFind(curretNode->right, curretNode, key, inserted);
		else //If key == value
			return  curretNode->Value();

	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	int AVLmap<KEY_TYPE, VALUE_TYPE>::getdepth(Node* node) const
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
	void AVLmap<KEY_TYPE, VALUE_TYPE>::erase(AVLmap_iterator it)
	{
		if (it == AVLmap::end_it)
			return;
		DeleteNode(it.p_node);
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	void AVLmap<KEY_TYPE, VALUE_TYPE>::DeleteNode(Node* node)
	{
		// Store all the parents in a stack
		Node* parentNode = node->parent;
		while (parentNode)
		{
			insertionPtrs.push_front(parentNode);
			parentNode = parentNode->parent;
		}
		
		// If node is a leaf node.
		if (!node->left && !node->right)
		{
			if (node != pRoot)
			{
				// Set our parents to nullptrs
				Node*& leftOrRight = findNode(node);
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
				Node*& leftOrRight = findNode(node);
				leftOrRight = child;
				child->parent = node->parent;
			}
			else
			{
				pRoot = child;
			}
			DestroyNode(node);
		}

		// Now handle AVL balancing.
		while(!insertionPtrs.empty())
		{
			Node* stackNode = insertionPtrs[0];
			insertionPtrs.pop_front();
			
			// Update balance and height
			Node::CalcNodeStatsCheap(stackNode);

			// Do balancing algo if less or eq to 1
			//
			Node*& node = findNode(stackNode);

			if (node->GetBalance() > 1 && node->left->GetBalance() >= 0) // RR
			{
				RotateRight(node);
			}
			else if (node->GetBalance() < -1 && node->right->GetBalance() <= 0)  // LL
			{
				RotateLeft(node);
			}
			else if (node->GetBalance() > 1 && node->left->GetBalance() < 0) // RL
			{
				RotateLeft(node->left);
				RotateRight(node);
			}
			else if (node->GetBalance() < -1 && node->right->GetBalance() > 0) //LR
			{
				RotateRight(node->right);
				RotateLeft(node);
			}
		}
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	void AVLmap<KEY_TYPE, VALUE_TYPE>::DestroyNode(Node* node)
	{
		delete node;
		size_--;
	}

	template<typename KEY_TYPE, typename VALUE_TYPE>
	typename AVLmap<KEY_TYPE, VALUE_TYPE>::Node*
		AVLmap<KEY_TYPE, VALUE_TYPE>::Copy(AVLmap::Node* root)
	{
		// Base case
		if (!root)
			return nullptr;
		Node* newNode = MakeNode(root->key, root->value, nullptr);
		newNode->left = Copy(root->left);
		newNode->right = Copy(root->right);
		return newNode;
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	void AVLmap<KEY_TYPE, VALUE_TYPE>::RotateLeft(Node*& root)
	{
		Node* temp = root;
		root = root->right;
		temp->right = root->left;
		root->left = temp;

		Node* copyRoot = root;
		// Set parants and update stats.
		root->parent = temp->parent;
		temp->right->parent = temp;
		temp->parent = root;
		
		Node::CalcNodeStatsCheap(temp);
		Node::CalcNodeStatsCheap(copyRoot);
		UpdateParentHeight(copyRoot);
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	void AVLmap<KEY_TYPE, VALUE_TYPE>::RotateRight(Node*& root)
	{
		Node* temp = root;
		root = root->left;
		temp->left = root->right;
		root->right = temp;

		Node* copyRoot = root;
		// Set parants and update stats.
		root->parent = temp->parent;
		temp->left->parent = temp;
		temp->parent = root;

		Node::CalcNodeStatsCheap(temp);
		Node::CalcNodeStatsCheap(copyRoot);
		UpdateParentHeight(copyRoot);
	}

	template <typename KEY_TYPE, typename VALUE_TYPE>
	void AVLmap<KEY_TYPE, VALUE_TYPE>::UpdateParentHeight(Node*& node)
	{
		while(node->parent != nullptr)
		{
			node = node->parent;
			Node::CalcNodeStatsCheap(node);
		}
	}
}