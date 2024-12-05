objects := solve.out

$(objects): %.out: %.c
	$(CC) $^ -o $@

run: $(objects) input
	./solve.out input

clean:
	rm $(objects)

all: $(objects)
