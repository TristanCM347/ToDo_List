# ToDo List Program

This program is designed to manage a ToDo list, offering a comprehensive set of functionalities for adding, managing, and tracking tasks effectively. It allows users to interact with the ToDo list through various commands, with each command triggering a specific function.

## Functionality

- **Priority Levels:** The priority of tasks can be set to "low", "medium", or "high".

### Adding Tasks
- **Command:** `a [task] [category] [priority]`
- **Description:** Adds a new task with specified category and priority.

### Printing Tasks
- **Command:** `p`
- **Description:** Prints all current tasks.

### Updating Priority
- **Command:** `i [task] [category]`
- **Description:** Updates the priority of a task in a cycle: low → medium → high → low, etc.

### Count Tasks
- **Command:** `n`
- **Description:** Counts the total number of tasks.

### Complete Task
- **Command:** `c [task] [category] [start_time (minutes)] [finish_time (minutes)]`
- **Description:** Marks a task as completed with the provided start and finish times.

### Print Completed Tasks
- **Command:** `P`
- **Description:** Prints all completed tasks.

### Expected Completion Time
- **Command:** `e`
- **Description:** Calculates the expected time to complete all tasks.

### Delete Task
- **Command:** `d [task] [category]`
- **Description:** Deletes a specified task.

### Finish Day
- **Command:** `f`
- **Description:** Clears the entire completed tasks list.

### Repeat Task
- **Command:** `r [task] [category]`
- **Description:** Moves a repeatable task from the completed list back to the uncompleted list when `f` command is used.

### Match Tasks
- **Command:** `m [pattern]`
- **Description:** Matches tasks based on a specified pattern.

#### Patterns:
- `*`: Matches any number of characters.
- `?`: Matches a single character.
- `[abc]`: Matches any single character in the brackets.
- `abc`: Matches the exact characters in order.
- Note: only one `*` can appear in a pattern.

### Delete Matched Tasks
- **Command:** `^ [pattern]`
- **Description:** Deletes tasks that match a given pattern.

### Sort Tasks
- **Command:** `s`
- **Description:** Sorts tasks by category, then by priority, and finally by name within each category and priority.


