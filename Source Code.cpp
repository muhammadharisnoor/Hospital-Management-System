#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 50;


struct Patient {
    int MRNo;
    string name;
    int age;
    string gender;
    string records;
    string room;
};

struct Doctor {
    string name;
    string specialization;
};


Patient patients[MAX];
int patientCount = 0;

Doctor doctors[MAX];
int doctorCount = 0;

string appointments[MAX];
int appointmentCount = 0;

string rooms[MAX];
int roomCount = 0;

float bills[MAX];
int billCount = 0;

void loadData();
void saveData();
void addPatient();
void viewPatients();
void addDoctor();
void viewDoctors();
void scheduleAppointment();
void viewAppointments();
void addRoom();
void viewRooms();
void createBill();
void viewBills();
void deletePatient();
void deleteDoctor();
void deleteAppointment();
void deleteRoom();
void deleteMenu();
void doctorMenu(int doctorIndex);
void patientMenu(int mrNo);
void receptionMenu();
void adminMenu();

void loadData() {
    ifstream file;

    file.open("patients.txt");
    if (file.is_open()) {
        patientCount = 0;
        while (file >> patients[patientCount].MRNo >> ws && getline(file, patients[patientCount].name, ',') &&
            file >> patients[patientCount].age >> patients[patientCount].gender) {
            patientCount++;
        }
        file.close();
    }

    file.open("doctors.txt");
    if (file.is_open()) {
        doctorCount = 0;
        while (getline(file, doctors[doctorCount].name, ',') &&
            getline(file, doctors[doctorCount].specialization)) {
            doctorCount++;
        }
        file.close();
    }

    file.open("appointments.txt");
    if (file.is_open()) {
        appointmentCount = 0;
        while (getline(file, appointments[appointmentCount])) appointmentCount++;
        file.close();
    }

    file.open("rooms.txt");
    if (file.is_open()) {
        roomCount = 0;
        while (getline(file, rooms[roomCount])) roomCount++;
        file.close();
    }

    file.open("bills.txt");
    if (file.is_open()) {
        billCount = 0;
        while (file >> bills[billCount]) billCount++;
        file.close();
    }

    file.open("patientRecords.txt");
    if (file.is_open()) {
        for (int i = 0; i < patientCount; i++) getline(file, patients[i].records);
        file.close();
    }

    file.open("patientRoom.txt");
    if (file.is_open()) {
        for (int i = 0; i < patientCount; i++) getline(file, patients[i].room);
        file.close();
    }
}

void saveData() {
    ofstream file;

    file.open("patients.txt");
    for (int i = 0; i < patientCount; i++)
        file << patients[i].MRNo << " " << patients[i].name << "," << " " << patients[i].age << " " << patients[i].gender << endl;
    file.close();

    file.open("doctors.txt");
    for (int i = 0; i < doctorCount; i++)
        file << doctors[i].name << "," << doctors[i].specialization << endl;
    file.close();

    file.open("appointments.txt");
    for (int i = 0; i < appointmentCount; i++)
        file << appointments[i] << endl;
    file.close();

    file.open("rooms.txt");
    for (int i = 0; i < roomCount; i++)
        file << rooms[i] << endl;
    file.close();

    file.open("bills.txt");
    for (int i = 0; i < billCount; i++)
        file << bills[i] << endl;
    file.close();

    file.open("patientRecords.txt");
    for (int i = 0; i < patientCount; i++)
        file << patients[i].records << endl;
    file.close();

    file.open("patientRoom.txt");
    for (int i = 0; i < patientCount; i++)
        file << patients[i].room << endl;
    file.close();
}


void addPatient() {
    if (patientCount < MAX) {
        cout << "\nEnter MR No: "; cin >> patients[patientCount].MRNo;
        cin.ignore();
        cout << "Enter Patient Name: "; getline(cin, patients[patientCount].name);
        cout << "Enter Age: "; cin >> patients[patientCount].age;
        cin.ignore();
        cout << "Enter Gender: "; getline(cin, patients[patientCount].gender);
        patientCount++;
        saveData();
        cout << "Patient Registered Successfully!\n";
    }
    else cout << "Patient list is full!\n";
}

