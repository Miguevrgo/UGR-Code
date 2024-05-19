require_relative 'Controller/controller'
require_relative 'UI/textUI'
require_relative 'dice'
require_relative 'directions'
require_relative 'game_character'
require_relative 'game_state'
require_relative 'game'
require_relative 'labyrinth'
require_relative 'orientation'
require_relative 'monster'
require_relative 'shield'
require_relative 'player'
require_relative 'weapon'

module Irrgarten
  class MainP3
    @@NUM_PLAYERS = 1 # Number of players in the game

    def self.main
      view = UI::TextUI.new
      game = Game.new(@@NUM_PLAYERS)

      controller = Control::Controller.new(game, view)
      controller.play
    end
  end

  MainP3.main
end
