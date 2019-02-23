#include<stdio.h>
#include<stdlib.h>
#include"conio2.h"
#include"funkcje.h"
#include <cstdlib>
#include <ctime>

akcje_t download_key(void)
{
	int key = getch();
	if (key == 0)
	{
		key = getch();
		if (key == 0x48)
		{
			return UP_ARROW;
		}
		else if (key == 0x50)
		{
			return DOWN_ARROW;
		}
		else if (key == 0x4b)
		{
			return LEFT_ARROW;
		}
		else if (key == 0x4d)
		{
			return RIGHT_ARROW;
		}
	}
	else if (key == 27) //esc
	{
		return EXIT;
	}
	else if (key == 'n' || key == 'N')
	{
		return NEW_GAME;
	}
	else if (key == '0')
	{
		return ENTER_0;
	}
	else if (key == '1')
	{
		return ENTER_1;
	}
	else if (key == 'o' || key == 'O')
	{
		return RANDOM_BOARD;
	}
	else if (key == 'p' || key == 'P')
	{
		return SIMPLE_HINT;
	}
	else if (key == 'r' || key == 'R')
	{
		return CHANGE_SIZE;
	}
	else if (key == 'k' || key == 'K')
	{
		return CHECK_POSSIBILTY_END;
	}
	else if (key == 'd' || key == 'D')
	{
		return CHECK_RULE2;
	}
	else if (key == 'a' || key == 'A')
	{
		return END_AUTODETECTION;
	}
	else if (key == 'w' || key == 'W')
	{
		return FULLFILLMENT_BACKLIGHT_UNEQUIVOCAL;
	}
	else if (key == 's' || key == 'S')
	{
		return SAVE_GAME;
	}
	else if (key == 'l' || key == 'L')
	{
		return LOAD_GAME;
	}
	else if (key == 'b' || key == 'B')
	{
		return FULL_CHECK;
	}
	else
	{
		return WRONG_KEY;
	}
	return WRONG_KEY;
}

