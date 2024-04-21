#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

void print_info(retire_info);

void print_balance(int age, double balance) { // age is given in months
  printf("Age %3d month %2d you have $%.2lf\n", age/12, age%12, balance);
}

double calculate_balance(double current_balance, retire_info info) {
  double increase = current_balance * info.rate_of_return;
  double new_balance = current_balance + increase + info.contribution;
  return new_balance;
}

double get_balance_for_all_months(int age, double balance, retire_info info) {
  while (info.months) {
    print_balance(age, balance);
    balance = calculate_balance(balance, info);
    age += 1;
    info.months -= 1;
  }
  return balance;
}

void retirement (int startAge,   //in months
                 double initial, //initial savings in dollars
                 retire_info working, //info about working
                 retire_info retired) //info about being retired
{
  int retirementAge = startAge + working.months;
  double balanceAtRetirement = get_balance_for_all_months(startAge, initial, working);
  get_balance_for_all_months(retirementAge, balanceAtRetirement, retired);    
}

void print_info(retire_info info) {
  printf("Months: %d\tContribution: %f\tRate of Return: %f\n", info.months, info.contribution, info.rate_of_return);
}

int main(void) {
  retire_info working;
  retire_info retired;
  int startAge = 327; // in months
  double initial = 21345.0;
  
  working.months = 489;
  working.contribution = 1000.0;
  working.rate_of_return = 0.045/12.0;
  
  retired.months = 384;
  retired.contribution = -4000.0;
  retired.rate_of_return = 0.01/12.0;
  
  retirement(startAge, initial, working, retired);
  
  return EXIT_SUCCESS;
}
