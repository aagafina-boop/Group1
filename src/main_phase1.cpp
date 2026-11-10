
#include "module1_staff.h"
#include "module2_triage.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

    cout << "--------------------------------------------\n";
    cout << "KCH PATIENT MANAGEMENT AND TRIAGE SYSTEM\n";
    cout << "PHASE 1 DEMONSTRATION\n";
    cout << "---------------------------------------------\n";


    // ==================================================
    // Q1.1 - DOCTOR ARRAY MANAGEMENT
    // ==================================================

    cout << "\n========== Q1.1 DOCTOR ARRAY MANAGEMENT ==========\n";

    Doctor doctorRoster[MAX_DOCTORS];
    int doctorCount = 0;

    cout << "\nInitial doctor roster:\n";
    print_roster(doctorRoster, doctorCount);

    cout << "\nStep 1: Insert Dr. Alex (101)\n";
    add_doctor(doctorRoster, doctorCount, 101, "Alex", "Emergency");
    print_roster(doctorRoster, doctorCount);

    cout << "\nStep 2: Insert Dr. Beatrice (102)\n";
    add_doctor(doctorRoster, doctorCount, 102, "Beatrice", "Pediatrics");
    print_roster(doctorRoster, doctorCount);

    cout << "\nStep 3: Insert Dr. Charles (103)\n";
    add_doctor(doctorRoster, doctorCount, 103, "Charles", "Surgery");
    print_roster(doctorRoster, doctorCount);

    cout << "\nDoctor count: " << doctorCount << "\n";


    // ==================================================
    // Q1.2 - NURSE LINKED LIST MANAGEMENT
    // ==================================================

    cout << "\n========== Q1.2 NURSE LINKED LIST MANAGEMENT ==========\n";

    Doctor& alex = doctorRoster[0];
    Doctor& beatrice = doctorRoster[1];

    cout << "\nStep 1: Insert N1 (501) for Dr. Alex\n";
    add_nurse(alex, 501, "N1", "Day");
    print_nurses(alex);

    cout << "\nStep 2: Insert N2 (502) for Dr. Alex\n";
    add_nurse(alex, 502, "N2", "Night");
    print_nurses(alex);

    cout << "\nStep 3: Insert N3 (503) for Dr. Beatrice\n";
    add_nurse(beatrice, 503, "N3", "Day");
    print_nurses(beatrice);

    cout << "\nDr. Alex's nurse list:\n";
    print_nurses(alex);

    cout << "\nDr. Beatrice's nurse list:\n";
    print_nurses(beatrice);

    cout << "\nStep 4: Delete N1 (501) from Dr. Alex's list\n";
    delete_nurse(alex, 501);
    print_nurses(alex);


    // ==================================================
    // Q1.1 - DOCTOR DELETION
    // ==================================================

    cout << "\n========== DOCTOR DELETION ==========\n";

    cout << "\nDoctor roster before deletion:\n";
    print_roster(doctorRoster, doctorCount);

    cout << "\nDelete Dr. Beatrice (102)\n";

    delete_doctor(doctorRoster, doctorCount, 102);

    cout << "\nDoctor roster after deletion and shifting:\n";
    print_roster(doctorRoster, doctorCount);

    cout << "\nUpdated doctor count: " << doctorCount << "\n";


    // ==================================================
    // Q2.1 AND Q2.2 - MAX-HEAP PRIORITY QUEUE
    // ==================================================

    cout << "\n========== Q2.1 AND Q2.2 MAX-HEAP ==========\n";

    PriorityQueue pq{};

    int scores[7] = {14, 22, 45, 10, 8, 30, 95};

    cout << "\nSequential patient insertion:\n";

    for (int i = 0; i < 7; i++) {

        cout << "\nInsert Patient P" << i + 1
             << " with acuity score " << scores[i] << "\n";

        pq_insert(&pq, Patient{i + 1, scores[i]});

        cout << "Heap array after insertion:\n";
        print_heap(&pq);

        cout << "Current patient count: "
             << pq.patientCount << "\n";
    }


    // ==================================================
    // Q2.2 - EXTRACT MAX
    // ==================================================

    cout << "\n========== EXTRACT MAX ==========\n";

    cout << "\nHeap before extraction:\n";
    print_heap(&pq);

    Patient extractedPatient = extract_max(&pq);

    cout << "\nExtracted patient:\n";
    cout << "Patient ID: P" << extractedPatient.patientID << "\n";
    cout << "Acuity score: "
         << extractedPatient.acuityScore << "\n";

    cout << "\nHeap after extraction and bubble_down:\n";
    print_heap(&pq);

    cout << "\nRemaining patient count: "
         << pq.patientCount << "\n";


    // ==================================================
    // Q2.2 - COMPLEXITY ANALYSIS
    // ==================================================

    cout << "\n========== COMPLEXITY ANALYSIS ==========\n";

    cout << "\nUnsorted array:\n";
    cout << "Finding the maximum: O(n)\n";
    cout << "Removing an element while maintaining array order: O(n)\n";
    cout << "Repeated maximum extraction: O(n^2)\n";

    cout << "\nMax-Heap:\n";
    cout << "Accessing maximum: O(1)\n";
    cout << "Insertion: O(log n)\n";
    cout << "Extracting maximum: O(log n)\n";
    cout << "Repeated extraction: O(n log n)\n";

    cout << "\nHeapsort auxiliary space: O(1)\n";


    // ==================================================
    // MEMORY CLEANUP
    // ==================================================

    cout << "\n========== MEMORY CLEANUP ==========\n";

    while (doctorCount > 0) {
        delete_doctor(
            doctorRoster,
            doctorCount,
            doctorRoster[0].doctorID
        );
    }

    cout << "Remaining doctors and their nurse lists cleaned up.\n";

    cout << "\nPhase 1 demonstration completed.\n";

    return 0;
}
