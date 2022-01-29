from texttable import Texttable


class Board:
    def __init__(self, rows, cols):
        self._rows = rows
        self._cols = cols
        self._data = [[None for j in range(self._cols)] for i in range(self._rows)]
        self._free_cells = self._rows * self._cols

    @property
    def nr_rows(self):
        return self._rows

    @property
    def nr_cols(self):
        return self._cols

    @property
    def get_board(self):
        return self._data

    def get_cell(self, x, y):
        return self._data[x][y]

    @property
    def get_nr_free_cells(self):
        return self._free_cells

    def get_free_cells(self):
        """
        Returns a list with all available cells on the board
        """
        free_cells = []
        for row in range(self._rows):
            for col in range(self._cols):
                if self._data[row][col] is None:
                    free_cells.append([row, col])
        return free_cells

    def move(self, x, y, symbol):
        """
        Performs the move
        :param x: Row coord
        :param y: Column coord
        :param symbol: 'X' or '0'
        :return: List of modified cells (marked with '#' and 'X'/'0')
        """
        affected_cells = []
        # check if valid
        if symbol not in ['X', '0']:
            raise Exception('Invalid symbol')
        if self._data[x][y] == 'X' or self._data[x][y] == '0' or self._data[x][y] == '#':
            raise Exception('Square already taken')
        # take the 3x3 square, with the center at (x, y)
        for row in range(max(x - 1, 0), min(x + 2, self._rows)):
            for col in range(max(y - 1, 0), min(y + 2, self._cols)):
                if self._data[row][col] is None:
                    self._data[row][col] = '#'  # mark the cell
                    self._free_cells -= 1
                    affected_cells.append([row, col])  # add it to the modified cells list
        self._data[x][y] = symbol  # mark the center
        return affected_cells

    def free(self, affected_cells):
        """
        Empties the cells in the list
        """
        for row, col in affected_cells:  # take each cell in the list
            if self._data[row][col] is not None:  # check if it's not None (just in case)
                self._data[row][col] = None  # 'un-mark' it
                self._free_cells += 1

    def __str__(self):
        """
        String representation of the board using Texttable
        """
        t = Texttable()
        header_data = [' ']
        for col in range(self._cols):
            header_data.append(col)
        t.header(header_data)
        for row in range(self._rows):
            row_data = []
            for index in self._data[row]:
                if index is None:
                    row_data.append(' ')
                elif index == 'X' or index == '0' or index == '#':
                    row_data.append(index)
            t.add_row([row] + row_data)
        return t.draw()