void key_action(int x, int y, board_t** board, char** default_tab, int size)
{
	int key;
	gotoxy(x, y);
	write_board_coordinates(screen_to_board_X(x), screen_to_board_Y(y));
	write_coordinates(screen_to_board_X(x), screen_to_board_Y(y));
	
	do
	{
		key = download_key();
		int tabX = screen_to_tab_Y(y); // tab coordinates are opposite to gotoxy coordinates
		int tabY = screen_to_tab_X(x);
		switch (key)
		{
		case UP_ARROW:
			if (y > board_row)
			{
				y--;
				gotoxy(x, y);
			}
			break;
		case DOWN_ARROW:
			if (y < board_row + board_size - 1)
			{
				y++;
				gotoxy(x, y);
			}
			break;
		case LEFT_ARROW:
			if (x > board_column)
			{
				x--;
				gotoxy(x, y);
			}
			break;
		case RIGHT_ARROW:
			if (x < board_column + board_size - 1)
			{
				x++;
				gotoxy(x, y);
			}
			break;
		case ENTER_0:
			enter_0(tabX, tabY, board, 0, size);
			break;

		case ENTER_1:
			enter_1(tabX, tabY, board, 0, size);
			break;
		case NEW_GAME:
			default_tab = create_default_board(x, y, size);
			copy_default(default_tab, board, size);
			free(default_tab);
			board_colour_reset(board, size);
			write_board(board, size);
			break;

		case RANDOM_BOARD:
		{
		remove_board(board);
		board = create_board(x, y, size);
		fill_with_dots(board, size);
		fill_side_values(board, size);
		int amount = draw_expected_fields_amount(size); // amount of expected fields to be drawn
		fill_with_drawn(amount, board, size);
		write_board(board, size); }
		break;

		case SIMPLE_HINT:
		{int* buffer_0;
			buffer_0 = check_rules('0', tabX, tabY, board, size);
			char* text_0;
			int number_0_0 = -1;
			int number_0_1 = -1;

			if (buffer_0[0] == UNMODIFIABLE &&  buffer_0[1] == -1) // initialized
			{
				text_0 = "This field was initialized by computer";
			}
			else if (buffer_0[0] == RULE_1_LEFT_RIGHT &&  buffer_0[1] == -1) // rule 1 LEFT RIGHT
			{
				text_0 = "RULE 1 - there are two 0 on the both sides of the field";
			}
			else if (buffer_0[0] == RULE_1_TOP_BOTTOM &&  buffer_0[1] == -1) // rule 1 TOP BOTTOM
			{
				text_0 = "RULE 1 - there is 0 above and under the field";
			}
			else if (buffer_0[0] == RULE_1_LEFT_LEFT &&  buffer_0[1] == -1) // rule 1 LEFT LEFT
			{
				text_0 = "RULE 1 - there are two 0 on the left of the field ";
			}
			else if (buffer_0[0] == RULE_1_RIGHT_RIGHT &&  buffer_0[1] == -1) // rule 1 RIGHT RIGHT
			{
				text_0 = "RULE 1 - there are two 0 on the right of the field ";
			}
			else if (buffer_0[0] == RULE_1_TOP_TOP &&  buffer_0[1] == -1) // rule 1 TOP TOP
			{
				text_0 = "RULE 1 - there are two 0 on the top of the field ";
			}
			else if (buffer_0[0] == RULE_1_BOTTOM_BOTTOM &&  buffer_0[1] == -1) // rule 1 BOTTOM BOTTOM
			{
				text_0 = "RULE 1 - there are two 0 on the bottom of the field ";
			}
			else if (buffer_0[0] == RULE_2_FALSITY_ROW &&  buffer_0[1] == -1) // rule 2 row
			{
				text_0 = "RULE 2 - there are too many 0 in the row ";
			}
			else if (buffer_0[0] == RULE_2_FALSITY_COLUMN &&  buffer_0[1] == -1) // rule 2 column
			{
				text_0 = "RULE 2 - there are too many 0 in the column ";
			}
			else if (buffer_0[2] == 1) // rule 3 row repeated
			{
				text_0 = "RULE 3 - entering 0 would cause repeating row number:";
				number_0_0 = buffer_0[0];

			}
			else if (buffer_0[2] == 2) // rule 3 column repeated
			{
				text_0 = "RULE 3 - entering 0 would cause repeating coulumn number:";
				number_0_0 = buffer_0[1];
			}
			else if (buffer_0[2] == 3) // rule 3 row and column repeated
			{
				text_0 = "RULE 3 - entering 0 causes repeating row and column, which numbers are:";
				number_0_0 = buffer_0[0];
				number_0_1 = buffer_0[1];
			}
			else if (buffer_0[0] == 0 && buffer_0[1] == -1) // managed
			{
				text_0 = "0 can be entered";
			}

			int* buffer_1;
			buffer_1 = check_rules('1', tabX, tabY, board, size);
			char* text_1;
			int number_1_0 = -1;
			int number_1_1 = -1;

			if (buffer_1[0] == UNMODIFIABLE &&  buffer_1[1] == -1) // initialized
			{
				text_1 = "This field was initialized by computer";
			}
			else if (buffer_1[0] == RULE_1_LEFT_RIGHT &&  buffer_1[1] == -1) // rule 1 LEFT RIGHT
			{
				text_1 = "RULE 1 - there are two 1 on the both sides of the field";
			}
			else if (buffer_1[0] == RULE_1_TOP_BOTTOM &&  buffer_1[1] == -1) // rule 1 TOP BOTTOM
			{
				text_1 = "RULE 1 - there is 1 above and under the field";
			}
			else if (buffer_1[0] == RULE_1_LEFT_LEFT &&  buffer_1[1] == -1) // rule 1 LEFT LEFT
			{
				text_1 = "RULE 1 - there are two 1 on the left of the field ";
			}
			else if (buffer_1[0] == RULE_1_RIGHT_RIGHT &&  buffer_1[1] == -1) // rule 1 RIGHT RIGHT
			{
				text_1 = "RULE 1 - there are two 1 on the right of the field ";
			}
			else if (buffer_1[0] == RULE_1_TOP_TOP &&  buffer_1[1] == -1) // rule 1 TOP TOP
			{
				text_1 = "RULE 1 - there are two 1 on the top of the field ";
			}
			else if (buffer_1[0] == RULE_1_BOTTOM_BOTTOM &&  buffer_1[1] == -1) // rule 1 BOTTOM BOTTOM
			{
				text_1 = "RULE 1 - there are two 1 on the bottom of the field ";
			}
			else if (buffer_1[0] == RULE_2_FALSITY_ROW &&  buffer_1[1] == -1) // rule 2 row
			{
				text_1 = "RULE 2 - there are too many 1 in the row ";
			}
			else if (buffer_1[0] == RULE_2_FALSITY_COLUMN &&  buffer_1[1] == -1) // rule 2 column
			{
				text_1 = "RULE 2 - there are too many 1 in the column ";
			}
			else if (buffer_1[2] == 1) // rule 3 row repeated
			{
				text_1 = "RULE 3 - entering 1 would cause repeating row number:";
				number_1_0 = buffer_1[0];

			}
			else if (buffer_1[2] == 2) // rule 3 column repeated
			{
				text_1 = "RULE 3 - entering 1 would cause repeating coulumn number:";
				number_1_0 = buffer_0[1];
			}
			else if (buffer_1[2] == 3) // rule 3 row and column repeated
			{
				text_1 = "RULE 3 - entering 1 causes repeating row and column, which numbers are:";
				number_1_0 = buffer_1[0];
				number_1_1 = buffer_1[1];
			}
			else if (buffer_1[0] == 0 && buffer_1[1] == -1) // managed
			{
				text_1 = "1 can be entered";
			}

			clrscr();
			write_board(board, size);
			write_border(size);
			write_legend();

			if (text_0 == text_1) // when the filed is initialized it shows tip one time
			{
				write_hints_0(text_0, size);
				if ((number_0_0 >= 0) && (number_0_0 <= board_size))
				{
					write_hints_number_0(number_0_0, size);
				}

				if ((number_0_1 >= 0) && (number_0_1 <= board_size))
				{
					write_hints_number_sec_0(number_0_1, size);
				}

			}
			else
			{
				write_hints_0(text_0, size);
				if ((number_0_0 >= 0) && (number_0_0 <= size))
				{
					write_hints_number_0(number_0_0, size);
				}

				if ((number_0_1 >= 0) && (number_0_1 <= size))
				{
					write_hints_number_sec_0(number_0_1, size);
				}

				write_hints_1(text_1, size);
				if ((number_1_0 >= 0) && (number_1_0 <= size))
				{
					write_hints_number_1(number_1_0, size);
				}

				if ((number_1_1 >= 0) && (number_1_1 <= size))
				{
					write_hints_number_sec_0(number_1_1, size);
				}
			}


			break;
		}
			case CHANGE_SIZE:
				{
				gotoxy(change_size_column, change_size_row);
				cputs("Enter what size of the board do you want to have: ");
				int size_tens = getch();
				size_tens = size_tens - 48; // because of ASCII 57-x=9
				int size_units = getch();
				size_units = size_units - 48;
				size = 10 * size_tens + size_units;

				clrscr();
				write_border(size);
				write_legend();
	
				remove_board(board);
				board = create_board(x, y, size);
				fill_with_dots(board, size);
				fill_side_values(board, size);
				int amount = draw_expected_fields_amount(size); // amount of expected fields to be drawn
				fill_with_drawn(amount, board, size);
				write_board(board, size);
				break;

			}

		}
		write_board_coordinates(screen_to_board_X(x), screen_to_board_Y(y));
		write_coordinates(screen_to_board_X(x), screen_to_board_Y(y));

		
		
	} while (key != EXIT);
}


