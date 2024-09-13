 * The code will print a board of x bits (power of 2), and place a key in a random slot.
 * Your task is to flip exactly ONE bit, and one bit only, in order to make the board "pont" to the right bit.
 * The board counts as such:
 * Least significant integer in the constructed bit, is the sum of all bit positions where the least significant
 * position of the bit-position is one AND where the value of the board is one.
 * This is then shifted, to look at the second-to-least significant position, and so on.
 * This is done for all tiles of the board.
