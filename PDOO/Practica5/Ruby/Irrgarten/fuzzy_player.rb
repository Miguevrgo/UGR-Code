require_relative 'dice'
module Irrgarten
  class FuzzyPlayer < Player
    def move(direction, valid_moves)
      if !valid_moves.empty? && !valid_moves.include?(direction)
        Dice.next_step(valid_moves[0], valid_moves, @intelligence)
      else
        Dice.next_step(direction, valid_moves, @intelligence)
      end
    end

    def attack
      sum_weapons + Dice.intensity(@strength)
    end

    def to_s
      "Fuzzy#{super}"
    end

    protected

    def defensive_energy
      sum_shields + Dice.intensity(@intelligence)
    end
  end
end
