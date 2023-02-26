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
vector<vector<int>> transitiveClosure(vector<vector<int>> matrix){
    // gets size of matrix
    int dimensions = matrix.size();
    // inits. vectors
    vector<vector<int>> closure, tempMatrix;
    
    // multiplies and adds it by itself for each dimension of the matrix
    for (int stuff = 0; stuff < dimensions; stuff++){
    // mults. matrix by itself for each dimension n
        matrix = multiplyMatrix(matrix, matrix);
    // now takes that value and adds it to a temporary value  
        closure = addMatrix(closure, matrix);}

    return closure;}

// opens file with data that will be read in 
vector<vector<int>> readMatrixFile(const string filename){
    // open file
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Failed to open file: " << filename << endl;
        exit(1);}
    vector<vector<int>> matrix;
    string line;
    int n = 0;
    while (getline(inputFile, line)){
        if (line.empty()){
            continue;}

        stringstream ss(line);
        if (n == 0) {
            // First line contains matrix size
            ss >> n;
            matrix.resize(n, vector<int>(n, 0));} 
            else{
            // Subsequent lines contain matrix rows
            for (int j = 0; j < n; j++) {
                ss >> matrix[n - 1][j];}
            n--;
            // says the matrix is done so we can run tests on the matrix
            if (n == 0) {
                // copied from the main function to reduce clutter in main
                cout << "adding the matrix to its self results in: " << endl;
                vector<vector<int>> addResult = addMatrix(matrix, matrix);
                printMatrix(addResult);

                cout << "the result of the matrix to the power of 2 is: " << endl;
                vector<vector<int>> squareResult = multiplyMatrix(matrix, matrix);
                printMatrix(squareResult);

                cout << "the result of the matrix to the power of 3 is: " << endl;
                vector<vector<int>> cubeResult = cubeMatrix(matrix);
                printMatrix(cubeResult);

                cout << "the result of the matrix to the power of 4 is: " << endl;
                vector<vector<int>> fourthResult = fourthMatrix(matrix);
                printMatrix(fourthResult);

                // calls functions that check if matrix is reflexive, symmetric, transitive
                isReflexive(matrix);
                isSymmetric(matrix);
                isTransitive(matrix);
            }
        }
    }
    return matrix;
}

