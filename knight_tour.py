class knight_tour:
    def __init__(self, row_number, col_number):
        self.row_number = row_number
        self.col_number = col_number
        self.row_move = [1, 1, -1, -1, 2, 2, -2, -2]
        self.col_move = [2, -2, -2, 2, 1, -1, -1, 1]
        self.chess = []
        for i in range(1, row_number + 1):
            for j in range(1, col_number + 1):
                new_cell = {"row": i, "col": j, "mark": None}
                self.chess.append(new_cell)
        self.tour = []

    def is_finished(self):
        return (
            self.tour[-1]["row"] == self.last_cell["row"]
            and self.tour[-1]["col"] == self.last_cell["col"]
        )

    def mark(self, marked_cell, mark):
        for cell in self.chess:
            if cell["row"] == marked_cell["row"] and cell["col"] == marked_cell["col"]:
                cell["mark"] = mark

    def next(self, current, i):
        row = current["row"] + self.row_move[i]
        col = current["col"] + self.col_move[i]
        for cell in self.chess:
            if cell["row"] == row and cell["col"] == col:
                if cell["mark"] is None:
                    cell["mark"] = True
                    new_cell = {"row": row, "col": col}
                    return new_cell
        return False

    def run_tour(self):
        if self.is_finished():
            return True

        current = self.tour[-1]

        for i in range(8):
            next_cell = self.next(current, i)
            if next_cell:
                self.tour.append(next_cell)
                if self.run_tour():
                    return True
                else:
                    self.tour.pop()
                    self.mark(next_cell, False)
        self.mark(current, False)
        return False

    def start_tour(self, first_cell, last_cell):
        first_cell["mark"] = True
        last_cell["mark"] = True
        self.last_cell = last_cell
        self.tour.append(first_cell)
        self.mark(first_cell, True)
        if self.run_tour():
            return self.tour
        else:
            return False


def print_chess(chess, row, col):
    for i in range(row):
        for j in range(col):
            print(chess[0]["mark"], end=" ")
            chess.remove(chess[0])
        print()


dims = input().split(" ")
row_number = int(dims[0])
col_number = int(dims[1])

start = input().split(" ")
start_row = int(start[0])
start_col = int(start[1])
start_cell = {"row": start_row, "col": start_col, "mark": True}

stop = input().split(" ")
stop_row = int(stop[0])
stop_col = int(stop[1])
stop_cell = {"row": stop_row, "col": stop_col, "mark": True}

knight_tour = knight_tour(row_number, col_number)

tour = knight_tour.start_tour(start_cell, stop_cell)
if tour:
    print_chess(knight_tour.chess, row_number, col_number)
else:
    print("No Way!")

