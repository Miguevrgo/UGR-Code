module Irrgarten
  class CombatElement
    def initialize(effect, uses)
      @effect = effect
      @uses = uses
    end

    # Returns whether the combat element is discarded or not based on the number of uses left
    # @return [Boolean] whether the weapon is discarded or not
    def discard
      Dice.discard_element(uses)
    end

    # Returns a string representation of the CombatElement
    # @return [String] The string representation of the CombatElement
    def to_s
      "[#{@effect}, #{@uses}]"
    end

    protected

    # Returns the effect of the combat element when there are uses left decreasing them,
    # and 0 otherwise
    # @return [Float] effect of the comabat element
    def produce_effect
      return 0.0 unless @uses.positive?

      @uses -= 1
      @effect
    end
  end
end
