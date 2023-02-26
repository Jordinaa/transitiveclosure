#include "functions.cpp"

int main(){
    // inits const variable for filename 
    const string FILENAME = "data.txt";

    // init choices 
    vector<vector<int>> matrix;
    int choice = 0;
    int vectorChoice;

    // main menu screen
    cout << "enter the type of input to use: " << endl;
    cout << "0 - File" << endl;
    cout << "1 - Use set values:" << endl;
    cout << "enter your choice: ";

    // user selects 1 or 0
    cin >> choice;

    if(choice == 0){
        // read matrix function which takes in path for file
        // assigns to vector in case you want to use it for something 
        vector<vector<int>> file = readMatrixFile(FILENAME);
    }

    // else statement which lets user decide of matrix size
    else{
        // prints and initializes matrix with sizes 2-4
        cout << "here are vectors with dimensions (2-4) which do you prefer? " << endl;
        initsMatrix(4, matrix, false);
        initsMatrix(3, matrix, false);
        initsMatrix(2, matrix, false);
        cout << "enter 2, 3, or 4: ";

        // user selects their desired matrix size
        cin >> vectorChoice;

        // prints and inits users selected matrix
        initsMatrix(vectorChoice, matrix, true);

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

        cout << "\n" << "the transitive closure is: " << endl;
        vector<vector<int>> tcResult = transitiveClosure(fourthResult);
        printMatrix(tcResult);}
}