int enter_0(int tabX, int tabY, board_t** board, int enter_method, int size)
{
	int rule_1 = check_side_values(tabX, tabY, board, '0');
	int rule_2 = check_rule_2('0', tabX, tabY, board, size);
	int* rule_3 = check_rule_3('0', tabX, tabY, board, size);
	int managed = falsity; // checks if value managed to be entered
	int initialized = board[tabX][tabY].initialized; // if field was initialized by computer, initialized = falsity

	if (initialized == falsity) // check if field can be modifiable
	{
		if (rule_1 == 0) // check if rule_1 is fulfilled
		{
			if (rule_2 == 0)  // check if rule_2 is fulfilled
			{
				if ((rule_3[0] == 0) && (rule_3[1] == 0)) // check if rule_3 is fulfilled
				{
					board[tabX][tabY].value = '0';
					if (enter_method == user)
					{
						board[tabX][tabY].field_colour = user_fulfillment_colour;
					}
					write_board(board, size);
					fill_side_values(board, size);
					managed = truth;
				}
			}
		}
	}
	return managed;
}

int enter_1(int tabX, int tabY, board_t** board, int enter_method, int size)
{
	int rule_1 = check_side_values(tabX, tabY, board, '1');
	int rule_2 = check_rule_2('1', tabX, tabY, board, size);
	int* rule_3 = check_rule_3('1', tabX, tabY, board, size);
	int managed = falsity; // checks if value managed to be entered
	int initialized = board[tabX][tabY].initialized; // if field was initialized by computer, initialized = falsity

	if (initialized == falsity) // check if field can be modifiable
	{
		if (rule_1 == 0) // check if rule_1 is fulfilled
		{
			if (rule_2 == 0)  // check if rule_2 is fulfilled
			{
				if ((rule_3[0] == 0) && (rule_3[1] == 0)) // check if rule_3 is fulfilled
				{
					board[tabX][tabY].value = '1';
					if (enter_method == user)
					{
						board[tabX][tabY].field_colour = user_fulfillment_colour;
					}
					write_board(board, size);
					fill_side_values(board, size);
					managed = truth;
				}
			}
		}
	}
	return managed;
}