void viewPatients() {
    if (patientCount == 0) cout << "No patients registered.\n";
    else {
        cout << "\n--- Patient List ---\n";
        for (int i = 0; i < patientCount; i++)
            cout << i + 1 << ". MR: " << patients[i].MRNo << " | " << patients[i].name << " | Age: "
            << patients[i].age << " | Gender: " << patients[i].gender << endl;
    }
}

void addDoctor() {
    if (doctorCount < MAX) {
        cin.ignore();
        cout << "\nEnter Doctor Name: "; getline(cin, doctors[doctorCount].name);
        cout << "Enter Specialization: "; getline(cin, doctors[doctorCount].specialization);
        doctorCount++;
        saveData();
        cout << "Doctor Added Successfully!\n";
    }
    else cout << "Doctor list is full!\n";
}

void viewDoctors() {
    if (doctorCount == 0) cout << "No doctors available.\n";
    else {
        cout << "\n--- Doctor List ---\n";
        for (int i = 0; i < doctorCount; i++)
            cout << i + 1 << ". " << doctors[i].name << " | Specialization: " << doctors[i].specialization << endl;
    }
}

void scheduleAppointment() {
    if (patientCount == 0 || doctorCount == 0) { cout << "You must have at least one patient and one doctor first!\n"; return; }

    cout << "\nEnter Patient MR No: "; int mr; cin >> mr;
    int pIndex = -1;
    for (int i = 0; i < patientCount; i++) if (patients[i].MRNo == mr) pIndex = i;
    if (pIndex == -1) { cout << "Patient not found!\n"; return; }

    cout << "Select Doctor (1 - " << doctorCount << "): "; int d; cin >> d;
    if (d <= 0 || d > doctorCount) { cout << "Invalid doctor!\n"; return; }

    appointments[appointmentCount] = "Patient " + patients[pIndex].name + " with Dr. " + doctors[d - 1].name;
    appointmentCount++;
    saveData();
    cout << "Appointment Scheduled Successfully!\n";
}

void viewAppointments() {
    if (appointmentCount == 0) cout << "No appointments scheduled.\n";
    else {
        cout << "\n--- Appointments ---\n";
        for (int i = 0; i < appointmentCount; i++)
            cout << i + 1 << ". " << appointments[i] << endl;
    }
}


void addRoom() {
    if (roomCount < MAX) {
        cin.ignore();
        cout << "\nEnter Room Name or Number: "; getline(cin, rooms[roomCount]);
        roomCount++;
        saveData();
        cout << "Room Added Successfully!\n";
    }
    else cout << "Room list is full!\n";
}

void viewRooms() {
    if (roomCount == 0) cout << "No rooms available.\n";
    else {
        cout << "\n--- Rooms ---\n";
        for (int i = 0; i < roomCount; i++)
            cout << i + 1 << ". " << rooms[i] << endl;
    }
}

void createBill() {
    if (patientCount == 0) { cout << "No patients to bill.\n"; return; }

    cout << "\nEnter Patient MR No: "; int mr; cin >> mr;
    int pIndex = -1;
    for (int i = 0; i < patientCount; i++) if (patients[i].MRNo == mr) pIndex = i;
    if (pIndex == -1) { cout << "Patient not found!\n"; return; }

    float doctorCharge, roomCharge, medCharge;
    cout << "Enter Doctor Charge: "; cin >> doctorCharge;
    cout << "Enter Room Charge: "; cin >> roomCharge;
    cout << "Enter Medication Charge: "; cin >> medCharge;

    bills[billCount++] = doctorCharge + roomCharge + medCharge;
    saveData();
    cout << "Total Bill for " << patients[pIndex].name << ": " << bills[billCount - 1] << endl;
}

void viewBills() {
    if (billCount == 0) cout << "No bills generated.\n";
    else {
        cout << "\n--- Billing Records ---\n";
        for (int i = 0; i < billCount; i++)
            cout << i + 1 << ". Amount: " << bills[i] << endl;
    }
}

void deletePatient() {
    if (patientCount == 0) { cout << "No patients to delete.\n"; return; }
    viewPatients();
    cout << "Enter patient number to delete: "; int n; cin >> n;
    if (n > 0 && n <= patientCount) {
        for (int i = n - 1; i < patientCount - 1; i++) patients[i] = patients[i + 1];
        patientCount--;
        saveData();
        cout << "Patient record deleted.\n";
    }
    else cout << "Invalid number.\n";
}

