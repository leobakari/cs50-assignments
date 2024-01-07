#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
int print_winner(int score1, int score2);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    print_winner(score1, score2);
}

int compute_score(string word)
{
    int wordLength = strlen(word);
    int indexChar = 0;
    int score = 0;
    for (int itteration = 0; itteration < wordLength; itteration++)
    {
        indexChar = (int) toupper(word[itteration]);

        if (indexChar <= 64 || indexChar >= 91)
        {
            score = score + 0;
        }
        else
        {
            indexChar = indexChar - 65;
            score = score + (int) POINTS[indexChar];
        }
    }
    return score;
}

int print_winner(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
    return 0;
}