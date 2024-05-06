/**
 * @file Monster.java
 * @author Miguel Angel De la Vega Rodríguez
 * @author Alberto De la Vera Sanchez
 * @description This file contains the Monster class, which provides methods
 * to manage the monsters
 */

package irrgarten;

public class Monster extends LabyrinthCharacter {
    private static final int INITIAL_HEALTH = 5;

    public Monster(String name, float intelligence, float strenght) {
        super(name, intelligence, strenght, strenght);
        setHealth(INITIAL_HEALTH); // TODO: Correcto?
    }

    /**
     * Calls Dice method intensity to calculate the attack of the monster
     * given its strength
     *
     * @return the attack value of the monster
     */
    public float attack() {
        return Dice.intensity(this.getStrength());
    }

    /**
     * This method allows a monster to defend against a given attack
     * it uses Dice to know whether the defend power is greater than the 
     * received attack.
     * 
     * @param receivedAttack
     * @return Whether the monster is dead or not
     */
    public boolean defend(float receivedAttack){
        boolean isDead = this.dead();
        if (!isDead) {
            if (Dice.intensity(this.getIntelligence()) < receivedAttack) {
                this.gotWounded();
                isDead = this.dead();
            }
        }

        return isDead;
    }

}
