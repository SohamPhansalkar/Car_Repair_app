// Import Libraries 
#include <gtk/gtk.h> // GUI library 
#include <stdio.h>
#include <string.h>

// Structure of the car and defining its properties
struct Car {
    char carName[50];
    char carNumber[20];
    char status[20];
    char repairs[100];
    char cost[100];
};

#define MAX_CARS 100 // Limiting max data allowance 
struct Car carList[MAX_CARS]; // creates a array (carList) which will store the data with datatype Car
int carCount = 0; // Keeps the track of number of entries (data), mainly for iteration

typedef struct {
    GtkWidget *entry_number;   // User inputs car number
    GtkWidget *label_info;     // Displays car name and number
    GtkWidget *combo_status;   // Dropdown to change status
    GtkWidget *btn_save;       // Save button
    GtkWidget *window;         // Current window
    int found_index;           // Index of the matched car in carList[]
} StatusWidgets;


// Declaring all the functions used 
// Registration related functions
void save_car_data(GtkWidget *button, gpointer user_data);
void on_register_car_clicked(GtkWidget *widget, gpointer data);

// Status Update related functions
void on_check_status_clicked(GtkWidget *widget, gpointer data);
void on_search_clicked(GtkWidget *widget, gpointer data);
void on_save_status_clicked(GtkWidget *widget, gpointer data);

// Receipt Generation related functions
void on_generate_receipt_clicked(GtkWidget *widget, gpointer data);
void on_generate_clicked(GtkWidget *widget, gpointer data);

// Car Listing related functions
void on_list_clicked(GtkWidget *widget, gpointer data);



GtkWidget *entry_name, *entry_number, *entry_repairs, *entry_cost; // Global text input fields


// Main function
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Creates the main menu window and sets basic parameters
    // Sets the window above other windows
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    //Gives a title at the top of window
    gtk_window_set_title(GTK_WINDOW(window), "C Mini Project");

    //Sets the size of the window
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);
    
    //Closes the window when clicked the X button on the top right corner
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Creates the buttons and labels them 
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *btn_register = gtk_button_new_with_label("Register Car");
    GtkWidget *btn_status = gtk_button_new_with_label("Check Status");
    GtkWidget *btn_receipt = gtk_button_new_with_label("Generate Receipt");
    GtkWidget *btn_list = gtk_button_new_with_label("List of Cars");

    // Links the functions to be executed by the button when clicked
    g_signal_connect(btn_register, "clicked", G_CALLBACK(on_register_car_clicked), NULL);
    g_signal_connect(btn_status, "clicked", G_CALLBACK(on_check_status_clicked), NULL);
    g_signal_connect(btn_receipt, "clicked", G_CALLBACK(on_generate_receipt_clicked), NULL);
    g_signal_connect(btn_list, "clicked", G_CALLBACK(on_list_clicked), NULL);
    
    // Adds all the buttons to the window
    gtk_box_pack_start(GTK_BOX(vbox), btn_register, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btn_status, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btn_receipt, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btn_list, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

// Save car data
// This function executes when 
void save_car_data(GtkWidget *button, gpointer user_data) {
    GtkWidget *window = GTK_WIDGET(user_data);

    // gets the data entered by the user
    const char *name = gtk_entry_get_text(GTK_ENTRY(entry_name));
    const char *number = gtk_entry_get_text(GTK_ENTRY(entry_number));
    const char *repairs = gtk_entry_get_text(GTK_ENTRY(entry_repairs));
    const char *cost = gtk_entry_get_text(GTK_ENTRY(entry_cost));

    // Check if any field is empty (error checking)
    if (strlen(name) == 0 || strlen(number) == 0 || strlen(repairs) == 0 || strlen(cost) == 0) {
        g_print("All fields are required!\n");
        return;
    }

    if (carCount >= MAX_CARS) {
        g_print("Car list full!\n");
        return;
    }

    // Appends the data to the array
    strcpy(carList[carCount].carName, name);
    strcpy(carList[carCount].carNumber, number);
    strcpy(carList[carCount].repairs, repairs);
    strcpy(carList[carCount].cost, cost);
    strcpy(carList[carCount].status, "in queue");

    g_print("Car registered: %s (%s)\n", name, number);

    // Increments the count for the next entry
    carCount++;

    gtk_widget_destroy(window); 
}

// Create Register Car window
static void on_register_car_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window, *grid, *btn_submit;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Register Car");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    // Creates text for labels
    GtkWidget *label_name = gtk_label_new("Car Name:");
    GtkWidget *label_number = gtk_label_new("Car Number:");
    GtkWidget *label_repairs = gtk_label_new("Repairs (comma separated):");
    GtkWidget *label_cost = gtk_label_new("Costs (comma separated):");

    // Creates text inputs 
    entry_name = gtk_entry_new();
    entry_number = gtk_entry_new();
    entry_repairs = gtk_entry_new();
    entry_cost = gtk_entry_new();

    // Creates button to submit and when clicked calls save_car_data() func
    btn_submit = gtk_button_new_with_label("Submit");
    g_signal_connect(btn_submit, "clicked", G_CALLBACK(save_car_data), window);

    // Give the labels and the input areas there positions
    gtk_grid_attach(GTK_GRID(grid), label_name, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_name, 1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), label_number, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_number, 1, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), label_repairs, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_repairs, 1, 2, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), label_cost, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_cost, 1, 3, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), btn_submit, 0, 4, 2, 1);

    // Packs everything together and then displays the window
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_show_all(window);
}

