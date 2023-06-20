# Tideman Voting Algorithm

This code implements the Tideman voting algorithm, which is used to determine the winner of an election based on ranked preferences of candidates. The algorithm solves the problem of determining the winner in a ranked-choice voting system where voters rank candidates in order of preference.

## Code Explanation

1. The code includes the necessary header files and defines constants and data structures needed for the algorithm.

2. The `main` function is where the execution of the program begins. It performs the following steps:
   - It checks the command-line arguments to ensure that at least one candidate is provided.
   - It populates the array of candidates based on the command-line arguments.
   - It initializes the preferences and locked arrays.
   - It prompts the user to enter the number of voters and collects their ranked preferences.
   - It calls various functions to process the votes and determine the winner.
   - It prints the winner of the election.

3. The `vote` function is responsible for updating the ranks array given a new vote. It searches for the candidate name in the candidates array and assigns the corresponding index to the ranks array.

4. The `record_preferences` function updates the preferences array based on a single voter's ranks. It iterates over the ranks array and records the number of voters who prefer one candidate over another.

5. The `add_pairs` function records pairs of candidates where one candidate is preferred over the other based on the preferences array. It compares the number of voters who prefer candidate i over candidate j with the number of voters who prefer candidate j over candidate i and adds the pair to the pairs array accordingly.

6. The `sort_pairs` function sorts the pairs array in decreasing order based on the strength of victory. It uses a selection sort algorithm to compare the strength of victory for each pair and swaps them if necessary.

7. The `lock_pairs` function locks the pairs into the candidate graph in order, without creating cycles. It iterates over the pairs array and checks if adding an edge between the winner and loser would create a cycle. If not, it adds the edge to the locked array.

8. The `print_winner` function determines and prints the winner of the election based on the locked array. It checks for the candidate (source) with no incoming edges, indicating that they are the winner.

9. The `check_cycle` function checks if adding a new edge between the row and column would create a cycle in the locked array. It recursively checks if there is a path from the column to the row, indicating the presence of a cycle.

## How to Use the Program

To use the Tideman voting program, follow these steps:

1. **Compile the program:** Compile the code using a C compiler. For example, if you have the GNU Compiler Collection (GCC) installed, you can compile the code by running the following command in the terminal:

2. **Run the program:** Execute the compiled program by running the following command in the terminal:
Replace `[candidate ...]` with the names of the candidates participating in the election. Specify at least two candidates.

3. **Enter the number of voters:** After running the program, it will prompt you to enter the number of voters participating in the election. Type the number and press Enter.

4. **Collect voter preferences:** The program will then ask each voter to rank the candidates in order of preference. For each voter, provide the ranks for each candidate by following the prompts. For example, if there are three candidates, the program will ask for the voter's first preference, second preference, and third preference.

5. **Determine the winner:** Once all the voters' preferences have been collected, the program will process the votes, determine the winner using the Tideman algorithm, and display the winner's name on the screen.

By following these steps, you can use the Tideman voting program to calculate the winner of an election based on ranked preferences.

Note: The program expects input in the terminal, so make sure to run it in a command-line environment.

## GitHub Profile

- GitHub: [maarten-mobron](https://github.com/maarten-mobron)
