#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

using namespace std;

// Objective function to be maximized: f(x) = -x^2 + 5x + 10
double objectiveFunction(double x)
{
    return -x * x + 5 * x + 10;
}

// Function to generate a random neighboring solution (neighbor of current x)
double getRandomNeighbor(double current, double step_size)
{
    // Generate a small random step either positive or negative
    double step = ((rand() % 2 == 0) ? 1 : -1) * step_size;
    return current + step;
}

// Hill Climbing algorithm
double hillClimbing(double start_x, double step_size, int max_iterations)
{
    double current_x = start_x;                          // Start with an initial solution
    double current_value = objectiveFunction(current_x); // Evaluate the function at the starting point

    for (int i = 0; i < max_iterations; i++)
    {
        // Get a neighboring solution
        double neighbor_x = getRandomNeighbor(current_x, step_size);
        double neighbor_value = objectiveFunction(neighbor_x);

        // If the neighboring solution is better, move to that solution
        if (neighbor_value > current_value)
        {
            current_x = neighbor_x;
            current_value = neighbor_value;
        }

        // Print the current state after each iteration for debugging
        cout << "Iteration " << i + 1 << ": x = " << current_x << ", f(x) = " << current_value << endl;
    }

    return current_x; // Return the best solution found
}

int main()
{
    srand(time(0)); // Seed the random number generator

    double start_x = 0.0;     // Starting point (initial guess)
    double step_size = 0.1;   // Small step size for neighboring solutions
    int max_iterations = 100; // Maximum number of iterations to perform

    cout << "Starting Hill Climbing with initial x = " << start_x << endl;

    // Perform hill climbing
    double best_x = hillClimbing(start_x, step_size, max_iterations);
    double best_value = objectiveFunction(best_x);

    cout << "Best solution found: x = " << best_x << ", f(x) = " << best_value << endl;

    return 0;
}