void on_check_status_clicked(GtkWidget *widget, gpointer data) {

    GtkWidget *status_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(status_window), "Check Car Status");
    gtk_window_set_default_size(GTK_WINDOW(status_window), 400, 300);
    gtk_container_set_border_width(GTK_CONTAINER(status_window), 10);

    // To stack widgets top to bottom 
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(status_window), vbox);

    GtkWidget *label = gtk_label_new("Enter Car Number:");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    GtkWidget *entry_number = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry_number, FALSE, FALSE, 0);

    GtkWidget *label_info = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), label_info, FALSE, FALSE, 0);

    // Creates a drop down menu
    GtkWidget *combo_status = gtk_combo_box_text_new();
    // Adds options 
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_status), "in queue");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_status), "in process");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_status), "ready");

    gtk_box_pack_start(GTK_BOX(vbox), combo_status, FALSE, FALSE, 0);
    //Disabled for now
    gtk_widget_set_sensitive(combo_status, FALSE);

    GtkWidget *btn_save = gtk_button_new_with_label("Save");
    gtk_box_pack_start(GTK_BOX(vbox), btn_save, FALSE, FALSE, 0);
    //Disabled for now
    gtk_widget_set_sensitive(btn_save, FALSE);

    GtkWidget *btn_search = gtk_button_new_with_label("Search");
    gtk_box_pack_start(GTK_BOX(vbox), btn_search, FALSE, FALSE, 0);

    // Pack widgets into struct
    StatusWidgets *widgets = g_malloc(sizeof(StatusWidgets));
    widgets->entry_number = entry_number;
    widgets->label_info = label_info;
    widgets->combo_status = combo_status;
    widgets->btn_save = btn_save;
    widgets->window = status_window;
    widgets->found_index = -1;

    g_signal_connect(btn_search, "clicked", G_CALLBACK(on_search_clicked), widgets);
    g_signal_connect(btn_save, "clicked", G_CALLBACK(on_save_status_clicked), widgets);

    gtk_widget_show_all(status_window);
}

void on_search_clicked(GtkWidget *widget, gpointer data) {
    StatusWidgets *widgets = (StatusWidgets *)data;

    // Gets the car number form the struct
    const gchar *car_num = gtk_entry_get_text(GTK_ENTRY(widgets->entry_number));

    // Iterates and searches for the data (linear search)
    for (int i = 0; i < carCount; i++) {
        if (strcmp(carList[i].carNumber, car_num) == 0) { // Main logic which compares the entered car no. with the current car no. at index i
            char info[200];
            snprintf(info, sizeof(info), "Name: %s\nVehicle Number: %s", carList[i].carName, carList[i].carNumber);
            gtk_label_set_text(GTK_LABEL(widgets->label_info), info);

            // Enables the dropdown menu and the save button
            gtk_widget_set_sensitive(widgets->combo_status, TRUE);
            gtk_widget_set_sensitive(widgets->btn_save, TRUE);

            // Set dropdown index
            if (strcmp(carList[i].status, "in queue") == 0)
                gtk_combo_box_set_active(GTK_COMBO_BOX(widgets->combo_status), 0);
            else if (strcmp(carList[i].status, "in process") == 0)
                gtk_combo_box_set_active(GTK_COMBO_BOX(widgets->combo_status), 1);
            else
                gtk_combo_box_set_active(GTK_COMBO_BOX(widgets->combo_status), 2);

            widgets->found_index = i;
            return;
        }
    }
    // Gets displayed if the data is not found 
    gtk_label_set_text(GTK_LABEL(widgets->label_info), "Car not found.");
}

