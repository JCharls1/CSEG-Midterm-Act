#include <iostream>
#include <vector>

using namespace std;

bool canPlace(vector<vector<int>>& container, vector<vector<int>>& box, int startRow, int startCol) {
    int boxHeight = box.size();
    int boxWidth = box[0].size();

    if (startRow + boxHeight > container.size() || startCol + boxWidth > container[0].size()) {
        return false;
    }

    for (int i = 0; i < boxHeight; ++i) {
        for (int j = 0; j < boxWidth; ++j) {
            if (box[i][j] == 1 && container[startRow + i][startCol + j] != 0) {
                return false;
            }
        }
    }
    return true;
}

void placeBox(vector<vector<int>>& container, vector<vector<int>>& box, int startRow, int startCol, int boxId) {
    int boxHeight = box.size();
    int boxWidth = box[0].size();

    for (int i = 0; i < boxHeight; ++i) {
        for (int j = 0; j < boxWidth; ++j) {
            if (box[i][j] == 1) {
                container[startRow + i][startCol + j] = boxId;
            }
        }
    }
}

void removeBox(vector<vector<int>>& container, vector<vector<int>>& box, int startRow, int startCol) {
    int boxHeight = box.size();
    int boxWidth = box[0].size();

    for (int i = 0; i < boxHeight; ++i) {
        for (int j = 0; j < boxWidth; ++j) {
            if (box[i][j] == 1) {
                container[startRow + i][startCol + j] = 0;
            }
        }
    }
}

int countCombinations(vector<vector<int>>& container, vector<pair<vector<vector<int>>, int>>& boxes, int currentBoxIndex = 0) {
    if (currentBoxIndex == boxes.size()) {
        return 1;  // All boxes placed, valid combination found
    }

    int count = 0;
    vector<vector<int>> box = boxes[currentBoxIndex].first;
    int boxId = boxes[currentBoxIndex].second;

    for (int row = 0; row < container.size(); ++row) {
        for (int col = 0; col < container[0].size(); ++col) {
            if (canPlace(container, box, row, col)) {
                placeBox(container, box, row, col, boxId);
                count += countCombinations(container, boxes, currentBoxIndex + 1);
                removeBox(container, box, row, col);
            }
        }
    }

    return count;
}


vector<pair<vector<vector<int>>, int>> fillUpSmallerBox(){
    int numberOfBoxes = 0;
    std::cout << "Enter number of boxes: ";
    std::cin >> numberOfBoxes;
    vector<pair<vector<vector<int>>, int>> smallerBoxes;
    for(int i = 0; i < numberOfBoxes; i++){
        vector<vector<int>> box;
        vector<int> boxValues;
        
        cout << "Box " << i+1 << endl;

        int boxWidth = 0;
        int boxHeight = 0;
        cout << "Enter box width: ";
        cin >> boxWidth;
        
        cout << "Enter box height: ";
        cin >> boxHeight;

        for(int j = 0; j < boxHeight; j++){
            for(int k = 0; k < boxWidth; k++){
                boxValues.push_back(1);         
            }
            box.push_back(boxValues);
        }
        smallerBoxes.push_back({box, i+1});
    }
    return smallerBoxes;
}

vector<vector<int>> fillUpContainer(){
    int containerWidth = 0;
    int containerHeight = 0;
    vector<vector<int>> container;
    vector<int> contener;
    cout << "Container" << endl;
    cout << "Enter container width: ";
    cin >> containerWidth;
    
    cout << "Enter container height: ";
    cin >> containerHeight;

    for(int i = 0; i < containerHeight; i++){
        for(int j = 0; j < containerWidth; j++){
            contener.push_back(0);
        }
        container.push_back(contener);
    }

    return container;
}

int main() {
    vector<vector<int>> container = fillUpContainer(); 
    vector<pair<vector<vector<int>>, int>> smallerBoxes = fillUpSmallerBox();

    int totalCombinations = countCombinations(container, smallerBoxes);
    cout << "Total combinations: " << totalCombinations << endl;

    return 0;
}
