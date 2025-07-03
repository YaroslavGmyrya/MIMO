all:
	g++ -g *.cpp -o main.out

run:
	./main.out > test_result.txt

graph:
	python3 create_graph.py test_result.txt
