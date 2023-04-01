#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> // Added to use toupper function
#pragma warning(disable : 4996)

#define MAX_RECORDS 100
#define MAX_ID_LENGTH 10
#define MAX_TITLE_LENGTH 150
#define MAX_AUTHOR_LENGTH 300
#define MAX_DATETIME_LENGTH 15

// Function prototypes
void function_v(const char* filename, char*** ids, char*** titles, char*** authors, char*** datetimes, int* records_count, bool* file_opened);
void function_n(const char* filename, char*** ids, char*** titles, char*** authors, char*** datetimes, int* records_count, bool* file_opened);
void function_p(char*** ids, char*** titles, char*** authors, char*** datetimes, int* records_count, bool* file_opened);
void function_s(char** ids, char** titles, char** authors, char** datetimes, int records_count, bool file_opened); // modified prototype
int function_w(char** authors, int records_count, char*** names);
void function_h(char** datetimes, char** pres_types, int records_count);
void function_menu();
void function_z(char*** ids_ptr, int* records_count, char* titles);
void function_d(char*** datetimes, int records_count);
void function_k(char*** ids, char*** titles, char*** authors, char*** datetimes, int records_count);    


int main() {
    char command;

    // Dynamic arrays for records
    char** ids = NULL;
    char** titles = NULL;
    char** authors = NULL;
    char** datetimes = NULL;

    // Number of records
    int records_count = 0;

    bool file_opened = false;

    while (true) {
        printf("Enter command: ");
        scanf(" %c", &command);

        switch (command) {
        case 'v':
            function_v("KonferencnyZoznam.txt", &ids, &titles, &authors, &datetimes, &records_count, &file_opened);
            break;
        case 'n':
            function_n("KonferencnyZoznam.txt", &ids, &titles, &authors, &datetimes, &records_count, &file_opened);
            break;
        case 'p':
            function_p(&ids, &titles, &authors, &datetimes, &records_count, &file_opened); // Add a new record
            break;
        case 's':
            function_s(ids, titles, authors, datetimes, records_count, file_opened);
            break;
        case 'w':
        {
            int names_count;
            char*** names = NULL;
            names_count = function_w(authors, records_count, &names);
            break;
        }
        case 'h':
        {
            char** pres_types = malloc(records_count * sizeof(char*));
            for (int i = 0; i < records_count; i++) {
                pres_types[i] = datetimes[i] + 10;
            }
            function_h(datetimes, pres_types, records_count);
            free(pres_types);
            break;
        }
        case 'm':
            function_menu(); // help
            break;
        case 'z':
            function_z(&ids, &records_count, titles);
            break;
        case 'd':
            function_d(datetimes, records_count); //
            break;
        case 'k':
            function_k(&ids, &titles, &authors, &datetimes, records_count); // 
            return 0;
        default:
            printf("Invalid command.\n");
            break;
        }
    }

    return 0;
}



