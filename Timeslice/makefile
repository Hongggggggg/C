OBJ=$(wildcard *.c)
test:$(OBJ)
	gcc -o $@ $^ -pthread

.PHONY:clean
clean:
	rm -rf *.o test