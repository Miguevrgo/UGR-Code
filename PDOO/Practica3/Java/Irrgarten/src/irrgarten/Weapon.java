/**
 * @file Weapon.java
 * @author Miguel Angel De la Vega Rodríguez
 * @author Alberto De la Vera Sanchez
 * @description This file contains the Weapon class, which represents the weapons
 * that the player can use in the game against a monster
 */

package irrgarten;

/**
 * This class is used to represent the weapons the player 
 * can use in the game against a monster
 */
public class Weapon {
    private float power;
    private int uses;

    public Weapon(float power, int uses) {
        this.power = power;
        this.uses = uses;
    }

    /**
     * Returns the power value of the weapon if it has uses left
     * and decreases the number of uses by one, returns 0 otherwise.
     * 
     * @return power value of the weapon
     */
    public float attack() {
        if (uses > 0){
            --uses;
            return power;
        }

        return 0f; // No uses for the current weapon left
    }
    
    /**
     * This method chooses whether the weapon will be discarded or not considering
     * its uses
     */
    public boolean discard() {
        return Dice.discardElement(uses);
    }

    /**
     * Returns a string with the current state of the weapon
     * 
     * @return string with the state
     */
    public String toString() {
        return "W[" + power + ", " + uses + "]";
    }

}