void on_save_status_clicked(GtkWidget *widget, gpointer data) {
    //You handed someone a box (void *), and now you're telling them:
    //Hey, that box actually contains a StatusWidgets struct. Please treat it like one.
    StatusWidgets *widgets = (StatusWidgets *)data;

    const gchar *new_status = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widgets->combo_status));
    if (new_status) {
        //Gets the new status and saves it
        strncpy(carList[widgets->found_index].status, new_status, sizeof(carList[widgets->found_index].status) - 1);
        gtk_widget_destroy(widgets->window);
    }
}

void on_generate_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **widgets = (GtkWidget **)data;
    GtkWidget *entry_number = widgets[0];
    GtkWidget *text_view = widgets[1];

    const gchar *car_num = gtk_entry_get_text(GTK_ENTRY(entry_number));
    struct Car foundCar;
    int found = 0;

    for (int i = 0; i < carCount; i++) {
        if (strcmp(carList[i].carNumber, car_num) == 0) {
            foundCar = carList[i];
            found = 1;
            break;
        }
    }

    if (!found) {
        gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view)), "Car not found.", -1);
        return;
    }

    // Make safe copies
    char repairs_copy[100], cost_copy[100];
    strcpy(repairs_copy, foundCar.repairs);
    strcpy(cost_copy, foundCar.cost);

    // Arrays to hold tokens
    char *repair_parts[20], *cost_parts[20];
    int repair_count = 0, cost_count = 0;

    // Split repairs
    char *token = strtok(repairs_copy, ","); // Function to split string
    while (token != NULL && repair_count < 20) {
        repair_parts[repair_count++] = token;
        token = strtok(NULL, ","); // Tells func to continue where it left off
    }

    // Split costs
    token = strtok(cost_copy, ",");
    while (token != NULL && cost_count < 20) {
        cost_parts[cost_count++] = token;
        token = strtok(NULL, ",");
    }

    // Build receipt
    char receipt[1024] = "";
    char linebuf[128];
    int total = 0;

    snprintf(receipt, sizeof(receipt),
             "Name: %s\nCar Number: %s\nStatus: %s\n\nRepairs:\n",
             foundCar.carName, foundCar.carNumber, foundCar.status);

    int count = (repair_count < cost_count) ? repair_count : cost_count;
    for (int i = 0; i < count; i++) {
        int c = atoi(cost_parts[i]);
        total += c;
        snprintf(linebuf, sizeof(linebuf), "- %s : ₹%d\n", repair_parts[i], c);
        strcat(receipt, linebuf);
    }

    snprintf(linebuf, sizeof(linebuf), "\nTotal: ₹%d", total);
    strcat(receipt, linebuf);

    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view)), receipt, -1);
}

void on_generate_receipt_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Generate Receipt");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    GtkWidget *entry_number = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_number), "Enter Car Number");

    GtkWidget *btn_generate = gtk_button_new_with_label("Generate");

    GtkWidget *text_view = gtk_text_view_new();
    // The final recept will be displayed but will not be editable by the user
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);

    gtk_box_pack_start(GTK_BOX(vbox), entry_number, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btn_generate, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget **widgets = g_new(GtkWidget *, 2);
    widgets[0] = entry_number;
    widgets[1] = text_view;

    g_signal_connect(btn_generate, "clicked", G_CALLBACK(on_generate_clicked), widgets);

    gtk_widget_show_all(window);
}

void on_list_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *list_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(list_window), "All Registered Cars");
    gtk_window_set_default_size(GTK_WINDOW(list_window), 800, 400);
    gtk_container_set_border_width(GTK_CONTAINER(list_window), 10);

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(list_window), scrolled_window);

    // Create the list store (5 columns: name, number, repairs, cost, status)
    GtkListStore *store = gtk_list_store_new(5,
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    // Iterates though the data and displays it
    for (int i = 0; i < carCount; i++) {
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            0, carList[i].carName,
            1, carList[i].carNumber,
            2, carList[i].repairs,
            3, carList[i].cost,
            4, carList[i].status,
            -1);
    }

    GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);

    // Free store automatically when done (free())
    g_object_unref(store);

    // Add columns to the TreeView / Give names 
    const char *titles[] = {"Name", "Number", "Repairs", "Cost", "Status"};
    for (int i = 0; i < 5; i++) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
            titles[i], renderer, "text", i, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    }

    gtk_widget_show_all(list_window);
}
