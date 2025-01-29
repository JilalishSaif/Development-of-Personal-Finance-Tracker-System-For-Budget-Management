#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRANSACTIONS 100
#define MAX_BUDGETS 10
#define MAX_GOALS 5

typedef struct {
    double amount;
    char source[50];
    char date[20];  // format: YYYY-MM-DD
} Income;

typedef struct {
    double amount;
    char category[50];
    char date[20];  // format: YYYY-MM-DD
} Expense;

typedef struct {
    char category[50];
    double budget_amount;
    double expenses;
} Budget;

typedef struct {
    char goal_name[50];
    double target_amount;
    char due_date[20];  // format: YYYY-MM-DD
    double current_savings;
} Goal;

Income incomes[MAX_TRANSACTIONS];
Expense expenses[MAX_TRANSACTIONS];
Budget budgets[MAX_BUDGETS];
Goal goals[MAX_GOALS];
int income_count = 0, expense_count = 0, budget_count = 0, goal_count = 0;

// Function to get month and year from a date (YYYY-MM-DD)
void get_month_year(const char *date, int *month, int *year) {
    sscanf(date, "%*4d-%d-%*2d", month);
    sscanf(date, "%4d", year);
}

// Function to save data to a file
void save_data() {
    FILE *file = fopen("transactions.txt", "w");
    if (file == NULL) {
        printf("Error saving data.\n");
        return;
    }

    // Save income transactions
    fprintf(file, "Income Transactions:\n");
    for (int i = 0; i < income_count; i++) {
        fprintf(file, "%.2f,%s,%s\n", incomes[i].amount, incomes[i].source, incomes[i].date);
    }

    // Save expense transactions
    fprintf(file, "Expense Transactions:\n");
    for (int i = 0; i < expense_count; i++) {
        fprintf(file, "%.2f,%s,%s\n", expenses[i].amount, expenses[i].category, expenses[i].date);
    }

    // Save budgets
    fprintf(file, "Budgets:\n");
    for (int i = 0; i < budget_count; i++) {
        fprintf(file, "%s,%.2f,%.2f\n", budgets[i].category, budgets[i].budget_amount, budgets[i].expenses);
    }

    // Save goals
    fprintf(file, "Goals:\n");
    for (int i = 0; i < goal_count; i++) {
        fprintf(file, "%s,%.2f,%s,%.2f\n", goals[i].goal_name, goals[i].target_amount, goals[i].due_date, goals[i].current_savings);
    }

    fclose(file);
    printf("Data saved to file successfully.\n");
}

// Function to load data from a file
void load_data() {
    FILE *file = fopen("transactions.txt", "r");
    if (file == NULL) {
        printf("No previous data found. Starting fresh.\n");
        return;
    }

    char line[100];
    income_count = 0;
    expense_count = 0;
    budget_count = 0;
    goal_count = 0;

    // Read income transactions
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Income Transactions:", 20) == 0) continue;
        if (strncmp(line, "Expense Transactions:", 21) == 0) break;
        sscanf(line, "%lf,%49[^,],%19[^\n]", &incomes[income_count].amount, incomes[income_count].source, incomes[income_count].date);
        income_count++;
    }

    // Read expense transactions
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Budgets:", 8) == 0) break;
        sscanf(line, "%lf,%49[^,],%19[^\n]", &expenses[expense_count].amount, expenses[expense_count].category, expenses[expense_count].date);
        expense_count++;
    }

    // Read budgets
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Goals:", 6) == 0) break;
        sscanf(line, "%49[^,],%lf,%lf", budgets[budget_count].category, &budgets[budget_count].budget_amount, &budgets[budget_count].expenses);
        budget_count++;
    }

    // Read goals
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%49[^,],%lf,%19[^,],%lf", goals[goal_count].goal_name, &goals[goal_count].target_amount, goals[goal_count].due_date, &goals[goal_count].current_savings);
        goal_count++;
    }

    fclose(file);
    printf("WELCOME TO OUR PROJECT:\n");
}

