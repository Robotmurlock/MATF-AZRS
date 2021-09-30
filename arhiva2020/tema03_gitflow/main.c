#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

/* ~~~~~~~~~~~~~~~~~~~~~~ */

// Predefined 'constants' (macros):
// CARD NUM      - number of card types
// MAX_PATH_LEN  - maximum size of path length to card image file
// LINE_SIZE     - maximum line size for printing cards from hand
// MAX_HAND_SIZE - maximum hand size: 4xAce, 4xTwo, 3xThree = 21
//                 thus theoretical maximum hand size is 12
// DECK_SIZE     - default deck size
// BUFFSIZE      - default buffer size
// BAR           - constant string used in show_hand function 

#define CARD_NUM 13
#define MAX_PATH_LEN 100
#define LINE_SIZE 256
#define MAX_LINES 32
#define MAX_HAND_SIZE 12
#define DECK_SIZE 52
#define BUFFSIZE 64
#define BAR "____________________________________________________________\n"

//---------------------------------------------------------------------------------------------------------
///
/// prints error message and exits program with given exit_code
/// @param msg is error message giving information about what went wrong
/// @param exit_code is program exit code number that must be different than 0
///        since error occured
//
void error(char* msg, int exit_code)
{
    printf("%s\n", msg);
    exit(exit_code);
}

enum card_type{
    C_ACE = 0,
    C_KING = 1,
    C_QUEEN = 2,
    C_JACK = 3,
    C_10 = 4,
    C_9 = 5,
    C_8 = 6,
    C_7 = 7,
    C_6 = 8,
    C_5 = 9,
    C_4 = 10,
    C_3 = 11,
    C_2 = 12
};

// Every card is defined by its enum type and image_path
typedef struct Card{
    enum card_type type;
    char image_path[MAX_PATH_LEN];
} card;

// Maximum hand size is 12: 4xAce, 4xTwo, 3xThree + ANYCARD > 21
typedef struct Hand{
    unsigned size;
    card* cards[MAX_HAND_SIZE];
} hand;

// Deck size is 52. Only difference between deck and hand struct is card* array size
typedef struct Deck{
    card* cards[DECK_SIZE];
    unsigned next_card;
} deck;

//---------------------------------------------------------------------------------------------------------
/// Checks if card image file is valid
/// Card image file must not exceed maximum line number
///
/// @param card is checked to see if size of some line in file card.image_path is too long
//
void check_card(card card)
{
    FILE* input = fopen(card.image_path, "r");
    // This can error can only occur if someone deletes image file
    // while the program is running
    if(input == NULL)
        error("Reading card image failed!", 1);

    // Reading every line in image txt file and checking line size
    char* line = malloc(LINE_SIZE);
    while(fgets(line, LINE_SIZE, input) != NULL)
    {
        int line_len = strlen(line);
        if(line_len >= 70)
            error("[ERR] Invalid File(s).", -3);
    }

    free(line);
    fclose(input);
}

