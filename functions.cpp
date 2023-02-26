#include "functions.h"

// function that prints a matrix
void printMatrix(vector<vector<int>> matrix){
    // takes size of matrix so you dont have to input size
    int n = matrix.size();
    int m = matrix[0].size();
    // iterates through rows and columns and prints 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(5) << left << matrix[i][j];}
        cout << endl;}
    // cout << "\n" << endl;
}

// takes 3 args if the print boolean is false it will print which vec dim else it will print the current matrix is ...
void initsMatrix(int dimension, vector<vector<int>>& matrix, bool print = false){
    // init. blank matrix 
    matrix.resize(dimension);
    for (int i = 0; i < dimension; i++){
        matrix[i].resize(dimension);
    }
    // switch case for each matrix provided
    switch (dimension){
        case 4:
            matrix = {{1, 1, 1, 0},
                      {1, 1, 0, 1},
                      {1, 0, 0, 0},
                      {0, 1, 0, 1}};
            break;
        case 3:
            matrix = {{1, 1, 0},
                      {0, 1, 0},
                      {1, 0, 1}};
            break;
        case 2:
            matrix = {{1, 0},
                      {0, 1}};
            break;
        default:
            cout << "Invalid dimension!" << endl;
            break;}
    // if the boolean arg is false it will print a different message for diff points in the program
    if (print == false){
        cout << "the matrix with dimension " << dimension << ":" << endl;
        printMatrix(matrix);}
    else{
        cout << "the current matrix is:" << endl;
        printMatrix(matrix);}
}

// adds two matrixs
vector<vector<int>> addMatrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2){
    // inits. variables for size of matrix 1 - they should be the same size
    int n = matrix1.size();
    int m = matrix1[0].size();
    // create a 2d vector called result with n rows and m columns all elements are init. to 0
    vector<vector<int>> result(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;
}

// multiplies two matrixs, this is a multi purpose function used in cube matrix and fourth matrix
vector<vector<int>> multiplyMatrix(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2){

    int n = matrix1.size();
    // this creates a vector called result with n rows and n columns respectively with all elements set to 0
    vector<vector<int>> result(n, vector<int>(n, 0));
    // iterates through each element of each matrix and then adds and multiplies each corresponding row # to its respective column #
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

// Function that calculates the third power of a matrix
vector<vector<int>> cubeMatrix(vector<vector<int>>& matrix){
    int n = matrix.size();
    // uses the the mult. matrix function to square them assigned them to a vector and uses it again. 
    vector<vector<int>> result = multiplyMatrix(matrix, matrix);
    result = multiplyMatrix(result, matrix);
    return result;
}

// Function to calculate the fourth power of a matrix
vector<vector<int>> fourthMatrix(vector<vector<int>>& matrix){
    int n = matrix.size();
    // uses the same logic has the cube matrix function. assigns the result to a vector and and multiplies it by itself again
    vector<vector<int>> result = multiplyMatrix(matrix, matrix);
    result = multiplyMatrix(result, result);
    return result;
}

// checks if matrix is reflexive 
bool isReflexive(vector<vector<int>> matrix){
    // gets size of matrix
    int n = matrix.size();
    // loop through rows
    for (int i = 0; i < n; i++) {
    // if diagnal element is not 1 then matrix is not reflexive
        if (matrix[i][i] != 1) {
            cout << "the matrix is not reflexive" << endl;
            return false;
        }
    }
    cout << "the matrix is reflexive" << endl;
    return true;
}

// checks if symmetric
bool isSymmetric(vector<vector<int>> matrix){
    // same as reflexive - gets size of matrix
    int n = matrix.size();
    // iterates over rows
    for (int i = 0; i < n; i++){
    // iterates over columns
        for (int j = 0; j < n; j++) {
    // checks for symmetry 
            if (matrix[i][j] != matrix[j][i]){
                cout << "the matrix is not symmetric" << endl;
                return false;
            }
        }
    }
    cout << "the matrix is symmetric" << endl;
    return true;
}

// checks if transitive
bool isTransitive(vector<vector<int>> matrix){
    // same as two functions before
    int n = matrix.size();
    // iterates over each row of the matrix
    vector<vector<int>> squaredMatrix = multiplyMatrix(matrix, matrix);
    // iterates over each row of matrix
    for (int i = 0; i < n; i++) {
    // iterates over each column of matrix 
        for (int j = 0; j < n; j++) {
    // if there is a directed path from i to j but no edge between them then it is not transitive
            if (squaredMatrix[i][j] > 0 && matrix[i][j] == 0){
                cout << "the matrix is not transitive" << endl;
                return false;
            }
        }
    }
    cout << "the matrix is transitive" << endl;
    return true;
}

// finds transitive closure of a matrix
// im not sure if this is wrong or right but the images provided in the rubrik i think are wrong
// they should be 1s and 0s if I am not mistaken at least from my linear algebra class that makes sense to me. i could be comepletely wrong.
vector<vector<int>> transitiveClosure(vector<vector<int>> matrix){
    int n = matrix.size();
    // initialize the closure matrix to all zeroes
    vector<vector<int>> closure(n, vector<int>(n, 0)); 
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
    // copy the original matrix to the closure matrix
            closure[i][j] = matrix[i][j]; 
        }
    }
    for (int k = 0; k < n; k++) {
    // initialize a new matrix to all zeroes
        vector<vector<int>> next(n, vector<int>(n, 0)); 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++){
    // update the new matrix using the transitive closure rule            
                next[i][j] = closure[i][j] || (closure[i][k] && closure[k][j]); 
            }
        }
    // set the closure matrix to the updated matrix
        closure = next; 
    }
    return closure;
}

// reads file and take sfirst input for dimension of array and uses the rest of the line to fill in the
vector<vector<vector<int>>> readMatrixFile(string filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: File not found" << endl;
        exit(1);
    }
    vector<vector<vector<int>>> matrices;
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);

        // Read the first integer to get the matrix size
        int n;
        iss >> n;
        // Create a matrix of size n x n
        vector<vector<int>> matrix(n, vector<int>(n));
        // Read the rest of the line and populate the matrix
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!(iss >> matrix[i][j])) {
                    cerr << "Error: Not enough elements in the line for matrix of size " << n << endl;
                    exit(1);
                }
            }
        }
        matrices.push_back(matrix);
    }

    return matrices;
}
