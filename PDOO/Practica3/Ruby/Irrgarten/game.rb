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
        @@ROWS = 15
        @@COLS = 15

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

            @players = Array.new
            @monsters = Array.new

            n_players.times do |i|
                @players.push(Player.new(i, Dice.random_intelligence, Dice.random_strength))
            end

            @current_player_index = Dice.who_starts(n_players)
            @current_player = @players[@current_player_index]

            @labyrinth = Labyrinth.new(@@ROWS, @@COLS, exit_row, exit_col)
            configure_labyrinth
            @labyrinth.spread_players(@players)

            @log = "\n╔════════════════════════════╗\n" +
                   "║    The Game has started!   ║\n" +
                   "╚════════════════════════════╝\n\n";
        end

        def next_step(preferred_direction)
            dead = @current_player.dead
            direction = actual_direction(preferred_direction)

            if (!dead)
                if (direction != preferred_direction)
                    self.log_player_no_orders
                end

                monster = (@labyrinth.put_player(direction, @current_player))
                if (monster == nil)
                    self.log_no_monster
                else
                    winner = self.combat(monster)
                    self.manage_reward(winner)
                end
            else
                self.manage_resurrection
            end

            end_game = self.finished
            if (!end_game)
                self.next_player
            end
            return end_game
        end


        def finished
            @labyrinth.have_a_winner
        end

        def game_state
            players_str = ""
            @players.each do |player|
                players_str += player.to_s + "\n"
            end

            monsters_str = ""
            @monsters.each do |monster|
                monsters_str += monster.to_s + "\n"
            end

            GameState.new(@labyrinth.to_s, players_str, monsters_str, @current_player_index, self.finished, @log)
        end

        def configure_labyrinth

            @@BLOCKS_POS.each do |block|
                orientation, row, col, size = block
                @labyrinth.add_block(orientation, row, col, size)
            end

            @@MONSTERS_POS.each do |pos|
                row, col = pos
                @monsters.push(Monster.new("Monster " + pos.to_s, Dice.random_intelligence, Dice.random_strength))
                @labyrinth.add_monster(row, col, @monsters.last)
            end
        end

        def next_player
            @current_player_index = (@current_player + 1) % players.size
            @current_player = @players[@current_player_index]
        end

        def actual_direction(preferred_direction)
            current_row = @current_player.row
            current_col = @current_player.col

            valid_moves = labyrinth.valid_moves(current_row,current_col)
            current_player.move(preferred_direction, valid_moves)
        end

        def combat(monster)
            rounds = 0
            winner = GameCharacter::PLAYER
            lose = monster.defend(@current_player.attack)

            while (!lose && rounds < @@MAX_ROUNDS) do
                winner = GameCharacter::MONSTER
                rounds += 1

                lose = @current_player.defend(monster.attack)

                if (!lose)
                    winner = GameCharacter::PLAYER
                    lose = monster.defend(@current_player.attack)
                end
            end

            winner
        end

        def manage_reward(winner)
            if (winner == GameCharacter::PLAYER)
                @current_player.receive_reward
                log_player_won
            else
                log_monster_won
            end
        end

        def manage_resurrection
            if (Dice.resurrect_player)
                @current_player.resurrect
                log_resurrected
            else
                log_player_skip_turn
            end
        end

        def log_player_won
            log += "Player #{@current_player_index} has won.\n"
        end

        def log_monster_won
            log += "A Monster has won the fight.\n"
        end

        def log_resurrected
            log += "Player #{@current_player_index} has resurrected.\n"
        end

        def log_player_skip_turn
            log += "Player #{@current_player_index} has skipped the turn.\n"
        end

        def log_player_no_orders
            log += "Player #{@current_player_index} didn't follow the order.\n"
        end

        def log_no_monster
            log += "Player #{@current_player_index} has moved to an empty cell or it wasn't possible to move.\n"
        end

        def log_rounds(rounds, max)
            log += "Rounds: #{rounds}|#{max}.\n"
        end
    end
end