//---------------------------------------------------------------------------------------------------------
/// Loads image paths from map_path into cards array
/// If card is missing or is not valid then program is interrupted with
/// some exit_code
///
/// @param cards is array where that are read from card directory (map_path) cards are being stored
/// @param map_path is path to directory with card images represented as txt file
///        if some card is missing in directory, error is "thrown" with some exit_code
//
void init_cards(card* cards, char* map_path)
{
    // Checking if file is a directory
    struct stat file_info;
    if(stat(map_path, &file_info) == -1)
        error("Reading file info failed!", 1);
    if(!S_ISDIR(file_info.st_mode))
        error("Map path does not point on a directory!", 1);
    
    // Opening directory to read all files
    DIR* dir = opendir(map_path);
    struct dirent* entry = NULL;
    // support array to check which card images were found
    // if some card image is missing then error is thrown
    int found_card[CARD_NUM];
    int i;
    for(i=0; i<CARD_NUM; i++)
        found_card[i] = 0;

    // reading files from dir
    while((entry = readdir(dir)) != NULL)
    {
        int card_index = -1;
        char* name = entry->d_name;
        if(strcmp(name, "2.txt") == 0)
            card_index = C_2;
        else if(strcmp(name, "3.txt") == 0)
            card_index = C_3;
        else if(strcmp(name, "4.txt") == 0)
            card_index = C_4;
        else if(strcmp(name, "5.txt") == 0)
            card_index = C_5;
        else if(strcmp(name, "6.txt") == 0)
            card_index = C_6;
        else if(strcmp(name, "7.txt") == 0)
            card_index = C_7;
        else if(strcmp(name, "8.txt") == 0)
            card_index = C_8;
        else if(strcmp(name, "9.txt") == 0)
            card_index = C_9;
        else if(strcmp(name, "10.txt") == 0)
            card_index = C_10;
        else if(strcmp(name, "jack.txt") == 0)
            card_index = C_JACK;
        else if(strcmp(name, "queen.txt") == 0)
            card_index = C_QUEEN;
        else if(strcmp(name, "king.txt") == 0)
            card_index = C_KING;
        else if(strcmp(name, "ace.txt") == 0)
            card_index = C_ACE;
        
        // if card_index is -1 then file in directory is not
        // card image file and is skipped
        if(card_index == -1)
            continue;
        found_card[card_index] = 1;

        // setting card relative path to image
        sprintf(cards[card_index].image_path, "./%s/%s", map_path, name);
        cards[card_index].type = card_index;
    }

    closedir(dir);

    // checking if all cards are found
    for(i=0; i<CARD_NUM; i++)
        if(found_card[i] == 0)
            error("Missing a card from map path!", 1);

    // checking line lenght for all cards
    for(i=0; i<CARD_NUM; i++)
        check_card(cards[i]);
}

//---------------------------------------------------------------------------------------------------------
///
/// Algorithm that shuffles deck in linear time complexity
/// @param deck is shuffled using Fisher Yates algorithm
/// @param seed is seed number for pseudo random number generating
///        same sequence of numbers is generated for same seed
//
void fisher_yates(deck* d, unsigned* seed)
{
    if(seed)
        srand(*seed);
    else
        srand(time(NULL));

    int k;
    // FISHER YATES
    for(k=DECK_SIZE-1; k>=1; k--)
    {
        int r = ((unsigned)rand()) % (k+1);
        card* t = d->cards[k];
        d->cards[k] = d->cards[r];
        d->cards[r] = t;
    }
}

//---------------------------------------------------------------------------------------------------------
///
/// returns new shuffled deck
/// @param cards is list of cards with their value and image_path
/// @param seed is parameter that is required in shuffle function
// 
deck new_deck(card* cards, unsigned* seed)
{
    // Initializing new deck and next_card index
    deck d;
    d.next_card = 0;
    int i;

    // Initial deck: A A A A K K K K Q Q Q Q ... 3 3 3 3 2 2 2 2
    for(i=0; i<DECK_SIZE; i++)
        d.cards[i] = &cards[i/4];

    // shufling deck
    fisher_yates(&d, seed);

    return d;
}

//---------------------------------------------------------------------------------------------------------
///
/// Draw a card from deck and add it to the hand
/// Hand (h) changes: new card, incremented size
/// Deck (d) changes: incremented next_card value
///
/// @param hand is player's (or dealer's) hand where new card is being added
/// @param deck is shuffled deck of cards from which next card is being drawn
//

void hit(hand* h, deck* d)
{
    h->cards[h->size] = d->cards[d->next_card++];
    h->size++;
}