board_t** create_board(int x, int y, int size)
{
	board_t **tab = NULL;
	tab = (board_t**)malloc(board_size * sizeof(board_t*));
	if (tab == NULL)
	{
		
	}
	for (int i = 0; i < board_size; i++)
	{
		tab[i] = NULL;
		tab[i] = (board_t*)malloc(board_size * sizeof(board_t));

		if (tab[i] == NULL)
		{
			gotoxy(legend_column, error_row);
			cputs("Error: no memmory for creating a board");
			gotoxy(x, y);
		}
	}
	return tab;
}


void write_board(board_t **tab, int size)
{
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			textcolor(text_colour);
			
			if (tab[i][j].field_colour == user_fulfillment_colour)
			{
				textcolor(user_fulfillment_colour);
			}
			gotoxy(board_column + j, board_row + i); // tab coordinates are opposite to gotoxy coordinates
			putch(tab[i][j].value);

			textcolor(text_colour);
		}
	}
}

void board_colour_reset(board_t **tab, int size)
{
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			tab[i][j].field_colour = text_colour;
		}
	}
}

void write_legend(void)
{
	for (int i = 0; i < legend_amount; i++)
	{
		gotoxy(legend_column, legend_row + i);
		switch (i)
		{
		case 0:
			cputs("Legend:");
			break;

		case 1:
			//new line
			break;

		case 2:
			cputs("Szymon Pietkun 171653");
			break;

		case 3:
			//new line
			break;

		case 4:
			cputs("arrows - moving on the board with cursor");
			break;

		case 5:
			cputs("esc - exit");
			break;

		case 6:
			cputs("n - new game");
			break;

		case 7:
			cputs("0 - entering 0 to the board");
			break;

		case 8:
			cputs("1 - entering 1 to the board");
			break;

		case 9:
			cputs("o - random board filling");
			break;

		case 10:
			cputs("p - simple hint");
			break;

		case 11:
			cputs("r - change of the board size");
			break;

		case 12:
			cputs("k - simple check of the possibility of completing the game");
			break;

		case 13:
			cputs("d - check rule 2");
			break;

		case 14:
			cputs("a - automatic detection of completing the game");
			break;

		case 15:
			cputs("j - backlight of the unequivocal fields");
			break;

		case 16:
			cputs("w - filling backlighted, unequivocal fields");
			break;

		case 17:
			cputs("s - saving the game");
			break;

		case 18:
			cputs("l - loading the game");
			break;

		case 19:
			cputs("b - full check and showing exemplary fields filling");
			break;

		case 20:
			//new line
			break;

		case 21:
			//new line
			break;

		case 22:
			//new line
			break;
		}
	}
}

void write_hints_0(char *text, int size)
{
	char *txt = NULL;
	txt = (char*)malloc(board_size *board_size*board_size* sizeof(char));

	if (txt == NULL)
	{
		gotoxy(legend_column, error_row);
		cputs("Error: no memmory for creating a board");
	}

	sprintf(txt, "HINT: %s", text);
	gotoxy(hints_column, hints_row);
	cputs(txt);
	free(txt);
}

void write_hints_number_0(int number, int size)
{
	char *txt = NULL;
	txt = (char*)malloc(board_size *board_size*board_size * sizeof(char));

	if (txt == NULL)
	{
		gotoxy(legend_column, error_row);
		cputs("Error: no memmory for creating a board");
	}
	sprintf(txt, "%d", number);
	gotoxy(hints_column + 78, hints_row);
	cputs(txt);
	free(txt);
}

