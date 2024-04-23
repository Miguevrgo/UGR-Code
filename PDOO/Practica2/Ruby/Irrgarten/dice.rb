module Irrgarten

    class Dice
        @@MAX_USES = 5
        @@MAX_INTELLIGENCE = 10.0
        @@MAX_STRENGTH = 10.0
        @@RESURRECT_PROB = 0.3
        @@WEAPONS_REWARD = 2
        @@SHIELDS_REWARD = 3
        @@HEALTH_REWARD = 5
        @@MAX_ATTACK = 3
        @@MAX_SHIELD = 2

        @@generator = Random.new

        # Random position
        def self.random_pos(max)
            @@generator.rand(max)
        end

        def self.who_starts(nplayers)
            @@generator.rand(nplayers)
        end

        def self.random_intelligence
            @@generator.rand(0...@@MAX_INTELLIGENCE)
        end

        def self.random_strength
            @@generator.rand(0...@@MAX_STRENGTH)
        end

        def self.resurrect_player
            return (@@generator.rand <= @@RESURRECT_PROB)
        end

        def self.weapons_reward
            @@generator.rand(0..@@WEAPONS_REWARD)
        end

        def self.shields_reward
            @@generator.rand(0..@@SHIELDS_REWARD)
        end

        def self.health_reward
            @@generator.rand(0..@@HEALTH_REWARD)
        end

        def self.weapon_power
            @@generator.rand(0.0...@@MAX_ATTACK)
        end

        def self.shield_power
            @@generator.rand(0.0...@@MAX_SHIELD)
        end

        def self.uses_left
            @@generator.rand(0..@@MAX_USES)
        end

        def self.intensity(competence)
            @@generator.rand(0.0...competence)
        end

        def self.discard_element(uses_left)
            prob = uses_left.to_f / @@MAX_USES.to_f
            return (@@generator.rand >= prob)
        end

    end

end
