OUTPUT_FILE_BIN = main.out
OUTPUT_TEST_FILE = test_result.txt
GXX = g++

all:
	@cd code && \
	$(GXX) *.cpp -o $(OUTPUT_FILE_BIN) && \
	printf "\n ===== Compilation completed successfully ===== \n\n"

run:
	@cd code && \
	./$(OUTPUT_FILE_BIN)

test:
	@cd code && \
	./$(OUTPUT_FILE_BIN) > ../tests/$(OUTPUT_TEST_FILE)

graph:
	@cd tests && \
	python3 create_graph.py $(OUTPUT_TEST_FILE)
