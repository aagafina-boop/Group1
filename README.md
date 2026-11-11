# KCH-PMTS — Patient Management and Triage System (Phase 1)

A C++ console program for a hospital. It manages staff and decides which emergency patient is treated next. It is built from basic data structures written by hand, with no STL containers.

Phase 1 has two modules.

## Module 1: Staff management

**Doctors are stored in a fixed-size array** (`MAX_DOCTORS = 50`).

- `add_doctor` puts the new doctor in the next free slot. Cost: O(1).
- `delete_doctor` removes a doctor and moves every doctor after them one slot left, so the array has no gaps. Cost: O(n).
- Duplicate IDs are rejected, and so is adding a doctor to a full roster.

**Each doctor has their own nurse list.** It is a singly linked list that starts at `nurseHead`.

- `add_nurse` adds a nurse at the end of the list. Duplicate nurse IDs are rejected.
- `delete_nurse` removes a nurse from the head, the middle or the tail of the list.
- When a doctor is deleted, all of that doctor's nurse nodes are freed, so no memory leaks.

## Module 2: Emergency room triage

Patients wait in a **max-heap priority queue**, stored in an array that starts at index 0. Each patient has an acuity score from 1 to 100. A higher score means the patient is more urgent, so the most urgent patient is always at the root.

- `pq_insert` adds a patient at the end, then moves it up the heap (`bubble_up`). Cost: O(log n).
- `extract_max` removes the root and moves the last patient to the top, then moves that patient down the heap (`bubble_down`). Cost: O(log n).
- Index helpers: `parent(i) = (i-1)/2`, `left_child(i) = 2i+1`, `right_child(i) = 2i+2`.

## Project layout

```
include/   module1_staff.h, module2_triage.h   structs and function declarations
src/       module1_staff.cpp                   doctor array and nurse linked list
           module2_triage.cpp                  max-heap priority queue
           main_phase1.cpp                     demo that prints the Phase 1 traces
tests/     test_phase1.cpp                     PASS/FAIL tests for both modules
Makefile
```

## Build and run

You need `g++` with C++17 support and `make`.

```bash
make                 # builds ./kch_phase1
./kch_phase1         # prints the doctor, nurse and heap traces

make test            # builds and runs ./test_phase1
make clean           # removes the build files
```

To check for memory leaks:

```bash
valgrind --leak-check=full ./kch_phase1
valgrind --leak-check=full ./test_phase1
```

## What the demo shows

1. **Doctor array:** adds Dr. Alex (101), Dr. Beatrice (102) and Dr. Charles (103), printing the roster after each add.
2. **Nurse list:** adds nurses 501 and 502 to Dr. Alex and 503 to Dr. Beatrice, then deletes 501.
3. **Heap insertion:** inserts patients with scores `14, 22, 45, 10, 8, 30, 95` and prints the heap after each insert.
4. **Heap extraction:** removes the most urgent patient (P7, score 95) and shows how the heap is repaired.

The final heap array is `[95, 14, 45, 10, 8, 22, 30]`. The tests check this value.

## Tests

Running `make test` prints `PASS` or `FAIL` for each check, followed by a summary. The tests cover:

- adding doctors, duplicate IDs, deleting a doctor with the shift left, unknown IDs and a full roster
- the empty nurse list, duplicate nurses, and deleting a nurse from the middle, the head and the end
- the empty heap, the final heap array after the inserts, `extract_max`, and the heap rule

Some `Error:` lines are expected in the test output. They come from the tests that deliberately pass bad input.
