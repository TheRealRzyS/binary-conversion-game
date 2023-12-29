# binary-conversion-game
A game to train speed for decimal to binary conversions

Created as an inspiration to a chapter in my Foundation of Computer Science Class

Made changes to improve the security of the code including:
1. Use of fgets instead of scanf for string inputs to prevent buffer overflow
2. Modified the generateRandomNumber function to prevent integer overflow
3. Improved the random number generation to be more unpredictable
4. Limited the use of the MAX_DIGITS global variable by passing it as an argument to function where needed
5. Added a function to validate binary input
6. Ensured safe clearing of input buffer
