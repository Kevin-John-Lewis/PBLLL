#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define CAT_SIZE 11
#define ITEM_SIZE 10

struct Item {
    char name[40];
    int score;
};

struct Category {
    char name[25];
    int totalScore;
    struct Item items[ITEM_SIZE];
};

struct Category table[CAT_SIZE];

void toLower(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = tolower(s[i]);
}

const char* trendLabel(int score) {
    if (score >= 90) return "🔥 VIRAL";
    if (score >= 75) return "📈 TRENDING";
    if (score >= 60) return "👍 POPULAR";
    return "🙂 EMERGING";
}

int hashCategory(const char *cat) {
    const char *cats[] = {
        "toys","technology","medical","automobile","food","destination",
        "entertainment","fitness","education","finance","gaming"
    };
    for (int i = 0; i < CAT_SIZE; i++)
        if (strcmp(cat, cats[i]) == 0) return i;
    return -1;
}

void updateItem(struct Item *items, const char *name, int score) {
    for (int i = 0; i < ITEM_SIZE; i++) {
        if (items[i].score == 0) {
            strcpy(items[i].name, name);
            items[i].score = score;
            return;
        }
        if (strcmp(items[i].name, name) == 0) {
            items[i].score += score;
            return;
        }
    }
}

void updateCategory(const char *cat, const char *item, int score) {
    int idx = hashCategory(cat);
    if (idx == -1) return;

    table[idx].totalScore += score;
    updateItem(table[idx].items, item, score);
}

void sortItems(struct Item *items) {
    struct Item t;
    for (int i = 0; i < ITEM_SIZE - 1; i++)
        for (int j = i + 1; j < ITEM_SIZE; j++)
            if (items[j].score > items[i].score) {
                t = items[i];
                items[i] = items[j];
                items[j] = t;
            }
}

int main() {

    /* FIXED HERE */
    const char *names[] = {
        "TOYS","TECHNOLOGY","MEDICAL","AUTOMOBILE","FOOD","DESTINATION",
        "ENTERTAINMENT","FITNESS","EDUCATION","FINANCE","GAMING"
    };

    for (int i = 0; i < CAT_SIZE; i++) {
        strcpy(table[i].name, names[i]);
        table[i].totalScore = 0;
        for (int j = 0; j < ITEM_SIZE; j++)
            table[i].items[j].score = 0;
    }

    updateCategory("toys","PinkBear",70);
    updateCategory("toys","TalkingCactus",65);
    updateCategory("toys","LegoSet",60);

    updateCategory("technology","iPhone17",95);
    updateCategory("technology","VisionPro",85);
    updateCategory("technology","GamingLaptop",80);

    updateCategory("medical","Paracetamol",75);
    updateCategory("medical","Insulin",70);
    updateCategory("medical","VitaminC",65);

    updateCategory("automobile","TataSafari",90);
    updateCategory("automobile","RoyalEnfield",82);
    updateCategory("automobile","TeslaModel3",78);

    updateCategory("food","ButterChicken",92);
    updateCategory("food","Biryani",85);
    updateCategory("food","Pizza",80);

    updateCategory("destination","Japan",95);
    updateCategory("destination","Paris",90);
    updateCategory("destination","Dubai",85);

    updateCategory("entertainment","Pushpa2",94);
    updateCategory("entertainment","NetflixSeries",88);
    updateCategory("entertainment","AnimeMerch",76);

    updateCategory("fitness","ProteinPowder",85);
    updateCategory("fitness","Dumbbells",78);
    updateCategory("fitness","YogaMat",65);

    updateCategory("education","DSA",88);
    updateCategory("education","PythonCourse",82);
    updateCategory("education","AIJobs",79);

    updateCategory("finance","Bitcoin",91);
    updateCategory("finance","MutualFunds",80);
    updateCategory("finance","SIP",72);

    updateCategory("gaming","GTA6",96);
    updateCategory("gaming","BGMI",85);
    updateCategory("gaming","PlayStation5",83);

    printf("\n TREND CHECKER REPORT \n\n");

    for (int i = 0; i < CAT_SIZE; i++) {
        printf("CATEGORY: %s (%s)\n",
               table[i].name,
               trendLabel(table[i].totalScore / 3));

        sortItems(table[i].items);

        for (int j = 0; j < 3 && table[i].items[j].score > 0; j++) {
            printf("  %d. %s → %s\n",
                   j + 1,
                   table[i].items[j].name,
                   trendLabel(table[i].items[j].score));
        }
        printf("\n");
    }

    return 0;
}