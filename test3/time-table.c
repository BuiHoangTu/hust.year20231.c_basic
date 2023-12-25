//
// Created by tu on 25/12/2023.
/**
 * Description
The time-table of a school is a structure in which each class is assigned to a teacher, and is scheduled into a slot and a room. There are N classes 1, 2, ..., N; T teachers 1, 2, ..., T: S slots 1, 2, ..., S; and R rooms 1, 2, ..., R. In the time-table, each class i is assigned to the teacher t[i], the slot s[i], and the room r[i].
If a teacher teaches a class i in the slot s, then he/she is said to be busy at that slot. The school want to find a slot to organize a meeting with teachers.
Objective: Find the slot in which the number of teachers who are not busy at that slot is maximal.

Input
Line 1: contains 4 positive integers N, T, S, R
Line i+1 (i = 1,...,N): contains i, t[i], s[i], r[i]

Output
Write the number of teachers who are not busy at the slot found
 */

#include <stdio.h>
#include <malloc.h>

// Structure to represent time-table entry
struct TimetableEntry {
    int class;
    int teacher;
    int slot;
    int room;
};

int main() {
    int N, T, S, R;

    // Input: Number of classes, teachers, slots, and rooms
//    printf("Enter the number of classes, teachers, slots, and rooms: ");
    scanf("%d %d %d %d", &N, &T, &S, &R);

    struct TimetableEntry *timetable = (struct TimetableEntry*) malloc(N * sizeof(struct TimetableEntry));

    // Input: Time-table entries
//    printf("Enter the time-table entries (class teacher slot room):\n");
    for (int i = 0; i < N; ++i) {
        scanf("%d %d %d %d", &timetable[i].class, &timetable[i].teacher, &timetable[i].slot, &timetable[i].room);
    }

    // Initialize an array to track teacher availability
    int **teacherAvailability = (int**)malloc((T + 1) * sizeof(int*));
    for (int i = 1; i <= T; ++i) {
        teacherAvailability[i] = (int*)calloc((S + 1), sizeof(int));
    }

    // Mark slots where teachers are busy
    for (int i = 0; i < N; ++i) {
        teacherAvailability[timetable[i].teacher][timetable[i].slot] = 1;
    }

    // Count the number of available teachers at each slot
    int maxAvailableTeachers = 0;
    int bestSlot = -1;
    for (int j = 1; j <= S; ++j) {
        int availableTeachers = 0;
        for (int i = 1; i <= T; ++i) {
            if (teacherAvailability[i][j] == 0) {
                ++availableTeachers;
            }
        }
        if (availableTeachers > maxAvailableTeachers) {
            maxAvailableTeachers = availableTeachers;
            bestSlot = j;
        }
    }

    // Output: Best slot for the meeting
    printf("%d", maxAvailableTeachers);

    return 0;
}
