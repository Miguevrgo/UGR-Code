require_relative 'dice'

module Irrgarten

    class Shield
        def initialize(protection, uses)
            @protection = protection
            @uses = uses
        end

        # Returns the protection value of the shield if it has uses left, or 0.0 otherwise
        # @return [Float] The protection value of the shield
        def protect
            if @uses > 0
                @uses -= 1
                return @protection
            else
                return 0.0
            end
        end

        # Returns whether the shield is discarded or not based on the number of uses left
        # @return [Boolean] whether the shield is discarded or not
        def discard
            return Dice.discard_element(@uses)
        end

        # Returns a string representation of the shield
        # @return [String] The string representation of the shield
        def to_s
            return "S[#{@protection}, #{@uses}]"
        end
    end
end
