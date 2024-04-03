module Irrgarten
    require_relative 'dice'
    require_relative 'weapon'
    require_relative 'shield'
    require_relative 'directions'

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

        def pos(row, col)
            @row = row
            @col = col
        end

        def dead 
            return @health <= 0 || @consecutive_hits >= @@HITS2LOSE
        end

        def move(direction, valid_moves)
            #INFORMATION PROVIDED IN NEXT PRACTICE
        end

        def attack
            return @strength + self.sum_weapons
        end

        def defend(received_attack)
            #INFORMATION PROVIDED IN NEXT PRACTICE
        end

        def receive_reward
            #INFORMATION PROVIDED IN NEXT PRACTICE
        end

        def to_s 
            return_string = "#{@name}[Intelligence:#{@intelligence};Strength:#{@strength};Health:#{@health};Consecutive_hits#{@consecutive_hits}]\n "
            return_string+="\nWeapons"
            self.weapons.each do |i|
                return_string+=i.to_string +"\t"
            end
            return_string+="\nShields"
            self.shieldas.each do |i|
                return_string+=i.to_string +"\t"
            end
            return return_string
        end

        private

        def receive_weapon(weapon)
            #INFORMATION PROVIDED IN NEXT PRACTICE
        end

        def receive_shield(shield)
            #INFORMATION PROVIDED IN NEXT PRACTICE
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
            #INFORMATION PROVIDED IN NEXT PRACTICE
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
