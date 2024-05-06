require_relative 'dice'
require_relative 'weapon'
require_relative 'shield'
require_relative 'directions'

module Irrgarten

    class Player
        @@MAX_WEAPONS = 2
        @@MAX_SHIELDS = 3
        @@INITIAL_HEALTH = 10
        @@HITS2LOSE = 3

        @@INVALID_POS = 0

        def initialize(number, intelligence, strength)
            @number = number
            @name = "Player ##{@number}"
            @intelligence = intelligence
            @strength = strength
            @health = @@INITIAL_HEALTH
            @weapons = Array.new
            @shields = Array.new

            @row = @@INVALID_POS
            @col = @@INVALID_POS

            @consecutive_hits = 0
        end

        # Resurrects the player, setting its health to the initial value provided by
        # the constant @@INITIAL_HEALTH, and clearing its weapons and shields
        # @return [void]
        def resurrect
            @health = @@INITIAL_HEALTH
            @weapons.clear
            @shields.clear
            reset_hits
        end

        attr_reader :row, :col, :number

        # Sets the position of the player in the labyrinth
        # @param [Integer] row
        # @param [Integer] col
        # @return [void]
        def set_pos(row, col)
            @row = row
            @col = col
        end

        # Returns whether the player is dead or not
        # @return [Boolean] True if the player is dead, false otherwise
        def dead
            return @health <= 0
        end

        # Moves the player in the preferred direction if it is valid, or in the first
        # valid direction if the preferred one is not valid
        # @param [Direction] direction The preferred direction to move
        # @param [Array<Direction>] valid_moves The valid directions to move
        # @return [Direction] The direction the player will move
        def move(direction, valid_moves)
            size = valid_moves.size
            contained = valid_moves.include?(direction)

            if (size > 0 && !contained)
                return valid_moves[0]
            else
                return direction
            end
        end

        # Returns the attack power of the player based on its strength and the sum of
        # its weapons
        # @return [Float] The attack power of the player
        def attack
            return @strength + self.sum_weapons
        end

        # Defends the player from an attack, reducing its health if the attack is successful
        # and returning whether the player is dead or not
        # @param [Float] received_attack The attack power received by the player
        # @return [Boolean] True if the player is dead, false otherwise
        def defend(received_attack)
            return manage_hit(received_attack)
        end

        # Receives a reward after winning a combat, consisting of a random number of weapons,
        # shields, and health units based on the constants defined in the Dice class
        # @return [void]
        def receive_reward
            w_reward=Dice.weapons_reward
            s_reward=Dice.shields_reward

            for i in 1..w_reward
                receive_weapon(new_weapon)
            end

            for i in 1..s_reward
                receive_shield(new_shield)
            end

            @health += Dice.health_reward
        end

        # Returns a string representation of the player, including its name, health, intelligence, strength,
        # and the number of consecutive hits it has received, as well as its weapons and shields
        # @return [String] The string representation of the player
        def to_s
            return_string = "P[#{@name}, " +
            ("%.1f♥, %.3f🧠, %.3f🗡, %i] \n" % [@health, @intelligence, @strength, @consecutive_hits])

            return_string+="\tWeapons: "
            @weapons.each do |i|
                return_string+=i.to_s + " "
            end
            return_string+="\n\tShields: "
            @shields.each do |i|
                return_string+=i.to_s + " "
            end
            return return_string
        end

        private

        # Receives a weapon w, it discards some weapons based on a probability and
        # adds the weapon to the player's weapons if the player has less than the maximum
        # number of weapons allowed
        # @param [Weapon] w The weapon to be received
        # @return [void]
        def receive_weapon(w)
            @weapons.delete_if{|weapon| weapon.discard}

            if @weapons.size < @@MAX_WEAPONS
                @weapons.push(w)
            end
        end

        # Receives a shield s, it discards some shields based on a probability and
        # adds the shield to the player's shields if the player has less than the maximum
        # number of shields allowed
        # @param [Shield] s The shield to be received
        # @return [void]
        def receive_shield(s)
            @shields.delete_if{|shield| shield.discard}

            if @shields.size < @@MAX_SHIELDS
                @shields.push(s)
            end
        end

        # Returns a new weapon with random power and uses left
        # @return [Weapon] The new weapon
        def new_weapon
            return Weapon.new(Dice.weapon_power, Dice.uses_left)
        end

        # Returns a new shield with random power and uses left
        # @return [Shield] The new shield
        def new_shield
            return Shield.new(Dice.shield_power, Dice.uses_left)
        end

        # Returns the sum of the attack power of the player's weapons
        # @return [Float] The sum of the attack power of the player's weapons
        def sum_weapons
            sum = 0.0
            @weapons.each do |weapon|
                sum += weapon.attack
            end
            return sum
        end

        # Returns the sum of the protection power of the player's shields
        # @return [Float] The sum of the protection power of the player's shields
        def sum_shields
            sum = 0.0
            @shields.each do |shield|
                sum += shield.protect
            end
            return sum
        end

        # Returns the defensive energy of the player, which is the sum of its intelligence
        # and the sum of the protection power of its shields
        # @return [Float] The defensive energy of the player
        def defensive_energy
            return @intelligence + sum_shields
        end

        # Manages the hit received by the player, reducing its health if the attack is successful
        # and returning whether the player is dead or not
        # @param [Float] received_attack The attack power received by the player
        # @return [Boolean] True if the player is dead, false otherwise
        def manage_hit(received_attack)
            if (self.defensive_energy < received_attack)
                self.got_wounded
                self.inc_consecutive_hits
            else
                self.reset_hits
            end

            if (@consecutive_hits == @@HITS2LOSE || dead)
                reset_hits
                return true
            end

            return false
        end

        # Resets the number of consecutive hits received by the player
        # @return [void]
        def reset_hits
            @consecutive_hits = 0
        end

        # Reduces the health of the player by one unit
        # @return [void]
        def got_wounded
            @health -= 1
        end

        # Increases the number of consecutive hits received by the player
        # @return [void]
        def inc_consecutive_hits
            @consecutive_hits += 1
        end
    end
end
