/**
 * @file Player.java
 * @author Miguel Angel De la Vega Rodríguez
 * @author Alberto De la Vera Sanchez
 * @description This file contains the Player class, which provides methods to
 * manage the player.
 */

package irrgarten;

import java.util.ArrayList;


public class Player extends LabyrinthCharacter{
    private static final int MAX_WEAPONS = 2;
    private static final int MAX_SHIELDS = 3;
    private static final int INITIAL_HEALTH = 10;
    private static final int HITS2LOSE = 3;

    private char number;
    private int consecutiveHits;
    private ArrayList<Weapon> weapons;
    private ArrayList<Shield> shields;

    public Player(char number, float intelligence, float strength) {
        super("Player #", number, intelligence, strength);
        this.consecutiveHits = 0;
        this.number = number;

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
        this.setHealth(INITIAL_HEALTH);
        this.weapons.clear();
        this.shields.clear();
        resetHits();
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
     * Returns the direction of the move if the move is possible and 
     * the first move possible in validMoves otherwise
     * 
     * @param direction Preferred direction to move
     * @param validMoves Valid moves array
     * @return The direction of the possible move 
     */
    public Directions move(Directions direction, ArrayList<Directions> validMoves) {
        if (validMoves.size() > 0 && !validMoves.contains(direction)) {
            return validMoves.get(0);
        }
        else{
            return direction;
        }
    }

    /**
     * Calculates the strength of the player and the sum of the power provided
     * by its weapons
     *
     * @return the attack value
     */
    public float attack() {
        return sumWeapons()+this.getStrength();
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
     * This method creates a reward for the player using random possibility
     * using Dice, it rewards the player with weapons, shields and health
     */
    public void receiveReward() {
        int wReward = Dice.weaponsReward();
        int sReward = Dice.weaponsReward();

        for (int i = 1; i <= wReward; ++i) {
            Weapon wnew = newWeapon();
            receiveWeapon(wnew);
        }

        for (int i = 1; i <= sReward; ++i) {
            Shield snew = newShield();
            receiveShield(snew);
        }

        this.setHealth(this.getHealth() + Dice.healthReward());
    }

    /**
     * Returns a string with the current state of the player, with the format:
     * P[number, health, intelligence, strength]
     *      Weapons: Weapon1    Weapon2 ... WeaponN
     *      Shields: Shield1    Shield2 ... ShieldN
     *
     * @return Current state of the player
     */
    public String toString() {
        String toReturn = "P" + super.toString();

        toReturn += "\tWeapons: ";
        for (Weapon weapon : weapons) {
            toReturn += weapon.toString() + "\t";
        }

        toReturn += "\n\tShields: ";
        for (Shield shield : shields) {
            toReturn += shield.toString() + "\t";
        }

        return toReturn;
    }

    /**
     * This method updates the weapons of the player if any has to be
     * discarded and adds one weapon if MAX_WEAPONS is not exceeded
     * 
     * @param w New weapon to be added
     */
    private void receiveWeapon(Weapon w) {
        for (int i = 0; i < weapons.size(); ++i) {
            if (weapons.get(i).discard()) {
                weapons.remove(i);
                --i;
            }
        }

        if (weapons.size() < MAX_WEAPONS) {
            weapons.add(w);
        }
    }

    /**
     * This method updates the shields of the player if any has to be 
     * discarded and adds one shield if MAX_SHIELDS is not exceeded
     * 
     * @param s New shield to be added
     */
    private void receiveShield(Shield s) {
        for (int i = 0; i < shields.size(); ++i){
            if (shields.get(i).discard()){
                shields.remove(i);
                --i;
            }
        }

        if (shields.size() < MAX_SHIELDS) {
            shields.add(s);
        }
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
    protected float sumWeapons() {
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
    protected float sumShields() {
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
    protected float defensiveEnergy() {
        return sumShields() + getIntelligence();
    }

    /**
     * It manages the attack received by the player, if the attack is greater
     * than the defensive energy of the player, the player is wounded and the number
     * of consecutive hits is incremented, otherwise the number of consecutive hits
     * is reset
     * 
     * @param receivedAttack power of the received attack
     * @return whether the player loses the combat or not
     */
    private boolean manageHit(float receivedAttack) {
        if (defensiveEnergy() < receivedAttack) {
            gotWounded();
            incConsecutiveHits();
        }
        else{
            resetHits();
        }

        boolean lose = (consecutiveHits == HITS2LOSE) || dead();

        if (lose) {
            resetHits();
        }

        return lose;
    }

    /**
     * Resets the number of consecutive hits to 0
     */
    private void resetHits() {
        consecutiveHits = 0;
    }

    /**
     * Increments the number of consecutive hits by one unit
     */
    private void incConsecutiveHits() {
        ++consecutiveHits;
    }

}
