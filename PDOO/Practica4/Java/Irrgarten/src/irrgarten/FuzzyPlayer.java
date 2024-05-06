package irrgarten;

import java.util.ArrayList;

public class FuzzyPlayer extends Player {
    FuzzyPlayer(Player other) {
        super(other.getNumber(), other.getIntelligence(), other.getStrength());
    }

    public Directions move(Directions direction,  ArrayList<Directions> validMoves) {
        if (validMoves.size() > 0 && !validMoves.contains(direction)) {
            return Dice.nextStep(validMoves.get(0), validMoves, getIntelligence()); 
        }
        else{
            return Dice.nextStep(direction, validMoves, getIntelligence());
        }
    }

    public float attack() {
        return this.sumWeapons() + Dice.intensity(getStrength());
    }

    protected float defensiveEnergy() {
        return this.sumShields() + Dice.intensity(getIntelligence());
    }

    public String toString() {
        return "Fuzzy-" + super.toString();
    }
}
