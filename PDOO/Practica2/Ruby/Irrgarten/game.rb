module Irrgarten

require_relative 'dice'
require_relative 'player'
require_relative 'monster'
require_relative 'labyrinth'
require_relative 'game_state'
require_relative 'game_character'
require_relative 'orientation'

    class Game
        @@MAX_ROUNDS = 10 # Variable para el combate
        
        #------------|Se personaliza el laberinto|---------------- 
        @@ROWS = 8
        @@COLS = 8
        @@MONSTER_INIT = [
            ["Monster 0", 0, 0],
            ["Monster 1", 0, 7],
            ["Monster 2", 7, 0],
            ["Monster 3", 7, 7]
        ]

        @@BLOCKS = [
            [Orientation::HORIZONTAL, 0, 0, 3],
            [Orientation::HORIZONTAL, 0, 4, 3],

        ]
        #----------------------------------------------------------

        def initialize(n_players)
            @players = Array.new
            @monsters = Array.new

            n_players.times do |i|
                @players.push(Player.new(i, Dice.random_intelligence, Dice.random_strength))
            end
        end

        def finished
            return @labyrinth.have_a_winner
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

            return GameState.new(@labyrinth.to_s, players_str, monsters_str, current_player_index, self.finished, @log)
        end

        def configure_labyrinth

            @@BLOCKS.each do |block|
                orientation, row, col, length = block
                @labyrinth.add_block(orientation, row, col, length)
            end

            @@MONSTER_INIT.each do |monster|
                name, row, col = monster
                @monsters.push(Monster.new(name, Dice.random_intelligence, Dice.random_strength))
                @labyrinth.add_monster(row, col, monster)
            end
        end

        def next_player
            @current_player_index = (@current_player + 1) % players.size
            @current_player = @players[@current_player_index]
        end

        def actual_direction(preferred_direction)
            #INFORMATION PROVIDED IN THE NEXT PRACTICE
        end

        def combat(monster)
            #INFORMATION PROVIDED IN THE NEXT PRACTICE
        end

        def manage_reward(winner)
            #INFORMATION PROVIDED IN THE NEXT PRACTICE
        end

        def manage_resurrection()
            #INFORMATION PROVIDED IN THE NEXT PRACTICE
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
