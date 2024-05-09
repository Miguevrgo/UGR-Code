package irrgarten;

import java.util.ArrayList;
//TODO: Comprobar en todos los sitios que cuando se muera un player y resurreccione 
// Se vuelva un fuzzy player
public class FuzzyPlayer extends Player {

    /**
     * Constructor for fuzzy Player 
     * @param other Player who turns into fuzzy
     */
    FuzzyPlayer(Player other) {
        super(other);
    }

    /**
     * Fuzzy Player moves to a given direction
     * @param direction direction to move
     * @param validMoves valid moves for player
     * @return new direction to move
     */
    @Override
    public Directions move(Directions direction,  ArrayList<Directions> validMoves) {
        if (validMoves.size() > 0 && !validMoves.contains(direction)) {
            return Dice.nextStep(validMoves.get(0), validMoves, getIntelligence()); 
        }
        else{
            return Dice.nextStep(direction, validMoves, getIntelligence());
        }
    }

    /**
     * Fuzzy Player attacks
     * 
     * @return attack value
     */
    @Override
    public float attack() {
        return this.sumWeapons() + Dice.intensity(getStrength());
    }

    /**
     * Fuzzy Player defends
     * 
     * @returns defensive value
     */
    @Override
    protected float defensiveEnergy() {
        return this.sumShields() + Dice.intensity(getIntelligence());
    }

    /**
     * Current state of the fuzzy player
     * 
     * @return string containing state
     */
    @Override
    public String toString() {
        return "Fuzzy" + super.toString();
    }
}
