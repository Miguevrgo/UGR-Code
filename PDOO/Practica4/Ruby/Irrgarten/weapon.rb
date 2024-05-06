module Irrgarten
    require_relative 'dice'

    class Weapon
        def initialize(power, uses)
            @power = power
            @uses = uses
        end

        # Returns the attack power of the weapon if it has uses left, or 0.0 otherwise
        # @return [Float] The attack power of the weapon
        def attack
            if @uses > 0
                @uses -= 1
                return @power
            else
                return 0.0
            end
        end

        # Returns whether the weapon is discarded or not based on the number of uses left
        # @return [Boolean] whether the weapon is discarded or not
        def discard
            return Dice.discard_element(@uses)
        end

        # Returns a string representation of the weapon
        # @return [String] The string representation of the weapon
        def to_s
            return "W[#{@power}, #{@uses}]"
        end
    end
end
