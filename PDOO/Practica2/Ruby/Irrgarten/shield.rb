module Irrgarten 
    require_relative 'dice'

    class Shield
        def initialize(protection, uses)
            @protection = protection.to_f
            @uses = uses.to_i
        end

        def attack 
            if @uses > 0
                @uses -= 1
                return @protection
            else
                return 0.0
            end
        end

        def discard
            return Dice.discard_element(@uses)
        end

        def to_s
            return "S[#{@protection}, #{@uses}]"
        end
    end
end
