/*
 * File:    module1_staff.cpp
 * Module:  1 - Staff Management & Dynamic Rostering (KCH-PMTS)
 *
 * Doctors are stored in a fixed-size contiguous array (doctorRoster, max
 * MAX_DOCTORS). doctorCount tracks how many slots are in use.
 *
 * Invariant: slots 0 .. doctorCount-1 are always filled with no gaps.
 *   - add_doctor    -> places the new doctor at index doctorCount   O(1)
 *   - delete_doctor -> frees the doctor's nurse list, then shifts all
 *                      later doctors one slot left to close the gap  O(n)
 *
 * Each doctor owns a singly linked list of nurses (nurseHead). The nurse
 * nodes are heap-allocated, so they must be freed when a doctor is deleted.
 */

#include "module1_staff.h"
#include <iostream>

using namespace std;

// function to add a new doctor to the doctor roster
// returns false if the roster is already full or the ID is already in use
bool add_doctor(Doctor roster[], int& doctorCount, int id, const string& name, const string& specialization){
    if(doctorCount >= MAX_DOCTORS){
        cerr << "Error: roster full (" << MAX_DOCTORS << " doctors). Cannot add Dr. " << name << "\n";
        return false;
    }

    // doctor IDs must be unique, otherwise delete_doctor could remove the wrong one
    for(int i = 0; i < doctorCount; i++){
        if(roster[i].doctorID == id){
            cerr << "Error: doctor ID " << id << " already exists. Cannot add Dr. " << name << "\n";
            return false;
        }
    }

    // the next free slot is always at index doctorCount
    Doctor& slot = roster[doctorCount];
    slot.doctorID = id;
    slot.name = name;
    slot.specialization = specialization;
    slot.nurseHead = nullptr;
    slot.nurseCount = 0;
    doctorCount++;
    return true;
}

// function to delete a doctor by ID
// frees their nurses, shifts remaining doctors left and decrements doctorCount
bool delete_doctor(Doctor roster[], int& doctorCount, int doctorID){
    int index = -1;   // -1 means "not found yet"

    // linear search for the doctor
    for(int i = 0; i < doctorCount; i++){
        if(roster[i].doctorID == doctorID){
            index = i;
            break;
        }
    }

    if(index == -1){
        cerr << "Error: doctor " << doctorID << " not found\n";
        return false;
    }

    // free every nurse node in this doctor's linked list
    Nurse* current = roster[index].nurseHead;
    while(current != nullptr){
        Nurse* nextNurse = current->next;   // save next before deleting current
        delete current;
        current = nextNurse;
    }

    // shift every doctor after index one slot to the left
    for(int i = index; i < doctorCount - 1; i++){
        roster[i] = roster[i + 1];
    }

    doctorCount--;
    roster[doctorCount] = Doctor{};   // clear the old last slot (no stale nurseHead copy)
    return true;
}

// function to print every doctor currently in the roster
void print_roster(const Doctor roster[], int doctorCount){
    cout << "Roster (" << doctorCount << " doctors):\n";
    for(int i = 0; i < doctorCount; i++){
        cout << " [" << i << "] Dr. " << roster[i].name << " (ID " << roster[i].doctorID
             << ", " << roster[i].specialization << ", nurses: " << roster[i].nurseCount << ")\n";
    }
}

// ---------------- Q1.2 - nurse linked list ----------------

// function to add a new nurse at the END (tail) of a doctor's nurse list
// returns false if this doctor already has a nurse with the same ID
bool add_nurse(Doctor& doc, int nurseID, const string& name, const string& shift){
    // reject duplicate IDs so delete_nurse always removes the intended nurse
    for(Nurse* check = doc.nurseHead; check != nullptr; check = check->next){
        if(check->nurseID == nurseID){
            cerr << "Error: nurse " << nurseID << " already assigned to Dr. " << doc.name << "\n";
            return false;
        }
    }

    // create the new node on the heap; it will be the last node so next = nullptr
    Nurse* newNurse = new Nurse;
    newNurse->nurseID = nurseID;
    newNurse->name = name;
    newNurse->shift = shift;
    newNurse->next = nullptr;

    // case 1: empty list -> the new node becomes the head
    if(doc.nurseHead == nullptr){
        doc.nurseHead = newNurse;
    }
    // case 2: walk to the last node, then link the new node after it
    else{
        Nurse* current = doc.nurseHead;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = newNurse;
    }

    doc.nurseCount++;
    return true;
}

// function to delete a nurse by ID from a doctor's nurse list
// handles: empty list, nurse at head, nurse in middle/tail, nurse not found
bool delete_nurse(Doctor& doc, int nurseID){
    // edge case 1: empty list
    if(doc.nurseHead == nullptr){
        cerr << "Error: Dr. " << doc.name << " has no nurses\n";
        return false;
    }

    // edge case 2: nurse is the head -> move head forward
    if(doc.nurseHead->nurseID == nurseID){
        Nurse* toDelete = doc.nurseHead;
        doc.nurseHead = doc.nurseHead->next;
        delete toDelete;
        doc.nurseCount--;
        return true;
    }

    // edge case 3: nurse in middle or tail -> keep a pointer to the node BEFORE it
    Nurse* previous = doc.nurseHead;
    Nurse* current = doc.nurseHead->next;
    while(current != nullptr){
        if(current->nurseID == nurseID){
            previous->next = current->next;   // bypass current (nullptr if it was the tail)
            delete current;
            doc.nurseCount--;
            return true;
        }
        previous = current;
        current = current->next;
    }

    // edge case 4: reached the end without finding the nurse
    cerr << "Error: nurse " << nurseID << " not found under Dr. " << doc.name << "\n";
    return false;
}

// function to print a doctor's nurse list as a chain
void print_nurses(const Doctor& doc){
    cout << "Dr. " << doc.name << " (" << doc.nurseCount << " nurses): head -> ";
    Nurse* current = doc.nurseHead;
    while(current != nullptr){
        cout << "[" << current->nurseID << " " << current->name << "] -> ";
        current = current->next;
    }
    cout << "nullptr\n";
}