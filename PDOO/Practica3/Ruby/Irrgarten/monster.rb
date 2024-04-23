require_relative 'dice'

module Irrgarten

    class Monster
        @@INITIAL_HEALTH = 5

        def initialize(name, intelligence, strength)
            @name = name
            @intelligence = intelligence
            @strength = strength
            @health = @@INITIAL_HEALTH
            @row = 0
            @col = 0
        end

        def dead
            return @health <= 0
        end

        def attack
            return Dice.intensity(@strength)
        end

        def set_pos(row, col)
            @row = row
            @col = col
        end

        def to_s
            return_string = "M[#{@name}, " +
            ("%.1f♥, %.3f🧠, %.3f🗡]" % [@health, @intelligence, @strength])
            return_string += " (#{@row}, #{@col}) ]"
            return return_string
        end

        def got_wounded
            @health -= 1
        end
    end
end
