#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct Date {
  int Day;
  int Month;
  int Year;
};
struct LedgerRecord {
  struct Date Timestamp;
  std::string Vendor;
  std::string Expense;
  double Amount;
};

struct BudgetRecord {
  std::string Expense;
  double Budget;
};

void match_entries_with_budget(const std::vector<LedgerRecord> &expenses, const std::vector<BudgetRecord> &budget);
std::vector<LedgerRecord> read_expense_file(const char *);
std::vector<BudgetRecord> read_budget_file(const char *);
  
int main(int argc, const char**argv) {
  std::vector<LedgerRecord> expense_entries = read_expense_file(argv[1]);
  std::vector<BudgetRecord> budget_entries = read_budget_file(argv[2]);
  
  match_entries_with_budget(expense_entries, budget_entries);
  return 0;
}

std::vector<LedgerRecord> read_expense_file(const char *filename)
{
  std::ifstream input(filename);
  std::vector<LedgerRecord> expenses;

  char date_sep;
  while (!input.eof())
  {
    struct LedgerRecord LR;
    input >> LR.Timestamp.Day; input >> date_sep;
    input >> LR.Timestamp.Month; input >> date_sep;
    input >> LR.Timestamp.Year;
    input >> LR.Vendor;
    input >> LR.Expense;
    input >> LR.Amount;
    expenses.push_back(LR);
  }
  return expenses;
}

std::vector<BudgetRecord> read_budget_file(const char *filename)
{
  std::ifstream input(filename);
  std::vector<BudgetRecord> budget;
  while (!input.eof())
  {
    struct BudgetRecord BR;
    input >> BR.Expense >> BR.Budget;
    budget.push_back(BR);
  }
  return budget;
}

void match_entries_with_budget(const std::vector<LedgerRecord> &expenses,
                              const std::vector<BudgetRecord> &budget)
{
  std::vector<BudgetRecord>::const_iterator it = budget.begin();
  for (; it != budget.end(); ++it)
  {
    std::vector<LedgerRecord>::const_iterator expense_it = expenses.begin();
    double accum_expense = 0;
    for (; expense_it != expenses.end(); ++expense_it)
    {
      if (expense_it->Expense == it->Expense)
      {
        accum_expense += expense_it->Amount;
      }
    }
    if (accum_expense > it->Budget)
    {
      std::cout << it->Expense << " exceeded budget by " << (accum_expense - it->Budget) << std::endl;
    }
    
  }
}
