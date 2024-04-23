require_relative 'dice'
require_relative 'directions'

module Irrgarten

    class Labyrinth
        @@BLOCK_CHAR = 'X'
        @@EMPTY_CHAR = '-'
        @@MONSTER_CHAR = 'M'
        @@COMBAT_CHAR = 'C'
        @@EXIT_CHAR = 'E'

        @@INVALID_POS = -1

        @@ROW = 0
        @@COL = 1

        def initialize(n_rows, n_cols, exit_row, exit_col)
            @n_rows     = n_rows
            @n_cols     = n_cols
            @exit_row   = exit_row
            @exit_col   = exit_col

            @monsters   = Array.new(@n_rows) { Array.new(@n_cols) }
            @players    = Array.new(@n_rows) { Array.new(@n_cols) }
            @labyrinth  = Array.new(@n_rows) { Array.new(@n_cols, @@EMPTY_CHAR) }

            @labyrinth[@exit_row][@exit_col] = @@EXIT_CHAR
        end

        def spread_players(players)
            players.each do |player|
                pos = self.random_empty_pos
                self.put_player2D(@@INVALID_POS,@@INVALID_POS,pos[@@ROW], pos[@@COL], player)
            end
        end

        def have_a_winner
            @players[@exit_row][@exit_col] != nil
        end

        def to_s
            return_string = "╔"
            @n_cols.times do
                return_string += "══"
            end
            return_string += "╗\n"

            @labyrinth.each do |row|
                return_string += "║"
                row.each do |cell|
                    return_string += cell.to_s + " "
                end
                return_string += "║\n"
            end

            return_string += "╚"
            @n_cols.times do
                return_string += "══"
            end
            return_string += "╝"
            return return_string
        end

        def add_monster(row, col, monster)
            if (pos_ok(row, col) && empty_pos(row, col))
                @monsters[row][col] = monster
                @labyrinth[row][col] = @@MONSTER_CHAR
                monster.set_pos(row, col)
            end
        end

        def put_player(direction, player)
            old_row = player.row
            old_col = player.col

            new_pos = dir_2_pos(old_row, old_col, direction)
            put_player2D(old_row, old_col, new_pos[@@ROW], new_pos[@@COL], player)
        end

        def add_block(orientation, start_row, start_col, length)
            if (orientation == Orientation::VERTICAL)
                inc_row = 1
                inc_col = 0
            else
                inc_row = 0
                inc_col = 1
            end

            row = start_row
            col = start_col

            while (pos_ok(row,col) && empty_pos(row,col) && length > 0) do
                @labyrinth[row][col] = @@BLOCK_CHAR
                row += inc_row
                col += inc_col
                length -= 1
            end
        end

        def valid_moves(row, col)
            output = Arrat.new
            if (can_step_on(row-1,col))
                output.add(Directions::UP)
            end
            if (can_step_on(row+1,col))
                output.add(Directions::DOWN)
            end
            if (can_step_on(row,col-1))
                output.add(Directions::LEFT)
            end
            if (can_step_on(row,col+1))
                output.add(Directions::RIGHT)
            end
            output
        end
        #------------|Metodos Privados|----------------
        private

        def pos_ok(row, col)
            row >= 0 && row < @n_rows && col >= 0 && col < @n_cols
        end

        def empty_pos(row, col)
            @labyrinth[row][col] == @@EMPTY_CHAR
        end

        def monster_pos(row, col)
            @labyrinth[row][col] == @@MONSTER_CHAR
        end

        def exit_pos(row, col)
            @labyrinth[row][col] == @@EXIT_CHAR
        end

        def combat_pos(row, col)
            @labyrinth[row][col] == @@COMBAT_CHAR
        end

        def can_step_on(row, col)
            pos_ok(row, col) && (empty_pos(row, col) || exit_pos(row, col) || monster_pos(row, col))
        end

        def update_old_pos(row, col)
            if (pos_ok(row,col))
                if (combat_pos(row,col))
                    @labyrinth[row][col] = @@MONSTER_CHAR
                else
                    @labyrinth[row][col] = @@EMPTY_CHAR
                end
            end
        end

        def dir_2_pos(row, col, direction)
            case direction
                when Directions::LEFT
                    return [row,col-1]
                when Directions::RIGHT
                    return [row,col+1]
                when Directions::UP
                    return [row-1,col]
                when Directions::DOWN
                    return [row+1,col]
            end
        end

        def random_empty_pos
            begin
                row = Dice.random_pos(@n_rows)
                col = Dice.random_pos(@n_cols)
            end until empty_pos(row, col)

            [row, col]
        end

        def put_player2D(old_row, old_col, row, col, player)
            output = nil

            if (can_step_on(row, col))
                if (pos_ok(old_row, old_col))
                    if (player == @players[old_row][old_col])
                        update_old_pos(old_row, old_col)
                        @players[old_row][old_col] = nil
                    end
                end
            end

            if (monster_pos(row,col))
                @labyrinth[row][col] = @@COMBAT_CHAR
                output = @monsters[row][col]
            else
                @labyrinth[row][col] = player.number
            end

            @players[row][col] = player
            player.set_pos(row,col)
            return output
        end
    end
end