// Function to add income, expense, budget, and goal (same as before)
void add_income() {
    if (income_count < MAX_TRANSACTIONS) {
        printf("Enter income amount: ");
        scanf("%lf", &incomes[income_count].amount);
        printf("Enter source: ");
        scanf("%s", incomes[income_count].source);
        printf("Enter date (YYYY-MM-DD): ");
        scanf("%s", incomes[income_count].date);
        income_count++;
        printf("Income added successfully!\n");
    } else {
        printf("Income list is full.\n");
    }

}
void delete_transaction() {
    int type, index;
    printf("\n--- Delete Transaction ---\n");
    printf("Choose transaction type:\n");
    printf("1. Income\n");
    printf("2. Expense\n");
    printf("Enter your choice: ");
    scanf("%d", &type);

    if (type == 1) {
        if (income_count == 0) {
            printf("No income transactions to delete.\n");
            return;
        }

        // Display income transactions
        printf("\nIncome Transactions:\n");
        for (int i = 0; i < income_count; i++) {
            printf("%d. Amount: %.2f BDT, Source: %s, Date: %s\n",
                   i + 1, incomes[i].amount, incomes[i].source, incomes[i].date);
        }

        // Select transaction to delete
        printf("Enter the number of the income transaction to delete: ");
        scanf("%d", &index);
        index--; // Convert to zero-based index

        if (index < 0 || index >= income_count) {
            printf("Invalid transaction number.\n");
            return;
        }

        // Shift transactions to remove the selected one
        for (int i = index; i < income_count - 1; i++) {
            incomes[i] = incomes[i + 1];
        }
        income_count--;
        printf("Income transaction deleted successfully!\n");

    } else if (type == 2) {
        if (expense_count == 0) {
            printf("No expense transactions to delete.\n");
            return;
        }

        // Display expense transactions
        printf("\nExpense Transactions:\n");
        for (int i = 0; i < expense_count; i++) {
            printf("%d. Amount: %.2f BDT, Category: %s, Date: %s\n",
                   i + 1, expenses[i].amount, expenses[i].category, expenses[i].date);
        }

        // Select transaction to delete
        printf("Enter the number of the expense transaction to delete: ");
        scanf("%d", &index);
        index--; // Convert to zero-based index

        if (index < 0 || index >= expense_count) {
            printf("Invalid transaction number.\n");
            return;
        }

        // Shift transactions to remove the selected one
        for (int i = index; i < expense_count - 1; i++) {
            expenses[i] = expenses[i + 1];
        }
        expense_count--;
        printf("Expense transaction deleted successfully!\n");

    } else {
        printf("Invalid choice.\n");
    }
}


void add_expense() {
    if (expense_count < MAX_TRANSACTIONS) {
        printf("Enter expense amount: ");
        scanf("%lf", &expenses[expense_count].amount);
        printf("Enter category: ");
        scanf("%s", expenses[expense_count].category);
        printf("Enter date (YYYY-MM-DD): ");
        scanf("%s", expenses[expense_count].date);
        expense_count++;
        printf("Expense added successfully!\n");
    } else {
        printf("Expense list is full.\n");
    }
}

void set_budget() {
    if (budget_count < MAX_BUDGETS) {
        printf("Enter budget category: ");
        scanf("%s", budgets[budget_count].category);
        printf("Enter budget amount: ");
        scanf("%lf", &budgets[budget_count].budget_amount);
        budgets[budget_count].expenses = 0;  // initialize expenses
        budget_count++;
        printf("Budget set successfully!\n");
    } else {
        printf("Budget list is full.\n");
    }
}

void set_goal() {
    if (goal_count < MAX_GOALS) {
        printf("Enter goal name: ");
        scanf("%s", goals[goal_count].goal_name);
        printf("Enter target amount: ");
        scanf("%lf", &goals[goal_count].target_amount);
        printf("Enter due date (YYYY-MM-DD): ");
        scanf("%s", goals[goal_count].due_date);
        goals[goal_count].current_savings = 0;  // initialize current savings
        goal_count++;
        printf("Goal set successfully!\n");
    } else {
        printf("Goal list is full.\n");
    }
}

