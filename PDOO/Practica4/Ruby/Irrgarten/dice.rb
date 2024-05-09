module Irrgarten
  class Dice # TODO: Si no vamos a hacer subclases de Dice ni queremos que se modifiquen las variables no es mejor usar variables de instancia de clase @?
    @@MAX_USES = 5 # Maximum use for weapons and shields
    @@MAX_INTELLIGENCE = 10.0 # Maximum intelligence for monsters and players
    @@MAX_STRENGTH = 10.0 # Maximum strength for monsters and players
    @@RESURRECT_PROB = 0.3 # Probability of a player being resurrected each round when dead
    @@WEAPONS_REWARD = 2 # Maximum number of weapons a player can receive
    @@SHIELDS_REWARD = 3 # Maximum number of shields a player can receive
    @@HEALTH_REWARD = 5 # Maximum number of units of health rewarded when winning a combat
    @@MAX_ATTACK = 3 # Maximum power for weapons
    @@MAX_SHIELD = 2 # maximum shield for shields

    @@generator = Random.new

    # Returns a random position int the range [0, max)
    # @param [Integer] max
    # @return [Integer]
    def self.random_pos(max)
      @@generator.rand(max)
    end

    # Returns a random number in the range [0, nplayers[ to determine who starts
    # @param [Integer] nplayers
    # @return [Integer]
    def self.who_starts(nplayers)
      @@generator.rand(nplayers)
    end

    # Returns a random number in the range [0, MAX_INTELLIGENCE[
    # @return [Float]
    def self.random_intelligence
      @@generator.rand(0.0...@@MAX_INTELLIGENCE)
    end

    # Returns a random number in the range [0, MAX_STRENGTH[
    # @return [Float]
    def self.random_strength
      @@generator.rand(0.0...@@MAX_STRENGTH)
    end

    # Returns whether a player is resurrected or not based on the resurrection probability
    # @return [Boolean]
    def self.resurrect_player
      (@@generator.rand <= @@RESURRECT_PROB)
    end

    # Returns a random number of weapons to be rewarded to a player in
    # the range [0, WEAPONS_REWARD]
    # @return [Integer]
    def self.weapons_reward
      @@generator.rand(0..@@WEAPONS_REWARD)
    end

    # Returns a random number of shields to be rewarded to a player in
    # the range [0, SHIELDS_REWARD]
    # @return [Integer]
    def self.shields_reward
      @@generator.rand(0..@@SHIELDS_REWARD)
    end

    # Returns a random number of health units to be rewarded to a player in
    # the range [0, HEALTH_REWARD]
    # @return [Integer]
    def self.health_reward
      @@generator.rand(0..@@HEALTH_REWARD)
    end

    # Returns a random power for a weapon in the range [0, MAX_ATTACK[
    # @return [Float]
    def self.weapon_power
      @@generator.rand(0.0...@@MAX_ATTACK)
    end

    # Returns a random power for a shield in the range [0, MAX_SHIELD[
    # @return [Float]
    def self.shield_power
      @@generator.rand(0.0...@@MAX_SHIELD)
    end

    # Returns a random number of uses left for a weapon or shield in the range [0, MAX_USES]
    # @return [Integer]
    def self.uses_left
      @@generator.rand(0..@@MAX_USES)
    end

    # Returns a random number of competence in the range [0, competence[
    # @param [Float] competence
    def self.intensity(competence)
      @@generator.rand(0.0...competence)
    end

    # Returns whether an element is discarded or not based on the number of uses left
    # @param [Integer] uses_left
    # @return [Boolean] whether the element is discarded or not
    def self.discard_element(uses_left)
      prob = uses_left.to_f / @@MAX_USES
      (@@generator.rand >= prob)
    end

    # Returns the direction of the preferred move with a probability directly proportional
    # to the value of intelligence provided, if the preferred direction
    # is not choosen, a random directions from validMoves will be returned
    # @param [Direction] preference
    # @param [Array] valid directions
    # @param [Float] Intelligence of the moving entity
    # @return [Direction] direction for the next step
    def self.next_step(preference, valid_moves, intelligence)
      intelligence >= random_intelligence ? preference : valid_moves[@@generator.rand(validMoves.length)]
    end
  end
end