// Open file and read records into dynamic arrays
void function_v(const char* filename, char*** ids, char*** titles, char*** authors, char*** datetimes, int* records_count, bool* file_opened) {
    if (!*file_opened) {
        FILE* file = fopen(filename, "r");

        if (file == NULL) {
            printf("Neotvoreny subor.\n");
            return;
        }

        // Deallocate previous arrays if they exist
        if (*records_count > 0) {
            for (int i = 0; i < *records_count; i++) {
                free((*ids)[i]);
                free((*titles)[i]);
                free((*authors)[i]);
                free((*datetimes)[i]);
            }
            free(*ids);
            free(*titles);
            free(*authors);
            free(*datetimes);
        }

        // Count records and allocate memory for the arrays
        *records_count = 0;
        char id[64], title[256], author[256], datetime[64];
        while (fscanf(file, " %[^\n] %[^\n] %[^\n] %[^\n]", id, title, author, datetime) == 4) {
            (*records_count)++;
        }
        fclose(file);

        *ids = malloc(*records_count * sizeof(char*));
        *titles = malloc(*records_count * sizeof(char*));
        *authors = malloc(*records_count * sizeof(char*));
        *datetimes = malloc(*records_count * sizeof(char*));

        // Read the data from the file and populate the arrays
        file = fopen(filename, "r");
        for (int i = 0; i < *records_count; i++) {
            fscanf(file, " %[^\n]", id);
            fscanf(file, " %[^\n]", title);
            fscanf(file, " %[^\n]", author);
            fscanf(file, " %[^\n]", datetime);

            (*ids)[i] = strdup(id);
            (*titles)[i] = strdup(title);
            (*authors)[i] = strdup(author);
            (*datetimes)[i] = strdup(datetime);
        }
        fclose(file);
        *file_opened = true;
    }

    if (*records_count > 0) {
        for (int i = 0; i < *records_count; i++) {
            printf("ID prispevku: %s\n", (*ids)[i]);
            printf("Nazov prispevku: %s\n", (*titles)[i]);
            printf("Mena autorov:");
            char* author_string = strdup((*authors)[i]);
            char* author = strtok(author_string, "#");
            while (author != NULL) {
                if (strcmp(author, "A") != 0) {
                    printf(" %s", author);
                }
                author = strtok(NULL, "#");
            }
            printf("\n");
            free(author_string);
            printf("Datum a cas: %4.4s-%2.2s-%2.2s %2.2s:%2.2s\n", (*datetimes)[i], (*datetimes)[i] + 4, (*datetimes)[i] + 6, (*datetimes)[i] + 8, (*datetimes)[i] + 10);
            printf("\n");
        }
    }
}



// Print number of records
void function_n(const char* filename, char*** ids, char*** titles, char*** authors, char*** datetimes, int* records_count, bool* file_opened) {
    if (!*file_opened) {
        printf("Neotvoreny subor.\n");
        return;
    }

    // Deallocate previous arrays if they exist
    if (*records_count > 0) {
        for (int i = 0; i < *records_count; i++) {
            free((*ids)[i]);
            free((*titles)[i]);
            free((*authors)[i]);
            free((*datetimes)[i]);
        }
        free(*ids);
        free(*titles);
        free(*authors);
        free(*datetimes);
    }

    // Count records and allocate memory for the arrays
    FILE* file = fopen(filename, "r");
    *records_count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        (*records_count)++;
    }
    fclose(file);

    *ids = malloc(*records_count * sizeof(char*));
    *titles = malloc(*records_count * sizeof(char*));
    *authors = malloc(*records_count * sizeof(char*));
    *datetimes = malloc(*records_count * sizeof(char*));

    // Read the data from the file and populate the arrays
    file = fopen(filename, "r");
    rewind(file); // Add this line to fix the issue
    for (int i = 0; i < *records_count; i++) {
        char id[64], title[256], author[256], datetime[64];
        fscanf(file, " %[^\n]", id);
        fscanf(file, " %[^\n]", title);
        fscanf(file, " %[^\n]", author);
        fscanf(file, " %[^\n]", datetime);

        (*ids)[i] = strdup(id);
        (*titles)[i] = strdup(title);
        (*authors)[i] = strdup(author);
        (*datetimes)[i] = strdup(datetime);
    }
    fclose(file);

    printf("Nacitane data.\n");
}




