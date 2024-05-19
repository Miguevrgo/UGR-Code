require_relative 'dice'
require_relative 'combat_element'

module Irrgarten
  class Shield < CombatElement
    # Returns the protection value of the shield if it has uses left, or 0.0 otherwise
    # @return [Float] The protection value of the shield
    def protect
      produce_effect
    end

    # Returns whether the shield is discarded or not based on the number of uses left
    # @return [Boolean] whether the shield is discarded or not
    def discard
      Dice.discard_element(@uses)
    end

    # Returns a string representation of the shield
    # @return [String] The string representation of the shield
    def to_s
      "S#{super}"
    end
  end
end
