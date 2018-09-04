#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE	(s->n)

#define START_POS_X     0
#define START_POS_Y     0
#define FINISH_POS_X    (TABLE_SIZE - 1)
#define FINISH_POS_Y    (TABLE_SIZE - 1)

#define EMPTY_SQUARE	0
#define OCCUPIED_SQUARE	1

typedef struct _State
{
    int   n;
    int** table;
    int   pos_x;
    int   pos_y;
} State;

#define NUMBER_OF_DIRECTIONS 4
#define UP    0
#define RIGHT 1
#define DOWN  2
#define LEFT  3
typedef int Direction;

State* State_Init  (int n);
void   State_Finish(State* s);

int  State_IsSolution(State* s);
int  State_CanMove   (State* s, Direction d);
void State_Move      (State* s, Direction d);
void State_Unmove    (State* s, Direction d);

int CalculatePaths(State* s);

int main(int argc, const char* argv[])
{
    int i;

    for (i = 3; i < 7; i++)
    {
        State* s = State_Init(i);
        printf("Number of paths for a square matrix of size %dx%d is: %d\n", i, i, CalculatePaths(s));
        State_Finish(s);
    }

    return 0;
}

State* State_Init(int n)
{
    int i, j;

    State* s = (State*)malloc(sizeof(State));

    s->n = n;
    s->table = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++)
        s->table[i] = (int*)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            s->table[i][j] = EMPTY_SQUARE;

    s->table[START_POS_Y][START_POS_X] = OCCUPIED_SQUARE;
    s->pos_x = START_POS_X;
    s->pos_y = START_POS_Y;

    return s;
}

void State_Finish(State* s)
{
    int i;

    for (i = 0; i < s->n; i++)
        free(s->table[i]);

    free(s->table);

    free(s);
}

int  State_IsSolution(State* s)
{
    return (s->pos_x == FINISH_POS_X) && (s->pos_y == FINISH_POS_Y);
}

int  State_CanMove(State* s, Direction d)
{
    switch (d)
    {
        case UP:
            if (s->pos_y == 0) return 0;
            return s->table[s->pos_y - 1][s->pos_x] != OCCUPIED_SQUARE;
        case RIGHT:
            if (s->pos_x == (TABLE_SIZE - 1)) return 0;
            return s->table[s->pos_y][s->pos_x + 1] != OCCUPIED_SQUARE;
        case DOWN:
            if (s->pos_y == (TABLE_SIZE - 1)) return 0;
            return s->table[s->pos_y + 1][s->pos_x] != OCCUPIED_SQUARE;
        case LEFT:
            if (s->pos_x == 0) return 0;
            return s->table[s->pos_y][s->pos_x - 1] != OCCUPIED_SQUARE;
    }

    return 0;
}

void State_Move(State* s, Direction d)
{
    switch (d)
    {
        case UP:
            s->pos_y--;
            break;
        case RIGHT:
            s->pos_x++;
            break;
        case DOWN:
            s->pos_y++;
            break;
        case LEFT:
            s->pos_x--;
            break;
    }

    s->table[s->pos_y][s->pos_x] = OCCUPIED_SQUARE;
}

void State_Unmove(State* s, Direction d)
{
    s->table[s->pos_y][s->pos_x] = EMPTY_SQUARE;
    
    switch (d)
    {
        case UP:
            s->pos_y++;
            break;
        case RIGHT:
            s->pos_x--;
            break;
        case DOWN:
            s->pos_y--;
            break;
        case LEFT:
            s->pos_x++;
            break;
    }
}

int CalculatePaths(State* s)
{
    int i, total = 0;

    if (State_IsSolution(s))
    {
        return 1;
    }

    for (i = UP; i < NUMBER_OF_DIRECTIONS; i++)
    {
        if (State_CanMove(s, i))
        {
            State_Move(s, i);
            total += CalculatePaths(s);
            State_Unmove(s, i);
        }
    }

    return total;
}

