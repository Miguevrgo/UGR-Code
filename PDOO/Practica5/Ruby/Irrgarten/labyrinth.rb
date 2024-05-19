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

    # This method is called by the game to spread the players in the labyrinth
    # in random positions. The method ensures that no two players are in the same position.
    # @param [Array<Player>] players The players to spread all over the labyrinth
    # @return [void]
    def spread_players(players)
      players.each do |player|
        pos = random_empty_pos
        put_player2D(@@INVALID_POS, @@INVALID_POS, pos[@@ROW], pos[@@COL], player)
      end
    end

    # This method is called by the game to know if a player has reached the exit of the labyrinth,
    # which means that the game has finished.
    # @return [Boolean] True if a player has reached the exit, false otherwise
    def have_a_winner
      !@players[@exit_row][@exit_col].nil?
    end

    # This method is called by the game to draw the labyrinth in the console.
    # @return [String] The labyrinth string representation
    def to_s
      top_border = "╔#{'══' * @n_cols}╗"
      bottom_border = "╚#{'══' * @n_cols}╝"

      labyrinth_string = @labyrinth.map do |row|
        '║' + row.map { |cell| "#{cell} " }.join + '║'
      end.join("\n")

      "#{top_border}\n#{labyrinth_string}\n#{bottom_border}"
    end

    # This method is called by the Game to add monsters to the labyrinth
    # @param [Integer] row The row where the monster will be placed
    # @param [Integer] col The column where the monster will be placed
    # @param [Monster] monster The monster to be placed
    # @return [void]
    def add_monster(row, col, monster)
      return unless pos_ok(row, col) && empty_pos(row, col)

      @monsters[row][col] = monster
      @labyrinth[row][col] = @@MONSTER_CHAR
      monster.set_pos(row, col)
    end

    # This method is called by the Game move a player in the labyrinth
    # in the preferred direction. The method returns the monster if the player
    # has found one, nil otherwise.
    def put_player(direction, player)
      old_row = player.row
      old_col = player.col

      new_pos = dir_2_pos(old_row, old_col, direction)
      put_player2D(old_row, old_col, new_pos[@@ROW], new_pos[@@COL], player)
    end

    # This method is called by the Game to add blocks to the labyrinth
    # @param [Integer] orientation The orientation of the block (vertical or horizontal)
    # @param [Integer] start_row The row where the block starts
    # @param [Integer] start_col The column where the block starts
    # @param [Integer] length The length of the block
    # @return [void]
    def add_block(orientation, start_row, start_col, length)
      if orientation == Orientation::VERTICAL
        inc_row = 1
        inc_col = 0
      else
        inc_row = 0
        inc_col = 1
      end

      row = start_row
      col = start_col

      while pos_ok(row, col) && empty_pos(row, col) && length.positive?
        @labyrinth[row][col] = @@BLOCK_CHAR
        row += inc_row
        col += inc_col
        length -= 1
      end
    end

    # This method is called to know which moves are valid for a player in a given position
    # @param [Integer] row The row where the player is
    # @param [Integer] col The column where the player is
    # @return [Array<Direction>] The valid moves for the player
    def valid_moves(row, col)
      output = []
      output.push(Directions::UP) if can_step_on(row - 1, col)
      output.push(Directions::DOWN) if can_step_on(row + 1, col)
      output.push(Directions::LEFT) if can_step_on(row, col - 1)
      output.push(Directions::RIGHT) if can_step_on(row, col + 1)
      output
    end

    private

    # This method is used to know if a position is within the labyrinth
    # @param [Integer] row The row to check
    # @param [Integer] col The column to check
    # @return [Boolean] True if the position is within the labyrinth, false otherwise
    def pos_ok(row, col)
      row >= 0 && row < @n_rows && col >= 0 && col < @n_cols
    end

    # This method is used to know if a position is empty
    # @param [Integer] row The row to check
    # @param [Integer] col The column to check
    # @return [Boolean] True if the position is empty, false otherwise
    def empty_pos(row, col)
      @labyrinth[row][col] == @@EMPTY_CHAR
    end

    # This method is used to know if a position has a monster
    # @param [Integer] row The row to check
    # @param [Integer] col The column to check
    # @return [Boolean] True if the position has a monster, false otherwise
    def monster_pos(row, col)
      @labyrinth[row][col] == @@MONSTER_CHAR
    end

    # This method is used to know if a position is the exit cell
    # @param [Integer] row The row to check
    # @param [Integer] col The column to check
    # @return [Boolean] True if the position is the exit, false otherwise
    def exit_pos(row, col)
      @labyrinth[row][col] == @@EXIT_CHAR
    end

    # This method is used to know if a position is a combat cell
    # @param [Integer] row The row to check
    # @param [Integer] col The column to check
    # @return [Boolean] True if the position is a combat cell, false otherwise
    def combat_pos(row, col)
      @labyrinth[row][col] == @@COMBAT_CHAR
    end

    # This method is used to know if a position can be stepped on, this is, if it is
    # either empty, the exit or a monster
    # @param [Integer] row The row to check
    # @param [Integer] col The column to check
    # @return [Boolean] True if the position can be stepped on, false otherwise
    def can_step_on(row, col)
      pos_ok(row, col) && (empty_pos(row, col) || exit_pos(row, col) || monster_pos(row, col))
    end

    # This method updates the position of the player who is turned into a FuzzyPlayer
    # when resurrected
    # @param [FuzzyPlayer] Fuzzy player whose position has to be updated
    def update_pos(fuzzy)
      @players[fuzzy.row][fuzzy.col] = fuzzy
    end

    # This method is used to update the position of a player in the labyrinth, if the position
    # was a combat cell, it is updated to a monster cell, otherwise it is updated to an empty cell
    # @param [Integer] row The row to update
    # @param [Integer] col The column to update
    # @return [void]
    def update_old_pos(row, col)
      return unless pos_ok(row, col)

      @labyrinth[row][col] = combat_pos(row, col) ? @@MONSTER_CHAR : @@EMPTY_CHAR
    end

    # This method is used to convert a direction into a position
    # @param [Integer] row The row to start from
    # @param [Integer] col The column to start from
    # @param [Direction] direction The direction to convert
    # @return [Array<Integer>] The position resulting from the conversion
    def dir_2_pos(row, col, direction)
      case direction
      when Directions::LEFT
        [row, col - 1]
      when Directions::RIGHT
        [row, col + 1]
      when Directions::UP
        [row - 1, col]
      when Directions::DOWN
        [row + 1, col]
      end
    end

    # This method is used to get a random empty position in the labyrinth, to do so,
    # it generates random positions using the Dice until it finds an empty one
    # @return [Array<Integer>] The random empty position
    def random_empty_pos
      loop do
        row = Dice.random_pos(@n_rows)
        col = Dice.random_pos(@n_cols)
        break if empty_pos(row, col)
      end

      [row, col]
    end

    # This method is used to update the position of a player in the labyrinth, if the position
    # is a monster, it is returned, otherwise, the player's position is updated in the labyrinth
    # @param [Integer] old_row The row where the player was
    # @param [Integer] old_col The column where the player was
    # @param [Integer] row The row where the player is
    # @param [Integer] col The column where the player is
    # @param [Player] player The player to update
    def put_player2D(old_row, old_col, row, col, player)
      output = nil

      if can_step_on(row, col) && pos_ok(old_row, old_col) && (player == @players[old_row][old_col])
        update_old_pos(old_row, old_col)
        @players[old_row][old_col] = nil
      end

      if monster_pos(row, col)
        @labyrinth[row][col] = @@COMBAT_CHAR
        output = @monsters[row][col]
      else
        @labyrinth[row][col] = player.number
      end

      @players[row][col] = player
      player.set_pos(row, col)
      output
    end
  end
end
