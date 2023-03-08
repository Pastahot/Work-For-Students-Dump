#include <stdio.h>
#include <string.h>

// function to convert a hexadecimal character to its integer value
int hexToInt(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    else {
        return -1;
    }
}

// function to calculate the checksum of an Intel HEX file record
unsigned char calculateChecksum(char* line) {
    int i, sum = 0;

    // iterate over the bytes in the line, skipping the start character ':'
    for (i = 1; i < strlen(line) - 2; i += 2) {
        // convert each pair of hexadecimal characters to an integer value and add it to the sum
        int value = hexToInt(line[i]) * 16 + hexToInt(line[i + 1]);
        sum += value;
    }

    // take the two's complement of the sum and return the lower 8 bits
    return (unsigned char)(~(sum & 0xFF) + 1);
}

int main() {
    char record[] = ":100030000C9445000C9445000C9445000C944500xx";
    printf("Original record: %s\n", record);

    // calculate the checksum for the record
    unsigned char checksum = calculateChecksum(record);

    // replace the last two characters of the record with the checksum in hexadecimal format
    sprintf(&record[strlen(record) - 2], "%02X", checksum);

    printf("Updated record: %s\n", record);

    return 0;
}
