all: main

main:
	clear
	g++ -o Main.exe Heap.cpp List.cpp Table.cpp BinarySearchTree.cpp RedBlackTree.cpp Main.cpp
	./Main.exe

buildRBT:
	clear
	g++ -g -o RBT RedBlackTree.cpp
	./RBT

RBTleak:
	clear
	g++ -g -o RBT RedBlackTree.cpp
	valgrind --leak-check=full ./RBT

RBTtrack:
	clear
	g++ -g -o RBT RedBlackTree.cpp
	valgrind --leak-check=full ./RBT


trackBST:
	clear
	g++ -g -o BST BinarySearchTree.cpp
	valgrind --track-origins=yes ./BST

leakBST:
	clear
	g++ -g -o BST BinarySearchTree.cpp
	valgrind --leak-check=full ./BST

trackHeap:
	clear
	g++ -g -o Heap Heap.cpp
	valgrind --track-origins=yes ./Heap

leakHeap:
	clear
	g++ -g -o Heap Heap.cpp
	valgrind --leak-check=full ./Heap