void write_hints_number_sec_0(int number, int size)
{
	char *txt = NULL;
	txt = (char*)malloc(board_size *board_size*board_size * sizeof(char));

	if (txt == NULL)
	{
		gotoxy(legend_column, error_row);
		cputs("Error: no memmory for creating a board");
	}
	sprintf(txt, "%d", number);
	gotoxy(hints_column_number_sec, hints_row);
	cputs(txt);
	free(txt);
}


void write_hints_1(char *text, int size)
{
	char *txt = NULL;
	txt = (char*)malloc(board_size *board_size*board_size * sizeof(char));

	if (txt == NULL)
	{
		gotoxy(legend_column, error_row);
		cputs("Error: no memmory for creating a board");
	}
	sprintf(txt, "HINT: %s", text);
	gotoxy(hints_column, hints_row + 1);
	cputs(txt);
	free(txt);
}

void write_hints_number_1(int number, int size)
{
	char *txt = NULL;
	txt = (char*)malloc(board_size * sizeof(char));

	if (txt == NULL)
	{
		gotoxy(legend_column, error_row);
		cputs("Error: no memmory for creating a board");
	}
	sprintf(txt, "%d", number);
	gotoxy(hints_column_number, hints_row + 1);
	cputs(txt);
	free(txt);
}

void write_hints_number_sec_1(int number, int size)
{
	char *txt = NULL;
	txt = (char*)malloc(board_size * sizeof(char));

	if (txt == NULL)
	{
		gotoxy(legend_column, error_row);
		cputs("Error: no memmory for creating a board");
	}
	sprintf(txt, "%d", number);
	gotoxy(hints_column_number_sec, hints_row + 1);
	cputs(txt);
	free(txt);
}


void write_border(int size)
{

	gotoxy(board_column - border_width, board_row - border_width); // border over board
	for (int j = 0; j < border_width; j++)
	{
		for (int i = 0; i < board_size + 2 * border_width; i++)
		{
			cputs(top_border_sign);
		}
		gotoxy(board_column - border_width, board_row - border_width + j + 1);
	}

	gotoxy(board_column - border_width, board_row); // border on the sides of the board
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < border_width; j++)
		{
			cputs(middle_border_sign);
		}
		gotoxy(board_column + board_size, board_row + i);
		for (int j = 0; j < border_width; j++)
		{
			cputs(middle_border_sign);
		}
		gotoxy(board_column - border_width, board_row + 1 + i);
	}

	gotoxy(board_column - border_width, board_row + board_size); // border under the board
	for (int j = 0; j < border_width; j++)
	{
		for (int i = 0; i < board_size + 2 * border_width; i++)
		{
			cputs(bottom_border_sign);
		}
		gotoxy(board_column - border_width, board_row + board_size + j + 1);
	}
}


void write_board_coordinates(int x, int y) // x and y are board coordinates
{
	char txt[coordinates_length];
	sprintf(txt, "cursor coordinates in the board: %2d %2d", x, y);
	gotoxy(legend_column, coordinares_row);
	cputs(txt);
	gotoxy(board_to_screen_X(x), board_to_screen_Y(y));
}

void write_coordinates(int x, int y) // x and y are board coordinates
{
	int currentX = board_to_screen_X(x);
	int currentY = board_to_screen_Y(y);
	char txt[coordinates_length];
	sprintf(txt, "cursor coordinates: %3d %3d", currentX, currentY);
	gotoxy(legend_column, board_coordinates_row);
	cputs(txt);
	gotoxy(board_to_screen_X(x), board_to_screen_Y(y));
}

int screen_to_board_X(int x)
{
	int screen_X = x;
	int board_X = screen_X - board_column + 1; //add "1", because of board coordinates are starting from 1
	return board_X;
}

int screen_to_board_Y(int y)
{
	int screen_Y = y;
	int board_Y = screen_Y - board_row + 1; //add "1", because of board coordinates starting from 1
	return board_Y;
}

int board_to_screen_X(int x)
{
	int board_X = x;
	int screen_X = board_X + board_column - 1; //subtract "1", because of board coordinates starting from 1
	return screen_X;
}

int board_to_screen_Y(int y)
{
	int board_Y = y;
	int screen_Y = board_Y + board_row - 1; //subtract "1", because of board coordinates starting from 1
	return screen_Y;
}


int screen_to_tab_X(int x)
{
	int screen_X = x;
	int tab_X = screen_X - board_column;
	return tab_X;
}

int screen_to_tab_Y(int y)
{
	int screen_Y = y;
	int tab_Y = screen_Y - board_row;
	return tab_Y;
}


