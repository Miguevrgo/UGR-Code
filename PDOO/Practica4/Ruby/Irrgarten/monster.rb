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

        # Returns whether the monster is dead or not
        # @return [Boolean]
        def dead
            return @health <= 0
        end

        # Returns the attack power of the monster based on its strength
        # @return [Float] The attack power of the monster
        def attack
            return Dice.intensity(@strength)
        end

        # Sets the position of the monster in the labyrinth
        # @param [Integer] row
        # @param [Integer] col
        def set_pos(row, col)
            @row = row
            @col = col
        end

        # Returns a string representation of the monster
        # @return [String] The string representation of the monster
        def to_s
            return_string = "M[#{@name}, " +
            ("%.1f♥, %.3f🧠, %.3f🗡]" % [@health, @intelligence, @strength])
            return_string += " (#{@row}, #{@col}) ]"
            return return_string
        end

        # Defends the monster from an attack, reducing its health if the attack is successful
        # and returning whether the monster is dead or not
        # @param [Float] received_attack The attack power received by the monster
        # @return [Boolean] True if the monster is dead, false otherwise
        def defend(received_attack)
            is_dead = dead
            if (!is_dead)
                if(Dice.intensity(@intelligence) < received_attack)
                    got_wounded
                    is_dead
                end
            end

            return is_dead
        end

        private

        # Reduces the health of the monster by one unit
        def got_wounded
            @health -= 1
        end
    end
end
