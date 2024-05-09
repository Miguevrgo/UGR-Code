require_relative 'dice'
require_relative 'weapon'
require_relative 'shield'
require_relative 'directions'
require_relative 'labyrinth_character'

module Irrgarten
  class Player < LabyrinthCharacter
    @@MAX_WEAPONS = 2
    @@MAX_SHIELDS = 3
    @@INITIAL_HEALTH = 10
    @@HITS2LOSE = 3

    def initialize(number, intelligence, strength)
      super("Player ##{number}", intelligence, strength, @@INITIAL_HEALTH)
      @weapons = []
      @shields = []
      @number = number

      @row = 0
      @col = 0

      @consecutive_hits = 0
    end

    # TODO: Constructor de copia?

    # Resurrects the player, setting its health to the initial value provided by
    # the constant @@INITIAL_HEALTH, and clearing its weapons and shields
    # @return [void]
    def resurrect
      @health = @@INITIAL_HEALTH
      @weapons.clear
      @shields.clear
      reset_hits
    end

    attr_reader :number

    # Moves the player in the preferred direction if it is valid, or in the first
    # valid direction if the preferred one is not valid
    # @param [Direction] direction The preferred direction to move
    # @param [Array<Direction>] valid_moves The valid directions to move
    # @return [Direction] The direction the player will move
    def move(direction, valid_moves)
      size = valid_moves.size
      contained = valid_moves.include?(direction)

      return valid_moves[0] if size.positive? && !contained

      direction
    end

    # Returns the attack power of the player based on its strength and the sum of
    # its weapons
    # @return [Float] The attack power of the player
    def attack
      @strength + sum_weapons
    end

    # Defends the player from an attack, reducing its health if the attack is successful
    # and returning whether the player is dead or not
    # @param [Float] received_attack The attack power received by the player
    # @return [Boolean] True if the player is dead, false otherwise
    def defend(received_attack)
      manage_hit(received_attack)
    end

    # Receives a reward after winning a combat, consisting of a random number of weapons,
    # shields, and health units based on the constants defined in the Dice class
    # @return [void]
    def receive_reward
      w_reward = Dice.weapons_reward
      s_reward = Dice.shields_reward

      w_reward.times do
        receive_weapon(new_weapon)
      end

      s_reward.times do
        receive_shield(new_shield)
      end

      @health += Dice.health_reward
    end

    # Returns a string representation of the player, including its name, health, intelligence, strength,
    # and the number of consecutive hits it has received, as well as its weapons and shields
    # @return [String] The string representation of the player
    def to_s
      base_str = super.chomp(" \n")

      weapons_str = @weapons.map(&:to_s).join(' ')
      shields_str = @shields.map(&:to_s).join(' ')
      additional_info = format(", %i", @consecutive_hits)

      "#{base_str}#{additional_info}] \n\tWeapons: #{weapons_str}\n\tShields: #{shields_str}"
    end

    protected

    # Returns the sum of the attack power of the player's weapons
    # @return [Float] The sum of the attack power of the player's weapons
    def sum_weapons
      sum = 0.0
      @weapons.each do |weapon|
        sum += weapon.attack
      end
      sum
    end

    # Returns the sum of the protection power of the player's shields
    # @return [Float] The sum of the protection power of the player's shields
    def sum_shields
      sum = 0.0
      @shields.each do |shield|
        sum += shield.protect
      end
      sum
    end

    # Returns the defensive energy of the player, which is the sum of its intelligence
    # and the sum of the protection power of its shields
    # @return [Float] The defensive energy of the player
    def defensive_energy
      @intelligence + sum_shields
    end

    private

    # Receives a weapon w, it discards some weapons based on a probability and
    # adds the weapon to the player's weapons if the player has less than the maximum
    # number of weapons allowed
    # @param [Weapon] w The weapon to be received
    # @return [void]
    def receive_weapon(w)
      @weapons.delete_if(&:discard)

      return unless @weapons.size < @@MAX_WEAPONS

      @weapons.push(w)
    end

    # Receives a shield s, it discards some shields based on a probability and
    # adds the shield to the player's shields if the player has less than the maximum
    # number of shields allowed
    # @param [Shield] s The shield to be received
    # @return [void]
    def receive_shield(s)
      @shields.delete_if(&:discard)

      return unless @shields.size < @@MAX_SHIELDS

      @shields.push(s)
    end

    # Returns a new weapon with random power and uses left
    # @return [Weapon] The new weapon
    def new_weapon
      Weapon.new(Dice.weapon_power, Dice.uses_left)
    end

    # Returns a new shield with random power and uses left
    # @return [Shield] The new shield
    def new_shield
      Shield.new(Dice.shield_power, Dice.uses_left)
    end

    # Manages the hit received by the player, reducing its health if the attack is successful
    # and returning whether the player is dead or not
    # @param [Float] received_attack The attack power received by the player
    # @return [Boolean] True if the player is dead, false otherwise
    def manage_hit(received_attack)
      if defensive_energy < received_attack
        got_wounded
        inc_consecutive_hits
      else
        reset_hits
      end

      if @consecutive_hits == @@HITS2LOSE || dead
        reset_hits
        return true
      end

      false
    end

    # Resets the number of consecutive hits received by the player
    # @return [void]
    def reset_hits
      @consecutive_hits = 0
    end

    # Increases the number of consecutive hits received by the player
    # @return [void]
    def inc_consecutive_hits
      @consecutive_hits += 1
    end
  end
end