void deleteDoctor() {
    if (doctorCount == 0) { cout << "No doctors to delete.\n"; return; }
    viewDoctors();
    cout << "Enter doctor number to delete: "; int n; cin >> n;
    if (n > 0 && n <= doctorCount) {
        for (int i = n - 1; i < doctorCount - 1; i++) doctors[i] = doctors[i + 1];
        doctorCount--;
        saveData();
        cout << "Doctor record deleted.\n";
    }
    else cout << "Invalid number.\n";
}

void deleteAppointment() {
    if (appointmentCount == 0) { cout << "No appointments to delete.\n"; return; }
    viewAppointments();
    cout << "Enter appointment number to delete: "; int n; cin >> n;
    if (n > 0 && n <= appointmentCount) {
        for (int i = n - 1; i < appointmentCount - 1; i++) appointments[i] = appointments[i + 1];
        appointmentCount--;
        saveData();
        cout << "Appointment removed.\n";
    }
    else cout << "Invalid number.\n";
}

void deleteRoom() {
    if (roomCount == 0) { cout << "No rooms to delete.\n"; return; }
    viewRooms();
    cout << "Enter room number to delete: "; int n; cin >> n;
    if (n > 0 && n <= roomCount) {
        for (int i = n - 1; i < roomCount - 1; i++) rooms[i] = rooms[i + 1];
        roomCount--;
        saveData();
        cout << "Room record deleted.\n";
    }
    else cout << "Invalid number.\n";
}

void deleteMenu() {
    int choice;
    do {
        cout << "\n--- Delete Menu ---\n1. Delete Patient\n2. Delete Doctor\n3. Delete Appointment\n4. Delete Room\n0. Back\n";
        cout << "Enter choice: "; cin >> choice;
        switch (choice) {
        case 1: deletePatient(); break;
        case 2: deleteDoctor(); break;
        case 3: deleteAppointment(); break;
        case 4: deleteRoom(); break;
        }
    } while (choice != 0);
}


void adminMenu() {
    int choice;
    do {
        cout << "\n===== Admin Menu =====\n";
        cout << "1. Add Patient\n2. View Patients\n3. Add Doctor\n4. View Doctors\n5. Schedule Appointment\n6. View Appointments\n";
        cout << "7. Add Room\n8. View Rooms\n9. Create Bill\n10. View Bills\n11. Delete Records\n0. Exit\n";
        cout << "Enter choice: "; cin >> choice;
        switch (choice) {
        case 1: addPatient(); break;
        case 2: viewPatients(); break;
        case 3: addDoctor(); break;
        case 4: viewDoctors(); break;
        case 5: scheduleAppointment(); break;
        case 6: viewAppointments(); break;
        case 7: addRoom(); break;
        case 8: viewRooms(); break;
        case 9: createBill(); break;
        case 10: viewBills(); break;
        case 11: deleteMenu(); break;
        }
    } while (choice != 0);
}

void doctorMenu(int doctorIndex) {
    int choice;
    do {
        cout << "\n===== Doctor Menu =====\n1. View Appointments\n2. Add Medication & Notes\n0. Exit\n";
        cout << "Enter choice: "; cin >> choice; cin.ignore();
        switch (choice) {
        case 1: viewAppointments(); break;
        case 2: {
            int mr; cout << "Enter Patient MR No: "; cin >> mr; cin.ignore();
            int pIndex = -1;
            for (int i = 0; i < patientCount; i++) if (patients[i].MRNo == mr) pIndex = i;
            if (pIndex == -1) { cout << "Patient not found!\n"; break; }

            string med, note, disease;
            cout << "Enter DIsease for " << patients[pIndex].name << ": "; getline(cin, disease);
            cout << "Enter Medication for " << patients[pIndex].name << ": "; getline(cin, med);
            cout << "Enter Notes for " << patients[pIndex].name << ": "; getline(cin, note);

            string entry = "Disease: " + disease + "Medication: " + med + " | Notes: " + note;
            if (patients[pIndex].records != "") patients[pIndex].records += "\n";
            patients[pIndex].records += entry;

            cout << "Medication and notes added for " << patients[pIndex].name << ".\n";
            saveData();
            break;
        }
        }
    } while (choice != 0);
}

