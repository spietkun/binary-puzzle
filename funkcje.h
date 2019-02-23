#ifndef FUNKCJE_H
#define FUNKCJE_H
#include"stale.h"
#include <cstdlib>
#include <ctime>

akcje_t download_key(void); 

void key_action(int x, int y, board_t** board, char** default_tab, int size);
int enter_0(int tabX, int tabY, board_t** board, int enter_method, int size);
int enter_1(int tabX, int tabY, board_t** board, int enter_method, int size);

board_t** create_board(int x, int y, int size);



void write_board(board_t **tab, int size);
void board_colour_reset(board_t **tab, int size);

void write_legend();
void write_hints_0(char *text, int size);
void write_hints_1(char *text, int size);
void write_hints_number_0(int number, int size);
void write_hints_number_1(int number, int size);
void write_hints_number_sec_0(int number, int size);
void write_hints_number_sec_1(int number, int size);
void write_border(int size);

void write_coordinates(int x, int y);
void write_board_coordinates(int x, int y);

int screen_to_board_X(int x);
int screen_to_board_Y(int y);
int board_to_screen_X(int x);
int board_to_screen_Y(int y);

int screen_to_tab_X(int x);
int screen_to_tab_Y(int y);

char** create_default_board(int x, int y, int size);
void fill_with_dots_char(char ** board, int size);
void fill_default_board(char** tab);
void copy_default_rows(char**tab, char* napis, int what_row);
void copy_default(char** tab, board_t** board, int size); //function "fill_side_values" is inside


void fill_side_values(board_t** tab, int size); // in order to know what fields are standing next to the field 
int check_side_values(int x, int y, board_t** tab, char value); // check RULE 1
 
/////////////////// RULE_2

int count_values_row(char value, int y, board_t** tab, int size); // count amount 
int count_values_column(char value, int x, board_t** tab, int size); // count amount
int check_rule_2(char value, int x, int y, board_t** tab, int size); // check RULE 2	

/////////////////// RULE_3

char* create_buffer_tab(int x, int y, int size);
void copy_row_to_buffer(char value, int x, int y, board_t** tab, char* buffer, int size);
void copy_column_to_buffer(char value, int x, int y, board_t** tab, char* buffer, int size);
int compare_row(int x, char* buffer, board_t** tab, int size);
int compare_column(int y, char* buffer, board_t** tab, int size);
int* check_rule_3(char value, int x, int y, board_t** tab, int size); // check RULE 3	

///////////////////

void remove_board(board_t ** board);
void fill_with_dots(board_t ** board, int size);
int draw_expected_fields_amount(int size);
int draw_values(void);
int draw_X_coordinate(int size);
int draw_Y_coordinate(int size);
void fill_with_drawn(int amount, board_t** board, int size);

int* check_rules(char value, int tabX, int tabY, board_t** board, int size);

#endif
