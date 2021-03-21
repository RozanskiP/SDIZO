all: trackHeap leakHeap trackBST leakBST buildRBT RBTleak buildMain

buildMain:
	clear
	g++ -o Main Heap.cpp List.cpp Table.cpp BinarySearchTree.cpp Main.cpp
	./Main 

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

funkcje:
	hyperfine  --parameter-scan size 1000 50000 -D 1000  "./List {size}" --export-csv results.csv
	explorer.exe .
	hyperfine --warmup 3 ./List