void function_p(char*** ids, char*** titles, char*** authors, char*** datetimes, int* records_count, bool* file_opened) {
    if (!*file_opened) {
        printf("Error: File not opened. You cannot add data.\n");
        return;
    }
    char id[MAX_ID_LENGTH + 1];
    char title[MAX_TITLE_LENGTH + 1];
    char author[MAX_AUTHOR_LENGTH + 1];
    char datetime[MAX_DATETIME_LENGTH + 1];

    // Read user input
    printf("Enter ID: ");
    scanf("%s", id);
    getchar(); // Consume newline
    printf("Enter Title: ");
    fgets(title, MAX_TITLE_LENGTH, stdin);
    title[strcspn(title, "\n")] = 0; // Remove newline character
    printf("Enter Author: ");
    fgets(author, MAX_AUTHOR_LENGTH, stdin);
    author[strcspn(author, "\n")] = 0; // Remove newline character
    printf("Enter Datetime: ");
    scanf("%s", datetime);

    // Reallocate memory for new record
    if (*ids != NULL) {
        *ids = realloc(*ids, (*records_count + 1) * sizeof(char*));
    }
    if (*titles != NULL) {
        *titles = realloc(*titles, (*records_count + 1) * sizeof(char*));
    }
    if (*authors != NULL) {
        *authors = realloc(*authors, (*records_count + 1) * sizeof(char*));
    }
    if (*datetimes != NULL) {
        *datetimes = realloc(*datetimes, (*records_count + 1) * sizeof(char*));
    }

    // Allocate memory for new record attributes
    (*ids)[*records_count] = malloc(MAX_ID_LENGTH + 1);
    (*titles)[*records_count] = malloc(MAX_TITLE_LENGTH + 1);
    (*authors)[*records_count] = malloc(MAX_AUTHOR_LENGTH + 1);
    (*datetimes)[*records_count] = malloc(MAX_DATETIME_LENGTH + 1);

    // Copy new record attributes
    strcpy((*ids)[*records_count], id);
    strcpy((*titles)[*records_count], title);
    strcpy((*authors)[*records_count], author);
    strcpy((*datetimes)[*records_count], datetime);

    // Increment records count
    (*records_count)++;

    printf("Zaznam sa podarilo pridat.\n");
}



void function_s(char** ids, char** titles, char** authors, char** datetimes, int records_count, bool file_opened) { // modified function signature
    if (!file_opened) {
        printf("Error: File not opened. You cannot use this function.\n");
        return;
    }

    char datetime[MAX_DATETIME_LENGTH + 1];
    char date[MAX_DATETIME_LENGTH + 1];
    char type[3];
    printf("Enter date and type (YYYYMMDD, UP, UD, PP, or PD): ");
    scanf("%s%s", date, type);
    if (strcmp(type, "UP") != 0 && strcmp(type, "UD") != 0 && strcmp(type, "PP") != 0 && strcmp(type, "PD") != 0) {
        printf("Invalid type.\n");
        return;
    }

    // Construct datetime string from date and type
    sprintf(datetime, "%s%s0000", date, type);

    bool found = false;
    for (int i = 0; i < records_count; i++) {
        char author_string[MAX_AUTHOR_LENGTH + 1];
        strcpy(author_string, authors[i]); // Make a copy of the author string, so that strtok doesn't modify the original
        char* author = strtok(author_string, "|"); // Use "|" as the delimiter
        while (author != NULL) {
            if (strcmp(author, "A") != 0) {
                printf("%s %s %s\n", datetimes[i] + 8, author, titles[i]); // Print the author without modifying it
                found = true;
            }
            author = strtok(NULL, "|");
        }
    }
    if (!found) {
        printf("Pre dany vstup neexistuju zaznamy.\n");
    }
}



int function_w(char** authors, int records_count, char*** names) {
    if (authors == NULL) {
        printf("Polia nie su vytvorene.\n");
        return 0;
    }

    // Free the previous names array if it exists
    if (*names != NULL) {
        for (int i = 0; (*names)[i] != NULL; i++) {
            free((*names)[i]);
        }
        free(*names);
    }

    *names = malloc(records_count * 10 * sizeof(char*)); // Allocate memory with an arbitrary maximum number of names
    int names_count = 0;

    // Process authors and populate the names array
    for (int i = 0; i < records_count; i++) {
        char* author = strdup(authors[i]);
        char* token = strtok(author, "#?#");
        while (token != NULL) {
            char* name = strtok(token, "AK");
            (*names)[names_count] = strdup(name);
            for (int j = 0; j < strlen((*names)[names_count]); j++) {
                (*names)[names_count][j] = toupper((*names)[names_count][j]);
            }
            names_count++;
            token = strtok(NULL, "#?#");
        }
        free(author);
    }

    (*names)[names_count] = NULL; // Add a NULL pointer at the end of the array to indicate the end

    // Print the names
    for (int i = 0; i < names_count; i++) {
        printf("%s\n", (*names)[i]);
    }

    return names_count;
}



