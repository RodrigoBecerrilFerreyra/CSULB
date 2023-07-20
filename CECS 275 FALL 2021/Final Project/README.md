# CECS-275-Final-Project

Final project for CECS 275. Here are the project requirements:

## Blackjack Slot Machine

#### Design a program in C++ that simulates a Blackjack Slot Machine. When the program runs, it should do the following:
  1. Ask the user to enter the account number.
  2. Ask the user to enter the amount of money he/she wants to bet.
  3. The program will randomly select two cards for the user. Make sure to show the user the two selected cards.
  4. The program will randomly select another two cards for the dealer and show one card to the user.
  5. The program will show the value of user's cards and ask if the user wants to hit or stand or split.
  6. If the user decides to stand, the program will reveal the remaining card of the dealer and determine the winner.
  7. If the user decides to hit and the total value is less than 21, the program will select a card for the user and ask if the user still wants to hit after each time a card is drawn. If the total value of the user's cards is more than 21 during this process, reveal the remaining card of the dealer and determine the winner.
  8. If the user decides to split, the dealer will draw two cards for the user. The user now has two hands. Also, an additional bet of equal value to the original bet is placed on the second hand. Proceed the game as in step 6 and/or 7 for each hand.
  9. The program will ask whether the user wants to play again. If so, repeat 2-8. If not, the program displays the account information from the text file.
  10. Be sure to update the player's account accordingly after a winner is determined.

#### Rules:
  1. User can only split if the two cards are of the same value. (e.g. 10 of heart and 10 of spades)
  2. The winner is determined by the total value of the cards.
    - If the value of the user's cards is more than the dealer's cards but less than or equal 21, the user wins.
    - If the value of the user's cards and the dealer's cards are the same, the game is a tie.
    - Otherwise, the dealer wins.
  3. - If the user wins, the money inputted will be doubled.
     - If the user ties, the money inputted will be split in half.
     - If the user loses, the user win 0 dollars.
  4. The value of the two cards is determined by the sum of the value of each card. Face cards have value of 10. Ace would have value of 1 or 11. For example:
    - Ace and Ace have value of 12.
    - Ace and Queen have value of 11 or 21.
    - Queen and Jack have value of 20.
    - King and two have value of 12.

#### Other Requirements:
  - You can assume that the user always input number for the amount to bet, but your program must verify whether the user have enough money to bet and cannot bet more than what is available in the account.
  - If both user and dealer are over 21, whoever has smaller value will win.
  - Your program must verify that account exists before allowing the user to bet.
  - Suppose ONE standard 52-card deck is used and must be reshuffled after a winner is determined.
  - Each card is drawn from the top of the deck.
  - Account information must be stored in `acc_<account-number>.txt`. (e.g. `acc_1242123.txt`)
  - Account information text file must include the following:
    - `Account Number: 12345678` <--- any 8 digits positive integer 
    - `Current Balance: $1000.00` <--- must format with two decimal places
    - `Game Played: 0`
    - `Total Amount Won: $0.00` <--- must format with two decimal places
    - `Total Amount Loss: $0.00` <--- must format with two decimal places
  - This program must use at least three classes `Card`, `Player`, and `Account`.

#### Sample output:
NOTE: This is to illustrate how the account file should be updated
Before playing game:
```
Account Number: 12345678
Current Balance: $1000.00
Game Played: 0
Total Amount Won: $0.00
Total Amount Loss: $0.00
```

After playing game 1: (Suppose the user bet $10 and wins --> user will receive $20 total)
```
Account Number: 12345678
Current Balance: $1010.00
Game Played: 1
Total Amount Won: $10.00
Total Amount Loss: $0.00
```

After playing game 2: (Suppose the user bet $500 and ties --> user will lose $250 total)
```
Account Number: 12345678
Current Balance: $760.00
Game Played: 2
Total Amount Won: $10.00
Total Amount Loss: $250.00
```

After playing game 3: (Suppose the user bet $100 and loses --> user will lose $100 total)
```
Account Number: 12345678
Current Balance: $660.00
Game Played: 3
Total Amount Won: $10.00
Total Amount Loss: $350.00
```

After playing game 4: (Suppose the user bet $100 and want to split, then an additional $100 will be withdrawn from the user account, say the user won both --> user will receive $400 total)
```
Account Number: 12345678
Current Balance: $1060.00
Game Played: 4
Total Amount Won: $210.00
Total Amount Loss: $350.00
```