//---------------------------------------------------------------------------------------------------------
///
/// Calculates value (score) of given hand
///
/// @param h is player's (or dealer's) hand 
///        score is being calculated for given hand
// 
int hand_value(hand* h)
{
    int i;
    int value = 0;

    // boolean value that it used to check is there is an ace in hand
    int has_ace = 0;
    for(i=0; i<h->size; i++)
    {
        enum card_type type = h->cards[i]->type;
        switch (type)
        {
            case C_2:
                value += 2;
                break;
            case C_3:
                value += 3;
                break;
            case C_4:
                value += 4;
                break;
            case C_5:
                value += 5;
                break;
            case C_6:
                value += 6;
                break;
            case C_7:
                value += 7;
                break;
            case C_8:
                value += 8;
                break;
            case C_9:
                value += 9;
                break;
            case C_10:
            case C_JACK:
            case C_QUEEN:
            case C_KING:
                value += 10;
                break;
            case C_ACE:
                // default value for ace is 1
                value += 1;
                has_ace = 1;
                break;
        }
    }
    // If hand has multiple aces then only one ace can have value 11
    // example: two aces with value 11 = 22 
    // By default every ace is values as 1
    // but if with default ace value, hand value is 11 or less
    // then we can cound one ace as 11 (from 1)
    if(has_ace && value <= 11)
        value += 10;
    return value;
}

//---------------------------------------------------------------------------------------------------------
///
/// Prints all cards from hand in one row
///
/// @param caption is message that is being shown
///        (ex. PLAYERS HAND:)
// 
void show_hand(hand* h, char* caption)
{
    // caption example: "YOUR HANDS:", "DEALER HANDS:", etc.
    printf("%s\n\n", caption);
    printf(BAR);
    int i;

    // allocated array of strings to store card image parts in one line
    char** lines = malloc(MAX_LINES*sizeof(char*));
    int size = 0;
    for(i=0; i<MAX_LINES; i++)
    {
        lines[i] = malloc(LINE_SIZE);
        int j;
        for(j=0; j<LINE_SIZE; j++)
            lines[i][j] = '\0';
    }

    for(i=0; i<h->size; i++)
    {
        // Opening card image file
        FILE* input = fopen(h->cards[i]->image_path, "r");
        if(input == NULL)
            error("Reading card image failed!", 1);

        char* line = malloc(LINE_SIZE);
        int line_index = 0;
        // Reading all lines from card image file
        while(fgets(line, LINE_SIZE, input) != NULL)
        {
            // if it is not first card (leftmost) then concatenate 
            // current row with new card line
            // else just take new card line
            if(strlen(lines[line_index]) > 0)
                sprintf(lines[line_index], "%s  %s", lines[line_index], line);
            else
                strcpy(lines[line_index], line);
            int n = strlen(lines[line_index]);
            // Removing '\n' character from end
            if(lines[line_index][n-1] == '\n')
                lines[line_index][n-1] = '\0';
        
            line_index++;
            // size represents number of lines that need to be printed
            size = (line_index > size) ? line_index : size;
        }

        free(line);
        fclose(input);
    }
    // Prints results
    for(i=0; i<size; i++)
        printf("%s\n", lines[i]);

    // Freeing all lines
    for(i=0; i<MAX_LINES; i++)
        free(lines[i]);
    free(lines);

    // Printing hand score and BAR
    printf("score:%d\n\n", hand_value(h));
    printf(BAR);
}

//---------------------------------------------------------------------------------------------------------
///
/// When game starts both player and dealer draw two cards
/// Dealer hand size is 'reduced' and only one hand is shown where second one is hidden
/// Initial player hand size is 2 and initial dealer hand size is 1
/// Both dealer and player hands are shown after initialization
///
/// @param dealer is dealer's hand that is being initialized 
///        dealer starts with two cards, where one is hidden
///        cards are being drawn using hit() function
/// @param player is player's hand that is being initialized
///        player starts with two cards
/// @param d is deck from which cards are being drawn using hit() function
//
void start_game(hand* dealer, hand* player, deck* d)
{
    player->size = 0;
    dealer->size = 0;
    // Player draws two cards
    hit(player, d);
    hit(player, d);

    // Dealer draws two cards and hides second card
    hit(dealer, d);
    hit(dealer, d);
    dealer->size--;

    show_hand(dealer, "DEALERS CARDS:");
    show_hand(player, "YOUR CARDS:");
}

