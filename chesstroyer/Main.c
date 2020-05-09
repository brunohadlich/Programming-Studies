//Não esquecer de implementar a anulação da variável last_pawn_move_two_ranks no método de execução de movimento
//Implementar casting

#include <stdlib.h>
#include <stdio.h>

typedef enum Piece_Type
{
	pawn,
	rook,
	knight,
	bishop,
	queen,
	king
} Piece_Type;

typedef enum Color
{
	white,
	black
} Color;

typedef struct Piece
{
	Piece_Type type;
	int row;
	int column;
	Color color;
} Piece;

Piece *create_piece(Piece_Type piece_type, Color color, int row, int column)
{
	Piece *piece = malloc(sizeof(piece));
	(*piece).type = piece_type;
	(*piece).color = color;
	(*piece).row = row;
	(*piece).column = column;
	return piece;
}

Piece *board[8][8];//[rows][columns]

void create_teams_pieces(Color color)
{
	int pawns_row = color == white ? 1 : 6,
		others_pieces_row = color == white ? 0 : 7,
		i = 0;
	
	for (;i <= 7; i++)//create the pawns
		board[pawns_row][i] = create_piece(pawn, color, pawns_row, i);
	
	//create the rooks
	board[others_pieces_row][0] = create_piece(rook, color, others_pieces_row, 0);
	board[others_pieces_row][7] = create_piece(rook, color, others_pieces_row, 7);
	
	//create the knights
	board[others_pieces_row][1] = create_piece(knight, color, others_pieces_row, 1);
	board[others_pieces_row][6] = create_piece(knight, color, others_pieces_row, 6);
	
	//create the bishops
	board[others_pieces_row][2] = create_piece(bishop, color, others_pieces_row, 2);
	board[others_pieces_row][5] = create_piece(bishop, color, others_pieces_row, 5);
	
	//create the queen
	board[others_pieces_row][3] = create_piece(queen, color, others_pieces_row, 3);
	
	//create the king
	board[others_pieces_row][4] = create_piece(king, color, others_pieces_row, 4);
}

void create_board()
{
	create_teams_pieces(white);
	create_teams_pieces(black);
}
/*
Piece **get_pieces()
{
	int i, y, qtd;
	
	for (i = 0;i <= 7; i++)
		for (y = 0;y <= 7; y++)
			if (board[i][y] != NULL)
				qtd++;
	
	Piece ** all_pieces = (Piece **)malloc(sizeof(Piece) * qtd);
	
	int n = 0;
	
	for (i = 0;i <= 7; i++)
		for (y = 0;y <= 7; y++)
			if (board[i][y] != NULL)
			{
				all_pieces[n] = board[i][y];
				n++;
			}
	
	return all_pieces;
}

Piece get_piece(int row, int column)
{
	return *board[row][column];
}
*/

int king_in_check = 0;

int would_king_be_in_check(Piece king, int dest_column, int dest_row)
{
	int row = 0, col = 0;

	for (;row <= 7; row++)
		for (col = 0; col <= 7; col++)
			if (board[row][col] != NULL && (*board[row][col]).color != king.color)
				if (is_valid_movement((*board[row][col]), dest_column, dest_row))
					return 1;

	return 0;
}

int can_piece_check_king(Piece enemy, Piece king)
{
	return is_valid_movement(enemy, king.column, king.row);
}

Piece *last_pawn_move_two_ranks;

