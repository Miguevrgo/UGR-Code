package irrgarten;

public class ShieldCardDeck extends CardDeck<Shield> {
    private final int DECK_SIZE = 5;

    /**
     * Adds cards to the Deck of Shields using DECK_SIZE to determine how many
     * cards will be added
     */
    @Override
    protected void addCards() {
        for (int i = 0; i < DECK_SIZE; ++i) {
            this.addCard(new Shield(Dice.shieldPower(), Dice.usesLeft()));
        }
    }

}
