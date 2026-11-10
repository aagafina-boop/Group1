
/*
 * File:    test_phase1.cpp
 * Purpose: Test KCH-PMTS Phase 1:
 *          Q1.1 - Doctor Array Management
 *          Q1.2 - Nurse Linked List Management
 *          Q2.1/Q2.2 - Max-Heap Priority Queue
 *
 * Each test prints PASS or FAIL.
 * A summary is displayed at the end.
 *
 * Run:          make test
 * Memory check: valgrind --leak-check=full ./test_phase1
 */

#include "module1_staff.h"
#include "module2_triage.h"
#include <iostream>
#include <string>

using namespace std;


// ----------------------------------------
// TEST SUMMARY COUNTERS
// ----------------------------------------
int passed = 0;
int failed = 0;


// Print the result of one test and update the counters.
void check(bool condition, const string& message) {

    if (condition) {
        cout << "PASS: " << message << "\n";
        passed++;
    }
    else {
        cout << "FAIL: " << message << "\n";
        failed++;
    }
}


// ----------------------------------------
// Q1.1 - DOCTOR ARRAY MANAGEMENT
// ----------------------------------------
void test_doctor_array() {

    cout << "\n============================================\n";
    cout << "Q1.1 - DOCTOR ARRAY MANAGEMENT\n";
    cout << "============================================\n";

    Doctor roster[MAX_DOCTORS];
    int doctorCount = 0;


    // -----------------------------------------------------------
    // STEP 1: Insert doctors into the roster
    // -----------------------------------------------------------

    cout << "\nStep 1: Adding doctors to the roster\n";

    Doctor doctors[] = {
        {101, "Alex", "Emergency"},
        {102, "Beatrice", "Pediatrics"},
        {103, "Charles", "Surgery"}
    };

    const int N = sizeof(doctors) / sizeof(doctors[0]);

    for (int i = 0; i < N; i++) {

        add_doctor(
            roster,
            doctorCount,
            doctors[i].doctorID,
            doctors[i].name,
            doctors[i].specialization
        );
    }

    // Check that all doctors were inserted in the correct order.
    bool doctorsInOrder = (doctorCount == N);

    for (int i = 0; i < N && doctorsInOrder; i++) {

        if (roster[i].doctorID != doctors[i].doctorID) {
            doctorsInOrder = false;
        }
    }

    check(doctorsInOrder, "all doctors added in the correct order");

    check(doctorCount == N, "doctor count is updated correctly");


    // -----------------------------------------------------------
    // STEP 2: Try inserting a doctor with an existing ID
    // -----------------------------------------------------------

    cout << "\nStep 2: Testing duplicate doctor insertion\n";

    bool duplicateResult = add_doctor(
        roster,
        doctorCount,
        doctors[0].doctorID,
        "Duplicate",
        "None"
    );

    check(!duplicateResult, "duplicate doctor ID is rejected");

    check(doctorCount == N, "doctor count remains unchanged after duplicate insertion");


    // -----------------------------------------------------------
    // STEP 3: Delete a doctor from the middle of the array
    // -----------------------------------------------------------

    cout << "\nStep 3: Deleting Dr. " << doctors[1].name
         << " (ID " << doctors[1].doctorID << ")\n";

    delete_doctor(roster, doctorCount, doctors[1].doctorID);

    // After deleting the doctor at index 1, every doctor after it
    // moves one place to the left.

    bool doctorsShifted = (doctorCount == N - 1 &&
                           roster[0].doctorID == doctors[0].doctorID);

    for (int i = 1; i < doctorCount; i++) {

        if (roster[i].doctorID != doctors[i + 1].doctorID) {
            doctorsShifted = false;
        }
    }

    check(doctorsShifted, "deleting a doctor shifts following doctors left");

    check(doctorCount == N - 1, "doctor count decreases after deletion");


    // -----------------------------------------------------------
    // STEP 4: Try deleting a doctor that does not exist
    // -----------------------------------------------------------

    cout << "\nStep 4: Testing deletion of an unknown doctor\n";

    bool unknownDoctorResult = delete_doctor(
        roster,
        doctorCount,
        -1
    );

    check(!unknownDoctorResult, "unknown doctor ID cannot be deleted");

    check(doctorCount == N - 1, "doctor count remains unchanged after unsuccessful deletion");


    // -----------------------------------------------------------
    // STEP 5: Fill the roster to its maximum capacity
    // -----------------------------------------------------------

    cout << "\nStep 5: Testing maximum roster capacity\n";

    while (doctorCount < MAX_DOCTORS) {

        add_doctor(
            roster,
            doctorCount,
            100000 + doctorCount,
            "Doc",
            "General"
        );
    }

    check(
        doctorCount == MAX_DOCTORS,
        "roster can be filled to maximum capacity"
    );

    // One additional doctor should not be accepted.
    bool extraDoctorResult = add_doctor(
        roster,
        doctorCount,
        200000,
        "Extra",
        "General"
    );

    check(!extraDoctorResult, "full roster rejects another doctor");

    check(
        doctorCount == MAX_DOCTORS,
        "doctor count does not exceed maximum capacity"
    );


    // -----------------------------------------------------------
    // STEP 6: Clean up the doctor roster
    // -----------------------------------------------------------

    cout << "\nStep 6: Cleaning up doctor records\n";

    while (doctorCount > 0) {

        delete_doctor(
            roster,
            doctorCount,
            roster[0].doctorID
        );
    }

    check(doctorCount == 0, "all doctors successfully removed");
}


