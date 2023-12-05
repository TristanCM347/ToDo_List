// Todo List
// This program takes input to create a todo list with multiple features

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define INVALID_PRIORITY -1

#define MAX_TASK_LENGTH     200
#define MAX_CATEGORY_LENGTH 40
#define MAX_STRING_LENGTH   1024

#define TRUE  1
#define FALSE 0

#define COMMAND_ADD_TASK                    'a'
#define COMMABD_PRINT_TASKS                 'p'
#define COMMAND_UPDATE_PRIORITY             'i'
#define COMMAND_COUNTING_TASKS              'n'
#define COMMAND_TASK_COMPLETION             'c'
#define COMMAND_PRINT_COMPLETED_TASKS       'P'
#define COMMAND_EXPECTED_TIME               'e'
#define COMMAND_DELETE_TASK                 'd'
#define COMMAND_FREE_COMPLETED_LIST         'f'
#define COMMAND_REPEAT_TASK                 'r'
#define COMMAND_MATCHING_TASK               'm'
#define COMMAND_DELETING_MATCHED_TASKS      '^'
#define COMMAND_SORTING_TASKS               's'

enum priority { LOW, MEDIUM, HIGH };

struct task {
    char task_name[MAX_TASK_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    enum priority priority;
    struct task *next;
    // this is a true or false value
    int repeatable;
};

struct completed_task {
    struct task *task;
    int start_time;
    int finish_time;
    struct completed_task *next;
};

struct todo_list {
    struct task *tasks;
    struct completed_task *completed_tasks;
};

////////////////////////////////////////////////////////////////////////////////
///////////////////// YOUR FUNCTION PROTOTYPES GO HERE /////////////////////////
////////////////////////////////////////////////////////////////////////////////



void command_loop(struct todo_list *todo);
void add_task_function(struct todo_list *todo);
void print_tasks_function(struct todo_list *todo);
void update_priority_function(struct todo_list *todo);
void changing_priority(struct todo_list *todo, int number_of_counts);
int checking_task_name_for_i_command(
    struct todo_list *todo, 
    char task[MAX_TASK_LENGTH]
);
int checking_task_name_for_c_command(
    struct todo_list *todo, 
    char task[MAX_TASK_LENGTH],
    int start_time,
    int finish_time
);
void counting_tasks_function(struct todo_list *todo);
void task_completed_function(struct todo_list *todo);
int checking_matching_category_function(
    struct todo_list *todo, 
    char category[MAX_CATEGORY_LENGTH]
);
void completed_task_operations(
    struct todo_list *todo, 
    int number_of_counts,
    int start_time,
    int finish_time
);
void print_completed_tasks_function(struct todo_list *todo);
void average_calculation_and_print(
    struct todo_list *todo, 
    struct task *current
);
void expected_completion_time_function(struct todo_list *todo); 
void delete_task_function(struct todo_list *todo);
int checking_task_name_for_d_command (
    struct todo_list *todo, 
    char task[MAX_TASK_LENGTH]
);
void deleting_task(struct todo_list *todo, int number_of_counts);
void free_completed_list_function(struct todo_list *todo);
void repeat_task_function(struct todo_list *todo);
int checking_task_name_for_r_command(
    struct todo_list *todo, 
    char task[MAX_TASK_LENGTH]
);
void making_it_repeatable(struct todo_list *todo, int number_of_counts); 
void adding_task_to_end_of_list(struct todo_list *todo, struct task *new_task);
void adding_task_start_of_list(struct todo_list *todo, struct task *new_task);
void free_memory_function(struct todo_list *todo);
void matching_task_function(struct todo_list *todo);
int does_the_task_match_function(
    struct task *current, 
    char pattern[MAX_STRING_LENGTH]
);
int paratheses_pattern_forward_fucntion(
    struct task *current, 
    char pattern[MAX_STRING_LENGTH],
    int *pattern_char_ptr1,
    int task_char,
    int matching_pattern
);
void task_finishes_b4_pattern(
    int pattern_char, 
    char pattern[MAX_STRING_LENGTH],
    int *star_certified_ptr1,
    int *matching_pattern_ptr1
);
void work_backwards_for_star_function(
    struct task *current, 
    char pattern[MAX_STRING_LENGTH],
    int *task_char,
    int *matching_pattern_ptr1
);
void paratheses_pattern_backward_fucntion(
    struct task *current, 
    char pattern[MAX_STRING_LENGTH],
    int *backwards_pattern_char_ptr1,
    int backwards_task_char,
    int **matching_pattern_ptr2
);
void deleting_matched_tasks_function(struct todo_list *todo);
void sorting_tasks_function(struct todo_list *todo);
struct task *adding_to_sorted_list(
    struct task *sorted_head, 
    struct task *insertion
);
void adding_one_to_chars(int *pattern_char_ptr1, int *task_char_ptr1);


////////////////////////////////////////////////////////////////////////////////
//////////////////////// PROVIDED HELPER PROTOTYPES ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void parse_add_task_line(
    char buffer[MAX_STRING_LENGTH], char task_name[MAX_TASK_LENGTH],
    char task_category[MAX_CATEGORY_LENGTH], enum priority *prio
);
void parse_task_category_line(
    char buffer[MAX_STRING_LENGTH], char task_name[MAX_TASK_LENGTH],
    char task_category[MAX_CATEGORY_LENGTH]
);
void parse_complete_task_line(
    char buffer[MAX_STRING_LENGTH], char task_name[MAX_TASK_LENGTH],
    char task_category[MAX_CATEGORY_LENGTH], int *start_time, int *finish_time
);

