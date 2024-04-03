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

        return 0; // No uses for the current shield left
    }

    /**
     * Returns a string with the current state of the shield
     
     * @return a string with the current state of the shield
     */
    public String toString() {
        String returnString = "S[" + protection + ", " + uses + "]";
        return returnString;
    }

}
