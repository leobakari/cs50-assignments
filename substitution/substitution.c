#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Programm that excepts a 26 character cypherstring via a command line argument and prints a given string in the cyphered format.
// Pogramm forbids doublicated characters, special characters, short cypherstring, more arguments and no argument.
// Print is case sensetive to the input string to cypher.
int validate_string_len(string cypherString);
int print_cyper_text(string plainText, string cypherSub);
int validate_chars_alpha(string cypherString);
int validate_arg_len(int argLen);
int validate_chars(string cypherString);

int main(int argc, string argv[])
{
    // initializing used variables.
    int validityCharIsAplha;
    string subString;
    // Function returning true if length of args is 2 (function and the cypherstring).
    int validityArgLen = validate_arg_len(argc);

    if (validityArgLen)
    {
        subString = argv[1];
        // Checks if user input is without special characters
        validityCharIsAplha = validate_chars_alpha(subString);
        if (validityCharIsAplha == 1)
        {
            printf("Only letters are allowed as cyhper characters. Please restart the program\n");
            return 1;
        }
    }
    else
    {
        printf("Please provide 1 argument, the cypher string.\n");
        return 1;
    }

    int validitySubStringChars = validate_chars(subString);
    int validitySubString = validate_string_len(subString);
    if (validitySubString && validitySubStringChars)
    {
        // promt plaintext
        // check if every character is present once!!
        string plainText = get_string("plaintext:");
        print_cyper_text(plainText, subString);
        return 0;
    }
    else if (validitySubStringChars == 0)
    {
        printf("Please enter a valid string. Character dublications and special characters are prohibited \n");
        return 1;
    }
    else
    {
        // throw message
        printf("Key must contain 26 characters.\n");
        return 1;
    }
}

int validate_arg_len(int argLen)
{
    if (argLen == 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int validate_string_len(string cypherString)
{
    int wordLength = strlen(cypherString);
    if (wordLength == 26)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int validate_chars_alpha(string cypherString)
{
    int isAlphaChars = 0;
    for (int i = 0; i < 26; i++)
    {
        if (isalpha(cypherString[i]))
        {
            isAlphaChars++;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

int validate_chars(string cypherString)
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int i = 0;
    char testChar;
    while (i < 27)
    {
        testChar = alphabet[i];
        int charCount = 0;
        for (int j = 0; cypherString[j]; j++)
        {
            if (toupper(testChar) == toupper(cypherString[j]))
            {
                charCount++;
                if (charCount != 1)
                {
                    return 0;
                    break;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }
        i++;
    }
    return 1;
}

int print_cyper_text(string plainText, string cypherSub)
{
    int plainLen = strlen(plainText);
    int charDigit = 0;
    int itteration = 0;
    int queryDigit;
    int cypherDigit;
    string cypherWord;
    printf("ciphertext: ");
    while (itteration < plainLen)
    {
        charDigit = plainText[itteration];
        if ((int) charDigit <= 122 && charDigit >= 97)
        {
            queryDigit = charDigit - 97;
            cypherDigit = cypherSub[queryDigit];
            printf("%c", tolower(cypherDigit));
        }
        else if ((int) charDigit <= 90 && charDigit >= 65)
        {
            queryDigit = charDigit - 65;
            cypherDigit = cypherSub[queryDigit];
            printf("%c", toupper(cypherDigit));
        }
        else
        {
            printf("%c", charDigit);
        }
        itteration++;
    }
    printf("\n");
    return 0;
}