char** create_default_board(int x, int y, int size) //with default initialization
{
	char **tab = NULL;
	tab = (char**)malloc(board_size* sizeof(char*));
	if (tab == NULL)
	{
		gotoxy(legend_column, error_row);
		cputs("Error: no memmory for creating a board");
		gotoxy(x, y);
	}
	for (int i = 0; i < board_size; i++)
	{
		tab[i] = NULL;
		tab[i] = (char*)malloc((board_size + 1)* sizeof(char)); // need 1 more place for NULL

		if (tab[i] == NULL)
		{
			gotoxy(legend_column, error_row);
			cputs("Error: no memmory for creating a board");
			gotoxy(x, y);
		}
	}
	fill_with_dots_char(tab, size);
	fill_default_board(tab);
	return tab;
}

void fill_with_dots_char(char ** board, int size) //char board
{
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size + 1; j++)
		{
			board[i][j] = '.';
			if (j == board_size)
			{
				board[i][j] = NULL;
			}
		}
	}
}


void fill_default_board(char** tab)
{
	
	copy_default_rows(tab, "...1.......1", 0);
	copy_default_rows(tab, ".0......1...", 1);
	copy_default_rows(tab, ".....0......", 2);
	copy_default_rows(tab, ".0.1.0.0.0.0", 3);
	copy_default_rows(tab, "1.1....0..1.", 4);
	copy_default_rows(tab, ".....0..1...", 5);
	copy_default_rows(tab, "..11....1...", 6);
	copy_default_rows(tab, "0.....0....0", 7);
	copy_default_rows(tab, ".1..1.....1.", 8);
	copy_default_rows(tab, "..0..0.0....", 9);
	copy_default_rows(tab, "..0..00....0", 10);
	copy_default_rows(tab, "...1..0..1..", 11);

}

void copy_default_rows(char**tab, char* inscription, int what_row)
{
	for (int i = 0; i < template_size; i++)
	{
		tab[what_row][i] = inscription[i]; // copy sign by sign
	}
}

void copy_default(char** tab, board_t** board, int size)
{
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			board[i][j].value = tab[i][j];
			switch (board[i][j].value)
			{
			case '0':
				board[i][j].initialized = truth; // means that this field was initialized at the start with 0
				break;
			case '1':
				board[i][j].initialized = truth; // means that this field was initialized at the start with 1
				break;
			default:
				board[i][j].initialized = falsity;
				break;
			}
		}
	}
	fill_side_values(board, size);
	
}


void fill_side_values(board_t** tab, int size)
{
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if ((j != 0) && (j != (board_size - 1)) && (i != 0) && (i != (board_size - 1)))
			{
				tab[i][j].left_field_value = tab[i][j - 1].value;
				tab[i][j].right_field_value = tab[i][j + 1].value;
				tab[i][j].top_field_value = tab[i - 1][j].value;
				tab[i][j].bottom_field_value = tab[i + 1][j].value;
			}
			else
			{
				if (j == 0) // extremely left side of the board
				{
					tab[i][j].left_field_value = LACK;
					tab[i][j].right_field_value = tab[i][j + 1].value;
					if (i != 0)
					{
						tab[i][j].top_field_value = tab[i - 1][j].value;
					}
					if (i != board_size - 1)
					{
						tab[i][j].bottom_field_value = tab[i + 1][j].value;
					}

				}
				if (j == (board_size - 1)) // extremely right side of the board // not else, becasue next steps must be checked (corners)
				{
					tab[i][j].right_field_value = LACK;
					tab[i][j].left_field_value = tab[i][j - 1].value;
					if (i != 0)
					{
						tab[i][j].top_field_value = tab[i - 1][j].value;
					}
					if (i != board_size - 1)
					{
						tab[i][j].bottom_field_value = tab[i + 1][j].value;
					}
				}
				if (i == 0) // extremely top side of the board
				{
					tab[i][j].top_field_value = LACK;
					tab[i][j].bottom_field_value = tab[i + 1][j].value;
					if (j != 0)
					{
						tab[i][j].left_field_value = tab[i][j - 1].value;
					}
					if (j != board_size - 1)
					{
						tab[i][j].right_field_value = tab[i][j + 1].value;
					}
				}
				if (i == (board_size - 1)) // extremely bottom side of the board
				{
					tab[i][j].bottom_field_value = LACK;
					tab[i][j].top_field_value = tab[i - 1][j].value;
					if (j != 0)
					{
						tab[i][j].left_field_value = tab[i][j - 1].value;
					}
					if (j != board_size - 1)
					{
						tab[i][j].right_field_value = tab[i][j + 1].value;
					}
				}

			}
		}
	}
}