void function_d(char*** records, int records_count) {
    if (records == NULL || *records == NULL) { // check if the pointer or the array is NULL
        printf("Polia nie su vytvorene.\n");
        return;
    }

    for (int i = 0; i < records_count; i++) {
        if ((*records)[i] != NULL) { // check if the record pointer is not NULL
            free((*records)[i]); // free memory for each record
            (*records)[i] = NULL; // set the pointer to NULL to indicate that the memory is deallocated
        }
    }
    free(*records); // free memory for the array of records
    *records = NULL; // set the pointer to NULL to indicate that the array is deallocated

    printf("Polia boli vymazane.\n");
}

void function_z(char*** ids_ptr, int* records_count, char* titles) {
    char** ids = *ids_ptr; // dereference the pointer to get the original pointer

    if (!ids || !records_count) {               // check if arrays are initialized
        printf("Polia nie su vytvorene.\n");
        return;
    }

    if (!titles) { // check if the titles parameter is null
        printf("Nazov prispevku je neplatny.\n");
        return;
    }

    int deleted_count = 0;                      // initialize count of deleted records

    for (int i = 0; i < *records_count; i++) {
        if (ids[i] && strcmp(ids[i], titles) == 0) {        // check if record matches the given name
            free(ids[i]);                       // free memory allocated for the record
            ids[i] = NULL;                      // set the pointer to null
            deleted_count++;                    // increment count of deleted records
        }
    }

    int new_count = *records_count - deleted_count;  // calculate new count of records
    char** new_ids = realloc(ids, new_count * sizeof(char*));  // reallocate memory for new array

    if (new_ids) {                              // check if reallocation was successful
        *ids_ptr = new_ids;                     // update pointer to the new array
        *records_count = new_count;             // update count of records
        printf("Vymazalo sa: %d zaznamov !\n", deleted_count);
    }
    else {
        printf("Chyba pri realokacii pola!\n");
    }
}


void function_menu() {
    printf("List of commands:\n");
    printf("v - Open and read file\n");
    printf("n - Print number of records\n");
    printf("p - Add records\n");
    printf("s - Print the records presentation based on date\n");
    printf("w - Print record with specific Author\n");
    printf("z - Change first 3 characters of all IDs\n");
    printf("d - Print number of records for specific date\n");
    printf("k - Close file and terminate program\n");
}

void function_h(char** datetimes, char** pres_types, int records_count) {
    if (!datetimes || !pres_types) {
        printf("Polia nie su vytvorene.\n");
        return;
    }

    int histogram[6][4] = { 0 };

    for (int i = 0; i < records_count; i++) {
        int hour = (datetimes[i][8] - '0') * 10 + (datetimes[i][9] - '0');
        int index = (hour - 8) / 2;

        if (index >= 0 && index < 6) {
            if (strcmp(pres_types[i], "UP") == 0) {
                histogram[index][0]++;
            }
            else if (strcmp(pres_types[i], "UD") == 0) {
                histogram[index][1]++;
            }
            else if (strcmp(pres_types[i], "PP") == 0) {
                histogram[index][2]++;
            }
            else if (strcmp(pres_types[i], "PD") == 0) {
                histogram[index][3]++;
            }
        }
    }

    printf("Histogram of presentations:\n");
    printf("Time of day | UP | UD | PP | PD\n");
    printf("------------+----+----+----+----\n");
    for (int i = 0; i < 6; i++) {
        printf("%02d:00-%02d:00 | %2d | %2d | %2d | %2d\n", 8 + i * 2, 10 + i * 2, histogram[i][0], histogram[i][1], histogram[i][2], histogram[i][3]);
    }
}




// Close file and release memory for dynamic arrays
void function_k(char*** ids, char*** titles, char*** authors, char*** datetimes, int records_count) {
    if (*ids != NULL) {
        for (int i = 0; i < records_count; i++) {
            free((*ids)[i]);
            free((*titles)[i]);
            free((*authors)[i]);
            free((*datetimes)[i]);
        }
        free(*ids);
        free(*titles);
        free(*authors);
        free(*datetimes);
    }

    printf("Program terminated.\n");
}