// Function to generate monthly report
void generate_monthly_report(int month, int year) {
    double total_income = 0, total_expenses = 0;
    double total_savings = 0;

    // Calculate monthly income and expenses
    for (int i = 0; i < income_count; i++) {
        int i_month, i_year;
        get_month_year(incomes[i].date, &i_month, &i_year);
        if (i_month == month && i_year == year) {
            total_income += incomes[i].amount;
        }
    }

    for (int i = 0; i < expense_count; i++) {
        int e_month, e_year;
        get_month_year(expenses[i].date, &e_month, &e_year);
        if (e_month == month && e_year == year) {
            total_expenses += expenses[i].amount;
        }
    }

    total_savings = total_income - total_expenses;

    // Print monthly report
    printf("\n--- Monthly Report for %d-%02d ---\n", year, month);
    printf("Total Income: %.2f BDT\n", total_income);
    printf("Total Expenses: %.2f BDT\n", total_expenses);
    printf("Net Savings: %.2f BDT\n", total_savings);

    // Monthly budget comparison
    printf("\n--- Budget Comparison ---\n");
    for (int i = 0; i < budget_count; i++) {
        double budget_expense = 0;
        for (int j = 0; j < expense_count; j++) {
            if (strcmp(expenses[j].category, budgets[i].category) == 0) {
                int e_month, e_year;
                get_month_year(expenses[j].date, &e_month, &e_year);
                if (e_month == month && e_year == year) {
                    budget_expense += expenses[j].amount;
                }
            }
        }
        printf("Category: %s, Budget: %.2f BDT, Actual: %.2f BDT\n", budgets[i].category, budgets[i].budget_amount, budget_expense);
    }

    // Monthly goal progress
    printf("\n--- Goal Progress ---\n");
    for (int i = 0; i < goal_count; i++) {
        printf("Goal: %s, Target: %.2f BDT, Saved: %.2f BDT, Remaining: %.2f BDT\n",
            goals[i].goal_name, goals[i].target_amount, goals[i].current_savings,
            goals[i].target_amount - goals[i].current_savings);
    }
}

