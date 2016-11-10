#pragma once

#ifndef GLOBALFUNCTIONSANDVTABLES_H
#define GLOBALFUNCTIONSANDVTABLES_H

#include <stdio.h>

#include "Employee.h"
#include "HourlyEmployee.h"
#include "CommissionEmployee.h"
#include "SeniorSalesman.h"


// Vtables
void* Vtable_hourly[2];
void* Vtable_commission[2];
void* Vtable_senior[2];

// Functions
void Speak_Hourly(struct Employee* e);
void Speak_Commission(struct Employee* e);

double GetPay_Hourly(struct Employee* e);
double GetPay_Commission(struct Employee* e);
double GetPay_Senior(struct Employee* e);

struct HourlyEmployee* Construct_Hourly(struct HourlyEmployee* he);
struct CommissionEmployee* Construct_Commission(struct CommissionEmployee* ce);
struct SeniorSalesman* Construct_Senior(struct SeniorSalesman* ss);

#endif
