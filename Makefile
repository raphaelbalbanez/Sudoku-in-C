
main: sudoku.c 
	gcc sudoku.c -o sudoku -pthread

run: sudoku
	./sudoku

clean:
	 rm sudoku

runnamefile: sudoku
	./sudoku [namefile]
