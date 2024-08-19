#include "welcome.h"
#include <stdio.h>

void welcome() {

    printf("     ██████╗ █████╗ ███╗   ██╗    ██╗   ██╗ ██████╗ ██╗   ██╗    ███╗   ███╗ ██████╗ ██████╗ ███████╗███████╗\n");
    printf("    ██╔════╝██╔══██╗████╗  ██║    ╚██╗ ██╔╝██╔═══██╗██║   ██║    ████╗ ████║██╔═══██╗██╔══██╗██╔════╝██╔════╝\n");
    printf("    ██║     ███████║██╔██╗ ██║     ╚████╔╝ ██║   ██║██║   ██║    ██╔████╔██║██║   ██║██████╔╝███████╗█████╗  \n");
    printf("    ██║     ██╔══██║██║╚██╗██║      ╚██╔╝  ██║   ██║██║   ██║    ██║╚██╔╝██║██║   ██║██╔══██╗╚════██║██╔══╝  \n");
    printf("    ╚██████╗██║  ██║██║ ╚████║       ██║   ╚██████╔╝╚██████╔╝    ██║ ╚═╝ ██║╚██████╔╝██║  ██║███████║███████╗\n");
    printf("     ╚═════╝╚═╝  ╚═╝╚═╝  ╚═══╝.......╚═╝    ╚═════╝  ╚═════╝     ╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝\n");
    printf("\n");
    printf("                              ██████╗ ██████╗  ██████╗ ██╗   ██╗██████╗     ██╗  ██╗\n");
    printf("                             ██╔════╝ ██╔══██╗██╔═══██╗██║   ██║██╔══██╗    ██║  ██║\n");
    printf("                             ██║  ███╗██████╔╝██║   ██║██║   ██║██████╔╝    ███████║\n");
    printf("                             ██║   ██║██╔══██╗██║   ██║██║   ██║██╔═══╝     ╚════██║\n");
    printf("                             ╚██████╔╝██║  ██║╚██████╔╝╚██████╔╝██║              ██║\n");
    printf("                              ╚═════╝ ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝              ╚═╝\n");
    printf("\n\n");


    printf("                                                 Gameplay:\n");
    printf("- Press the GP21 button for a short duration to input a Morse \"dot\" (.) and a longer duration for a Morse \"dash\" (-).\n");
    printf("           - A pause of at least 1 second after entering dots or dashes will register as a \"space\" character.\n");
    printf("            - Another pause of at least 1 second will complete the sequence and submit it for pattern matching.\n");
    printf("- The input sequence will be displayed as Morse code and its alphanumeric equivalent. If it doesn't match any character, a \"?\" will be shown.\n");
    printf("                   - You start the game with three lives, indicated by the RGB LED turning green.\n");
    printf( "                 - With each mistake, you lose a life. Lives can be gained by answering correctly.\n\n");
   
    printf("                                        USE GP21 TO ENTER A SEQUENCE TO BEGIN       \n");
    printf("                                           \".----\" - LEVEL 01 - CHARS (EASY)          \n");
    printf("                                           \"..---\" - LEVEL 02 - CHARS (HARD)          \n");
    printf("                                           \"...--\" - LEVEL 03 - WORDS (EASY)         \n");
    printf("                                           \"....-\" - LEVEL 04 - WORDS (HARD)         \n");

    printf("                    - To advance to the next level, you must input 5 correct sequences in a row.\n");
    printf("                             - If no input is detected for 9 seconds, the game will end.\n\n");

    printf("                           ███╗   ███╗ █████╗ ██╗   ██╗    ████████╗██╗  ██╗███████╗\n");
    printf("                           ████╗ ████║██╔══██╗╚██╗ ██╔╝    ╚══██╔══╝██║  ██║██╔════╝\n");
    printf("                           ██╔████╔██║███████║ ╚████╔╝        ██║   ███████║█████╗  \n");
    printf("                           ██║╚██╔╝██║██╔══██║  ╚██╔╝         ██║   ██╔══██║██╔══╝  \n");
    printf("                           ██║ ╚═╝ ██║██║  ██║   ██║          ██║   ██║  ██║███████╗\n");
    printf("                           ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝          ╚═╝   ╚═╝  ╚═╝╚══════╝\n");
    printf("\n");
    printf("                                ███╗   ███╗ ██████╗ ██████╗ ███████╗███████╗\n");
    printf("                                ████╗ ████║██╔═══██╗██╔══██╗██╔════╝██╔════╝\n");
    printf("                                ██╔████╔██║██║   ██║██████╔╝███████╗█████╗  \n");
    printf("                                ██║╚██╔╝██║██║   ██║██╔══██╗╚════██║██╔══╝  \n");
    printf("                                ██║ ╚═╝ ██║╚██████╔╝██║  ██║███████║███████╗\n");
    printf("                                ╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝\n");
    printf("\n");
    printf("                            ██████╗ ███████╗    ██╗    ██╗██╗████████╗██╗  ██╗\n");
    printf("                            ██╔══██╗██╔════╝    ██║    ██║██║╚══██╔══╝██║  ██║\n");
    printf("                            ██████╔╝█████╗      ██║ █╗ ██║██║   ██║   ███████║\n");
    printf("                            ██╔══██╗██╔══╝      ██║███╗██║██║   ██║   ██╔══██║\n");
    printf("                            ██████╔╝███████╗    ╚███╔███╔╝██║   ██║   ██║  ██║\n");
    printf("                            ╚═════╝ ╚══════╝     ╚══╝╚══╝ ╚═╝   ╚═╝   ╚═╝  ╚═╝\n");
    printf("\n");
    printf("                                        ██╗   ██╗ ██████╗ ██╗   ██╗          \n");
    printf("                                        ╚██╗ ██╔╝██╔═══██╗██║   ██║          \n");
    printf("                                         ╚████╔╝ ██║   ██║██║   ██║          \n");
    printf("                                          ╚██╔╝  ██║   ██║██║   ██║          \n");
    printf("                                           ██║   ╚██████╔╝╚██████╔╝          \n");
    printf("                                           ╚═╝    ╚═════╝  ╚═════╝           \n");
}
