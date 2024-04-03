class GameState
    def initialize(labyrinthv, players, monsters, current_player, winner, log)
        @labyrinthv = labyrinthv
        @players = players
        @monsters = monsters
        @current_player = current_player
        @winner = winner
        @log = log
    end

    def get_labyrinthv
        return @labyrinthv
    end

    def get_players
        return @players
    end

    