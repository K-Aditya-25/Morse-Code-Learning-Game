// welcome.h
#ifndef MORSE_CODE_H
#define MORSE_CODE_H
const char* morse_encode(char input); //Encode
char morse_decode(const char* input); // Decode
extern const char alpha_table[36];
extern const char *morse_table[];
#endif // WELCOME_H
