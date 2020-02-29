###############################################################
# Program:
#     Assignment 08, Binary Tree
#     Brother JonesL, CS235
# Author:
#     Adam Goff, Aaron Rook, Martin Melerio, Tanner Stratford
# Summary:
#     <put a description here>
# Time:
#     <how long did it take to complete this program>?
###############################################################

##############################################################
# The main rule
##############################################################
a.out: vector.h assignment08.o huffman.o 
	g++ -o a.out assignment08.o huffman.o -g
	tar -cf assignment08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment08.o : the driver program
#      huffman.o      : the logic for the huffman code program
##############################################################
assignment08.o: bnode.h huffman.h assignment08.cpp
	g++ -c assignment08.cpp -g

huffman.o: bnode.h huffman.h vector.h huffman.cpp
	g++ -c huffman.cpp -g

