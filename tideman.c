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
}
pair;

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
bool check_cycle(int row, int column);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
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
    // iterate through ranks array to find the preferred candidate
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int preferred = ranks[i];

        // iterate through ranks array to find preferred over candidates
        for (int j = i + 1; j < candidate_count; j++)
        {
            int preferred_over = ranks[j];
            preferences[preferred][preferred_over]++;
        }

    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            else if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // performs selection sort based on the decreasing order of strength of victory
    for (int i = 0; i < pair_count - 1; i++)
    {
        int strong_victory_index = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            int diff = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            int curr_diff = preferences[pairs[strong_victory_index].winner][pairs[strong_victory_index].loser] -
                            preferences[pairs[strong_victory_index].loser][pairs[strong_victory_index].winner];
            if (diff > curr_diff)
            {
                strong_victory_index = j;
            }
        }
        // swaps the first element with strong_victory_index
        pair temp = pairs[strong_victory_index];
        pairs[strong_victory_index] = pairs[i];
        pairs[i] = temp;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int row = pairs[i].winner;
        int column = pairs[i].loser;
        if (!check_cycle(row, column))
        {
            // creates edge between winner and loser
            locked[row][column] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{

    int source = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        int sum = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            sum += locked[j][i];
        }
        if (sum == 0)
        {
            source = i;
            break;
        }
    }

    printf("%s\n", candidates[source]);
    return;
}

// checks if adding a new edge would result in an cycle.
bool check_cycle(int row, int column)
{
    // checks if there is an edge between column and row.
    // if true adding and edge between row and column will result in a cycle.
    if (locked[column][row])
    {
        return true;
    }
    // The loop iterates over all i from 0 to candidate_count-1.
    for (int i = 0; i < candidate_count; i++)
    {
        // if i is true, call recursive with row and i.
        // if recursive call returns true, both conditions are met and function will return true.
        if (locked[column][i] && check_cycle(row, i))
        {
            return true;
        }
    }
    return false;
}
