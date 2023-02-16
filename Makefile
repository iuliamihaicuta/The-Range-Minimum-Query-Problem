.PHONY: run-p1 run-p2 run-p3

all: run-p1 run-p2 run-p3 run-best

build:
	cp in/test1.in test.in
	gcc -o run-p1 square_root.c
	gcc -o run-p2 segment_tree.c
	gcc -o run-p3 sparse_table.c
	rm test.in

run-p1: square_root.c
	cp in/test1.in test.in
	gcc -o run-p1 square_root.c && ./run-p1
	rm test.in
	

run-p2: segment_tree.c
	cp in/test1.in test.in
	gcc -o run-p2 segment_tree.c && ./run-p2
	rm test.in

run-p3: sparse_table.c
	cp in/test1.in test.in
	gcc -o run-p3 sparse_table.c && ./run-p3
	rm test.in

run-best: run-p2

.PHONY: clean
clean:
	rm -f run-p1.exe run-p2.exe run-p3.exe run-best.exe test.out