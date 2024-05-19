require_relative 'dice'
require_relative 'labyrinth_character'

module Irrgarten
  class Monster < LabyrinthCharacter
    @@INITIAL_HEALTH = 5

    def initialize(name, intelligence, strength)
      super(name, intelligence, strength, @@INITIAL_HEALTH)
    end

    # Returns the attack power of the monster based on its strength
    # @return [Float] The attack power of the monster
    def attack
      Dice.intensity(@strength)
    end

    # Returns a string representation of the monster
    # @return [String] The string representation of the monster
    def to_s
      return_string = "M[#{@name}, " +
                      format('%.1f♥, %.3f🧠, %.3f🗡]', @health, @intelligence, @strength)
      return_string += " (#{@row}, #{@col}) ]"
      return_string
    end

    # Defends the monster from an attack, reducing its health if the attack is successful
    # and returning whether the monster is dead or not
    # @param [Float] received_attack The attack power received by the monster
    # @return [Boolean] True if the monster is dead, false otherwise
    def defend(received_attack)
      is_dead = dead
      if !is_dead && Dice.intensity(@intelligence) < received_attack
        got_wounded
        is_dead
      end

      is_dead
    end
  end
end
