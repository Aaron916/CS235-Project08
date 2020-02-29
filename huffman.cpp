/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Adam Goff, Aaron Rook, Martin Melerio, Tanner Stratford
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include <cassert>         // for ASSERT
#include <string>          // for STRING: binary representation of codes
#include "bnode.h"         // for BINARY_NODE class definition
#include "vector.h"        // for VECTOR container
#include "pair.h"          // for PAIR container
#include "huffman.h"       // for HUFFMAN() prototype

using namespace std;

void display(HuffmanTree top, string str)
{
	if (!top.tree)
		return;

	if (top.tree->data.second != "\0")
	{
		cout << top.tree->data.second << " = "
			<< str << endl;
	}

	display(top.tree->pLeft, str + "0");
	display(top.tree->pRight, str + "1");
}

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(const string & fileName)
{

  custom::vector<custom::pair<int, string>> data;
	string name;
	int freq;

	ifstream fin(fileName.c_str());

	while (fin) // loop through the file and add values to vector
	{
		fin >> name >> freq;
		custom::pair<int, string> p;
    p.first = freq;
    p.second = name;
		data.push_back(p);
	}

  fin.close(); // close file

	custom::vector<HuffmanTree> nodes;

	for (int i = 0; i < data.size(); i++) // Loop through the vector and push to a vector of trees
	{
		HuffmanTree tree(data[i]);
		nodes.push_back(tree);
	}

	// create dummy value that will be bigger than all frequencies in smallest vector
	custom::pair<int, string> biggest(1, string());
	HuffmanTree smallest[2];
	// used to keep track of left-most position
	int leftmost;
	int rightmost;

	while (nodes.size() != 1)
	{
		smallest[0].tree->data = biggest;
		smallest[1].tree->data = biggest;
		leftmost = -1;
		rightmost = -1;

		// find two smallest nodes
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i].tree->data < smallest[0].tree->data)
			{
				HuffmanTree temp = smallest[0];
				smallest[0] = nodes[i];
				smallest[1] = temp;
			}
			else if (nodes[i].tree->data < smallest[1].tree->data)
			{
				smallest[1] = nodes[i];
			}
		}

		// find leftmost tree
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i].tree->data == smallest[0].tree->data ||
				nodes[i].tree->data == smallest[1].tree->data)
			{
				leftmost = i;
				break;
			}
		}

		// find rightmost tree
		for (int i = nodes.size() - 1; i >= 0; i--)
		{
			if (nodes[i].tree->data == smallest[0].tree->data ||
				nodes[i].tree->data == smallest[1].tree->data)
			{
				rightmost = i;
				break;
			}
		}

		// new weight of the two combined.
		int nWeight = smallest[0].tree->data.first + smallest[1].tree->data.first;
		custom::pair<int, string> p1;
    p1.first = nWeight;
    p1.second = string();
		HuffmanTree add(p1);
		addLeft(add.tree, smallest[0].tree);
		addRight(add.tree, smallest[1].tree);

		custom::vector<HuffmanTree> temp;
		for (int i = 0; i < nodes.size(); i++)
		{
			if (i != rightmost)
				temp.push_back(nodes[i]);
		}

		nodes.clear();
		nodes = temp;
		nodes[leftmost] = add;
	}

	display(nodes[0], "");
  /*{
  ifstream myfile(fileName);

  string line;
  custom::vector <string> myLines;
  while (std::getline(myfile, line))
  {
    myLines.push_back(line);
  }
  cout << myLines[0] << endl;
}
   return;
  */
}
