/**
 * @file Shield.java
 * @author Miguel Angel De la Vega Rodríguez
 * @author Alberto De la Vera Sanchez
 * @brief This file contains the class that represents the shield which 
 * can be used by the player in the game to protect himself from a monster
 */

package irrgarten;

public class Shield extends CombatElement{
    
    /**
     * Constructor for Shield class, receives protection value and amount of uses
     * 
     * @param protection Protection provided by the shield
     * @param uses Uses of the shield
     */
    public Shield(float protection, int uses) {
        super(protection, uses);
    }

    /**
     * Returns the protection value of the shield if it has uses left
     * and decreases the number of uses by one and returns 0 otherwise,
     * delegating in the method produceEffect
     * 
     * @return the protection value of the shield
     */
    public float protect() {
        return this.produceEffect();
    }

    /**
     * Returns a string with the current state of the shield in the following
     * format:
     * 
     * S[Protection, Uses]
     * 
     * @return a string with the current state of the shield
     */
    @Override
    public String toString() {
        return "S" + super.toString();
    }

}
