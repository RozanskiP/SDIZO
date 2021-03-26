all: trackHeap leakHeap trackBST leakBST buildRBT RBTleak buildMain

test:
	clear
	g++ -o RBT RedBlackTree.cpp
	hyperfine  --warmup 2 --parameter-scan size 1000 100000 -D 10000  "./Heap {size}" --export-csv WynikiKopiecDodawanie2.csv

zapis:
	tablica:
		g++ -o Table Table.cpp
		hyperfine  --warmup 2 --parameter-scan size 1000 30000 -D 1000  "./Table {size}" --export-csv WynikiTablicaDodawanieIndex.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 30000 -D 1000  "./Table {size}" --export-csv WynikiTablicaUsuwaniePoczatek.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 30000 -D 1000  "./Table {size}" --export-csv WynikiTablicaUsuwanieKoniec.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 30000 -D 1000  "./Table {size}" --export-csv WynikiTablicaUsuwanieIndex.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 30000 -D 1000  "./Table {size}" --export-csv WynikiTablicaWyszukiwanie.csv
	lista:
		g++ -o List List.cpp
		hyperfine  --warmup 2 --parameter-scan size 1000 50000 -D 1000  "./List {size}" --export-csv WynikiListaDodawaniePoczatek.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 50000 -D 1000  "./List {size}" --export-csv WynikiListaDodawanieKoniec.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 30000 -D 1000  "./List {size}" --export-csv WynikiListaDodawanieIndex.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 30000 -D 1000  "./List {size}" --export-csv WynikiListaUsuwaniePoczatek.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 30000 -D 1000  "./List {size}" --export-csv WynikiListaUsuwanieKoniec.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 30000 -D 1000  "./List {size}" --export-csv WynikiListaUsuwanieIndex.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 30000 -D 1000  "./List {size}" --export-csv WynikiListaWyszukiwanie.csv
	kopiec: //sprawdzi ilosc danych
		g++ -o Heap Heap.cpp
		hyperfine  --warmup 2 --parameter-scan size 1000 50000 -D 1000  "./Heap {size}" --export-csv WynikiKopiecDodawanie.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 50000 -D 1000  "./Heap {size}" --export-csv WynikiKopiecUsuwanie.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 50000 -D 1000  "./Heap {size}" --export-csv WynikiKopiecWyszukiwanie.csv
	BST: //sprawdzi ilosc danych
		g++ -o BST BinarySearchTree.cpp
		hyperfine  --warmup 2 --parameter-scan size 1000 30000 -D 1000  "./BST {size}" --export-csv WynikiBSTDodawanie.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 20000 -D 1000  "./BST {size}" --export-csv WynikiBSTUsuwanie.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 20000 -D 1000  "./BST {size}" --export-csv WynikiBSTWyszukiwanieCzasDodawanie.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 20000 -D 1000  "./BST {size}" --export-csv WynikiBSTWyszukiwanie.csv
	RBT: //sprawdzi ilosc danych
		g++ -o RBT RedBlackTree.cpp
		hyperfine  --warmup 2 --parameter-scan size 1000 50000 -D 1000  "./RBT {size}" --export-csv WynikiRBTDodawanie.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 50000 -D 1000  "./RBT {size}" --export-csv WynikiRBTUsuwanie.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 50000 -D 1000  "./RBT {size}" --export-csv WynikiRBTUsuwanieCzasDodawanie.csv
		hyperfine  --warmup 2 --parameter-scan size 1000 50000 -D 1000  "./RBT {size}" --export-csv WynikiRBTWyszukiwanie.csv

buildMain:
	clear
	g++ -o Main Heap.cpp List.cpp Table.cpp BinarySearchTree.cpp RedBlackTree.cpp Main.cpp
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