//----------------------------------------
// Q1.2 - NURSE SINGLY LINKED LIST MANAGEMENT
//----------------------------------------

void test_nurse_list() {

    cout << "\n----------------------------------------\n";
    cout << "Q1.2 - NURSE LINKED LIST MANAGEMENT\n";
    cout << "----------------------------------------\n";

    // Create one doctor with an initially empty nurse list.
    Doctor doc{101, "Alex", "Emergency"};


    // -----------------------------------------------------------
    // STEP 1: Try deleting a nurse from an empty list
    // -----------------------------------------------------------

    cout << "\nStep 1: Testing deletion from an empty list\n";

    bool emptyDeleteResult = delete_nurse(doc, 501);

    check(!emptyDeleteResult, "deleting from an empty nurse list fails");

    check(
        doc.nurseHead == nullptr && doc.nurseCount == 0,
        "nurse list remains empty"
    );


    // -----------------------------------------------------------
    // STEP 2: Insert three nurses
    // -----------------------------------------------------------

    cout << "\nStep 2: Adding nurses to Dr. Alex's list\n";

    add_nurse(doc, 501, "N1", "Day");
    add_nurse(doc, 502, "N2", "Night");
    add_nurse(doc, 503, "N3", "Day");

    // Expected linked list:
    // Head -> 501 -> 502 -> 503 -> nullptr

    bool nursesAdded = (
        doc.nurseCount == 3 &&
        doc.nurseHead != nullptr &&
        doc.nurseHead->nurseID == 501
    );

    check(nursesAdded, "three nurses are added to the list");

    check(doc.nurseCount == 3, "nurse count is updated correctly");


    // -----------------------------------------------------------
    // STEP 3: Try inserting a duplicate nurse ID
    // -----------------------------------------------------------

    cout << "\nStep 3: Testing duplicate nurse insertion\n";

    bool duplicateNurseResult = add_nurse(
        doc,
        502,
        "Duplicate",
        "Day"
    );

    check(!duplicateNurseResult, "duplicate nurse ID is rejected");

    check(doc.nurseCount == 3, "nurse count remains unchanged after duplicate insertion");


    // -----------------------------------------------------------
    // STEP 4: Delete the middle nurse
    // -----------------------------------------------------------

    cout << "\nStep 4: Deleting the middle nurse (ID 502)\n";

    delete_nurse(doc, 502);

    // Expected linked list:
    // Head -> 501 -> 503 -> nullptr

    bool middleRemoved = (
        doc.nurseHead != nullptr &&
        doc.nurseHead->next != nullptr &&
        doc.nurseHead->nurseID == 501 &&
        doc.nurseHead->next->nurseID == 503 &&
        doc.nurseCount == 2
    );

    check(middleRemoved, "middle nurse is removed and links are updated");


    // -----------------------------------------------------------
    // STEP 5: Delete the first nurse (head node)
    // -----------------------------------------------------------

    cout << "\nStep 5: Deleting the first nurse (ID 501)\n";

    delete_nurse(doc, 501);

    // Expected linked list:
    // Head -> 503 -> nullptr

    bool headRemoved = (
        doc.nurseHead != nullptr &&
        doc.nurseHead->nurseID == 503 &&
        doc.nurseCount == 1
    );

    check(headRemoved, "deleting the head updates nurseHead correctly");


    // -----------------------------------------------------------
    // STEP 6: Delete the last remaining nurse
    // -----------------------------------------------------------

    cout << "\nStep 6: Deleting the last nurse (ID 503)\n";

    delete_nurse(doc, 503);

    check(
        doc.nurseHead == nullptr && doc.nurseCount == 0,
        "deleting the last nurse makes the list empty"
    );
}


// ----------------------------------------
// Q2.1 / Q2.2 - MAX-HEAP PRIORITY QUEUE
//----------------------------------------
// Check the Max-Heap property:
//
// Every parent's acuity score must be greater than
// or equal to the acuity score of its children.

