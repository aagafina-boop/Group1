/*
 * File:    module2_triage.cpp
 * Module:  2 - Emergency Room Triage Engine (KCH-PMTS)
 *
 * Array-backed Max-Heap priority queue (indexed from 0).
 * Max-heap property: every parent's acuityScore >= its children's,
 * so the most urgent patient is always at index 0 (the root).
 *
 *   pq_insert   -> place the patient at index patientCount (next free slot),
 *                  then bubble_up (sift-up) until its parent is >= it.   O(log n)
 *   extract_max -> save the root, move the last leaf to the root, shrink,
 *                  then bubble_down (sift-down) to repair the order.     O(log n)
 *
 * bubble_up / bubble_down are recursive: each call fixes one level of the tree.
 * No standard-library utilities are used: swapping is done by swap_patients.
 */

#include "module2_triage.h"
#include <iostream>

using namespace std;

// function to swap two patients in the heap array
void swap_patients(PriorityQueue* pq, int i, int j){
    Patient temp = pq->patientHeap[i];          // 1. save i
    pq->patientHeap[i] = pq->patientHeap[j];    // 2. overwrite i with j
    pq->patientHeap[j] = temp;                  // 3. put the saved i into j
}

// function to move the patient at index UP until max-heap order is restored
void bubble_up(PriorityQueue* pq, int index){
    // base case: root reached
    if(index == 0) return;

    int p = parent(index);

    // child more urgent than parent -> swap and continue from the parent's position
    if(pq->patientHeap[index].acuityScore > pq->patientHeap[p].acuityScore){
        swap_patients(pq, index, p);
        bubble_up(pq, p);
    }
}

// function to move the patient at index DOWN until max-heap order is restored
void bubble_down(PriorityQueue* pq, int index){

    int left = left_child(index);
    int right = right_child(index);

    int largest = index;

    // checking if the left child exists and if it is greater than the current largest
    if(left < pq->patientCount && pq->patientHeap[left].acuityScore > pq->patientHeap[largest].acuityScore){
        largest = left;
    }

    // checking if the right child exists and if it is greater than the current largest
    if(right < pq->patientCount && pq->patientHeap[right].acuityScore > pq->patientHeap[largest].acuityScore){
        largest = right;
    }

    // a child is bigger -> swap with the bigger child and continue from there
    if(largest != index){
        swap_patients(pq, index, largest);
        bubble_down(pq, largest);
    }
}

// function to insert a new patient into the triage queue
void pq_insert(PriorityQueue* pq, Patient patientRecord){
    if(pq == nullptr){
        return;
    }

    // checking if the array is already full (slots 0 .. MAX_PATIENTS-1)
    if(pq->patientCount >= MAX_PATIENTS){
        cerr << "Error: triage queue full (" << MAX_PATIENTS << " patients). Cannot admit patient "
             << patientRecord.patientID << "\n";
        return;
    }

    // inserting the patient in the next available position
    pq->patientHeap[pq->patientCount] = patientRecord;

    pq->patientCount++;

    // the new patient is at patientCount - 1 -> move it up to its correct place
    bubble_up(pq, pq->patientCount - 1);
}

// function to remove and return the most urgent patient (the root)
Patient extract_max(PriorityQueue* pq){
    if(pq == nullptr || pq->patientCount == 0){
        cerr << "Error: triage queue is empty\n";
        return Patient{-1, -1};   // sentinel: no patient
    }

    // save the root before it gets overwritten
    Patient maxPatient = pq->patientHeap[0];

    // move the last leaf to the root and shrink the heap
    pq->patientHeap[0] = pq->patientHeap[pq->patientCount - 1];

    pq->patientCount--;

    // repair the order from the root (nothing to repair if the heap is now empty)
    if(pq->patientCount > 0){
        bubble_down(pq, 0);
    }

    return maxPatient;
}

// function to print the heap array as (patientID:acuity) pairs
void print_heap(const PriorityQueue* pq){
    if(pq == nullptr){
        return;
    }

    cout << "Heap [" << pq->patientCount << "]: ";
    for(int i = 0; i < pq->patientCount; i++){
        cout << "[" << i << "] P" << pq->patientHeap[i].patientID
             << ":" << pq->patientHeap[i].acuityScore << "  ";
    }
    cout << "\n";
}