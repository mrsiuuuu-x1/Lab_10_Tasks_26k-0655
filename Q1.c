#include <stdio.h>

int main() {
    FILE *fp;
    int item_no, qty, stock, id;
    char name[25];
    float price, total = 0.0;

    fp = fopen("items.txt", "wb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 1, "Rice", 250.00, 40);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 2, "Sugar", 160.00, 25);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 3, "Milk", 220.00, 30);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 4, "CookingOil", 560.00, 12);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 5, "Tea", 450.00, 18);
    fclose(fp);

    fp = fopen("items.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    while (1) {
        printf("Item no: ");
        scanf("%d", &item_no);
        if (item_no == 0) {
            break;
        }
        printf("Quantity: ");
        scanf("%d", &qty);

        fseek(fp, (item_no - 1) * 42, SEEK_SET);
        fscanf(fp, "%d %s %f %d", &id, name, &price, &stock);

        if (stock >= qty) {
            float line_total = qty * price;
            printf("%-12s %d x %.2f = %.2f\n", name, qty, price, line_total);
            total += line_total;
            stock -= qty;

            fseek(fp, (item_no - 1) * 42, SEEK_SET);
            fprintf(fp, "%-4d %-20s %9.2f %5d\n", id, name, price, stock);
            fflush(fp);
        } else {
            printf("Only %d %s in stock\n", stock, name);
        }
    }

    printf("Total bill: %.2f\n", total);
    fclose(fp);

    return 0;
}