bool is_max_heap(const PriorityQueue& pq) {

    for (int i = 1; i < pq.patientCount; i++) {

        int parentIndex = (i - 1) / 2;

        if (
            pq.patientHeap[parentIndex].acuityScore <
            pq.patientHeap[i].acuityScore
        ) {
            return false;
        }
    }

    return true;
}


void test_heap() {

    cout << "\n----------------------------------------\n";
    cout << "Q2.1 / Q2.2 - MAX-HEAP PRIORITY QUEUE\n";
    cout << "----------------------------------------\n";

    // Start with an empty priority queue.
    PriorityQueue pq{};


    // -----------------------------------------------------------
    // STEP 1: Try extracting from an empty priority queue
    // -----------------------------------------------------------

    cout << "\nStep 1: Testing extraction from an empty heap\n";

    Patient emptyResult = extract_max(&pq);

    check(
        emptyResult.patientID == -1,
        "extracting from an empty heap returns patient ID -1"
    );

    check(
        pq.patientCount == 0,
        "empty heap remains empty after extraction"
    );


    // -----------------------------------------------------------
    // STEP 2: Insert the seven patients from the assignment
    // -----------------------------------------------------------

    cout << "\nStep 2: Inserting patients into the Max-Heap\n";

    int scores[7] = {
        14, 22, 45, 10, 8, 30, 95
    };

    // Expected heap array after all seven insertions.
    int expected[7] = {
        95, 14, 45, 10, 8, 22, 30
    };

    for (int i = 0; i < 7; i++) {

        cout << "Inserting Patient P" << i + 1
             << " with acuity score " << scores[i] << "\n";

        pq_insert(
            &pq,
            Patient{i + 1, scores[i]}
        );
    }

    // Check that all seven patients were inserted.
    check(
        pq.patientCount == 7,
        "all seven patients are inserted"
    );


    // -----------------------------------------------------------
    // STEP 3: Compare the resulting heap with the expected array
    // -----------------------------------------------------------

    cout << "\nStep 3: Checking the final heap array\n";

    bool heapMatches = true;

    for (int i = 0; i < 7; i++) {

        if (pq.patientHeap[i].acuityScore != expected[i]) {
            heapMatches = false;
        }
    }

    check(
        heapMatches,
        "heap array matches [95, 14, 45, 10, 8, 22, 30]"
    );


    // -----------------------------------------------------------
    // STEP 4: Check the Max-Heap property
    // -----------------------------------------------------------

    cout << "\nStep 4: Checking the Max-Heap property\n";

    check(
        is_max_heap(pq),
        "every parent has a score greater than or equal to its children"
    );


    // -----------------------------------------------------------
    // STEP 5: Extract the patient with the highest acuity score
    // -----------------------------------------------------------

    cout << "\nStep 5: Extracting the highest-priority patient\n";

    Patient top = extract_max(&pq);

    check(
        top.patientID == 7 && top.acuityScore == 95,
        "extract_max returns Patient P7 with acuity score 95"
    );


    // -----------------------------------------------------------
    // STEP 6: Check the heap after extraction
    // -----------------------------------------------------------

    cout << "\nStep 6: Checking the heap after extraction\n";

    check(
        pq.patientCount == 6,
        "patient count decreases to six after extraction"
    );

    check(
        pq.patientHeap[0].acuityScore == 45,
        "patient with acuity score 45 becomes the new root"
    );

    check(
        is_max_heap(pq),
        "Max-Heap property still holds after extraction"
    );
}


// MAIN - RUN ALL PHASE 1 TESTS


int main() {

    cout << "\n";
    cout << "-----------------------------------------\n";
    cout << "KCH PATIENT MANAGEMENT AND TRIAGE SYSTEM\n";
    cout << "PHASE 1 TEST SUITE\n";
    cout << "----------------------------------------\n";


    // Run the test groups in assignment order.

    test_doctor_array();

    test_nurse_list();

    test_heap();



    // FINAL TEST SUMMARY

    cout << "\n--------------------------------------------\n";
    cout << "FINAL TEST SUMMARY\n";

    cout << "Tests passed: " << passed << "\n";
    cout << "Tests failed: " << failed << "\n";
    cout << "Total tests:  " << passed + failed << "\n";

    if (failed == 0) {

        cout << "\nAll tests passed successfully!\n";
    }
    else {

        cout << "\nSome tests failed. Please review the results above.\n";
    }

    cout << "============================================\n";

    // Return 0 when all tests pass.
    // Return 1 when at least one test fails.
    return failed == 0 ? 0 : 1;
}
