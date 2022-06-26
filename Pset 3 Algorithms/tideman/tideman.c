#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j (DIRECTED GRAPH)
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
void print_preferences(void);
void print_pairs(void);
bool check_cycle(int winner, int base_case);
void print_locked();

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
        //print_preferences();

        printf("\n");
    }

    add_pairs();
    //print_pairs();
    sort_pairs();
    //print_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // First I need to se if the candidate exists.
    for (int i = 0; candidates[i] != NULL; i++)
    {
        if (strcmp(name, candidates[i]) == 0) // If candidate existes we can put it on the voter's ranking
        {
            ranks[rank] = i; // We store the candidate index of Candidates (Like emulate pointers on python)
            return true;
        }
    }

    return false; // If candidate doesn't exist: Invalid vote.
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1 ; i++)
    {
        for (int j = i + 1; j < candidate_count ; j++)
        {
            preferences[ranks[i]][ranks[j]]++;   // Update preferences matrix (Diagonal is 0)
        }

    }
    return;
}

void print_preferences()
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i", preferences[i][j]);
        }
        printf("\n");
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++) // Iterates right half of the matrix (Avoid the diagonal)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair new_pair;         // Create new element of type pair
                new_pair.winner = i;
                new_pair.loser = j;
                pairs[pair_count] = new_pair;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pair new_pair;         // Create new element of type pair
                new_pair.winner = j;
                new_pair.loser = i;
                pairs[pair_count] = new_pair;
                pair_count++;
            }
        }
    }
    return;
}

void print_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        printf("(%i, %i),", pairs[i].winner, pairs[i].loser);
    }
    printf("\n");
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++) // I will perform bubble sort
    {
        for (int j = 0; j < pair_count - 1; j++)
        {
            if(preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                pair aux = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = aux;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < candidate_count; i++) // Iterate pairs to be added
    {
        // Before add that pair we need to know if it not creates a cycle. We have to folow the path
        bool answer = check_cycle(pairs[i].loser, pairs[i].winner);
        if (answer == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = 1;
        }
        //print_locked();
    }
    return;
}

void print_locked()
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i", locked[i][j]);
        }
        printf("\n");
    }
}

bool check_cycle(int winner, int base_case)
{
    // BASE CASE
    if (winner == base_case)
    {
        return true;
    }

    // RECURSIVE CASE
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[winner][i] == 1)
        {
            if (check_cycle(i, base_case))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    int recount = 0;

    // Wich column doesn't have 1
    for (int i = 0; i < candidate_count; i++)
    {
        recount = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == 1)
            {
                recount++;
            }
        }

        if (recount == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}