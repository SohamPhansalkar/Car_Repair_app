# 🚗 Car Service Management System 🛠️  
--------------------------------------------------
## 🌟 Overview  
A GTK3-based application for managing car service records with:  
- 🆕 Car registration system  
- 🔍 Status tracking (In Queue/In Process/Ready)  
- 🧾 Automated receipt generation  
- 📋 Complete vehicle listing  

--------------------------------------------------
## 🎯 Key Features  

### 📝 Registration Module  
- Store complete vehicle details  
- Track repair requirements  
- Record service costs  

### 🔄 Status Management  
- Real-time status updates  
- Quick search by license number  
- Visual status indicators  

### 💰 Receipt System  
- Automatic cost calculation  
- Itemized repair listing  
- Printable format  

### 📊 Data Management  
- View all registered vehicles  
- Scrollable interface  
- Compact information display  

--------------------------------------------------
## 🛠️ Function Reference  

### 🏗️ Core Functions  
1. main() - App entry point, creates main window  
2. save_car_data() - Handles new vehicle registration  

### 📥 Registration  
3. on_register_car_clicked() - Builds registration form UI  

### 🔍 Status Tracking  
4. on_check_status_clicked() - Status window setup  
5. on_search_clicked() - Vehicle lookup logic  
6. on_save_status_clicked() - Status update handler  

### 🧾 Receipts  
7. on_generate_receipt_clicked() - Receipt UI builder  
8. on_generate_clicked() - PDF-style receipt generator  

### 📋 Data Display  
9. on_list_clicked() - Creates vehicle listing table  

--------------------------------------------------
## 🏗️ System Architecture  

### 🧩 Data Structure  
```C
struct Car {
    char carName[50];     // Vehicle make/model
    char carNumber[20];   // License plate
    char status[20];      // Service status
    char repairs[100];    // Repair list
    char cost[100];       // Associated costs
};
```

### 📦 Storage  
- Array-based system (100 vehicle capacity)  
- Persistent during runtime

--------------------------------------------------
# Function Documentation

## Core Functions

### main()
- Entry point of the application
- Initializes GTK framework
- Creates main window with navigation buttons
- Starts the GTK main event loop

### save_car_data(GtkWidget *button, gpointer user_data)
- Saves new car registration data
- Validates input fields
- Stores data in carList array
- Sets default status to "in queue"
- Closes registration window

## Registration Functions

### on_register_car_clicked(GtkWidget *widget, gpointer data)
- Creates registration form window
- Contains fields for:
  • Car name (text entry)
  • Car number (text entry)
  • Repairs (comma-separated)
  • Costs (comma-separated)
- Connects submit button to save_car_data()

## Status Management

### on_check_status_clicked(GtkWidget *widget, gpointer data)
- Creates status check window
- Adds search field and buttons
- Initializes disabled status dropdown

### on_search_clicked(GtkWidget *widget, gpointer data)
- Searches for car by number
- If found:
  • Displays car info
  • Enables status dropdown
  • Sets current status
- If not found shows error message

### on_save_status_clicked(GtkWidget *widget, gpointer data)
- Updates car status from dropdown
- Saves changes to carList
- Closes status window

## Receipt Generation

### on_generate_receipt_clicked(GtkWidget *widget, gpointer data)
- Creates receipt window
- Adds car number input field
- Initializes receipt display area

### on_generate_clicked(GtkWidget *widget, gpointer data)
- Generates formatted receipt
- Parses repairs and costs
- Calculates total
- Displays itemized receipt

## Data Display

### on_list_clicked(GtkWidget *widget, gpointer data)
- Shows all registered cars
- Creates scrollable table display
- Columns: Name, Number, Repairs, Cost, Status

--------------------------------------------------
## 💻 Installation Guide  

### 🚀 Setup Steps  

1. Install MSYS2  
   Download: msys2.org  
   Run installer (default settings recommended)  

2. Update Packages  
   ```
   pacman -Syu
   ```

3. Install Dependencies
4. ```
   pacman -S mingw-w64-x86_64-gtk3 
   pacman -S mingw-w64-x86_64-toolchain
   pacman -S git
   ```

5. Configure Environment  
   Add to PATH: C:\msys64\mingw64\bin  

6. Build & Run
7. ```
   git clone https://github.com/SohamPhansalkar/Car_Repair_app.git
   cd car-service-system
   gcc -o car_service main.c `pkg-config --cflags --libs gtk+-3.0`
   ./car_service.exe
   ```

--------------------------------------------------
## 🚦 Getting Started  
1. Register new vehicles via Registration  
2. Track status changes with Status Manager  
3. Generate receipts after service completion  
4. View all records in Vehicle Listing  

💡 Pro Tip: Use comma-separation for multiple repairs/costs!
