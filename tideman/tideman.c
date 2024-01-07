#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool dfs_finds_loop(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Done!
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int candidate_i = 0; candidate_i < candidate_count; candidate_i++)
    {
        for (int loser_i = candidate_i + 1; loser_i < candidate_count; loser_i++)
        {
            preferences[ranks[candidate_i]][ranks[loser_i]] += 1;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int candidate_i = 0; candidate_i < candidate_count; candidate_i++)
    {
        for (int opponent_i = 0; opponent_i < candidate_count; opponent_i++)
        {
            if (preferences[candidate_i][opponent_i] > preferences[opponent_i][candidate_i])
            {
                pair viewed;
                viewed.winner = candidate_i;
                viewed.loser = opponent_i;
                pairs[pair_count] = viewed;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Googled for further ressources of sorting and addapted this logic to my issue:
    // https://www.sanfoundry.com/c-program-sort-array-descending-order/
    pair tempPair;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                tempPair.winner = pairs[i].winner;
                tempPair.loser = pairs[i].loser;

                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;

                pairs[j].winner = tempPair.winner;
                pairs[j].loser = tempPair.loser;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles

void lock_pairs(void)
{
    for (int pair_i = 0; pair_i < pair_count; pair_i++)
    {
        if (!dfs_finds_loop(pairs[pair_i].winner, pairs[pair_i].loser))
        {
            locked[pairs[pair_i].winner][pairs[pair_i].loser] = true;
        }
    }
    return;
}

bool dfs_finds_loop(int winner, int loser)
{
    // Additional ressources checked in order to get solution:
    // Recursion and Callstack: https://www.youtube.com/watch?v=ygK0YON10sQ
    // Reddit community discussion - Brought me the tip to check for Depth first search algorthim:
    // https://www.reddit.com/r/cs50/comments/x1ve0t/advice_on_locked_pairs_tideman/
    // the DFS lesson: https://www.youtube.com/watch?v=jQmlXAwUvZ4
    if (locked[loser][winner] == true)
    {
        return true;
    }
    for (int candidate_i = 0; candidate_i < candidate_count; candidate_i++)
    {
        if (locked[loser][candidate_i] == true && dfs_finds_loop(winner, candidate_i))
        {
            return true;
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int canidate_i = 0; canidate_i < candidate_count; canidate_i++)
    {
        bool winner = true;
        for (int opponent_i = 0; opponent_i < candidate_count; opponent_i++)
        {
            if (locked[opponent_i][canidate_i] == true)
            {
                winner = false;
                break;
            }
        }
        if (winner == true)
        {
            printf("%s\n", candidates[canidate_i]);
            return;
        }
    }
    return;
}