/**
 * @file Monster.java
 * @author Miguel Angel De la Vega Rodríguez
 * @description This file contains the Monster class, which provides methods
 * to manage the monsters
 */

package irrgarten;

public class Monster {
    private static final int INITIAL_HEALTH = 5;
    private String name;
    private float intelligence;
    private float strength;
    private float health;
    private int row;
    private int col;


    public Monster(String name, float intelligence, float strenght) {
        this.name = name;
        this.intelligence = intelligence;
        this.strength = strenght;
        this.health = INITIAL_HEALTH;
        this.row = 0;
        this.col = 0;
    }

    /**
     * Returns whether the monster is dead or not
     *
     * @return health <= 0
     */
    public boolean dead() {
        return health <= 0;
    }

    /**
     * Calls Dice method intensity to calculate the attack of the monster
     * given its strength
     *
     * @return the attack value of the monster
     */
    public float attack() {
        return Dice.intensity(this.strength);
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
        boolean isDead = dead();
        if (!isDead) {
            if (Dice.intensity(intelligence) < receivedAttack) {
                gotWounded();
                isDead = dead();
            }
        }

        return isDead;
    }

    /**
     * Modifies the position of the monsterSi
     *
     * @param row row of the new position
     * @param col column of the new position
     */
    public void setPos(int row, int col) {
        this.row = row;
        this.col = col;
    }

    /**
     * Return a string with the full state of the monster
     *
     * @return the string
     */
    public String toString() {
        String toReturn = "M[";
        toReturn += name + ", ";
        toReturn += String.format("%.1f♥, %.3f🧠, %.3f🗡", health, intelligence, strength);
        toReturn += " (" + row + "," + col + ") ]";
        return toReturn;
    }

    /**
     * Decrements in one unit the health of the monster
     */
    private void gotWounded() {
        --health;
    }

}
