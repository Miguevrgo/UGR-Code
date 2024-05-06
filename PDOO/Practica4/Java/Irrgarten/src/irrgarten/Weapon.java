/**
 * @file Weapon.java
 * @author Miguel Angel De la Vega Rodríguez
 * @author Alberto De la Vera Sanchez
 * @description This file contains the Weapon class, which represents the weapons
 * that the player can use in the game against a monster
 */

package irrgarten;

public class Weapon extends CombatElement {

    public Weapon(float power, int uses) {
        super(power, uses);
    }

    /**
     * Returns the power value of the weapon if it has uses left
     * and decreases the number of uses by one, returns 0 otherwise,
     * delegating in the method produceEffect
     * 
     * @return power value of the weapon
     */
    public float attack() {
        return this.produceEffect();
    }

    /**
     * Returns a string with the current state of the weapon
     * 
     * @return string with the state
     */
    public String toString() {
        return "W" + super.toString();
    }

}
