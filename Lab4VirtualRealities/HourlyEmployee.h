#pragma once

#ifndef HOURLYEMPLOYEE_H
#define HOURLYEMPLOYEE_H

struct HourlyEmployee {
    void** vtable;
    int age;
    double hourly_rate;
    double hours;
};

#endif