int check_side_values(int x, int y, board_t** tab, char value) // RULE 1
{
	if ((tab[x][y].left_field_value == value) && (tab[x][y].right_field_value == value)) //chceck if LEFT AND RIGHT values are the same as the main field
	{
		return RULE_1_LEFT_RIGHT;
	}

	else if ((tab[x][y].top_field_value == value) && (tab[x][y].bottom_field_value == value)) //chceck if TOP AND BOTTOM values are the same as the main field
	{
		return RULE_1_TOP_BOTTOM;
	}

	else if ((tab[x][y].left_field_value == value) && (tab[x][y - 1].left_field_value == value)) //chceck if TWO LEFT values are the same as the main field
	{
		return RULE_1_LEFT_LEFT; // tab[y-1] won't show error because it isn't checked when first if isn't fulfilled
	}

	else if ((tab[x][y].right_field_value == value) && (tab[x][y + 1].right_field_value == value)) //chceck if TWO RIGHT values are the same as the main field
	{
		return RULE_1_RIGHT_RIGHT;
	}

	else if ((tab[x][y].top_field_value == value) && (tab[x - 1][y].top_field_value == value)) //chceck if TWO TOP values are the same as the main field
	{
		return RULE_1_TOP_TOP;
	}

	else if ((tab[x][y].bottom_field_value == value) && (tab[x + 1][y].bottom_field_value == value)) //chceck if TWO BOTTOM values are the same as the main field
	{
		return RULE_1_BOTTOM_BOTTOM;
	}
	else
	{
		return RULE_TRUTH;
	}
}

////////////////////////////////////////// RULE 2

int count_values_row(char value, int row, board_t** tab, int size) // count amount 
{
	int amount = 0;
	for (int i = 0; i < board_size; i++)
	{
		if (tab[row][i].value == value)
		{
			amount++;
		}
	}
	return amount;
}

int count_values_column(char value, int column, board_t** tab, int size) // count amount
{
	int amount = 0;
	for (int i = 0; i < board_size; i++)
	{
		if (tab[i][column].value == value)
		{
			amount++;
		}
	}
	return amount;
}

int check_rule_2(char value, int x, int y, board_t** tab, int size) // check RULE 2  // x and y are TAB coordinates
{
	int RULE2;
	int amount_r = count_values_row(value, x, tab, size);
	int amount_c = count_values_column(value, y, tab, size);

	if (amount_r < half_board_size && amount_c < half_board_size)
	{
		RULE2 = RULE_TRUTH;
	}
	else if (amount_r >= half_board_size)
	{
		RULE2 = RULE_2_FALSITY_ROW;
	}
	else if (amount_c >= half_board_size)
	{
		RULE2 = RULE_2_FALSITY_COLUMN;
	}
	return RULE2;
}

//////////////////////////////////// RULE 3
char* create_buffer_tab(int x, int y, int size)
{
	char *tab = NULL;
	tab = (char*)malloc(board_size * sizeof(char));
	if (tab == NULL)
	{
		gotoxy(legend_column, error_row);
		cputs("Error: no memmory for creating a board");
		gotoxy(x, y);
	}
	return tab;
}

void copy_row_to_buffer(char value, int x, int y, board_t** tab, char* buffer, int size) // adds value, that user wants to put, to the buffer
{
	for (int i = 0; i < board_size; i++)
	{
		buffer[i] = tab[x][i].value;
	}
	buffer[y] = value;
}

void copy_column_to_buffer(char value, int x, int y, board_t** tab, char* buffer, int size) // adds value, that user wants to put, to the buffer 
{
	for (int i = 0; i < board_size; i++)
	{
		buffer[i] = tab[i][y].value;
	}
	buffer[x] = value;
}

int compare_row(int x, char* buffer, board_t** tab, int size)
{
	int repeats = 0;
	int RULE_3_row = RULE_TRUTH;
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if ((buffer[j] == tab[i][j].value) && (i != x)) // then it won't check its row
			{
				++repeats;
			}
		}
		if (repeats == board_size)
		{
			RULE_3_row = (i+1); // (adds 1, becasuse board coordinates are counted from 1)
			return RULE_3_row;
		}
		repeats = 0;
	}
	return RULE_3_row;
}

