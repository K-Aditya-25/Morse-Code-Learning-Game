#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "morse_code.h"

const char alpha_table[36]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
                    'R','S','T','U','V','W','X','Y','Z',
                    '0','1','2','3','4','5','6','7','8','9'};
const char *morse_table[] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--..",
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
    };
// Function to encode a single character into Morse code
const char* morse_encode(char input) {

    // Convert input to uppercase to simplify matching
    input = toupper(input);

    // Check if input is a letter
    if(input >= 'A' && input <= 'Z') {
        return morse_table[input - 'A'];
    }
    // Check if input is a digit
    else if(input >= '0' && input <= '9') {
        return morse_table[input - '0' + 26]; // Offset by 26 to reach the digit's position in morse_table
    }
    // Return an error message if input is not a letter or digit
    else {
        return "Invalid input";
    }
}
// Function to decode a Morse code string into an alphanumeric character
char morse_decode(const char* input) {

    // Number of elements in morse_table
    const int table_size = sizeof(morse_table) / sizeof(morse_table[0]);

    // Search for the input Morse code in the morse_table
    for(int i = 0; i < table_size; i++) {
        if(strcmp(morse_table[i], input) == 0) {
            // If the index is less than 26, it's a letter
            if(i < 26) {
                return 'A' + i;
            }
            // Otherwise, it's a digit
            else {
                return '0' + (i - 26);
            }
        }
    }

    // Return an error indicator if the Morse code is not found
    return '?';
}
// This is a function that decodes the morse code into the character
// However changes are required because the assignment only asks to decode characters not whole words
// void morse_decode(char *input, char *output, char **morse_table)
// {
//     // Main index for the output Array
//     int z = 0;
//     // temp string Index (For the morse String we form)
//     int index = 0;
//     // Temperory string (To hold the morse String)
//     char *tempString = malloc(2 * sizeof(char));

//     // Looping through the input array
//     for (int i = 0; i < strlen(input); i++)
//     {
//         char x = input[i];

//         // End of Character OR End of word
//         if (x == ' ')
//         {
//             tempString[index] = '\0';
//             // To find the index of the morse String we have
//             int morseIndex = -1;
//             for (int j = 0; j < alphanumeric_Count; j++)
//             {
//                 if (strcmp(morse_table[j], tempString) == 0)
//                 {
//                     morseIndex = j;
//                     break;
//                 }
//             }

//             // End Of Word (Require Space in output Array)
//             if (input[i + 1] == '_')
//             {
//                 output[z] = 'A' + morseIndex;
//                 z++;
//                 output[z] = ' ';
//                 z++;
//                 i = i + 2;
//             }

//             // End of Character (No Space in ouput array needed)
//             else
//             {
//                 output[z] = 'A' + morseIndex;
//                 z++;
//             }

//             free(tempString);
//             tempString = malloc(2 * sizeof(char));
//             index = 0;
//         }
//         // Conactenate
//         else
//         {
//             tempString[index] = x;
//             index++;
//             tempString = realloc(tempString, (index + 2) * sizeof(char));
//         }
//     }
// }

