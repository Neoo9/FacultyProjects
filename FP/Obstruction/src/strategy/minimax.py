class Minimax:
    def minimax_root(self, board, symbol, depth, is_maximizing):
        """
        The 'root' of the tree
        Keeps count of the best move available for the current state of the board
        :param depth: Current depth in the tree
        :param is_maximizing: Keeps count of whether we need to take the max node or the min node
        :return: The optimal move possible
        """
        free_cells = board.get_free_cells()  # get available free cells
        best_move, best_move_final = -9999, None  # we begin with the worst case possible
        for row, col in free_cells:  # take each available cell
            if board.get_cell(row, col) is None:
                affected_cells = board.move(row, col, symbol)  # make the move
                symbol = '0' if symbol == 'X' else 'X'  # switch the symbol for next player, then recursive step
                val = max(best_move, self.minimax(board, symbol, depth - 1, not is_maximizing, -9999, 9999))
                symbol = '0' if symbol == 'X' else 'X'  # switch symbol back
                board.free(affected_cells)  # free the previously marked cells
                if val > best_move:  # check if it's a better move (better heuristics)
                    best_move = val
                    best_move_final = [row, col]
        if best_move_final is None:  # there are some cases in which the ai is sure to lose, given any of the available
            best_move_final = free_cells[0]  # cells; thus, we can take the first available cell (it doesn't really
        return best_move_final  # matter which cell we take)

    def minimax(self, board, symbol, depth, is_maximizing, alpha, beta):
        """
        The 'depth' minimax
        Also uses alpha-beta pruning for faster calculations
        """
        free_cells = board.get_free_cells()  # get free cells
        if board.get_nr_free_cells <= 0:  # if there are no more available moves
            if is_maximizing:  # check if cpu's turn
                return -9999  # cpu lost
            else:
                return 9999  # cpu won
        if depth == 0:  # if we've reached the maximum depth possible
            if is_maximizing:
                return -(board.get_nr_free_cells / 9 + 1)  # don't ask how i've got it, i have no idea either
            else:
                return board.get_nr_free_cells / 9 + 1  # it just works
        if is_maximizing:  # check if cpu's turn
            best_move = -9999  # we're trying to find a move that will help the cpu as much as possible
            for row, col in free_cells:
                if board.get_cell(row, col) is None:
                    affected_cells = board.move(row, col, symbol)
                    symbol = '0' if symbol == 'X' else 'X'
                    best_move = max(best_move, self.minimax(board, symbol, depth - 1, not is_maximizing, alpha, beta))
                    symbol = '0' if symbol == 'X' else 'X'
                    board.free(affected_cells)
                    alpha = max(alpha, best_move)  # update value of alpha
                    if beta <= alpha:
                        return best_move
            return best_move
        else:
            best_move = 9999  # we're trying to find a move that will help the human as little as possible
            for row, col in free_cells:
                if board.get_cell(row, col) is None:
                    affected_cells = board.move(row, col, symbol)
                    symbol = '0' if symbol == 'X' else 'X'
                    best_move = min(best_move, self.minimax(board, symbol, depth - 1, not is_maximizing, alpha, beta))
                    symbol = '0' if symbol == 'X' else 'X'
                    board.free(affected_cells)
                    beta = min(beta, best_move)  # update value of beta
                    if beta <= alpha:
                        return best_move
            return best_move
