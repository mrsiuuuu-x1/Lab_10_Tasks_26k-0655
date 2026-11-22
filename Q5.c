#include <stdio.h>

int main() {
    FILE *fp;
    char category[20];
    float amount;
    int entry_no;

    fp = fopen("expenses.txt", "wb");
    fprintf(fp, "%-12s %9.2f\n", "Food", 1200.00);
    fprintf(fp, "%-12s %9.2f\n", "Transport", 500.00);
    fprintf(fp, "%-12s %9.2f\n", "Books", 850.00);
    fprintf(fp, "%-12s %9.2f\n", "Mobile", 300.00);
    fclose(fp);

    printf("Category: ");
    scanf("%s", category);
    printf("Amount: ");
    scanf("%f", &amount);

    fp = fopen("expenses.txt", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(fp, "%-12s %9.2f\n", category, amount);
    fclose(fp);

    fp = fopen("expenses.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    char cat1[20], cat2[20];
    float amt1, amt2;
    fseek(fp, -2 * 23, SEEK_END);
    fscanf(fp, "%s %f", cat1, &amt1);
    fscanf(fp, "%s %f", cat2, &amt2);
    printf("Latest two: %s %.2f, %s %.2f\n", cat1, amt1, cat2, amt2);

    printf("Entry to fix: ");
    scanf("%d", &entry_no);
    printf("Correct amount: ");
    scanf("%f", &amount);

    float old_amt;
    fseek(fp, (entry_no - 1) * 23, SEEK_SET);
    fscanf(fp, "%s %f", category, &old_amt);

    fseek(fp, (entry_no - 1) * 23, SEEK_SET);
    fprintf(fp, "%-12s %9.2f\n", category, amount);
    fflush(fp);

    rewind(fp);
    float total = 0.0;
    while (fscanf(fp, "%s %f", category, &amount) == 2) {
        printf("%s %.2f\n", category, amount);
        total += amount;
    }
    printf("Total: %.2f\n", total);

    fclose(fp);
    return 0;
}