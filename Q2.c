#include <stdio.h>

int main() {
    FILE *fp;
    int roll, attended, r, leave_lectures;
    char name[20];

    fp = fopen("attendance.txt", "wb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "%-3d %-15s %3d\n", 1, "Ayesha", 18);
    fprintf(fp, "%-3d %-15s %3d\n", 2, "Bilal", 14);
    fprintf(fp, "%-3d %-15s %3d\n", 3, "Hamza", 20);
    fprintf(fp, "%-3d %-15s %3d\n", 4, "Sana", 12);
    fprintf(fp, "%-3d %-15s %3d\n", 5, "Zainab", 16);
    fclose(fp);

    fp = fopen("attendance.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Roll number: ");
    scanf("%d", &r);

    fseek(fp, (r - 1) * 24, SEEK_SET);
    fscanf(fp, "%d %s %d", &roll, name, &attended);

    float percent = (attended / 20.0) * 100.0;
    printf("%s: %d / 20 (%.1f%%)", name, attended, percent);
    if (percent < 75.0) {
        printf(" Short attendance");
    }
    printf("\n");

    printf("Roll number for leave: ");
    scanf("%d", &r);
    printf("Lectures: ");
    scanf("%d", &leave_lectures);

    fseek(fp, (r - 1) * 24, SEEK_SET);
    fscanf(fp, "%d %s %d", &roll, name, &attended);

    attended += leave_lectures;
    percent = (attended / 20.0) * 100.0;

    fseek(fp, (r - 1) * 24, SEEK_SET);
    fprintf(fp, "%-3d %-15s %3d\n", roll, name, attended);
    fflush(fp);

    printf("%s: now %d / 20 (%.1f%%)\n", name, attended, percent);

    fseek(fp, -24, SEEK_END);
    fscanf(fp, "%d %s %d", &roll, name, &attended);
    printf("Last record: %d %s %d\n", roll, name, attended);

    fclose(fp);
    return 0;
}