enum priority string_to_priority(char priority[MAX_STRING_LENGTH]);
void remove_newline(char input[MAX_STRING_LENGTH]);
void trim_whitespace(char input[MAX_STRING_LENGTH]);
void print_one_task(int task_num, struct task *task);
void print_completed_task(struct completed_task *completed_task);

int task_compare(struct task *t1, struct task *t2);
struct task *resetting_current(struct todo_list *todo, int number_of_counts);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {
    printf("Welcome to ToDo!\n");
    struct todo_list *todo = malloc(sizeof(struct todo_list));
    todo->tasks = NULL;
    todo->completed_tasks = NULL;
    
    command_loop(todo);
    free_memory_function(todo);
    return 0;

}


//command loop that scans in first char in every input to decide required action
void command_loop(struct todo_list *todo) {
    printf("Enter Command: ");
    char command;
    while (scanf(" %c", &command) == 1) {
        if (command == COMMAND_ADD_TASK) {
            add_task_function(todo);
        } else if (command == COMMABD_PRINT_TASKS) {
            print_tasks_function(todo);
        } else if (command == COMMAND_UPDATE_PRIORITY) {
            update_priority_function(todo);
        } else if (command == COMMAND_COUNTING_TASKS) {
            counting_tasks_function(todo);
        } else if (command == COMMAND_TASK_COMPLETION) {
            task_completed_function(todo);
        } else if (command == COMMAND_PRINT_COMPLETED_TASKS) {
            print_completed_tasks_function(todo);
        } else if (command == COMMAND_EXPECTED_TIME) {
            expected_completion_time_function(todo);
        } else if (command == COMMAND_DELETE_TASK) {
            delete_task_function(todo);
        } else if (command == COMMAND_FREE_COMPLETED_LIST) {
            free_completed_list_function(todo);
        } else if (command == COMMAND_REPEAT_TASK) {
            repeat_task_function(todo);
        } else if (command == COMMAND_MATCHING_TASK) {
            matching_task_function(todo);
        } else if (command == COMMAND_DELETING_MATCHED_TASKS) {
            deleting_matched_tasks_function(todo);
        } else if (command == COMMAND_SORTING_TASKS) {
            sorting_tasks_function(todo);
        }

        printf("Enter Command: ");
    }
    printf("All done!\n");
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////// YOUR HELPER FUNCTIONS ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////


//loops thorugh all tasks and sends them to adding sorted to list function
// once tasks list is empty replaces it with new osrted list of tasks
void sorting_tasks_function(struct todo_list *todo) {
    struct task *sorted_head = NULL;
    //add tasks in sorted order to new_head list and at the same time deleting 
    //that task from todo->tasks
    //eventually todo->tasks == NULL
    //then todo->tasks = new_head
    while (todo->tasks != NULL) {
        struct task *current = todo->tasks;
        if (todo->tasks->next == NULL) {
            //last one so dont have to reattach
            todo->tasks = NULL;
            current->next = NULL;
            sorted_head = adding_to_sorted_list(sorted_head, current);
        } else {
            todo->tasks = todo->tasks->next;
            current->next = NULL;
            sorted_head = adding_to_sorted_list(sorted_head, current);
        }
    }
    todo->tasks = sorted_head;
}


// returns the sorted list function after editting it with the inputed tasks
struct task *adding_to_sorted_list(
    struct task *sorted_head, 
    struct task *insertion
) {
    struct task *current = sorted_head;
    //loop through sorted list anc compare to each task
    if (sorted_head == NULL) {
        sorted_head = insertion;
        //this means there 0 in list
    } else if (task_compare(insertion, sorted_head) < 0) {
        //make insertion the new head
        sorted_head = insertion;
        insertion->next = current;
    } else if (sorted_head->next == NULL) {
        //theres only 1 in list and it didnt go at the start so must go next
        sorted_head->next = insertion;
    } else {
        //theres more than 1 in the list and it doesnt insert at the start
        int been_inserted = FALSE;
        //loop through to find where it inserts
        while (been_inserted != TRUE && current->next != NULL) {
            if (task_compare(insertion, current->next) < 0) {
                insertion->next = current->next;
                current->next = insertion;
                been_inserted = TRUE;
            } else {
                current = current->next;
            }
        }
        //its going in at the end of the list
        if (been_inserted == FALSE) {
            current->next = insertion;
        }
    }
    
    return sorted_head;
}


//loops through all tasks and checks to see if they matched, 
//so they can be removed
void deleting_matched_tasks_function(struct todo_list *todo) {
    char pattern[MAX_STRING_LENGTH];
    fgets(pattern, MAX_STRING_LENGTH, stdin);
    trim_whitespace(pattern);
    int matching_pattern;
    //loop thoruhg every task and use the rules for patterns
    if (todo->tasks != NULL) {
        int number_of_counts = 1;
        struct task *current = todo->tasks;
        
        while (current != NULL) {
            matching_pattern = does_the_task_match_function(current, pattern);
            if (matching_pattern == TRUE) {
                deleting_task(todo, number_of_counts);
                current = resetting_current(todo, number_of_counts);
            } else {
                number_of_counts++;
                current = current->next;
            }
        }
    }
}


//resets teh current struct so that it points to the end of the list
//retruns current
struct task *resetting_current(struct todo_list *todo, int number_of_counts) {
    struct task *current = todo->tasks;
    for (int i = 1; i < number_of_counts; i++) {
        current = current->next;
    }
    return current;
}


//deletes task, frees it, and relinks the linked list
void deleting_task(struct todo_list *todo, int number_of_counts) {
    struct task *current = todo->tasks;
    if (number_of_counts == 1) {
        todo->tasks = current->next;
        free(current);
    } else {
        for (int i = 1; i < (number_of_counts - 1); i++) {
            current = current->next;
        }
        struct task *temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
}


//scans in pattern
//loops through every tasks so each task undergoes does the taks match function
void matching_task_function(struct todo_list *todo) {
    //scans in pattern from input
    char pattern[MAX_STRING_LENGTH];
    fgets(pattern, MAX_STRING_LENGTH, stdin);
    trim_whitespace(pattern);
    printf("Tasks matching pattern '%s':\n", pattern);
    int task_num = 1;
    int matching_pattern;
    
    //loop thoruhg every task and use the rules 
    if (todo->tasks != NULL) {
        struct task *current = todo->tasks;
        while (current != NULL) {
            matching_pattern = does_the_task_match_function(current, pattern);
            if (matching_pattern == TRUE) {
                print_one_task(task_num, current);
                task_num++;
            }
            current = current->next;
        }
    }
}


//checks if chars in paretheses match
//returns true or false
int paratheses_pattern_forward_fucntion(
    struct task *current, 
    char pattern[MAX_STRING_LENGTH],
    int *pattern_char_ptr1,
    int task_char,
    int matching_pattern
) {
    if (pattern[*pattern_char_ptr1] == current->task_name[task_char]) {
        matching_pattern = TRUE;
    }
    if (matching_pattern == TRUE) {
        while (pattern[*pattern_char_ptr1 + 1] != ']') {
            *pattern_char_ptr1 = *pattern_char_ptr1 + 1;
        }
    }

    return matching_pattern;
}


//checks if chars in paretheses match
//returns pointer to value that is true or false
void paratheses_pattern_backward_fucntion(
    struct task *current, 
    char pattern[MAX_STRING_LENGTH],
    int *backwards_pattern_char_ptr1,
    int backwards_task_char,
    int **matching_pattern_ptr2
) {
    if (pattern[*backwards_pattern_char_ptr1] == 
    current->task_name[backwards_task_char]) {
        **matching_pattern_ptr2 = TRUE;
    }

    if (**matching_pattern_ptr2 == TRUE) {
        while (pattern[*backwards_pattern_char_ptr1 - 1] != '[') {
            *backwards_pattern_char_ptr1 = *backwards_pattern_char_ptr1 - 1;
        }
    }
}


//cases when task finsishes before pattern
//alters pointers for matching pattern and stat certified
void task_finishes_b4_pattern(
    int pattern_char, 
    char pattern[MAX_STRING_LENGTH],
    int *star_certified_ptr1,
    int *matching_pattern_ptr1
) {
    if (pattern[pattern_char] == '*' && pattern[pattern_char + 1] == '\0') {
        *star_certified_ptr1 = TRUE;
    } else {
        *matching_pattern_ptr1 = FALSE;
    }
}


//adds one to task char and pattern char pointers
void adding_one_to_chars(int *pattern_char_ptr1, int *task_char_ptr1) {
    *pattern_char_ptr1 = *pattern_char_ptr1 + 1;
    *task_char_ptr1 = *task_char_ptr1 + 1;
}


//checks inputed task if it matches inputted pattern
//returns true or false if it matches or not
int does_the_task_match_function(
    struct task *current, 
    char pattern[MAX_STRING_LENGTH]
) {
    int star_certified = FALSE;
    int matching_pattern = TRUE;
    int pattern_char = 0; 
    int task_char = 0;
    
    while (star_certified == FALSE && 
    pattern[pattern_char] != '\0' && matching_pattern == TRUE) {
        if (current->task_name[task_char] == '\0') {
            task_finishes_b4_pattern(pattern_char, 
            pattern, &star_certified, &matching_pattern);
        } else if (pattern[pattern_char] == '?') {
            adding_one_to_chars(&pattern_char, &task_char);

        } else if (pattern[pattern_char] == '[') {
            pattern_char++;
            matching_pattern = FALSE;
            while (pattern[pattern_char] != ']') {
                matching_pattern = 
                paratheses_pattern_forward_fucntion(current, pattern, 
                &pattern_char, task_char, matching_pattern);
                pattern_char++;
            }
            adding_one_to_chars(&pattern_char, &task_char);

        } else if (pattern[pattern_char] == '*') {
            work_backwards_for_star_function(current, pattern, &task_char,
            &matching_pattern);
            if (matching_pattern == TRUE) {
                star_certified = TRUE;
            }

        } else {
            if (pattern[pattern_char] != current->task_name[task_char]) {
                matching_pattern = FALSE;
            } else {
                adding_one_to_chars(&pattern_char, &task_char);
            }
        }
    }

    if (star_certified == FALSE && matching_pattern == TRUE 
    && current->task_name[task_char] != '\0') {
        matching_pattern = FALSE;
    }
    return matching_pattern;
}


//similar to does the task match function but loops from the end to front
//to account for the * that is in the pattern
void work_backwards_for_star_function(
    struct task *current, 
    char pattern[MAX_STRING_LENGTH],
    int *task_char,
    int *matching_pattern_ptr1
) {
    int backwards_pattern_char = 0;
    int backwards_task_char = 0;

    //sets backwards chars to last characters in there strings
    while (pattern[backwards_pattern_char + 1] != '\0') {
        backwards_pattern_char++;
    }
    while (current->task_name[backwards_task_char + 1] != '\0') {
        backwards_task_char++;
    }
    *task_char = *task_char - 1;

    while (*matching_pattern_ptr1 == TRUE 
    && pattern[backwards_pattern_char] != '*') {
        if (*task_char == backwards_task_char) {
            *matching_pattern_ptr1 = FALSE;
        } else if (pattern[backwards_pattern_char] == '?') {
            backwards_pattern_char--;
            backwards_task_char--;
        } else if (pattern[backwards_pattern_char] == ']') {
            backwards_pattern_char--;
            *matching_pattern_ptr1 = FALSE;
            while (pattern[backwards_pattern_char] != '[') {
                paratheses_pattern_backward_fucntion(current, pattern, 
                &backwards_pattern_char, backwards_task_char, 
                &matching_pattern_ptr1);
                backwards_pattern_char--;
            }
            backwards_pattern_char--;
            backwards_task_char--;
        } else {
            if (pattern[backwards_pattern_char] != 
            current->task_name[backwards_task_char]) {
                *matching_pattern_ptr1 = FALSE;
            } else {
                backwards_task_char--;
                backwards_pattern_char--;
            }
        }
    }
}


// frees all the leftover memeory in the program after its exited
void free_memory_function(struct todo_list *todo) {
    free_completed_list_function(todo);
    //todo->completed_tasks = NULL now
    //now free tasks
    while (todo->tasks != NULL) {
        struct task *current = todo->tasks;
        if (todo->tasks->next == NULL) {
            free(todo->tasks);
            todo->tasks = NULL;
        } else {
            while (current->next->next != NULL) {
                current = current->next;
            }
            /// now on second last
            free(current->next);
            current->next = NULL;
        }
    }
    free(todo);
}


//adds tasks to the end of the tasks linked list
void add_task_function(struct todo_list *todo) {
    //READ IN TASK
    char buffer[MAX_STRING_LENGTH];
    fgets(buffer, MAX_STRING_LENGTH, stdin);
    char task_name[MAX_TASK_LENGTH];
    char task_category[MAX_CATEGORY_LENGTH];
    enum priority task_priority;
    parse_add_task_line(buffer, task_name, task_category, 
    &task_priority);
    
    //adding the task
    struct task *new_task = malloc(sizeof(struct task));
    strcpy(new_task->task_name, task_name);
    strcpy(new_task->category, task_category);
    new_task->priority = task_priority;
    new_task->next = NULL;
    new_task->repeatable = FALSE;
    
    adding_task_to_end_of_list(todo, new_task);
}


//scans in input and checks if task matches so it can undergo changing 
//repeatability function
void repeat_task_function(struct todo_list *todo) {
    char buffer[MAX_STRING_LENGTH];
    fgets(buffer, MAX_STRING_LENGTH, stdin);

    char task[MAX_TASK_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    parse_task_category_line(buffer, task, category);

    if (todo->tasks == NULL) {
        printf("Could not find task '%s' in category '%s'.\n", task, category);
    } else {
        int matching_category_or_task = 
        checking_matching_category_function(todo, category);
    
        if (matching_category_or_task == TRUE) {
            matching_category_or_task = 
            checking_task_name_for_r_command(todo, task);
        }
        
        //takes this action if no matches
        if (matching_category_or_task == FALSE) {
            printf("Could not find task '%s' in category '%s'.\n", 
            task, category);
        }
    }
}


// scans in input and checks if a task matches so it can undergo deleting task
//function
void delete_task_function(struct todo_list *todo) {
    char buffer[MAX_STRING_LENGTH];
    fgets(buffer, MAX_STRING_LENGTH, stdin);

    char task[MAX_TASK_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    parse_task_category_line(buffer, task, category);

    if (todo->tasks == NULL) {
        printf("Could not find task '%s' in category '%s'.\n", task, category);
    } else {
        int matching_category_or_task = 
        checking_matching_category_function(todo, category);
    
        if (matching_category_or_task == TRUE) {
            matching_category_or_task = 
            checking_task_name_for_d_command(todo, task);
        }
        
        //takes this action if no matches
        if (matching_category_or_task == FALSE) {
            printf("Could not find task '%s' in category '%s'.\n", 
            task, category);
        }
    }
}


//cahnges repeatabilty of task inputed
void making_it_repeatable(struct todo_list *todo, int number_of_counts) {
    struct task *current = todo->tasks;
    for (int i = 1; i < number_of_counts; i++) {
        current = current->next;
    }
    
    //harcode changes in repeatability
    if (current->repeatable == FALSE) {
        current->repeatable = TRUE;
    } else if (current->repeatable == TRUE) {
        current->repeatable = FALSE;
    }
}


//scans input and checks to see if it mathces so it can undergo making it
//repeatable function
int checking_task_name_for_r_command(
    struct todo_list *todo, 
    char task[MAX_TASK_LENGTH]
) {
    int matching_category_or_task = FALSE;
    struct task *current = todo->tasks;
    int number_of_counts = 1;
    while (current->next != NULL) {
        if (strcmp(current->task_name, task) == 0) {
            matching_category_or_task = TRUE;
            making_it_repeatable(todo, number_of_counts);
        }
        current = current->next;
        number_of_counts++;
    }
    if (strcmp(current->task_name, task) == 0) {
        matching_category_or_task = TRUE;
        making_it_repeatable(todo, number_of_counts);
    }
    return matching_category_or_task;
}


//scans input and checks to see if it mathces so it can delete task
//returns true or false for if it matches
int checking_task_name_for_d_command (
    struct todo_list *todo, 
    char task[MAX_TASK_LENGTH]
) {
    int matching_category_or_task = FALSE;
    struct task *current = todo->tasks;
    int task_has_been_deleted = FALSE;
    int number_of_counts = 1;
    while (task_has_been_deleted == FALSE && current->next != NULL) {
        if (strcmp(current->task_name, task) == 0) {
            matching_category_or_task = TRUE;
            deleting_task(todo, number_of_counts);
            task_has_been_deleted = TRUE;
            
        }
        if (task_has_been_deleted == FALSE) {
            current = current->next;
            number_of_counts++;
        }
    }   
    if (task_has_been_deleted == FALSE && 
    strcmp(current->task_name, task) == 0) {
        matching_category_or_task = TRUE;
        deleting_task(todo, number_of_counts);
    }

    return matching_category_or_task;
}


//counts all tasks  and prints out statement
void counting_tasks_function(struct todo_list *todo) {
    int number_of_tasks = 0;
    if (todo->tasks != NULL) {
        struct task *current = todo->tasks;
        number_of_tasks = 1;
        while (current->next != NULL) {
            current = current->next;
            number_of_tasks++;
        }
    }
    printf("There are %d items on your list!\n", number_of_tasks);
}


//scans in input, and checks if it matches an existing task
//if so undergos adding completed task function
void task_completed_function(struct todo_list *todo) {
    //scans input in
    char buffer[MAX_STRING_LENGTH];
    fgets(buffer, MAX_STRING_LENGTH, stdin);
    char task[MAX_TASK_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    int start_time;
    int finish_time;
    parse_complete_task_line(buffer, task, category, &start_time, &finish_time);

    //checks if list is empty
    if (todo->tasks == NULL) {
        printf("Could not find task '%s' in category '%s'.\n", task, category);
    } else {
        //checks category to see if there is any matches
        int matching_category_or_task = 
        checking_matching_category_function(todo, category);
    
        if (matching_category_or_task == TRUE) {
            matching_category_or_task = 
            checking_task_name_for_c_command(todo, task, 
            start_time, finish_time);
        }
        
        //takes this action if no matches
        if (matching_category_or_task == FALSE) {
            printf("Could not find task '%s' in category '%s'.\n", 
            task, category);
        }
    }
}


//checks category to see if there is any matches
//returns true if matches and false else
int checking_matching_category_function(
    struct todo_list *todo, 
    char category[MAX_CATEGORY_LENGTH]
) {
    int matching_category_or_task = FALSE;
    struct task *current = todo->tasks;
    
    //remember that it already checked before if list was empty
    while (current != NULL) {
        if (strcmp(current->category, category) == 0) {
            matching_category_or_task = TRUE;
        }
        current = current->next;
    }
    
    return matching_category_or_task;
}


//prints all tasks
void print_tasks_function(struct todo_list *todo) {
    printf("==== Your ToDo List ====\n");
    if (todo->tasks == NULL) {
        printf("All tasks completed, you smashed it!\n");
    } else {
        struct task *current = todo->tasks;
        int task_num = 1;
        while (current->next != NULL) {
            print_one_task(task_num, current);
            current = current->next;
            task_num++;
        }
        print_one_task(task_num, current);
    }
    printf("====   That's it!   ====\n");
}


//prints all completed tasks
void print_completed_tasks_function(struct todo_list *todo) {
    printf("==== Completed Tasks ====\n");
    if (todo->completed_tasks == NULL) {
        printf("No tasks have been completed today!\n");
    } else {
        struct completed_task *current = todo->completed_tasks;
        while (current->next != NULL) {
            print_completed_task(current);
            current = current->next;
        }
        print_completed_task(current);
    }
    printf("=========================\n");

}


//frees completed list linked list and moves all repeatable tasks connected to 
//it back to tasks linked list
void free_completed_list_function(struct todo_list *todo) {
    while (todo->completed_tasks != NULL) {
        //move the first one
        //repeat until theres no first one i.e its NULL
        
        struct completed_task *current = todo->completed_tasks;
        if (todo->completed_tasks->next == NULL) {
            //now dont have to reattach anyhting as its the last one
            if (todo->completed_tasks->task->repeatable == TRUE) {
                adding_task_to_end_of_list(todo, todo->completed_tasks->task);
            } else {
                free(todo->completed_tasks->task);
                todo->completed_tasks->task = NULL;
            }
            
            free(todo->completed_tasks);
            todo->completed_tasks = NULL;

        } else {
            //if here it means theres more completed tasks afterwards
            if (current->task->repeatable == TRUE) {
                adding_task_to_end_of_list(todo, current->task);
            } else {
                free(current->task);
                current->task = NULL;
            }
            
            todo->completed_tasks = todo->completed_tasks->next;
            free(current);
        }
    }
}


//adds task to the the start of the linked list of tasks
void adding_task_start_of_list(struct todo_list *todo, struct task *new_task) {
    if (todo->tasks == NULL) {
        //add straight away
        todo->tasks = new_task;
    } else {
        //have to relink list
        struct task *temp = todo->tasks;
        todo->tasks = new_task;
        todo->tasks->next = temp;
    }
}


//adds task to the end of the linked list of tasks
void adding_task_to_end_of_list(struct todo_list *todo, struct task *new_task) {
    if (todo->tasks == NULL) {
        //add straight away
        todo->tasks = new_task;
    } else {
        //loop through linked list to find last task
        struct task *current = todo->tasks;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_task;
    }
}


//scans in and makes sure that task and category match a task
//if not prints could not find, if so undergos update priority function
void update_priority_function(struct todo_list *todo) {
    //scans in input
    char buffer[MAX_STRING_LENGTH];
    fgets(buffer, MAX_STRING_LENGTH, stdin);
    char task[MAX_TASK_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    parse_task_category_line(buffer, task, category);
    
    //trying to find a match
    if (todo->tasks == NULL) {
        printf("Could not find task '%s' in category '%s'.\n", task, category);
    } else {
        int matching_category_or_task = 
        checking_matching_category_function(todo, category);
    
        if (matching_category_or_task == TRUE) {
            matching_category_or_task = 
            checking_task_name_for_i_command(todo, task);
        }
        
        if (matching_category_or_task == FALSE) {
            printf("Could not find task '%s' in category '%s'.\n", 
            task, category);
        }
    }
}


// loops thorugh each remaining task in the linked list so each can 
//undergo the average calculation function and printing functions
void expected_completion_time_function(struct todo_list *todo) {
    printf("Expected completion time for remaining tasks:\n\n");
    //loop through all tasks 
    if (todo->tasks != NULL) {
        struct task *current = todo->tasks;
        int task_num = 1;
        while (current->next != NULL) {
            print_one_task(task_num, current);
            average_calculation_and_print(todo, current);
            current = current->next;
            task_num++;
        }
        print_one_task(task_num, current);
        average_calculation_and_print(todo, current);
    }
}


//calculates the average of the the times in category and then prints 
//out that time 
void average_calculation_and_print(
    struct todo_list *todo, 
    struct task *current
) {
    //loop through all tasks in that category 
    //and add to sum and number in category
    //already checked if tasks list is empty
    int sum_of_times = 0;
    int number_of_tasks = 0;
    int average;
    if (todo->completed_tasks !=NULL) {
        struct completed_task *potential_match = todo->completed_tasks;
        while (potential_match->next != NULL) {
            if (strcmp(potential_match->task->category, 
            current->category) == 0) {
                sum_of_times = sum_of_times + 
                (potential_match->finish_time - potential_match->start_time);
                number_of_tasks++;
            }
            potential_match = potential_match->next;
        }

        //now on the completed task in the list
        if (strcmp(potential_match->task->category, current->category) == 0) {
            sum_of_times = sum_of_times + 
            (potential_match->finish_time - potential_match->start_time);
            number_of_tasks++;
        }
    }

    if (number_of_tasks == 0) {
        average = 100;
    } else {
        average = sum_of_times / number_of_tasks;
    }
    
    printf("Expected completion time: %d minutes\n\n", average);
}


//checks task name to see if there is any matches
//returns if there was any matches so the appropriate outcome can happen
int checking_task_name_for_i_command (
    struct todo_list *todo, 
    char task[MAX_TASK_LENGTH]
) {
    int matching_category_or_task = FALSE;
    struct task *current = todo->tasks;
    int number_of_counts = 1;
    
    while (current->next != NULL) {
        if (strcmp(current->task_name, task) == 0) {
            matching_category_or_task = TRUE;
            changing_priority(todo, number_of_counts);
        }
        current = current->next;
        number_of_counts++;
    }
    //now on the last task in list
    if (strcmp(current->task_name, task) == 0) {
        matching_category_or_task = TRUE;
        changing_priority(todo, number_of_counts);
    }
    return matching_category_or_task;
}


//checks task name to see if there is any matches
//returns if there was any matches so the appropriate outcome can happen
int checking_task_name_for_c_command (
    struct todo_list *todo, 
    char task[MAX_TASK_LENGTH],
    int start_time,
    int finish_time
) {
    int matching_category_or_task = FALSE;
    struct task *current = todo->tasks;
    
    //remember that the list of tasks is > 0 ie not empty
    int number_of_counts = 1;
    int operation_completed = FALSE;
    //starts on task 1
    //operation completed makes sure the loop is broken 
    //once the operation is completed so theres no bugs involving current->next
    while (operation_completed == FALSE && current->next != NULL) {
        if (strcmp(current->task_name, task) == 0) {
            matching_category_or_task = TRUE;
            completed_task_operations(todo, number_of_counts, 
            start_time, finish_time);
            operation_completed = TRUE;
        }
        if (operation_completed == FALSE) {
            current = current->next;
            number_of_counts++;
        }
    }
    
    //now current task is on the last task but this task hasnt been checked
    //checking is below
    if (operation_completed == FALSE && strcmp(current->task_name, task) == 0) {
        matching_category_or_task = TRUE;
        completed_task_operations(todo, number_of_counts, 
        start_time, finish_time);
    }
    return matching_category_or_task;
}


//creates memory for completed task and fills in its variable with values
// as well as linking it appropriately to the link list todo
void completed_task_operations(
    struct todo_list *todo, 
    int number_of_counts,
    int start_time,
    int finish_time
) {
    struct completed_task *new_completed_task = 
    malloc(sizeof(struct completed_task));

    //adds this new completed task to the start of the linked list
    if (todo->completed_tasks == NULL) {
        todo->completed_tasks = new_completed_task;
        new_completed_task->next = NULL;
    } else {
        new_completed_task->next = todo->completed_tasks;
        todo->completed_tasks = new_completed_task;
    }

    //initialises times
    if (start_time == -1) {
        if (new_completed_task->next == NULL) {
            new_completed_task->start_time = 0;
        } else {
            new_completed_task->start_time = 
            new_completed_task->next->finish_time;
        }
    } else {
        new_completed_task->start_time = start_time;
    }
    new_completed_task->finish_time = finish_time;

    //adds associated task to completed task and takes the task out of tasks 
    //linked list
    struct task *current = todo->tasks;
    if (number_of_counts == 1) {
        new_completed_task->task = todo->tasks;
        todo->tasks = new_completed_task->task->next;
    } else {
        for (int i = 1; i < (number_of_counts - 1); i++) {
            current = current->next;
        }
        new_completed_task->task = current->next;
        current->next = current->next->next;
    }
    new_completed_task->task->next = NULL;
}


//changes the prioity of task 'number of counts' down the list 
void changing_priority(struct todo_list *todo, int number_of_counts) {
    //find task with number of counts inputed
    struct task *current = todo->tasks;
    for (int i = 1; i < number_of_counts; i++) {
        current = current->next;
    }
    
    //hardcodes the changes in priority
    if (current->priority == LOW) {
        current->priority = MEDIUM;
    } else if (current->priority == MEDIUM) {
        current->priority = HIGH;
    } else if (current->priority == HIGH) {
        current->priority = LOW;
    }
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////// PROVIDED HELPER FUNCTIONS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * Helper Function
 * You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
 *
 * Given a raw string in the format: [string1] [string2] [enum priority]
 * This function will extract the relevant values into the given variables.
 * The function will also remove any newline characters.
 *
 * For example, if given: "finish_assignment_2 assignment2 high"
 * The function will copy the string:
 *     "finish_assignment_2" into the `task_name` array
 * Then copy the string:
 *     "assignment2" into the `task_category` array
 * And finally, copy over the enum:
 *     "high" into the memory that `prio` is pointing at.
 *
 * Parameters:
 *     buffer        - A null terminated string in the following format
 *                     [string1] [string2] [enum priority]
 *     task_name     - A character array for the [string1] to be copied into
 *     task_category - A character array for the [string2] to be copied into
 *     prio          - A pointer to where [enum priority] should be stored
 *
 * Returns:
 *     None
 */
void parse_add_task_line(
    char buffer[MAX_STRING_LENGTH],
    char task_name[MAX_TASK_LENGTH],
    char task_category[MAX_CATEGORY_LENGTH],
    enum priority *prio
) {
    remove_newline(buffer);

    // Extract value 1 as string
    char *name_str = strtok(buffer, " ");
    if (name_str != NULL) {
        strcpy(task_name, name_str);
    }

    // Extract value 2 as string
    char *category_str = strtok(NULL, " ");
    if (category_str != NULL) {
        strcpy(task_category, category_str);
    }
    
    // Extract value 3 as string
    char *prio_str = strtok(NULL, " ");
    if (prio_str != NULL) {
        *prio = string_to_priority(prio_str);
    }

    if (
        name_str == NULL ||
        category_str == NULL ||
        prio_str == NULL ||
        *prio == INVALID_PRIORITY
    ) {
        // If any of these are null, there were not enough words.
        printf("Could not properly parse line: '%s'.\n", buffer);
    }
}

/*
* Helper Function
* You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
*
* See `parse_add_task_line` for explanation - This function is very similar,
* with only the exclusion of an `enum priority`.
*/
void parse_task_category_line(
    char buffer[MAX_STRING_LENGTH],
    char task_name[MAX_TASK_LENGTH],
    char task_category[MAX_CATEGORY_LENGTH]
) {
    remove_newline(buffer);

    // Extract value 1 as string
    char *name_str = strtok(buffer, " ");
    if (name_str != NULL) {
        strcpy(task_name, name_str);
    }

    // Extract value 2 as string
    char *category_str = strtok(NULL, " ");
    if (category_str != NULL) {
        strcpy(task_category, category_str);
    }

    if (name_str == NULL || category_str == NULL) {
        // If any of these are null, there were not enough words.
        printf("Could not properly parse line: '%s'.\n", buffer);
    }
}

/*
* Helper Function
* You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
*
* See `parse_add_task_line` for explanation - This function is very similar,
* with only the exclusion of an `enum priority` and addition of start/end times
*/
void parse_complete_task_line(
    char buffer[MAX_STRING_LENGTH],
    char task_name[MAX_TASK_LENGTH],
    char task_category[MAX_CATEGORY_LENGTH],
    int *start_time,
    int *finish_time
) {
    remove_newline(buffer);

    // Extract value 1 as string
    char *name_str = strtok(buffer, " ");
    if (name_str != NULL) {
        strcpy(task_name, name_str);
    }

    // Extract value 2 as string
    char *category_str = strtok(NULL, " ");
    if (category_str != NULL) {
        strcpy(task_category, category_str);
    }
    
    // Extract value 2 as string
    char *start_str = strtok(NULL, " ");
    if (start_str != NULL) {
        *start_time = atoi(start_str);
    }
    
    // Extract value 2 as string
    char *finish_str = strtok(NULL, " ");
    if (finish_str != NULL) {
        *finish_time = atoi(finish_str);
    }

    if (
        name_str == NULL ||
        category_str == NULL ||
        start_str == NULL ||
        finish_str == NULL
    ) {
        // If any of these are null, there were not enough words.
        printf("Could not properly parse line: '%s'.\n", buffer);
    }
}

/**
 * Helper Function
 * You should not need to change this function.
 *
 * Given a raw string, will return the corresponding `enum priority`,
 * or INVALID_PRIORITY if the string doesn't correspond with the enums.
 *
 * Parameters:
 *     priority - string representing the corresponding `enum priority` value
 * Returns:
 *     enum priority
 */
enum priority string_to_priority(char priority[MAX_STRING_LENGTH]) {
    if (strcmp(priority, "low") == 0) {
        return LOW;
    } else if (strcmp(priority, "medium") == 0) {
        return MEDIUM;
    } else if (strcmp(priority, "high") == 0) {
        return HIGH;
    }

    return INVALID_PRIORITY;
}

/**
 * Helper Function
 * You should not need to change this function.
 *
 * Given an priority and a character array, fills the array with the
 * corresponding string version of the priority.
 *
 * Parameters:
 *     prio - the `enum priority` to convert from
 *     out  - the array to populate with the string version of `prio`.
 * Returns:
 *     Nothing
 */
void priority_to_string(enum priority prio, char out[MAX_STRING_LENGTH]) {
    if (prio == LOW) {
        strcpy(out, "LOW");
    } else if (prio == MEDIUM) {
        strcpy(out, "MEDIUM");
    } else if (prio == HIGH) {
        strcpy(out, "HIGH");
    } else {
        strcpy(out, "Provided priority was invalid");
    }
}

/*
* Helper Function
* You should not need to change this function.
*
* Given a raw string will remove and first newline it sees.
* The newline character wil be replaced with a null terminator ('\0')
*
* Parameters:
*     input - The string to remove the newline from
*
* Returns:
*     Nothing
*/
void remove_newline(char input[MAX_STRING_LENGTH]) {
    // Find the newline or end of string
    int index = 0;
    while (input[index] != '\n' && input[index] != '\0') {
        index++;
    }
    // Goto the last position in the array and replace with '\0'
    // Note: will have no effect if already at null terminator
    input[index] = '\0';
}

/*
* Helper Function
* You likely do not need to change this function.
*
* Given a raw string, will remove any whitespace that appears at the start or
* end of said string.
*
* Parameters:
*     input - The string to trim whitespace from
*
* Returns:
*     Nothing
*/
void trim_whitespace(char input[MAX_STRING_LENGTH]) {
    remove_newline(input);
    
    int lower;
    for (lower = 0; input[lower] == ' '; ++lower);
    
    int upper;
    for (upper = strlen(input) - 1; input[upper] == ' '; --upper);
    
    for (int base = lower; base <= upper; ++base) {
        input[base - lower] = input[base];
    }

    input[upper - lower + 1] = '\0';
}

/**
 * Helper Function
 * You SHOULD NOT change this function.
 *
 * Given a task, prints it out in the format specified in the assignment.
 *
 * Parameters:
 *     task_num - The position of the task within a todo list
 *     task     - The task in question to print
 *
 * Returns:
 *     Nothing
 */
void print_one_task(int task_num, struct task *task) {
    char prio_str[MAX_STRING_LENGTH];
    priority_to_string(task->priority, prio_str);

    printf(
        "  %02d. %-30.30s [ %s ] %s\n",
        task_num, task->task_name, task->category, prio_str
    );

    int i = 30;
    while (i < strlen(task->task_name)) {
        printf("      %.30s\n", task->task_name + i);
        i += 30;
    }
}

/**
 * Helper Function
 * You SHOULD NOT change this function.
 *
 * Given a completed task, prints it out in the format specified in the
 * assignment.
 *
 * Parameters:
 *     completed_task - The task in question to print
 *
 * Returns:
 *     Nothing
 */
void print_completed_task(struct completed_task *completed_task) {
    int start_hour = completed_task->start_time / 60;
    int start_minute = completed_task->start_time % 60;
    int finish_hour = completed_task->finish_time / 60;
    int finish_minute = completed_task->finish_time % 60;
    
    printf(
        "  %02d:%02d-%02d:%02d | %-30.30s [ %s ]\n",
        start_hour, start_minute, finish_hour, finish_minute,
        completed_task->task->task_name, completed_task->task->category
    );

    int i = 30;
    while (i < strlen(completed_task->task->task_name)) {
        printf("      %.30s\n", (completed_task->task->task_name + i));
        i += 30;
    }
}

/**
 * Compares two tasks by precedence of category -> priority -> name and returns
 * an integer referring to their relative ordering
 * 
 * Parameters:
 *     t1 - The first task to compare
 *     t2 - The second task to compare
 *
 * Returns:
 *     a negative integer if t1 belongs before t2
 *     a positive integer if t1 belongs after t2
 *     0 if the tasks are identical (This should never happen in your program)
 */
int task_compare(struct task *t1, struct task *t2) {
    int category_diff = strcmp(t1->category, t2->category);
    if (category_diff != 0) {
        return category_diff;
    }
    
    int priority_diff = t2->priority - t1->priority;
    if (priority_diff != 0) {
        return priority_diff;
    }
    
    return strcmp(t1->task_name, t2->task_name);
}