all: simple_loop

simple_loop: simple_loop.c
	gcc -std=c99 -o simple_loop -gdwarf-2 simple_loop.c
	
clean:
	rm -f simple_loop
	rm -rf cd TARGET *pinball *.csv forward* *.out *.tt *dot* *.log *.txt
