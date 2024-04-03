module Irrgarten
    require_relative 'dice'

    class Monster
        @@INITIAL_HEALTH = 5
        @@INVALID_POS = 0

        def initialize(name, intelligence, strength)
            @name = name
            @intelligence = intelligence
            @strength = strength
            @health = @@INITIAL_HEALTH
            @row = @@INVALID_POS
            @col = @@INVALID_POS
        end

        def dead
            return @health <= 0
        end

        def attack
            return Dice.intensity(@strength)
        end

        def pos(row, col)
            @row = row
            @col = col
        end

        def to_s 
            return "M[#{@name}, #{@intelligence}, #{@strength}, #{@health}, #{@row}, #{@col}]"
        end

        def got_wounded 
            @health -= 1
        end
    end
end
