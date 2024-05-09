/**
 * @file CombatElement.java
 * @author Miguel Angel De la Vega Rodríguez
 * @author Alberto De la Vera Sánchez
 * @description This file contains the CombatElement class, which provides an
 * abstraction for the elements used by a player in combat (weapon and shield)
 */
package irrgarten;

abstract public class CombatElement {
    private float effect;
    private int uses;

    public CombatElement(float effect, int uses) {
        this.effect = effect;
        this.uses = uses;
    }

    public CombatElement(CombatElement other) {
        this(other.effect,other.uses);
    }

    /**
     * Returns the effect of the combat element if there are uses left, decrementing
     * its value, returns 0 otherwise
     * 
     * @return effect of the combat element
     */
    protected float produceEffect() {
        if (uses >= 0) {
            --uses;
            return effect;
        }

        return 0f;
    }

    /**
     * This method returns whether the combat element will be discarded or not
     * depending on its uses
     * 
     * @return whether combat element is discarded or not
     */
    public boolean discard() {
        return Dice.discardElement(uses);
    }

    /**
     * Returns a string with the current state of the Combat Element
     * 
     * @return string with the current state of the combat element
     */
    @Override
    public String toString() {
        return "[" + effect + ", " + uses + "]";
    }
}
