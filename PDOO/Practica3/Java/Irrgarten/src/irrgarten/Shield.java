/**
 * @file Shield.java
 * @author Miguel Angel De la Vega Rodríguez
 * @author Alberto De la Vera Sanchez
 * @brief This file contains the class that represents the shield which 
 * can be used by the player in the game to protect himself from a monster
 */

package irrgarten;

/**
 * Class that represents the shield that the player uses
 * in game when fighting against a monster
 */
public class Shield {
    private float protection;
    private int uses;


    public Shield(float protection, int uses) {
        this.protection = protection;
        this.uses = uses;
    }

    /**
     * Returns the protection value of the shield if it has uses left
     * and decreases the number of uses by one and returns 0 otherwise.
     * 
     * @return the protection value of the shield
     */
    public float protect() {
        if (uses > 0){
            --uses;
            return protection;
        }

        return 0f; // No uses for the current shield left
    }

    /**
     * This method delegates to the Dice class method discardElement with the argument
     * the number of uses left of the shield
     *
     * @return the result of the call to discardElement
     */
    public boolean discard() {
        return Dice.discardElement(uses);
    }
    /**
     * Returns a string with the current state of the shield
     
     * @return a string with the current state of the shield
     */
    public String toString() {
        return "S[" + protection + ", " + uses + "]";
    }

}
