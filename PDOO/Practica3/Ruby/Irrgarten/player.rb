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
            @name = "Player #{@number}"
            @intelligence = intelligence.to_f
            @strength = strength.to_f
            @health = @@INITIAL_HEALTH
            @weapons = Array.new
            @shields = Array.new

            @row = @@INVALID_POS
            @col = @@INVALID_POS

            @consecutive_hits = 0
        end

        def resurrect
            if Dice.resurrect_player then
                @health = @@INITIAL_HEALTH
                @weapons.clear
                @shields.clear
                reset_hits()
            end
        end

        attr_reader :row, :col, :number

        def set_pos(row, col)
            @row = row
            @col = col
        end

        def dead
            return @health <= 0 || @consecutive_hits >= @@HITS2LOSE
        end

        def move(direction, valid_moves)
            size = valid_moves.size
            contained = valid_moves.include?(direction)

            if (size > 0 && !contained)
                return valid_moves.get(0)
            else
                return direction
            end
        end

        def attack
            return @strength + self.sum_weapons
        end

        def defend(received_attack)
            return manage_hit(received_attack)
        end

        def receive_reward
            w_reward=Dice.weapons_reward
            s_reward=Dice.shields_reward

            for i in 0..w_Reward
                receive_weapon(new_weapon)
            end

            for i in 0..s_reward
                receive_shield(new_shield)
            end

            @health += Dice.health_reward
        end

        def to_s
            "P[#{name}, " +
            ("%.1f♥, %.3f, %.3f]\n" % [@health, @intelligence, @strength]) +
            "\tWeapons: " + weapons.map(&:to_s).join("\t") + "\n" +
            "\tShields: " + shields.map(&:to_s).join("\t")
        end

        private

        def receive_weapon(weapon)
            for weapon in @weapons
                if (weapon.discard())
                    @weapons.delete(weapon)
                end
            end

            if @weapons.size < @@MAX_WEAPONS
                @weapons.push(weapon)
            end
        end

        def receive_shield(shield)
            for shield in @shields
                if (shield.discard())
                    @shields.delete(shield)
                end
            end

            if @shields.size < @@MAX_SHIELDS
                @shields.push(shield)
            end
        end

        def new_weapon
            return Weapon.new(Dice.weapon_power, Dice.uses_left)
        end

        def new_shield
            return Shield.new(Dice.shield_power, Dice.uses_left)
        end

        def sum_weapons
            sum = 0
            @weapons.each do |weapon|
                sum += weapon.power
            end
            return sum
        end

        def sum_shields
            sum = 0
            @shields.each do |shield|
                sum += shield.power
            end
            return sum
        end

        def defensive_energy
            return @intelligence + sum_shields
        end

        def manage_hit(received_attack)
            if (self.defensive_energy < received_attack)
                self.got_wounded()
                self.inc_consecutive_hits()
                return true
            else
                self.reset_hits()
                return false
            end
        end

        def reset_hits
            @consecutive_hits = 0
        end

        def got_wounded
            @health -= 1
        end

        def inc_consecutive_hits
            @consecutive_hits += 1
        end
    end
end
