#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define MAX_QUESTIONS 15
#define MAX_OPTIONS 4
typedef struct {
    char question[256];
    char options[MAX_OPTIONS][100];
    char correct;
    char explanation[256];
    int difficulty; 
} QuizQuestion;
typedef struct {
    char name[50];
    int score;
    int level;
} Player;
void clearInputBuffer() {
    while ((getchar()) != '\n');
}
void awardBadge(int score) {
    printf("\n=== PERFORMANCE SUMMARY ===\n");
    if (score >= 80) {
        printf("?? GOLD Badge earned! You're a Clean Sport Champion!\n");
    } else if (score >= 60) {
        printf("?? SILVER Badge earned! Great dedication!\n");
    } else if (score >= 40) {
        printf("?? BRONZE Badge earned! Keep improving!\n");
    } else {
        printf("No badge this time. Stay motivated and try again!\n");
    }
}
void askQuestion(Player *player, QuizQuestion q) {
    char input[10];
    char answer;
    int valid = 0;
    do {
        printf("\n%s\n", q.question);
        int i;
        for (i = 0; i < MAX_OPTIONS; i++) {
            printf("%c. %s\n", 'A' + i, q.options[i]);
        }
        printf("Enter your answer (A-D): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == 1 && toupper(input[0]) >= 'A' && toupper(input[0]) <= 'D') {
            answer = toupper(input[0]);
            valid = 1;
            if (answer == q.correct) {
                printf("? Correct!\n");
                int reward = q.difficulty * 10;
                printf("You earned %d points!\n", reward);
                player->score += reward;
            } else {
                printf("? Wrong! The correct answer is %c\n", q.correct);
            }

            printf("?? Explanation: %s\n", q.explanation);
        } else {
            printf("Invalid input! Please enter a letter A-D.\n");
        }
    } while (!valid);
}
void surpriseBox(Player *player) {
    char input[10];
    int choice = 0;
    int valid = 0;
    do {
        printf("\n?? Choose a number between 1 and 5 for a surprise: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 1 && isdigit(input[0])) {
            choice = input[0] - '0';
            if (choice >= 1 && choice <= 5) {
                valid = 1;
            }
        }

        if (!valid) {
            printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }

    } while (!valid);
    switch (choice) {
        case 1:
            printf("?? Bonus! +10 points!\n");
            player->score += 10;
            break;
        case 2:
            printf("?? You're a clean sport ambassador!\n");
            break;
        case 3:
            printf("?? Joke: Why did the athlete bring string to the race? To tie the score!\n");
            break;
        case 4:
            printf("?? Tip: Always check your supplements with trusted authorities.\n");
            break;
        case 5:
            printf("????? Oops, no bonus. Stay clean and focused!\n");
            break;
    }
    printf("Current Score: %d\n", player->score);
}
void loadQuestions(QuizQuestion questions[]) {
    strcpy(questions[0].question, "1. What is the main goal of anti-doping?");
    strcpy(questions[0].options[0], "Fair play");
    strcpy(questions[0].options[1], "More medals");
    strcpy(questions[0].options[2], "Faster recovery");
    strcpy(questions[0].options[3], "Entertainment");
    questions[0].correct = 'A';
    questions[0].difficulty = 1;
    strcpy(questions[0].explanation, "Anti-doping protects fair competition and athlete health.");
    strcpy(questions[1].question, "2. What does WADA stand for?");
    strcpy(questions[1].options[0], "World Anti-Doping Agency");
    strcpy(questions[1].options[1], "Wide Area Drug Association");
    strcpy(questions[1].options[2], "World Athlete Defense Act");
    strcpy(questions[1].options[3], "World Alliance for Doping Awareness");
    questions[1].correct = 'A';
    questions[1].difficulty = 1;
    strcpy(questions[1].explanation, "WADA is the global body that governs anti-doping in sport.");
    strcpy(questions[2].question, "3. What is EPO?");
    strcpy(questions[2].options[0], "Energy Power Output");
    strcpy(questions[2].options[1], "Endurance Performance Oil");
    strcpy(questions[2].options[2], "A banned performance-enhancing drug");
    strcpy(questions[2].options[3], "Legal supplement");
    questions[2].correct = 'C';
    questions[2].difficulty = 2;
    strcpy(questions[2].explanation, "EPO increases red blood cells and endurance, and is banned.");
    strcpy(questions[3].question, "4. When can doping tests be done?");
    strcpy(questions[3].options[0], "Only after competitions");
    strcpy(questions[3].options[1], "Only if athlete agrees");
    strcpy(questions[3].options[2], "At any time, anywhere");
    strcpy(questions[3].options[3], "Never during rest days");
    questions[3].correct = 'C';
    questions[3].difficulty = 2;
    strcpy(questions[3].explanation, "Random testing ensures fairness and catches cheaters anytime.");
    strcpy(questions[4].question, "5. What is the principle of 'Strict Liability'?");
    strcpy(questions[4].options[0], "Blame coaches for doping");
    strcpy(questions[4].options[1], "Athletes are always responsible for what they take");
    strcpy(questions[4].options[2], "Doping is legal with permission");
    strcpy(questions[4].options[3], "Officials must test all players");
    questions[4].correct = 'B';
    questions[4].difficulty = 3;
    strcpy(questions[4].explanation, "Strict Liability means athletes are responsible for any substance in their body.");
    strcpy(questions[5].question, "BONUS: Can athletes use medicine if it’s prescribed?");
    strcpy(questions[5].options[0], "Yes, if reported and approved");
    strcpy(questions[5].options[1], "No, never");
    strcpy(questions[5].options[2], "Only vitamins");
    strcpy(questions[5].options[3], "Only during events");
    questions[5].correct = 'A';
    questions[5].difficulty = 2;
    strcpy(questions[5].explanation, "Therapeutic Use Exemptions (TUEs) allow certain medicines with approval.");
}
void startQuiz(Player *player) {
    QuizQuestion questions[MAX_QUESTIONS];
    loadQuestions(questions);
    printf("\nLet's begin your Clean Sport Journey!\n");
    int i;
    for (i = 0; i < 5; i++) {
        askQuestion(player, questions[i]);
    }
    if (player->score >= 80) player->level = 3;
    else if (player->score >= 50) player->level = 2;
    else player->level = 1;
    printf("\nFinal Score: %d\n", player->score);
    printf("?? You reached Level %d\n", player->level);
    awardBadge(player->score);
    printf("\nBONUS ROUND: Double or Nothing!\n");
    int oldScore = player->score;
    askQuestion(player, questions[5]);
    if (player->score > oldScore) {
        player->score *= 2;
        printf("?? Bonus Success! Score doubled to %d!\n", player->score);
    } else {
        player->score = oldScore;
        printf("?? No change. Score stays at %d.\n", player->score);
    }
    awardBadge(player->score);
    surpriseBox(player);
    printf("\n?? EDUCATIONAL IMPACT:\n");
    printf("? Increased your knowledge of anti-doping rules.\n");
    printf("? Promoted clean sport behavior.\n");
    printf("? Helped you commit to fair play principles.\n");
    printf("? You're now part of the clean sport movement!\n");
    printf("\nFun Fact:\n");
    printf("In 1983, a sprinter used someone else's urine for a test — but got caught because the donor was pregnant!\n");
    printf("?? Moral: Be smart, stay clean, and take pride in your natural performance!\n");
}
void showMenu() {
    char input[10];
    Player player;
    printf("Enter your name: ");
    fgets(player.name, sizeof(player.name), stdin);
    player.name[strcspn(player.name, "\n")] = '\0';
    while (1) {
        printf("\n=== Welcome, %s! ===\n", player.name);
        printf("1. Start Quiz\n");
        printf("2. View Rules\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "1") == 0) {
            player.score = 0;
            player.level = 1;
            startQuiz(&player);
        } else if (strcmp(input, "2") == 0) {
            printf("\n?? Rules & Purpose:\n");
            printf("- Answer anti-doping questions to score points and level up.\n");
            printf("- Higher levels = harder questions = more rewards.\n");
            printf("- Surprise box & bonus round for extra fun.\n");
            printf("?? Our Mission: Promote clean sport and educate young athletes!\n");
        } else if (strcmp(input, "3") == 0) {
            printf("Thank you for playing! Stay strong and stay clean! ??\n");
            break;
        } else {
            printf("Invalid choice. Enter 1, 2, or 3.\n");
        }
    }
}
int main() {
    srand((unsigned int)time(NULL));
    showMenu();
    return 0;
}



