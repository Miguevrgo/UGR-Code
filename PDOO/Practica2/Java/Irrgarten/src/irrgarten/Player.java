/**
 * @file Player.java
 * @author Miguel Angel De la Vega Rodríguez
 * @description This file contains the Player class, which provides methods to
 * manage the player.
 */

package irrgarten;

import java.util.ArrayList;

public class Player {
    private static final int MAX_WEAPONS = 2;
    private static final int MAX_SHIELDS = 3;
    private static final int INITIAL_HEALTH = 10;
    private static final int HITS2LOSE = 3;

    private String name = "Player #";
    private char number;
    private float intelligence;
    private float strength;
    private float health;
    private int row;
    private int col;
    private int consecutiveHits;
    private ArrayList<Weapon> weapons;
    private ArrayList<Shield> shields;

    public Player(char number, float intelligence, float strength) {
        this.consecutiveHits = 0;
        this.number = number;
        this.intelligence = intelligence;
        this.strength = strength;
        this.name += number;
        this.health = INITIAL_HEALTH;
        this.weapons = new ArrayList<Weapon>();
        this.shields = new ArrayList<Shield>();
    }

    /**
     * It resurrects the player, setting its health to the initial value,
     * resetting the number of consecutive hits and setting the player's weapons
     * and shields to empty lists
     * 
     */
    public void resurrect() {
        if (Dice.resurrectPlayer()){
            this.health = INITIAL_HEALTH;
            this.weapons.clear();
            this.shields.clear();
            resetHits();
        }
    }

    /**
     * Returns the row of the player
     * 
     * @return row
     */
    public int getRow() {
        return row;
    }

    /**
     * Returns the column of the player
     * 
     * @return column
     */
    public int getCol() {
        return col;
    }

    /**
     * Returns the number of the player
     * 
     * @return number
     */
    public char getNumber() {
        return number;
    }

    /**
     * Sets the position of the player to the values provided
     * 
     * @param row new row
     * @param col new column
     */
    public void setPos(int row, int col) {
        this.row = row;
        this.col = col;
    }

    /**
     * Returns whether the player is dead or not
     *
     * @return health <= 0 || consecutiveHits >= HITS2LOSE
     */
    public boolean dead() {
        return health <= 0 || consecutiveHits >= HITS2LOSE;
    }

    /**
     * INFORMATION PROVIDED IN THE NEXT PRACTICE
     */
    public Directions move(Directions direction, Directions[] validMoves) {
        throw new UnsupportedOperationException();
    }

    /**
     * Calculates the strength of the player and the sum of the power provided
     * by its weapons
     *
     * @return the attack value
     */
    public float attack() {
        return sumWeapons()+strength;
    }

    /**
     * This method delegates its functionality to the manageHit method
     *
     * @param receivedAttack the attack value received
     * @return manageHit(receivedAttack)
     */
    public boolean defend(float receivedAttack) {
        return manageHit(receivedAttack);
    }

    /**
     * INFORMATION PROVIDED IN THE NEXT PRACTICE
     */
    public void receiveReward() {
        throw new UnsupportedOperationException();
    }

    /**
     * Returns a string with the current state of the player, with the format:
     * P[number, health, intelligence, strength]
     *
     * @return Current state of the player
     */
    public String toString() {
        String toReturn = "P[" + name + ", " + health + ", " + intelligence + ", " + strength + "]\n Weapons: \n";

        for (Weapon weapon : weapons) {
            toReturn += weapon.toString() + "\t";
        }

        toReturn += "\n Shields: \n";

        for (Shield shield : shields) {
            toReturn += shield.toString() + "\t";
        }
        
        return toReturn;
    }

    /**
     * INFORMATION PROVIDED IN THE NEXT PRACTICE
     */
    private void receiveWeapon(Weapon w) {
        throw new UnsupportedOperationException();
    }

    /**
     * INFORMATION PROVIDED IN THE NEXT PRACTICE
     */
    private void receiveShield(Shield s) {
        throw new UnsupportedOperationException();
    }

    /**
     * Creates a new instance of the Weapon class and adds it, parameters needed to
     * generate the weapon are taken from Dice class
     *
     * @return new weapon
     */
    private Weapon newWeapon() {
        return new Weapon(Dice.weaponPower(), Dice.usesLeft());
    }

    /**
     * Creates a new instance of the Shield class and adds it, parameters needed to
     * generate the shield are taken from Dice class
     *
     * @return new shield
     */
    private Shield newShield() {
        return new Shield(Dice.shieldPower(), Dice.usesLeft());
    }

    /**
     * Returns the sum of the attack values of the weapons calling attack method
     *
     * @return sum of the attack values
     */
    private float sumWeapons() {
        float sum = 0f;
        for (Weapon weapon : weapons) {
            sum += weapon.attack();
        }
        return sum;
    }

    /**
     * Returns the sum of the protection provided by the shields calling
     * protect method
     *
     * @return sum of the protection
     */
    private float sumShields() {
        float sum = 0f;
        for (Shield shield : shields) {
            sum += shield.protect();
        }
        return sum;
    }

    /**
     * Returns the sum of the intelligence and the protection provided by the
     * shields
     *
     * @return the sum 
     */
    private float defensiveEnergy() {
        return sumShields() + intelligence;
    }

    /**
     * INFORMATION PROVIDED IN THE NEXT PRACTICE
     */
    private boolean manageHit(float receivedAttack) {
        throw new UnsupportedOperationException();
    }

    /**
     * Resets the number of consecutive hits to 0
     */
    private void resetHits() {
        consecutiveHits = 0;
    }

    /**
     * Decrements the health of the player by one unit
     */
    private void gotWounded() {
        --health;
    }

    /**
     * Increments the number of consecutive hits by one unit
     */
    private void incConsecutiveHits() {
        ++consecutiveHits;
    }


}
