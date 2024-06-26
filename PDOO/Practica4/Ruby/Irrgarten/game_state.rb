module Irrgarten
  class GameState
    def initialize(labyrinth, players, monsters, current_player, winner, log)
      @labyrinth = labyrinth
      @players        = players
      @monsters       = monsters
      @current_player = current_player
      @winner         = winner
      @log            = log
    end

    attr_reader :labyrinth, :players, :monsters, :current_player, :winner, :log
  end
end