int compare_column(int y, char* buffer, board_t** tab, int size)
{
	int repeats = 0;
	int RULE_3_column = RULE_TRUTH;
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if ((buffer[j] == tab[j][i].value) && (i != y)) // then it won't check its column
			{
				++repeats;
			}
		}
		if (repeats == board_size)
		{
			RULE_3_column = (i+1);
			return RULE_3_column;
		}
		repeats = 0;
	}
	return RULE_3_column;
}

int* check_rule_3(char value, int x, int y, board_t** tab, int size) // needs to return what row or column is repeated
{
	int RULE_3[3]; // check rule_3 fulfillment // x and y in array
	char* buffer = create_buffer_tab(x, y, size);
	
	
	copy_row_to_buffer(value, x, y, tab, buffer, size);
	RULE_3[0] = compare_row(x, buffer, tab, size);
	
	copy_column_to_buffer(value, x, y, tab, buffer, size);
	RULE_3[1] = compare_column(y, buffer, tab, size);

	if (RULE_3[0] > 0 && RULE_3[1] > 0) RULE_3[2] = 3;
	else if (RULE_3[0] > 0 && RULE_3[1] == 0) RULE_3[2] = 1;
	else if (RULE_3[0] == 0 && RULE_3[1] > 0) RULE_3[2] = 2;
	

	free(buffer);
	return RULE_3;
}
//////////////
void remove_board(board_t ** board)
{
	free(board);
}

void fill_with_dots(board_t ** board, int size) //structure board
{
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			board[i][j].value = '.';
			board[i][j].initialized = falsity;
		}
	}
}

int draw_expected_fields_amount (int size)
{
	int amount = rand() % draw_range + min_drawn_fields_amount;
	return amount;
}

int draw_values(void)
{
	int value = rand() % (draw_values_range); // draw 0 or 1
	return value;
}

int draw_X_coordinate(int size)
{
	int tabX = rand() % (board_size);
	return tabX;
}

int draw_Y_coordinate(int size)
{
	int tabY = rand() % (board_size);
	return tabY;
}

void fill_with_drawn(int amount, board_t** board, int size)
{
	int entered = 0;
	int tabX;
	int tabY;
	int managed;
	int method = computer;
	for (int i = 0; i < max_draw_attempts; i++)
	{
		tabX = draw_X_coordinate(size);
		tabY = draw_Y_coordinate(size);
		if (entered > amount)
		{
			return;
		}
		int value = draw_values();
		if (value == 0)
		{
			managed = enter_0(tabX, tabY, board, computer, size);
			if (managed)
			{
				board[tabX][tabY].initialized = truth;
				entered++;
				fill_side_values(board, size);
			}
		}
		else if (value == 1)
		{
			managed = enter_1(tabX, tabY, board, computer, size);
			if (managed)
			{
				board[tabX][tabY].initialized = truth;
				entered++;
				fill_side_values(board, size);
			}
		}
		
	}
}
///////

int* check_rules(char value, int tabX, int tabY, board_t** board, int size)
{
	int rule_1[2]; // holds 2 values, becasuse it is needed to differ it from rule 3
	rule_1[0] = check_side_values(tabX, tabY, board, value);
	rule_1[1] = -1;
	int rule_2[2]; // holds 2 values, becasuse it is needed to differ it from rule 3
	rule_2[0] = check_rule_2(value, tabX, tabY, board, size);
	rule_2[1] = -1;
	
	int *rule_3 = check_rule_3(value, tabX, tabY, board, size);
	int managed[2]; // holds 2 values, becasuse it is needed to deffer it from rule 3
	managed[0] = falsity; // checks if value managed to be entered
	managed[1] = -1;
	int initialized[2];
	initialized[0] = board[tabX][tabY].initialized; // if field was initialized by computer, initialized = falsity
	initialized[1] = -1;


	if (initialized[0] == falsity) // check if field can be modifiable
	{
		if (rule_1[0] == 0) // check if rule_1 is fulfilled
		{
			if (rule_2[0] == 0)  // check if rule_2 is fulfilled
			{
				if ( (rule_3[0] == 0) && (rule_3[1] == 0) ) // check if rule_3 is fulfilled
				{
					managed[0] = RULE_TRUTH;
				}
				else
				{
					return rule_3;
				}
			}
			else
			{
				return rule_2;
			}
		}
		else
		{
			return rule_1;
		}
	}
	else
	{
		initialized[0] = UNMODIFIABLE;
		return initialized;
	}
	return managed;
}