void patientMenu(int mrNo) {
    int index = -1;
    for (int i = 0; i < patientCount; i++) if (patients[i].MRNo == mrNo) index = i;
    if (index == -1) { cout << "Patient not found!\n"; return; }

    int choice;
    do {
        cout << "\n===== Patient Menu =====\n1. View Profile\n2. View Bills\n3. Book Appointment\n4. View Available Doctors\n0. Exit\n";
        cout << "Enter choice: "; cin >> choice; cin.ignore();
        switch (choice) {
        case 1:
            cout << "MR: " << patients[index].MRNo << " | " << patients[index].name
                << " | Age: " << patients[index].age << " | Gender: " << patients[index].gender << endl;
            if (patients[index].room != "") cout << "Admitted to Room: " << patients[index].room << endl;
            if (patients[index].records != "") cout << "Medications & Notes:\n" << patients[index].records << endl;
            else cout << "No medications or notes yet.\n";
            break;
        case 2: if (billCount > 0) cout << "Bill: " << bills[index] << endl; else cout << "No bills yet.\n"; break;
        case 3: scheduleAppointment(); break;
        case 4: viewDoctors(); break;
        }
    } while (choice != 0);
}

void receptionMenu() {
    int choice;
    do {
        cout << "\n===== Reception Menu =====\n1. Admit Patient to Ward\n2. Create Bills\n3. View Appointments\n4. Delete Menu\n0. Exit\n";
        cout << "Enter choice: "; cin >> choice; cin.ignore();
        switch (choice) {
        case 1: {
            if (patientCount == 0 || roomCount == 0) { cout << "No patients or rooms available!\n"; break; }
            int mr; cout << "Enter Patient MR No: "; cin >> mr; cin.ignore();
            int pIndex = -1;
            for (int i = 0; i < patientCount; i++) if (patients[i].MRNo == mr) pIndex = i;
            if (pIndex == -1) { cout << "Patient not found!\n"; break; }

            cout << "Select Room:\n";
            for (int i = 0; i < roomCount; i++) cout << i + 1 << ". " << rooms[i] << endl;
            int r; cout << "Enter Room number: "; cin >> r; cin.ignore();
            if (r <= 0 || r > roomCount) { cout << "Invalid room number!\n"; break; }

            patients[pIndex].room = rooms[r - 1];
            cout << patients[pIndex].name << " admitted to " << patients[pIndex].room << ".\n";
            saveData();
            break;
        }
        case 2: createBill(); break;
        case 3: viewAppointments(); break;
        case 4: deleteMenu(); break;
        }
    } while (choice != 0);
}


int main() {
    loadData();
    int mainChoice;
    do {
        cout << "\n============= Hospital Management System ==============\nProject By: Haris Noor | Mohammadullah Ashori | M Irzam \n\n Main Menu\n1. Admin\n2. Doctor\n3. Patient\n4. Reception\n0. Exit\n";
        cout << "Enter choice: "; cin >> mainChoice; cin.ignore();
        if (mainChoice == 1) {
            string user, pass;
            cout << "Username: "; getline(cin, user);
            cout << "Password: "; getline(cin, pass);
            if (user == "Admin" && pass == "123") adminMenu();
            else cout << "Invalid credentials!\n";
        }
        else if (mainChoice == 2) {
            string name; cout << "Enter Doctor Name: "; getline(cin, name);
            int found = -1; for (int i = 0; i < doctorCount; i++) if (doctors[i].name == name) found = i;
            if (found != -1) doctorMenu(found); else cout << "Doctor not found!\n";
        }
        else if (mainChoice == 3) {
            int mr; cout << "Enter MR No: "; cin >> mr;
            patientMenu(mr);
        }
        else if (mainChoice == 4) {
            string user, pass;
            cout << "Username: "; getline(cin, user);
            cout << "Password: "; getline(cin, pass);
            if (user == "reception" && pass == "123") receptionMenu();
            else cout << "Invalid credentials!\n";
        }
    } while (mainChoice != 0);

    saveData();
    return 0;
}
