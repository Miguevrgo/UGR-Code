module Irrgarten
  class LabyrinthCharacter
    def initialize(name, intelligence, strength, health)
      @name = name
      @intelligence = intelligence
      @strength = strength
      @health = health

      @row = 0
      @col = 0
    end

    def dead
      @health <= 0
    end

    attr_reader :row, :col

    def set_pos(row, col)
      @row = row
      @col = col
    end

    def to_s
      "[#{@name}, #{format('%.1f♥, %.3f🧠, %.3f🗡', @health, @intelligence, @strength)}] \n"
    end

    protected

    attr_reader :intelligence, :strength, :health

    def set_health(health)
      @health = health
    end

    def got_wounded
      @health -= 1
    end
  end
end
