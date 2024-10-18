import java.util.*;

public class Main {

    public static boolean canPlace(int[][] container, int[][] box, int startRow, int startCol) {
        int boxHeight = box.length;
        int boxWidth = box[0].length;

        if (startRow + boxHeight > container.length || startCol + boxWidth > container[0].length) {
            return false;
        }

        for (int i = 0; i < boxHeight; i++) {
            for (int j = 0; j < boxWidth; j++) {
                if (box[i][j] == 1 && container[startRow + i][startCol + j] != 0) {
                    return false;
                }
            }
        }
        return true;
    }

    public static void placeBox(int[][] container, int[][] box, int startRow, int startCol, int boxId) {
        int boxHeight = box.length;
        int boxWidth = box[0].length;

        for (int i = 0; i < boxHeight; i++) {
            for (int j = 0; j < boxWidth; j++) {
                if (box[i][j] == 1) {
                    container[startRow + i][startCol + j] = boxId;
                }
            }
        }
    }

    public static void removeBox(int[][] container, int[][] box, int startRow, int startCol) {
        int boxHeight = box.length;
        int boxWidth = box[0].length;

        for (int i = 0; i < boxHeight; i++) {
            for (int j = 0; j < boxWidth; j++) {
                if (box[i][j] == 1) {
                    container[startRow + i][startCol + j] = 0;
                }
            }
        }
    }

    public static int countCombinations(int[][] container, List<int[][]> boxes, List<Integer> boxIds, int currentBoxIndex) {
        if (currentBoxIndex == boxes.size()) {
            return 1;  // All boxes placed, valid combination found
        }

        int count = 0;
        int[][] box = boxes.get(currentBoxIndex);
        int boxId = boxIds.get(currentBoxIndex);

        for (int row = 0; row < container.length; row++) {
            for (int col = 0; col < container[0].length; col++) {
                if (canPlace(container, box, row, col)) {
                    placeBox(container, box, row, col, boxId);
                    count += countCombinations(container, boxes, boxIds, currentBoxIndex + 1);
                    removeBox(container, box, row, col);
                }
            }
        }

        return count;
    }

    public static void main(String[] args) {
        // Define the container
        int[][] container = {
            {0, 0, 0},
            {0, 0, 0}
        };

        // Define the smaller boxes
        List<int[][]> smallerBoxes = new ArrayList<>();
        smallerBoxes.add(new int[][]{{1, 1}});  // 2x1 box
        smallerBoxes.add(new int[][]{{1}});     // 1x1 box

        // Define the box IDs
        List<Integer> boxIds = new ArrayList<>();
        boxIds.add(1);  // ID for 2x1 box
        boxIds.add(2);  // ID for 1x1 box

        // Count how many combinations the smaller boxes can fit into the container
        int totalCombinations = countCombinations(container, smallerBoxes, boxIds, 0);
        System.out.println("Total combinations: " + totalCombinations);
    }
}
