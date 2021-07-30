#include <iostream>

class solver
{
public:
//    int[81] matrix = {0, 0, 0, 0, 0, 0, 0, 0, 0,
//                      0, 0, 0, 0, 0, 0, 0, 0, 0,
//                      0, 0, 0, 0, 0, 0, 0, 0, 0,
//                      0, 0, 0, 0, 0, 0, 0, 0, 0,
//                      0, 0, 0, 0, 0, 0, 0, 0, 0,
//                      0, 0, 0, 0, 0, 0, 0, 0, 0,
//                      0, 0, 0, 0, 0, 0, 0, 0, 0,
//                      0, 0, 0, 0, 0, 0, 0, 0, 0,
//                      0, 0, 0, 0, 0, 0, 0, 0, 0};
    int matrix[81];
    int frozen[81];
    void solve(int grd[81]);
    int iter_solve(int sqr);
    void display_matrix();
    int isvalid(int number, int square);
    int squares[9][9] = {{0,1,2,9,10,11,18,19,20}, {3,4,5,12,13,14,21,22,23}, {6,7,8,15,16,17,24,25,26},
                        {27,28,29,36,37,38,45,46,47}, {30,31,32,39,40,41,48,49,50}, {33,34,35,42,43,44,51,52,53},
                        {54,55,56,63,64,65,72,73,74}, {57,58,59,66,67,68,75,76,77}, {60,61,62,69,70,71,78,79,80}};
    int sqsquare[81] = {0, 0, 0, 1, 1, 1, 2, 2, 2,
                        0, 0, 0, 1, 1, 1, 2, 2, 2,
                        0, 0, 0, 1, 1, 1, 2, 2, 2,
                        3, 3, 3, 4, 4, 4, 5, 5, 5,
                        3, 3, 3, 4, 4, 4, 5, 5, 5,
                        3, 3, 3, 4, 4, 4, 5, 5, 5,
                        6, 6, 6, 7, 7, 7, 8, 8, 8,
                        6, 6, 6, 7, 7, 7, 8, 8, 8,
                        6, 6, 6, 7, 7, 7, 8, 8, 8};
};

void solver::solve(int grd[81])
{
    // copy grid
    for (int i(0); i<81; ++i)
    {
        matrix[i] = grd[i];
    }
    // freeze base matrix
    for (int i(0); i<81; ++i)
    {
        if (matrix[i])
        {
            frozen[i] = 1;
        }
        else
        {
            frozen[i] = 0;
        }
    }
    // iterative solve
    iter_solve(0);
}

void solver::display_matrix()
{
    for (int i(0); i<9; ++i)
    {
        for (int j(0); j<9; ++j)
        {
            std::cout << matrix[9*i+j] << " ";
        }
        std::cout << std::endl;
    }
}

int solver::isvalid(int number, int square)
{
    int line = square / 9;
    int col = square % 9;
    int sqr = sqsquare[square];
    for (int sq(line * 9); sq<line*9 + 9; ++sq)
    {
        if (matrix[sq] == number)
        {
            return 0;
        }
    }
    for (int sq(col); sq<81; sq+=9)
    {
        if (matrix[sq] == number)
        {
            return 0;
        }
    }
    for (int sq(0); sq<9; ++sq)
    {
        if (matrix[squares[sqr][sq]] == number)
        {
            return 0;
        }
    }
    return 1;
}

int solver::iter_solve(int sqr)
{
    int r;
    if (!frozen[sqr])
    {
        for (int nb(1); nb<10; ++nb)
        {
            if (isvalid(nb, sqr))
            {
                matrix[sqr] = nb;
                if (sqr == 80)
                {
                    return 0;
                }
                r = iter_solve(sqr+1);
                if (!r){return 0;}
            }
            if (nb==9)
            {
                matrix[sqr] = 0;
            }
        }
    }
    else
    {
        if (sqr < 80)
        {
            r = iter_solve(sqr+1);
            if (!r){return 0;}
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int grid[81] = {0, 0, 6, 1, 0, 0, 9, 5, 0,
                   9, 0, 3, 5, 0, 0, 0, 0, 0,
                   0, 5, 0, 0, 0, 0, 0, 7, 0,
                   0, 2, 8, 9, 4, 0, 0, 0, 0,
                   0, 0, 7, 0, 2, 0, 0, 0, 0,
                   6, 0, 0, 0, 0, 0, 0, 8, 0,
                   0, 8, 0, 0, 0, 0, 0, 9, 0,
                   3, 0, 1, 0, 6, 0, 0, 0, 8,
                   0, 0, 0, 2, 1, 0, 0, 0, 0};
    solver slv;
    for (int i(0); i<1; ++i) // structure used as a timer function
    {
        slv.solve(grid);
    }
    slv.display_matrix();
}
