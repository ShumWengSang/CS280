#ifndef NODE_H
#define NODE_H
#include <fstream>

class INT {
        //operator int() const { return data; }
        int data;
        static int counter; // to count comparisons
    public:
        INT( int d = 0 ) : data(d) {}
        bool operator<( INT const& op2 ) const {  ++counter; return data < op2.data; }
        bool operator>( INT const& op2 ) const {  ++counter; return data > op2.data; }
        bool operator<=( INT const& op2 ) const { ++counter; return data <= op2.data; }
        bool operator>=( INT const& op2 ) const { ++counter; return data >= op2.data; }
        bool operator==( INT const& op2 ) const { ++counter; return data == op2.data; }
        bool operator!=( INT const& op2 ) const { ++counter; return data != op2.data; }
        static int GetCounter() { return counter; }
        friend std::ostream& operator<<( std::ostream& os, INT const& val );
};

struct Node {
    Node( int k, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr ) : key(k), left(l), right(r), parent(p) {}
	INT    key;
	struct Node *left;
	struct Node *right;
	struct Node *parent; // <<----- parent pointer
};

struct Node2 {
    Node2( int k, Node2* l = nullptr, Node2* r = nullptr ) : key(k), left(l), right(r) {}
	INT    key;
	struct Node2 *left;
	struct Node2 *right;
	// <<----- no parent pointer !!!
};
#endif
