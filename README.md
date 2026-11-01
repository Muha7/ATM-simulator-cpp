# ATM Simulator (C++)

A console-based Automated Teller Machine (ATM) Simulator developed using C++. The project simulates essential ATM operations, allowing users to authenticate their bank accounts and perform basic financial transactions through an interactive menu-driven interface.

The application uses file handling to retrieve and update client account information, maintaining account data locally between program executions.

## Features

### 1. Account Authentication
- Login using an account number and PIN code.
- Validate user credentials against stored client records.
- Prevent access when incorrect credentials are entered.
- Logout and return to the login screen.

### 2. Quick Cash Withdrawal
- Withdraw predefined amounts quickly.
- Available withdrawal amounts: 20, 50, 100, 200, 400, 600, 800, and 1000.
- Check available account balance before withdrawal.
- Confirm transactions before updating account records.

### 3. Normal Cash Withdrawal
- Enter a custom withdrawal amount.
- Require withdrawal amounts to be multiples of 5.
- Validate the requested amount against the available balance.
- Confirm transactions before processing.

### 4. Cash Deposit
- Enter a deposit amount.
- Validate the entered amount.
- Confirm the transaction before updating the account balance.

### 5. Balance Inquiry
- Display the current account balance.
- Retrieve account information from stored client records.

## Technologies Used

- **Programming Language:** C++
- **Data Structures:** Structures and Vectors
- **Programming Concepts:** Functions, Enumerations, Conditional Statements, Loops, and References
- **File Handling:** `fstream`, `ifstream`, `ofstream`
- **Standard Libraries:** iostream, vector, string, iomanip, cctype, fstream, ctime
- **Data Storage:** Local text files

## Project Structure

```text
atm-simulator-cpp/
│
├── ATM.cpp          # Main C++ source code
├── Client.txt       # Client account records
├── README.md        # Project documentation
└── .gitignore       # Git ignored files
```

## Data Storage

The application uses a local text file named `Client.txt` to store client account information.

Each client record contains:

- Account Number
- Client Name
- Phone Number
- PIN Code
- Account Balance

The records are separated using a custom delimiter (`#//#`).

When a transaction is confirmed, the application updates the corresponding client record and saves the modified data to the file.

## How to Run

### Prerequisites

- A C++ compiler such as GCC or MinGW.
- Visual Studio Code, Visual Studio, or another C++ development environment.

### Installation and Execution

1. Clone the repository:

```bash
git clone https://github.com/Muha7/atm-simulator-cpp.git
```

2. Navigate to the project directory:

```bash
cd atm-simulator-cpp
```

3. Compile the source code:

```bash
g++ ATM.cpp -o ATM
```

4. Run the application on Windows:

```bash
ATM.exe
```

**Important:** Keep `Client.txt` in the same working directory as the executable because the application reads and updates this file during execution.

## Project Objectives

This project was developed to practice and demonstrate practical C++ programming skills, including:

- Building an interactive console-based application.
- Implementing account authentication.
- Managing client account information.
- Processing deposits and withdrawals.
- Validating financial transactions.
- Working with file-based data persistence.
- Using vectors and structures to manage records.

## Project Notes

This is an educational ATM simulation developed for programming practice. It does not connect to real banking systems or process actual financial transactions.

The project uses plain-text storage for account information and is not intended for production banking environments.

## Author

**Muha7**

GitHub: [@Muha7](https://github.com/Muha7)
