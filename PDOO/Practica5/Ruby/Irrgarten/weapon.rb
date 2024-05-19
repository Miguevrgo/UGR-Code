require_relative 'dice'
require_relative 'combat_element'

module Irrgarten
  class Weapon < CombatElement
    # Returns the attack power of the weapon if it has uses left, or 0.0 otherwise
    # @return [Float] The attack power of the weapon
    def attack
      produce_effect
    end

    # Returns whether the weapon is discarded or not based on the number of uses left
    # @return [Boolean] whether the weapon is discarded or not
    def discard
      Dice.discard_element(@uses)
    end

    # Returns a string representation of the weapon
    # @return [String] The string representation of the weapon
    def to_s
      "W#{super}"
    end
  end
end
