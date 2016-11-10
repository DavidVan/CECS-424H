#include <stdio.h>

#include "Employee.h"
#include "HourlyEmployee.h"
#include "CommissionEmployee.h"
#include "SeniorSalesman.h"
#include "GlobalFunctionsAndVtables.h"

// Construct Vtable.
void* Vtable_hourly[2] = { Speak_Hourly, GetPay_Hourly };
void* Vtable_commission[2] = { Speak_Commission, GetPay_Commission };
void* Vtable_senior[2] = { Speak_Commission, GetPay_Senior };

void Speak_Hourly(struct Employee* e) {
    printf("I work for %.2f dollars per hour :(\n", ((struct HourlyEmployee*) e)->hourly_rate);
}

void Speak_Commission(struct Employee* e) {
    printf("I make commission on %.2f dollars in sales!\n", ((struct CommissionEmployee*) e)->sales_amount);
}

double GetPay_Hourly(struct Employee* e) {
    return ((struct HourlyEmployee*) e)->hours * ((struct HourlyEmployee*) e)->hourly_rate;
}

double GetPay_Commission(struct Employee* e) {
    return 0.1 * ((struct CommissionEmployee*) e)->sales_amount + 40000;
}

double GetPay_Senior(struct Employee* e) {
    return e->age >= 40 ? 0.25 * ((struct SeniorSalesman*) e)->sales_amount + 50000 : 0.2 * ((struct SeniorSalesman*) e)->sales_amount + 50000;
}

struct HourlyEmployee* Construct_Hourly(struct HourlyEmployee* he) {
    he->age = 0;
    he->hourly_rate = 0;
    he->hours = 0;
    he->vtable = Vtable_hourly;
    return he;
}

struct CommissionEmployee* Construct_Commission(struct CommissionEmployee* ce) {
    ce->age = 0;
    ce->sales_amount = 0;
    ce->vtable = Vtable_commission;
    return ce;
}

struct SeniorSalesman* Construct_Senior(struct SeniorSalesman* ss) {
    ss->age = 0;
    ss->sales_amount = 0;
    ss->vtable = Vtable_senior;
    return ss;
}