//Replace return 0 by exceptions
int is_valid_movement(Piece piece, int dest_column, int dest_row)
{
	//error_codes should be implemented in the future
	int error_code = 0;
	
	if (dest_row >= 0 && dest_row <= 7 && dest_column >= 0 && dest_column <= 7)
	{
		if (king_in_check && piece.type != king)
			error_code = 1;
			
		switch(piece.type)
		{
			case pawn:
				if (piece.color == white)
					if(!(((dest_row == 3) &&
						  (piece.row == 1) &&
						  (piece.column == dest_column) &&
						  (board[2][piece.column] == NULL) && 
						  (board[3][piece.column] == NULL)) ||
						 ((dest_row == piece.row + 1) &&
						  (piece.column == dest_column) &&
						  (board[piece.row + 1][piece.column] == NULL)) ||
						 ((dest_row == piece.row + 1) &&
						  (piece.column == dest_column + 1) &&
						  (board[piece.row + 1][piece.column + 1] != NULL) &&
						  ((*board[piece.row + 1][piece.column + 1]).color == black)) ||
						 ((dest_row == piece.row + 1) &&
						  (piece.column == dest_column - 1) &&
						  (board[piece.row + 1][piece.column - 1] != NULL) &&
						  ((*board[piece.row + 1][piece.column - 1]).color == black)) ||
						 ((last_pawn_move_two_ranks != NULL) &&
						  ((*last_pawn_move_two_ranks).row == piece.row) &&
						  (abs((*last_pawn_move_two_ranks).column - piece.column) == 1) &&
						  (dest_column == (*last_pawn_move_two_ranks).column) &&
						  (piece.row + 1 == dest_row))))
						error_code = 1;
				else
					if(!(((dest_row == 4) &&
						  (piece.row == 6) &&
						  (piece.column == dest_column) &&
						  (board[5][piece.column] == NULL) && 
						  (board[4][piece.column] == NULL)) ||
						 ((dest_row == piece.row - 1) &&
						  (piece.column == dest_column) &&
						  (board[piece.row - 1][piece.column] == NULL)) ||
						 ((dest_row == piece.row - 1) &&
						  (piece.column == dest_column + 1) &&
						  (board[piece.row - 1][piece.column + 1] != NULL) &&
						  ((*board[piece.row - 1][piece.column + 1]).color == white)) ||
						 ((dest_row == piece.row - 1) &&
						  (piece.column == dest_column - 1) &&
						  (board[piece.row - 1][piece.column - 1] != NULL) &&
						  ((*board[piece.row - 1][piece.column - 1]).color == white)) ||
						 ((last_pawn_move_two_ranks != NULL) &&
						  ((*last_pawn_move_two_ranks).row == piece.row) &&
						  (abs((*last_pawn_move_two_ranks).column - piece.column) == 1) &&
						  (dest_column == (*last_pawn_move_two_ranks).column) &&
						  (piece.row - 1 == dest_row))))
						  error_code = 1;
			case rook:
				error_code = 1;
				
				if ((piece.row != dest_row && piece.column == dest_column) || (piece.row == dest_row && piece.column != dest_column))
				{
					int i;
					
					if (dest_row != piece.row)
					{
						for (i = piece.row + 1; i < dest_row; i++)
							if (board[i][dest_column] != NULL)
								goto error_rook;
						//Não esquecer do tratamento para casting
						if   (!((board[dest_row][dest_column] == NULL ||
								 (board[dest_row][dest_column] != NULL &&
								  (*board[dest_row][dest_column]).color != piece.color))))
							goto error_rook;
					}
					else
					{
						for (i = piece.row - 1; i > dest_row; i--)
							if (board[dest_row][i] != NULL)
								goto error_rook;
						//Não esquecer do tratamento para casting
						if   (!((board[dest_row][dest_column] == NULL ||
								 (board[dest_row][dest_column] != NULL &&
								  (*board[dest_row][dest_column]).color != piece.color))))
							goto error_rook;
					}
				}
				else
					goto error_rook;
				error_code = 0;
				error_rook:
			case knight:
				if   (!((piece.column + 1 == dest_column &&
						 piece.row + 2 == dest_row) ||
						(piece.column - 1 == dest_column &&
						 piece.row + 2 == dest_row) ||
						(piece.column + 2 == dest_column &&
						 piece.row + 1 == dest_row) ||
						(piece.column + 2 == dest_column &&
						 piece.row - 1 == dest_row) ||
						(piece.column - 2 == dest_column &&
						 piece.row + 1 == dest_row) ||
						(piece.column - 2 == dest_column &&
						 piece.row - 1 == dest_row) ||
						(piece.column + 1 == dest_column &&
						 piece.row - 2 == dest_row) ||
						(piece.column - 1 == dest_column &&
						 piece.row - 2 == dest_row)))
					error_code = 1;
				else
					if (board[dest_row][dest_column] != NULL &&
						(*board[dest_row][dest_column]).color == piece.color)
						error_code = 1;
			case bishop:
				{
					int delta_col = piece.column - dest_column,
						delta_row = piece.row - dest_row,
						x = abs(delta_col),
						y = abs(delta_row),
						xx;
					
					if (x != y)
						error_code = 1;
					else
					{
						for (xx = 1; xx < x; xx++)
							if  (board[dest_row + ((delta_row / y) * xx)][dest_column + ((delta_col / x) * xx)] != NULL)
								error_code = 1;
						if (board[dest_row][dest_column] != NULL &&
						   (*board[dest_row][dest_column]).color == piece.color)
							error_code = 1;
					}
				}
			case queen:
				error_code = 1;
				
				if (abs(dest_row - piece.row) == abs(dest_column - piece.column))
				{
					int delta_col = piece.column - dest_column,
						delta_row = piece.row - dest_row,
						x = abs(delta_col),
						y = abs(delta_row),
						xx;
					
					for (xx = 1; xx < x; xx++)
						if  (board[dest_row + ((delta_row / y) * xx)][dest_column + ((delta_col / x) * xx)] != NULL)
							goto error_queen;
					if (board[dest_row][dest_column] != NULL &&
					   (*board[dest_row][dest_column]).color == piece.color)
						goto error_queen;
				}
				else if (dest_row != piece.row && dest_column == piece.column)
				{
					int i;
					
					if (dest_row != piece.row)
					{
						for (i = dest_row > piece.row ? piece.row + 1 : piece.row - 1; i != dest_row; dest_row > piece.row ? i++ : i--)
							if (board[i][dest_column] != NULL)
								goto error_queen;
						
						if   (!(board[dest_row][dest_column] != NULL &&
								(*board[dest_row][dest_column]).color == piece.color))
							goto error_queen;
					}
				} else if (dest_column != piece.column && dest_row == piece.row)
				{
					int i;
					
					for (i = dest_column > piece.column ? piece.column + 1 : piece.column - 1; i != dest_column; dest_column > piece.column ? i++ : i--)
						if (board[dest_row][i] != NULL)
							goto error_queen;
					
					if   (!(board[dest_row][dest_column] != NULL &&
							(*board[dest_row][dest_column]).color == piece.color))
						goto error_queen;
				} else
					goto error_queen;
				error_code = 0;
				error_queen:
			case king:
				if (!((((abs(dest_row - piece.row) == 1) &&
					    (abs(dest_column - piece.column) <= 1)) ||
					   ((abs(dest_column - piece.column) == 1) &&
					    (abs(dest_row - piece.row) <= 1))) &&
				      !would_king_be_in_check(piece, dest_column, dest_row)))
				{
					//Throws: Destination will put king in check
					return 0;
				}
		}
	}
	else
		error_code = 1;
	
	if (error_code)
		return 0;
	
	return 1;
}

int main(int argc, char ** argv)
{
	//Allocate 16 pieces for each side, 8 pawns, 2 rooks, 2 knights, 2 bishops, 1 queen, 1 king
	
	create_board();
	
	int i, y;
	
	for (i = 0;i <= 7; i++){
		for (y = 0;y <= 7; y++){
			printf("%d - %d - %d - %d\n", i, y, (*board[i][y]).type, (*board[i][y]).color);
		}
	}
	//return 0;
	//return 0;
}