int main(int argc, char** argv)
{
    // There must be at least two arguments 
    // (first one is program name and second one is card directory)
    if(argc < 2)
    {
        printf("usage: %s <input_folder>", argv[0]);
        exit(-1);
    }

    // path to card files
    char* map_path = argv[1];

    // If user inserts second argument then set it as seed
    unsigned* seed = NULL;
    if(argc >= 3)
    {
        unsigned seed_value = strtol(argv[2], NULL, 10);
        seed = &seed_value;
    }

    // Allocating cards array and setting up card image paths for every card
    card* cards = malloc(CARD_NUM*sizeof(card));
    init_cards(cards, map_path);

    // Creating new shuffled deck and initializing player and dealer card hands
    deck d = new_deck(cards, seed);
    hand dealer;
    hand player;
    start_game(&dealer, &player, &d);

    // If player has blackjack then check if dealer also has blackjack
    // If dealer does not have a blackjack then player instantly wins
    // otherwise it's a tie
    int player_has_blackjack = hand_value(&player) == 21;
    if(player_has_blackjack)
    {
        dealer.size++;
        int dealer_has_blackjack = hand_value(&dealer) == 21;;
        show_hand(&dealer, "BLACKJACK! DEALERS CARDS:");

        if(!dealer_has_blackjack)
            printf("YOU WIN!");
        else
            printf("BLACKJACK! PUSH!\n");
    }
    else
    {
        // No blackjacks occured, thus playing game normally 
        // Player turn!
        char* buffer = malloc(BUFFSIZE);
        while(1)
        {
            printf("HIT (h) or STAND (s)\n");
            scanf("%s", buffer);
            // h (HIT) - draw another card
            if(strcmp(buffer, "h") == 0)
            {
                // draw a card and show new hand
                // if hand value is greater than 21 then player looses
                hit(&player, &d);
                show_hand(&player, "YOUR CARDS:");
                int value = hand_value(&player);
                if(value > 21)
                {
                    printf("BUST! YOU LOOSE!");
                    break;
                }
                else if(value == 21)
                    break;
            }
            // s (STAND) - keep your hand
            else if(strcmp(buffer, "s") == 0)
                break;
        }

        free(buffer);
        int player_hand_value = hand_value(&player);
        int dealer_hand_value = hand_value(&dealer);

        // If player has hand value higher than 21 then dealer automaticly wins
        if(player_hand_value <= 21)
        {
            printf("DEALERS TURN\n");
            // revealing dealer's hidden card by incrementing hand size
            dealer.size++;
            // Calculating dealer hand value and showing dealer hand with revealed card
            dealer_hand_value = hand_value(&dealer);
            show_hand(&dealer, "DEALERS CARDS:");
            int dealer_has_blackjack = hand_value(&dealer) == 21;
            // if dealer doesn't have blackjack then he draws cards until he has 
            // better hand than player or looses
            if(!dealer_has_blackjack)
            {
                // Dealer draws cards until he has better hand than player or 21
                while(dealer_hand_value < 21 && dealer_hand_value <= player_hand_value)
                {
                    hit(&dealer, &d);
                    dealer_hand_value = hand_value(&dealer);
                    printf("DEALER GETS ANOTHER CARD..\n");
                    show_hand(&dealer, "DEALERS CARDS:");
                }

                if(dealer_hand_value > 21)
                    printf("BUST! YOU WIN!");
                else if(dealer_hand_value == player_hand_value)
                    printf("PUSH!\n");
            }
            // otherwise dealer has blackjack and instantly wins
            else
            {
                printf("BLACKJACK! YOU LOOSE!");
            }
        }
    }
    
    free(cards);
    return 0;
}