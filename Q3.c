#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char city[15], hottest_city[15];
    float temp, new_temp, max_temp = -999.0;
    int city_no;

    fp = fopen("temperature.txt", "wb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        printf("Enter city %d name and temperature: ", i + 1);
        scanf("%s %f", city, &temp);
        fprintf(fp, "%-10s %5.1f\n", city, temp);
    }
    fclose(fp);

    fp = fopen("temperature.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("City number: ");
    scanf("%d", &city_no);
    fseek(fp, (city_no - 1) * 17, SEEK_SET);
    fscanf(fp, "%s %f", city, &temp);
    printf("%s %.1f\n", city, temp);

    printf("City number to correct: ");
    scanf("%d", &city_no);
    printf("New temperature: ");
    scanf("%f", &new_temp);

    fseek(fp, (city_no - 1) * 17, SEEK_SET);
    fscanf(fp, "%s %f", city, &temp);

    fseek(fp, (city_no - 1) * 17, SEEK_SET);
    fprintf(fp, "%-10s %5.1f\n", city, new_temp);
    fflush(fp);
    printf("%s updated to %.1f\n", city, new_temp);

    rewind(fp);
    while (fscanf(fp, "%s %f", city, &temp) == 2) {
        if (temp > max_temp) {
            max_temp = temp;
            strcpy(hottest_city, city);
        }
    }

    printf("Hottest city: %s (%.1f)\n", hottest_city, max_temp);
    fclose(fp);

    return 0;
}