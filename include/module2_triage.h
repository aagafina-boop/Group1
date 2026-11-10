/*
 * File:    module2_triage.h
 * Module:  2 - Emergency Room Triage Engine (KCH-PMTS)
 *
 * Array-backed Max-Heap priority queue, indexed from 0.
 * Max-heap property: every parent's acuityScore >= its children's,
 * so the most urgent patient is always at index 0 (the root).
 *
 * Index mapping for a node at index i:
 *   parent(i)      = (i - 1) / 2
 *   left_child(i)  = 2i + 1
 *   right_child(i) = 2i + 2
 */

#ifndef MODULE2_TRIAGE_H
#define MODULE2_TRIAGE_H

constexpr int MAX_PATIENTS = 100;

struct Patient {
    int patientID;
    int acuityScore;   // 1 (low urgency) .. 100 (critical)
};

struct PriorityQueue {
    Patient patientHeap[MAX_PATIENTS];
    int patientCount = 0;
};

// helpers are defined in the header, so they must be "inline"
// (otherwise every .cpp that includes this file defines them again -> link error)
inline int parent(int i)      { return (i - 1) / 2; }
inline int left_child(int i)  { return 2 * i + 1; }
inline int right_child(int i) { return 2 * i + 2; }

void swap_patients(PriorityQueue* pq, int i, int j);
void bubble_up(PriorityQueue* pq, int index);
void bubble_down(PriorityQueue* pq, int index);
void pq_insert(PriorityQueue* pq, Patient patientRecord);
Patient extract_max(PriorityQueue* pq);
void print_heap(const PriorityQueue* pq);

#endif