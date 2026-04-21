#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store bill details
struct Bill {
    char customerName[50];
    int customerID;
    float units;
    float outstanding;
    float energyCharge;
    float fixedCharge;
    float tax;
    float totalAmount;
};

// Function to calculate energy charge based on slabs
float calculateEnergyCharge(float units) {
    float charge = 0;

    if (units <= 100)
        charge = units * 1.50;
    else if (units <= 200)
        charge = (100 * 1.50) + ((units - 100) * 2.00);
    else
        charge = (100 * 1.50) + (100 * 2.00) + ((units - 200) * 3.50);

    return charge;
}

// Function to safely get integer input
int getValidatedInt(char *msg) {
    int x;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", &x) == 1) return x;
        else {
            printf("Invalid input! Enter a valid number.\n");
            fflush(stdin);
        }
    }
}

// Function to safely get float input
float getValidatedFloat(char *msg) {
    float x;
    while (1) {
        printf("%s", msg);
        if (scanf("%f", &x) == 1) return x;
        else {
            printf("Invalid input! Enter a valid number.\n");
            fflush(stdin);
        }
    }
}

// Save bill to file
void saveBillToFile(struct Bill b) {
    FILE *fp = fopen("bill_records.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "Customer: %s | ID: %d | Units: %.2f | Total: %.2f\n",
            b.customerName, b.customerID, b.units, b.totalAmount);

    fclose(fp);
    printf("\nBill saved successfully!\n");
}

// Display previous bills
void showPreviousBills() {
    FILE *fp = fopen("bill_records.txt", "r");
    if (fp == NULL) {
        printf("No previous bills found.\n");
        return;
    }

    char line[200];
    printf("\n----- Previous Bill Records -----\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

// Show units chart
void showUnitsChart(float units) {
    int bars = units / 20; // 1 bar = 20 units

    printf("\n----- Units Consumption Chart -----\n");
    printf("20 units per bar\n");
    printf("[ ");
    int i;
    for ( i = 0; i < bars; i++)
        printf("#");

    printf(" ]  %.2f units\n", units);
}

int main() {

    struct Bill b;

    // Accept User Input
    printf("Enter Customer Name: ");
    scanf("%s", b.customerName);

    b.customerID = getValidatedInt("Enter Customer ID: ");
    b.units = getValidatedFloat("Enter Units Consumed: ");
    b.outstanding = getValidatedFloat("Enter Outstanding Amount: ");

    // Calculate tariff
    b.energyCharge = calculateEnergyCharge(b.units);
    b.fixedCharge = 50;
    b.tax = (b.energyCharge + b.fixedCharge) * 0.05;
    b.totalAmount = b.energyCharge + b.fixedCharge + b.tax + b.outstanding;

    // Display breakdown
    printf("\n----- ELECTRICITY BILL -----\n");
    printf("Customer Name     : %s\n", b.customerName);
    printf("Customer ID       : %d\n", b.customerID);
    printf("Units Consumed    : %.2f\n\n", b.units);

    printf("Energy Charges    : %.2f\n", b.energyCharge);
    printf("Fixed Charges     : %.2f\n", b.fixedCharge);
    printf("Tax (5%%)          : %.2f\n", b.tax);
    printf("Outstanding Amt   : %.2f\n", b.outstanding);

    printf("--------------------------------------\n");
    printf("Total Payable     : %.2f\n", b.totalAmount);
    printf("--------------------------------------\n");

    // Units chart
    showUnitsChart(b.units);

    // Save bill to file
    saveBillToFile(b);

    // Previous bill tracking
    int choice = getValidatedInt("Do you want to see previous bills? (1 = Yes): ");

    if (choice == 1) {
        showPreviousBills();
    }

    printf("\n--- THANK YOU ---\n");

    return 0;
}
