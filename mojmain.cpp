#include <stdio.h>
#include <iostream>
#include"conio2.h"
#include"funkcje.h"


using namespace std;

int main() {
	
	int x = board_column; //screen coordinate
	int y = board_row; //screen coordinate
	int size = 12;
	

	srand(time(NULL));
	char** default_tab = create_default_board(x,y, size);
	board_t **board;
	board = create_board(x,y, size);
	copy_default(default_tab, board, size);
	free(default_tab);
	write_board(board, size);
	write_border(size);
	
	write_legend();
	key_action(x, y, board, default_tab, size);
	free(board);
	return 0;
}