/*
 * File:    module1_staff.h
 * Module:  1 - Staff Management & Dynamic Rostering (KCH-PMTS)
 *
 * Declares the Nurse and Doctor structs and the functions that manage
 * the doctor array (Q1.1) and each doctor's nurse linked list (Q1.2).
 * NOTE: no "using namespace std;" in a header, always write std::string.
 */

#ifndef MODULE1_STAFF_H
#define MODULE1_STAFF_H

#include <string>

constexpr int MAX_DOCTORS = 50;

// one node in a doctor's singly linked list of nurses
struct Nurse {
    int nurseID;
    std::string name;
    std::string shift;        // shift can be "Day" or "Night"
    Nurse* next = nullptr;
};

// one doctor in the contiguous doctorRoster array
struct Doctor {
    int doctorID;
    std::string name;
    std::string specialization;
    Nurse* nurseHead = nullptr;   // head of this doctor's nurse list
    int nurseCount = 0;           // number of nurses currently assigned
};

// Q1.1 - doctor array
bool add_doctor(Doctor roster[], int& doctorCount, int id, const std::string& name, const std::string& specialization);
bool delete_doctor(Doctor roster[], int& doctorCount, int doctorID);
void print_roster(const Doctor roster[], int doctorCount);

// Q1.2 - nurse linked list
bool add_nurse(Doctor& doc, int nurseID, const std::string& name, const std::string& shift);
bool delete_nurse(Doctor& doc, int nurseID);
void print_nurses(const Doctor& doc);

#endif