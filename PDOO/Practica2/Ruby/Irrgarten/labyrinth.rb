module Irrgarten

require_relative 'dice'
require_relative 'directions'

    class Labyrinth
        @@BLOCK_CHAR = 'X'
        @@EMPTY_CHAR = '-'
        @@MONSTER_CHAR = 'M'
        @@COMBAT_CHAR = 'C'
        @@EXIT_CHAR = 'E'

        @@ROW = 0
        @@COL = 1

        def initialize(n_rows, n_cols, exit_row, exit_col)
            @n_rows     = n_rows.to_i # TODO: Check if it is necessary to convert to integer
            @n_cols     = n_cols.to_i
            @exit_row   = exit_row.to_i
            @exit_col   = exit_col.to_i

            @monsters   = Array.new(@n_rows) { Array.new(@n_cols) }
            @players    = Array.new(@n_rows) { Array.new(@n_cols) }
            @labyrinth  = Array.new(@n_rows) { Array.new(@n_cols, @@EMPTY_CHAR) }

            @labyrinth[@exit_row][@exit_col] = @@EXIT_CHAR
        end

        def have_a_winner
            return @players[@exit_row][@exit_col] != nil
        end

        def to_s
            result = ""
            @labyrinth.each do |row|
                row.each do |cell|
                    result += cell
                end
                result += "\n"
            end
            return result
        end

        def add_monster(row, col, monster)
            if (pos_ok(row, col) && empty_pos(row, col))
                @monsters[row][col] = monster
                @labyrinth[row][col] = @@MONSTER_CHAR
                monster.pos(row, col)
            end
        end

        def put_player(direction, player)
            #INFORMATION PROVIDED IN NEXT PRACTICE
            throw "Not implemented"
        end
        
        def add_block(orientation, start_row, start_col, length)
            #INFORMATION PROVIDED IN NEXT PRACTICE
            throw "Not implemented"
        end

        def valid_moves(row, col)
            #INFORMATION PROVIDED IN NEXT PRACTICE
            throw "Not implemented"
        end
        #------------|Metodos Privados|----------------
        private

        def pos_ok(row, col)
            return row >= 0 && row < @n_rows && col >= 0 && col < @n_cols
        end

        def empty_pos(row, col)
            return @labyrinth[row][col] == @@EMPTY_CHAR
        end

        def monster_pos(row, col)
            return @labyrinth[row][col] == @@MONSTER_CHAR
        end

        def exit_pos(row, col)
            return @labyrinth[row][col] == @@EXIT_CHAR
        end

        def combat_pos(row, col)
            return @labyrinth[row][col] == @@COMBAT_CHAR
        end

        def can_step_on(row, col)
            return pos_ok(row,col) && (empty_pos(row,col) || exit_pos(row,col) || monster_pos(row,col))
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
            end while !empty_pos(row,col)
           
            return [row,col]
        end
        
        def put_player2D(old_row, old_col, row, col, player)
            #INFORMATION PROVIDED IN NEXT PRACTICE
            throw "Not implemented"
        end
    end
end