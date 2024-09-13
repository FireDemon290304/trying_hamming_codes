#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int print_board(bool board_inp[], int size);
int get_board_status(bool board_inp[], const int size);

/**
 * Intro:
 * The code will print a board of x bits (power of 2), and place a key in a random slot.
 * Your task is to flip exactly ONE bit, and one bit only, in order to make the board "pont" to the right bit.
 * The board counts as such:
 * Least significant integer in the constructed bit, is the sum of all bit positions where the least significant
 * position of the bit-position is one AND where the value of the board is one.
 * This is then shifted, to look at the second-to-least significant position, and so on.
 * This is done for all tiles of the board.
 * @return Exit code
 */
int main(void)
{
    int board_size = 16;        // Has to be power of 2, otherwise impossible

    srand(time(NULL));              // Seed rand
    bool board_state[board_size];           // Randomize board
    for (int i = 0; i < board_size; i++) { board_state[i] = rand() % 2; }


    const int key_pos = rand() % board_size;      // Place the key

    // Print the board
    print_board(board_state, board_size);

    // Print the bit that the board is currently pointing to, and get the number in decimal
    get_board_status(board_state, board_size);

    // Print key_pos for debugging
    printf("Key Pos: %d\n", key_pos);

    // flip one bit
    int chosen_bit = 0;
    printf("Please choose a bit to flip: ");
    scanf("%d", &chosen_bit);

    board_state[chosen_bit] = !board_state[chosen_bit];        // Flip
    printf("\n");

    // Show new board to player so they can cry when they get it wrong
    print_board(board_state, board_size);

    // Check if player won
    key_pos == get_board_status(board_state, board_size) ? printf("You win!\n") : printf("You lose!\n");

    return EXIT_SUCCESS;
}

/**
 * Prints the current state of the board / theoretical bit array
 * @param board_inp Array containing the board
 * @param size The size of the board
 * @return Exit code
 */
int print_board(bool board_inp[], const int size) {
    const int s = (int)sqrt(size);
    for (int i = 1; i < size + 1; i++) { printf((i % s) == 0 ? "%d\n\n" : "%d\t", board_inp[i - 1]); }
    return EXIT_SUCCESS;
}

/**
 * Prints the bit-position that the current board is pointing to as bits, and returns the value as decimal
 * @param board_inp Array containing the board
 * @param size The size of the board
 * @return The current bit that is pointed to in the board (as int)
 */
int get_board_status(bool board_inp[], const int size) {
    const int req_bits = (int)log2(size);
    int bits_count[req_bits];  // Array to store counts for log2 of the size
    int constructed_number = 0;  // Variable to store the final number

    /* for each place in the board, loop over every bit
     * If the least significant is a one, add to the relevant groups. */
    for (int i = 0; i < size; i++) {
        int current_board_pos = i;
        int bit_position = 0;
        while (current_board_pos > 0) {
            if ((current_board_pos & 1) && board_inp[i] == true) {        // Check least significant
                if (bit_position < req_bits) {                            // Handle up to `req_bits` bits
                    bits_count[bit_position]++;                    // Increment relevant bit count
                }
            }
            current_board_pos >>= 1;            // shift one to the right (div by 2)
            bit_position++;
        }
    }

    // Print results and construct the number
    for (int i = req_bits - 1; i >= 0; i--) {   // Print in reverse order to match original order
        int bit_value = bits_count[i] % 2;
        printf("%d ", bit_value);

        // Construct the number from the bits
        constructed_number |= (bit_value << i);
    }
    printf("\n");

    // Print the constructed number
    printf("Constructed number: %d\n", constructed_number);

    return constructed_number;
}
