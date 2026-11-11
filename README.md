# Task 4: Banking System

## Features
- Uses `Customer`, `Account`, and `Transaction` classes.
- Creates customers and unique account numbers during the program run.
- Supports deposits, withdrawals, and transfers between accounts.
- Prevents invalid amounts, overdrafts, and transfers to the same account.
- Displays customer/account details and the five most recent transactions.

## Compile and run
```bash
g++ -std=c++17 main.cpp -o banking
./banking
```
On Windows:
```bash
g++ -std=c++17 main.cpp -o banking.exe
banking.exe
```

## Important note
This beginner project stores data in memory while the program is running. Customer, account, balance, and transaction data are reset when the program closes. It is a learning project, not production banking software.
