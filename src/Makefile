all: trackHeap leakHeap trackBST leakBST buildRBT RBTleak main

test:
	clear
	g++ -o List List.cpp
	hyperfine  --warmup 2 --parameter-scan size 1000 41000 -D 10000  "./List {size}" --export-csv WynikiListaDodawanieIndex2.csv

main:
	clear
	g++ -o Main Heap.cpp List.cpp Table.cpp BinarySearchTree.cpp RedBlackTree.cpp Main.cpp
	./Main
	rm Main

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