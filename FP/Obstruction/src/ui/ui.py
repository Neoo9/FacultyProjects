from src.game.game import Game


class UI:
    def __init__(self, rows, cols):
        self._game = Game(rows, cols)

    def read_human_move(self):
        """
        Reads human player's coordinates for next move
        :return: row and column of next move
        """
        coord = input("Give coordinates (line, column): ")
        try:
            row, col = int(coord[0]), int(coord[1])
            self._game.board.get_cell(row, col)
        except Exception:
            raise ValueError("Invalid coordinates")
        return row, col

    def start(self):
        human_turn = True if input("Do you want to play first? (y/n): ") == 'y' else False
        human_symbol = 'X' if human_turn else '0'
        cpu_symbol = 'X' if not human_turn else '0'
        while True:
            try:
                print(self._game.board)
                if human_turn:
                    coord = self.read_human_move()
                    self._game.human_move(coord[0], coord[1], human_symbol)
                    if self._game.board.get_nr_free_cells <= 0:
                        print("You win")
                        print(self._game.board)
                        return
                else:
                    self._game.cpu_move(cpu_symbol)
                    if self._game.board.get_nr_free_cells <= 0:
                        print("You lost")
                        print(self._game.board)
                        return
                human_turn = not human_turn
            except Exception as err:
                print("ERROR! " + str(type(err).__name__) + ': ' + str(err) + '\n')
                input("Press any key to continue...\n")
