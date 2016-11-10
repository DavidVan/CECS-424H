#include <stdio.h>
#include <stdlib.h>

#include "Employee.h"
#include "HourlyEmployee.h"
#include "CommissionEmployee.h"
#include "SeniorSalesman.h"

#include "GlobalFunctionsAndVtables.h" // I should really find a better way of doing this...

int main() {
    struct Employee* employee;
    
    printf("Select an employee:\n1. Hourly Employee\n2. Commission Employee\n3. Senior Salesman\n");
    int choice;
    scanf("%d", &choice); // Get choice from user.

    printf("How old is the employee?\n");
    int age;
    scanf("%d", &age); // Ask the age.

    double salesAmount; // Use this later.
    
    switch(choice) {
        case 1:
            employee = malloc(sizeof(struct HourlyEmployee));

            // Pass in employee pointer, initialize it, and return a pointer to the same employee.
            // No ugly casting needed!
            struct HourlyEmployee* hourlyEmployee = Construct_Hourly((struct HourlyEmployee*) employee);

            hourlyEmployee->age = age; // Got the age above.

            printf("What is the employee's pay rate?\n");
            double hourlyRate;
            scanf("%lf", &hourlyRate);
            hourlyEmployee->hourly_rate = hourlyRate;

            printf("What is the employee's hours?\n");
            double hours;
            scanf("%lf", &hours);
            hourlyEmployee->hours = hours;

            break;
        case 2:
            employee = malloc(sizeof(struct CommissionEmployee));

            // Pass in employee pointer, initialize it, and return a pointer to the same employee.
            // No ugly casting needed!
            struct CommissionEmployee* commissionEmployee = Construct_Commission((struct CommissionEmployee*) employee);

            commissionEmployee->age = age; // Got the age above.

            printf("What is the employee's sales amount?\n");
            // salesAmount variable declared outside switch statement.
            scanf("%lf", &salesAmount);
            commissionEmployee->sales_amount = salesAmount;

            break;
        case 3:
            employee = malloc(sizeof(struct SeniorSalesman));

            // Pass in employee pointer, initialize it, and return a pointer to the same employee.
            // No ugly casting needed!
            struct SeniorSalesman* seniorSalesman = Construct_Senior((struct SeniorSalesman*) employee);

            seniorSalesman->age = age; // Got the age above.

            printf("What is the employee's sales amount?\n");
            // salesAmount variable declared outside switch statement.
            scanf("%lf", &salesAmount);
            seniorSalesman->sales_amount = salesAmount;

            break;
        default:
            printf("That is not a valid choice!\nExiting program...\n");
            return 1;
            break;
    }

    ((void(*)(struct Employee*)) employee->vtable[0])(employee);
    printf("This employee makes %.2f dollars!\n", ((double(*)(struct Employee*)) employee->vtable[1])(employee));
    
    free(employee);
    
    return 0;
}