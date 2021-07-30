import time

class Solver:

    def __init__(self, display):

        self.display = 1 - display

        self.squares = [[0,1,2,9,10,11,18,19,20], [3,4,5,12,13,14,21,22,23], [6,7,8,15,16,17,24,25,26],
                       [27,28,29,36,37,38,45,46,47], [30,31,32,39,40,41,48,49,50], [33,34,35,42,43,44,51,52,53],
                       [54,55,56,63,64,65,72,73,74], [57,58,59,66,67,68,75,76,77], [60,61,62,69,70,71,78,79,80]]

        self.sqsquare = [0, 0, 0, 1, 1, 1, 2, 2, 2,
                         0, 0, 0, 1, 1, 1, 2, 2, 2,
                         0, 0, 0, 1, 1, 1, 2, 2, 2,
                         3, 3, 3, 4, 4, 4, 5, 5, 5,
                         3, 3, 3, 4, 4, 4, 5, 5, 5,
                         3, 3, 3, 4, 4, 4, 5, 5, 5,
                         6, 6, 6, 7, 7, 7, 8, 8, 8,
                         6, 6, 6, 7, 7, 7, 8, 8, 8,
                         6, 6, 6, 7, 7, 7, 8, 8, 8]


    def display_matrix(self):
        if self.display:
            for i in range(9): print(*self.matrix[i*9:i*9+9])

    def isvalid(self, number, square):
        line = square // 9
        col = square % 9
        sqr = self.sqsquare[square]
        for sq in range(line*9, line*9+9):
            if self.matrix[sq] == number: return 0
        for sq in range(col, 81, 9):
            if self.matrix[sq] == number: return 0
        for sq in range(9):
            if self.matrix[self.squares[sqr][sq]] == number: return 0
        return 1

    def iter_solve(self, sqr):
        if self.frozen[sqr]:
            if sqr < 80:
                r = self.iter_solve(sqr+1)
                if not r: return 0
            else: self.display_matrix(); return 0
        else:
            for nb in range(1, 10):
                if self.isvalid(nb, sqr):
                    self.matrix[sqr] = nb
                    if sqr == 80: self.display_matrix(); return 0
                    r = self.iter_solve(sqr+1)
                    if not r: return 0
                if nb == 9: self.matrix[sqr] = 0
        return 1

    def solve(self):
        self.matrix = [0, 0, 6, 1, 0, 0, 9, 5, 0,
                       9, 0, 3, 5, 0, 0, 0, 0, 0,
                       0, 5, 0, 0, 0, 0, 0, 7, 0,
                       0, 2, 8, 9, 4, 0, 0, 0, 0,
                       0, 0, 7, 0, 2, 0, 0, 0, 0,
                       6, 0, 0, 0, 0, 0, 0, 8, 0,
                       0, 8, 0, 0, 0, 0, 0, 9, 0,
                       3, 0, 1, 0, 6, 0, 0, 0, 8,
                       0, 0, 0, 2, 1, 0, 0, 0, 0]

        self.frozen = []

        for i in range(81):
            self.frozen.append(self.matrix[i] > 0)

        self.iter_solve(0)

def run(display=0):
    solver = Solver(display)
    solver.solve()

def timer():
    start_time = time.time()
    for _ in range(10):
        run(1)
    print("--- %s seconds ---" % (time.time() - start_time))

timer()

