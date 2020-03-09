// g++ -std=c++11 tree2dot_test.cpp
//
// print tree in dot format:
// https://en.wikipedia.org/wiki/DOT_(graph_description_language)
// Simple dot file describing:
//           a
/*          / \    */
//         b   c
//         |   |
//         d   e
// digraph graphname {
//      a -> b;
//      a -> c;
//      b -> d;
//      c -> e;
// }
// to generate PostScript from dot use graphviz library:
// dot -Tps pic1.dot -o outfile.ps

#include <fstream>
#include <string>

template < typename NodeType, typename GetData, typename GetChildren, typename MarkNode >
void print_dot( 
        NodeType const* pRoot,  // root of the tree
        std::ostream & os,      // where to output
        GetData getdata,        // functional to get data
        GetChildren getchildren,// functional to get children, assume returned container supports range-for
        MarkNode    mark = [](NodeType*) { return false; }  // default value
        );
    
////////////////////////////////////////////////////////////////////////////////
template < typename NodeType, typename GetData, typename MarkNode >
void create_label( NodeType const* pNode, std::ostream & os, GetData getdata, MarkNode mark )
{
    if ( mark( pNode ) ) {
        os << "L"<<pNode << "[label=\"" << getdata( pNode ) << "\",shape=box];\n"; // create visible label
    } else { // regular node
        os << "L"<<pNode << "[label=\"" << getdata( pNode ) << "\"];\n"; // create visible label
    }
}

template < typename NodeType, typename GetData, typename GetChildren, typename MarkNode >
void print_dot_aux( NodeType const* pRoot, std::ostream & os, int & nullcount, GetData getdata, GetChildren getchildren, MarkNode mark )
{
    for ( NodeType const* child : getchildren( pRoot ) ) {
        if ( child ) { // not null
            create_label( child, os, getdata, mark );
            os << "    " << "L"<<pRoot << " -> " << "L"<<child << ";\n";
            //os << "    \"" << getdata( pRoot ) << "\" -> \"" << getdata( child ) << "\";\n";
            print_dot_aux( child, os, nullcount, getdata, getchildren, mark );
        } else { // null
            os << "    null" << ++nullcount << " [shape=point];\n";
            os << "    " << "L"<<pRoot << " -> null" << nullcount << ";\n";
        }
    }
}

template < typename NodeType, typename GetData, typename GetChildren, typename MarkNode >
void print_dot( NodeType const* pRoot, std::ostream & os, 
        GetData getdata, GetChildren getchildren, MarkNode mark
        ) {
    os << "digraph {\n";
    os << "    node [fontname=\"Arial\"];\n";

    if ( !pRoot ) { // empty
        os << "\n";
    } else {
        int terminal_node_counter = 0;
        create_label( pRoot, os, getdata, mark );
        print_dot_aux( pRoot, os, terminal_node_counter, getdata, getchildren, mark );
    }

    os << "}\n";
}
