package irrgarten;

public class WeaponCardDeck extends CardDeck<Weapon> {
    private final int DECK_SIZE = 5;

    /**
     * Adds cards to the Deck of Weapons using DECK_SIZE to determine how many
     * cards will be added
     */
    @Override
    protected void addCards() {
        for (int i = 0; i < DECK_SIZE; ++i) {
            this.addCard(new Weapon(Dice.weaponPower(), Dice.usesLeft()));
        }
    }

}
