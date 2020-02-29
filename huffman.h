/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H
using namespace std;

#include <string>
#include <iostream>
#include <fstream>
#include "vector.h"
#include "bnode.h"
#include "pair.h"


struct HuffmanTree
{
public:
	HuffmanTree() : tree(NULL) {};
	HuffmanTree(BNode<custom::pair<int, string> >* node) : tree(node) {};
	HuffmanTree(custom::pair<int, string> data)
	{
		BNode<custom::pair<int, string> >* node = new BNode<custom::pair<int, string> >;
		node->data = data;
	}

	BNode<custom::pair<int, string> >* tree;
};

void huffman(const std::string & fileName);

void display(HuffmanTree top, string str);


#endif // HUFFMAN_h