// Function to generate overall report
void generate_overall_report() {
    double total_income = 0, total_expenses = 0, total_savings = 0;

    // Calculate overall income and expenses
    for (int i = 0; i < income_count; i++) {
        total_income += incomes[i].amount;
    }

    for (int i = 0; i < expense_count; i++) {
        total_expenses += expenses[i].amount;
    }

    total_savings = total_income - total_expenses;

    // Print overall report
    printf("\n--- Overall Report ---\n");
    printf("Total Income: %.2f BDT\n", total_income);
    printf("Total Expenses: %.2f BDT\n", total_expenses);
    printf("Net Savings: %.2f BDT\n", total_savings);

    // Overall budget comparison
    printf("\n--- Budget Comparison ---\n");
    for (int i = 0; i < budget_count; i++) {
        double total_budget_expense = 0;
        for (int j = 0; j < expense_count; j++) {
            if (strcmp(expenses[j].category, budgets[i].category) == 0) {
                total_budget_expense += expenses[j].amount;
            }
        }
        printf("Category: %s, Budget: %.2f BDT, Actual: %.2f BDT\n", budgets[i].category, budgets[i].budget_amount, total_budget_expense);
    }

    // Overall goal progress
    printf("\n--- Goal Progress ---\n");
    for (int i = 0; i < goal_count; i++) {
        printf("Goal: %s, Target: %.2f BDT, Saved: %.2f BDT, Remaining: %.2f BDT\n",
            goals[i].goal_name, goals[i].target_amount, goals[i].current_savings,
            goals[i].target_amount - goals[i].current_savings);
    }
}
// Function to delete all data
void delete_all_data() {
    income_count = 0;
    expense_count = 0;
    budget_count = 0;
    goal_count = 0;

    // Optionally clear the file content
    FILE *file = fopen("transactions.txt", "w");
    if (file != NULL) {
        fclose(file);
    }

    printf("All data has been deleted.\n");
}
void add_savings_to_goal() {
    char goal_name[50];
    double amount;
    printf("Enter goal name: ");
    scanf("%s", goal_name);
    printf("Enter amount to add to savings: ");
    scanf("%lf", &amount);

    for (int i = 0; i < goal_count; i++) {
        if (strcmp(goals[i].goal_name, goal_name) == 0) {
            goals[i].current_savings += amount;
            printf("Savings added successfully!\n");
            return;
        }
    }
    printf("Goal not found.\n");
}
void view_transactions() {
    printf("\n--- Income Transactions ---\n");
    for (int i = 0; i < income_count; i++) {
        printf("Amount: %.2f BDT, Source: %s, Date: %s\n",
               incomes[i].amount, incomes[i].source, incomes[i].date);
    }

    printf("\n--- Expense Transactions ---\n");
    for (int i = 0; i < expense_count; i++) {
        printf("Amount: %.2f BDT, Category: %s, Date: %s\n",
               expenses[i].amount, expenses[i].category, expenses[i].date);
    }
}
void update_transaction() {
    int type, index;
    printf("\n--- Update Transaction ---\n");
    printf("Choose transaction type:\n");
    printf("1. Income\n");
    printf("2. Expense\n");
    printf("Enter your choice: ");
    scanf("%d", &type);

    if (type == 1) {
        if (income_count == 0) {
            printf("No income transactions to update.\n");
            return;
        }

        // Display income transactions
        printf("\nIncome Transactions:\n");
        for (int i = 0; i < income_count; i++) {
            printf("%d. Amount: %.2f BDT, Source: %s, Date: %s\n",
                   i + 1, incomes[i].amount, incomes[i].source, incomes[i].date);
        }

        // Select transaction to update
        printf("Enter the number of the income transaction to update: ");
        scanf("%d", &index);
        index--; // Convert to zero-based index

        if (index < 0 || index >= income_count) {
            printf("Invalid transaction number.\n");
            return;
        }

        // Update income details
        printf("Enter new income amount: ");
        scanf("%lf", &incomes[index].amount);
        printf("Enter new source: ");
        scanf("%s", incomes[index].source);
        printf("Enter new date (YYYY-MM-DD): ");
        scanf("%s", incomes[index].date);
        printf("Income transaction updated successfully!\n");

    } else if (type == 2) {
        if (expense_count == 0) {
            printf("No expense transactions to update.\n");
            return;
        }

        // Display expense transactions
        printf("\nExpense Transactions:\n");
        for (int i = 0; i < expense_count; i++) {
            printf("%d. Amount: %.2f BDT, Category: %s, Date: %s\n",
                   i + 1, expenses[i].amount, expenses[i].category, expenses[i].date);
        }

        // Select transaction to update
        printf("Enter the number of the expense transaction to update: ");
        scanf("%d", &index);
        index--; // Convert to zero-based index

        if (index < 0 || index >= expense_count) {
            printf("Invalid transaction number.\n");
            return;
        }

        // Update expense details
        printf("Enter new expense amount: ");
        scanf("%lf", &expenses[index].amount);
        printf("Enter new category: ");
        scanf("%s", expenses[index].category);
        printf("Enter new date (YYYY-MM-DD): ");
        scanf("%s", expenses[index].date);
        printf("Expense transaction updated successfully!\n");

    } else {
        printf("Invalid choice.\n");
    }
}


int main() {
    load_data();

    int choice;
    do {
        printf("\nPersonal Finance Tracker\n");
        printf("1. Add Income\n");
        printf("2. Add Expense\n");
        printf("3. Set Budget\n");
        printf("4. Set Financial Goal\n");
        printf("5. Add Savings to Goal\n");
        printf("6. Generate Monthly Report\n");
        printf("7. Generate Overall Financial Report\n");
        printf("8. Save Transactions to File\n");
        printf("9. View Transactions\n");
        printf("10.Update Transaction\n");
        printf("11.Delete Transaction\n");
        printf("12.Delete All Data\n");
        printf("13.Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_income(); break;
            case 2: add_expense(); break;
            case 3: set_budget(); break;
            case 4: set_goal(); break;
            case 5:add_savings_to_goal(); break;
            case 6: {
                int month, year;
                printf("Enter month (1-12): ");
                scanf("%d", &month);
                printf("Enter year (YYYY): ");
                scanf("%d", &year);
                generate_monthly_report(month, year);
                break;
            }
            case 7: generate_overall_report(); break;
            case 8: save_data(); break;
            case 9: view_transactions(); break;
            case 10: update_transaction(); break;
            case 11: delete_transaction(); break;
            case 12: delete_all_data(); break;
            case 13: printf("Exiting program...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
}
