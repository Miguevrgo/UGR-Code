require_relative 'dice'
require_relative 'player'
require_relative 'monster'
require_relative 'labyrinth'
require_relative 'game_state'
require_relative 'game_character'
require_relative 'orientation'

module Irrgarten
  class Game
    @@MAX_ROUNDS = 10

    #------------------------|Custom Labyrinth|------------------------
    @@ROWS = 11
    @@COLS = 10

    @@NMONSTERS = 5
    @@MONSTERS_POS = [[0, 0], [1, 6], [2, 2], [5, 5], [7, 1]]

    @@NBLOCKS = 4
    @@BLOCKS_POS = [
      [Orientation::HORIZONTAL, 0, 1, 4],
      [Orientation::HORIZONTAL, 9, 0, 2],
      [Orientation::VERTICAL, 2, 8, 7],
      [Orientation::VERTICAL, 3, 3, 4]
    ]
    #------------------------------------------------------------------

    def initialize(n_players)
      exit_row = Dice.random_pos(@@ROWS)
      exit_col = Dice.random_pos(@@COLS)

      @players = []
      @monsters = []

      n_players.times do |i|
        @players.push(Player.new(i, Dice.random_intelligence, Dice.random_strength))
      end

      @current_player_index = Dice.who_starts(n_players)
      @current_player = @players[@current_player_index]

      @labyrinth = Labyrinth.new(@@ROWS, @@COLS, exit_row, exit_col)
      configure_labyrinth
      @labyrinth.spread_players(@players)

      @log = "\n╔════════════════════════════╗\n" \
             "║    The Game has started!   ║\n" \
             "╚════════════════════════════╝\n\n"
    end

    # This method is called by play method in Controller to advance the game moving a player
    # in the preferred direction. The method returns true if the game has finished, false otherwise.
    # @param [Direction] preferred_direction The direction the player wants to move
    # @return [Boolean] True if the game has finished, false otherwise
    def next_step(preferred_direction)
      @log = ''
      dead = @current_player.dead

      if !dead
        direction = actual_direction(preferred_direction)
        log_player_no_orders if direction != preferred_direction

        monster = @labyrinth.put_player(direction, @current_player)

        if monster.nil?
          log_no_monster
        else
          winner = combat(monster)
          manage_reward(winner)
        end
      else
        manage_resurrection
      end

      end_game = finished

      next_player unless end_game

      end_game
    end

    # Returns whether the game has finished or not
    # @return [Boolean]
    def finished
      @labyrinth.have_a_winner
    end

    # Returns the current state of the game as a GameState object to be shown by the view
    # @return [GameState] The current state of the game
    def game_state
      players_str  = @players.map(&:to_s).join("\n")
      monsters_str = @monsters.map(&:to_s).join("\n")

      GameState.new(@labyrinth.to_s, players_str, monsters_str, @current_player_index, finished, @log)
    end

    private

    # Configures the labyrinth with the blocks and monsters in the positions defined by the constants
    # @@BLOCKS_POS and @@MONSTERS_POS for it to initialize the game with the custom labyrinth configuration
    # defined in the constants.
    # @return [void]
    def configure_labyrinth
      @@BLOCKS_POS.each do |block|
        orientation, row, col, size = block
        @labyrinth.add_block(orientation, row, col, size)
      end

      i = 0
      @@MONSTERS_POS.each do |pos|
        row, col = pos
        @monsters.push(Monster.new("Monster #{i} ", Dice.random_intelligence, Dice.random_strength))
        @labyrinth.add_monster(row, col, @monsters.last)
        i += 1
      end
    end

    # Advances the game to the next player in the list of players
    # @return [void]
    def next_player
      @current_player_index = (@current_player_index + 1) % @players.size
      @current_player = @players[@current_player_index]
    end

    # Moves the player in the preferred direction and returns the actual direction the player will move
    # based on the valid moves in the labyrinth
    # @param [Direction] preferred_direction The direction the player wants to move
    def actual_direction(preferred_direction)
      current_row = @current_player.row
      current_col = @current_player.col

      valid_moves = @labyrinth.valid_moves(current_row, current_col)
      @current_player.move(preferred_direction, valid_moves)
    end

    # Manages the combat between the current player and a monster, it keeps fighting until one of the two
    # is dead or the maximum number of rounds (@@MAX_ROUNDS) is reached.
    # @param [Monster] monster The monster the player is fighting against
    # @return [GameCharacter] The winner of the combat
    def combat(monster)
      rounds = 0
      winner = GameCharacter::PLAYER
      lose = monster.defend(@current_player.attack)

      while !lose && rounds < @@MAX_ROUNDS
        winner = GameCharacter::MONSTER
        rounds += 1

        lose = @current_player.defend(monster.attack)

        unless lose
          winner = GameCharacter::PLAYER
          lose = monster.defend(@current_player.attack)
        end
      end

      log_rounds(rounds, @@MAX_ROUNDS)
      winner
    end

    # Manages the reward provided to the winner of the combat and logs the result of the combat
    # @param [GameCharacter] winner The winner of the combat
    # @return [void]
    def manage_reward(winner)
      if winner == GameCharacter::PLAYER
        @current_player.receive_reward
        log_player_won
      else
        log_monster_won
      end
    end

    # Manages the resurrection of a player if it is dead and logs the result of the resurrection
    # @return [void]
    def manage_resurrection
      if Dice.resurrect_player
        @current_player.resurrect
        log_resurrected

        fuzzy = FuzzyPlayer.new(@current_player)
        @players[@current_player_index] = fuzzy
        @labyrinth.update_pos(fuzzy)
      else
        log_player_skip_turn
      end
    end

    # Logs the result of the combat when a player wins
    # @return [void]
    def log_player_won
      @log += "Player #{@current_player_index} has won.\n"
    end

    # Logs the result of the combat when a monster wins
    # @return [void]
    def log_monster_won
      @log += "A Monster has won the fight.\n"
    end

    # Logs the result of the resurrection of a player
    # @return [void]
    def log_resurrected
      @log += "Player #{@current_player_index} has resurrected.\n"
    end

    # Logs the result of a player skipping the turn
    # @return [void]
    def log_player_skip_turn
      @log += "Player #{@current_player_index} has skipped the turn.\n"
    end

    # Logs the result of a player not following the orded provided because it was not possible
    # @return [void]
    def log_player_no_orders
      @log += "Player #{@current_player_index} didn't follow the order.\n"
    end

    # Logs the result of a player moving to an empty cell or not being able to move
    # @return [void]
    def log_no_monster
      @log += "Player #{@current_player_index} has moved to an empty cell or it wasn't possible to move.\n"
    end

    # Logs the number of rounds of a combat
    # @param [Integer] rounds The number of rounds of the combat
    # @param [Integer] max The maximum number of rounds allowed
    # @return [void]
    def log_rounds(rounds, max)
      @log += "Rounds: #{rounds}|#{max}.\n"
    end
  end
end
