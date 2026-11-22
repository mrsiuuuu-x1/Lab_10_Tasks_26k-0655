#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    int room_no, nights, r_read;
    char status, guest[25], search_name[25];
    float rate;

    fp = fopen("hotel.txt", "wb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for (int i = 101; i <= 110; i++) {
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n", i, 'F', "-", 0, 8000.00);
    }
    fclose(fp);

    fp = fopen("hotel.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for (int attempt = 0; attempt < 2; attempt++) {
        printf("Check-in room: ");
        scanf("%d", &room_no);
        printf("Name: ");
        scanf("%s", guest);
        printf("Nights: ");
        scanf("%d", &nights);

        fseek(fp, (room_no - 101) * 39, SEEK_SET);
        char curr_guest[25];
        int curr_nights;
        fscanf(fp, "%d %c %s %d %f", &r_read, &status, curr_guest, &curr_nights, &rate);

        if (status == 'F') {
            fseek(fp, (room_no - 101) * 39, SEEK_SET);
            fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room_no, 'B', guest, nights, 8000.00);
            fflush(fp);
            printf("Room %d booked\n", room_no);
        } else {
            printf("Room already booked\n");
        }
    }

    char guests[10][21];
    int rooms[10];

    rewind(fp);
    for (int i = 0; i < 10; i++) {
        fscanf(fp, "%d %c %s %d %f", &rooms[i], &status, guests[i], &nights, &rate);
    }

    printf("Search name: ");
    scanf("%s", search_name);

    int found = 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp(guests[i], search_name) == 0) {
            printf("%s is in room %d\n", search_name, rooms[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Guest not found\n");
    }

    printf("Check-out room: ");
    scanf("%d", &room_no);

    fseek(fp, (room_no - 101) * 39, SEEK_SET);
    fscanf(fp, "%d %c %s %d %f", &r_read, &status, guest, &nights, &rate);

    printf("Bill: %d x %.2f = %.2f\n", nights, rate, nights * rate);

    fseek(fp, (room_no - 101) * 39, SEEK_SET);
    fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room_no, 'F', "-", 0, 8000.00);
    fflush(fp);

    fclose(fp);
    return 0;
}