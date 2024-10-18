def can_place(container, box, start_row, start_col):
    # Check if the box fits in the given position (no overlap, within bounds)
    box_height, box_width = len(box), len(box[0])
    if start_row + box_height > len(container) or start_col + box_width > len(container[0]):
        return False
    for i in range(box_height):
        for j in range(box_width):
            if box[i][j] == 1 and container[start_row + i][start_col + j] != 0:
                return False
    return True

def place_box(container, box, start_row, start_col, box_id):
    # Place the box by marking its position
    box_height, box_width = len(box), len(box[0])
    for i in range(box_height):
        for j in range(box_width):
            if box[i][j] == 1:
                container[start_row + i][start_col + j] = box_id

def remove_box(container, box, start_row, start_col):
    # Remove the box by resetting its position
    box_height, box_width = len(box), len(box[0])
    for i in range(box_height):
        for j in range(box_width):
            if box[i][j] == 1:
                container[start_row + i][start_col + j] = 0

def count_combinations(container, boxes, current_box_index=0):
    if current_box_index == len(boxes):
        return 1  # All boxes placed, valid combination found

    count = 0
    box, box_id = boxes[current_box_index]

    # Try placing the box in all possible positions without rotation
    for row in range(len(container)):
        for col in range(len(container[0])):
            if can_place(container, box, row, col):
                place_box(container, box, row, col, box_id)
                count += count_combinations(container, boxes, current_box_index + 1)
                remove_box(container, box, row, col)

    return count

# Define the container and the smaller boxes
container = [
    [0, 0, 0],
    [0, 0, 0],
    [0, 0, 0]
]

smaller_boxes = [
    ([[1, 1]], 1),  # 2x1 box
    ([[1]], 2)      # 1x1 box
]

# Count how many combinations the smaller boxes can fit into the container
total_combinations = count_combinations(container, smaller_boxes)
print(f"Total combinations: {total_combinations}")
