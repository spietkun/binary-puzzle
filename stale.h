#ifndef STALE_H
#define STALE_H

typedef enum //values for legend options
{
	LEFT_ARROW,
	RIGHT_ARROW,
	UP_ARROW,
	DOWN_ARROW,
	EXIT,
	NEW_GAME,
	ENTER_0,
	ENTER_1,
	RANDOM_BOARD,
	SIMPLE_HINT,
	CHANGE_SIZE,
	CHECK_POSSIBILTY_END,
	CHECK_RULE2,
	END_AUTODETECTION,
	BACKLIGHT_UNEQUIVOCAL,
	FULLFILLMENT_BACKLIGHT_UNEQUIVOCAL,
	SAVE_GAME,
	LOAD_GAME,
	FULL_CHECK,
	WRONG_KEY,
}akcje_t;

#define user_fulfillment_colour YELLOW
#define text_colour WHITE

#define truth 1
#define falsity 0

#define zero_inside 0
#define one_inside 1


typedef struct //board  type
{
	char value;
	int initialized; // holds information if the field was initialized at the start with 0 or 1
	int field_colour;
	char left_field_value;
	char right_field_value;
	char top_field_value;
	char bottom_field_value;
}board_t;

#define board_size size //board size
#define board_fields_amount (board_size*board_size)
#define template_size 12

#define board_column 130 // starter board column
#define board_row 8 // starter board row

#define legend_column 9 // starter legend column
#define legend_row 2 // starter legend row
#define legend_amount 24 // including lines for "new line"
#define legend_length 54

#define hints_column (legend_column + legend_length + 8) 
#define hints_row (legend_row)
#define hints_column_number (hints_column + 78)
#define hints_column_number_sec (hints_column_number+2)

#define coordinares_row 23 
#define board_coordinates_row (coordinares_row + 1)
#define error_row (board_coordinates_row + 1)
#define change_size_column (legend_column)
#define change_size_row (error_row+1)

#define border_width 2
#define top_border_sign "/"
#define middle_border_sign "/"
#define bottom_border_sign "/"

#define coordinates_length 50

#define side_fields_amount 2

//////// RULE 1
typedef enum // reasons why rule 1 is not fulfilled
{
	RULE_TRUTH, // rule is fulfilled // used for every rule
	UNMODIFIABLE,
	RULE_1_LEFT_RIGHT, // left and right fields are the same 
	RULE_1_TOP_BOTTOM,
	RULE_1_LEFT_LEFT,
	RULE_1_RIGHT_RIGHT,
	RULE_1_TOP_TOP,
	RULE_1_BOTTOM_BOTTOM,
	RULE_2_FALSITY_COLUMN,
	RULE_2_FALSITY_ROW,
}rules_t;

#define LACK 'L'

#define half_board_size board_size/2

#define max_draw_attempts (board_fields_amount*board_fields_amount)
#define min_drawn_fields_amount (20*board_fields_amount/100) //percent
#define max_drawn_fields_amount (30*board_fields_amount/100) //percent
#define draw_range (max_drawn_fields_amount - min_drawn_fields_amount)
#define computer 1
#define user 0


#define draw_values_range 2

#endif