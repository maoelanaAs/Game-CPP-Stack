#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include "header.h"

using namespace std;

void init();

// All About Score
int xScore = 86;
int xHighestScore = 86;
int score = 0;
int highestScore;
int scoreAdd = 1;
int getHighScore();
void pushHighScore(int);
void dispScore();

// Keyboard Clicked
char clickedKey;
char clickedKeyTemp;
void keyDetection();

// All About Hero
int charHero = 206;
int xHero = 39;
int yHero = 14;
int xHeroPrev = xHero + 1;
int yHeroPrev = yHero;
// Batas Gerak Hero
int tAtas = 1;
int tKiri = 1;
int tBawah = 27;
int tKanan = 77;
// Nyawa hero
struct nyawa
{
  int value;
  nyawa *next;
};

nyawa *head = NULL;
nyawa *tail = NULL;
int xNyawa = 88;
int jmlNyawa;

bool isEmpty();
void insNyawa();
void delNyawa();
void dispNyawa();

// All About Enemy
int charEnemy = 60;
float xEnemy = 76;
float yEnemy = 26;
float xEnemyPrev = xEnemy;
float yEnemyPrev = yEnemy;
// langkah enemy
float lEnemy = 0.2;

// Displaying dan Movement hero & enemy
void dispHeroEnemy();
void heroMovement();
void enemyMovement();
void lidahHero();

// All About Fruit
int xFruit = xAcak();
int yFruit = yAcak();
void dispFruit();
void eatFruit(int, int);

// End of Game
int isOver = 0;
int gameOver(int, int);
void init2();
void endGame(string);

// All About Timer
float timer = 0;
void dispTimer();
void overTime();

// All About Item
int xItem;
int yItem;
int charItem;
float itemCountdown = rand() % 10 + 10;
float itemCooldown = 11;
int isCountdown = 1;
int isCooldown = 0;
void itemAlgorithm();
void dispItem();
void eatItem(int, int);

int main()
{
  init();

  // start the game
  do
  {
    // Menghitung detik
    dispTimer();

    // Algoritma Item
    itemAlgorithm();

    // overtime (timer > 10 tp tdk makan)
    overTime();

    // jika fruit tertimpa enemy (memindahkan fruit)
    if ((int)xEnemy == xFruit && (int)yEnemy == yFruit)
    {
      dispFruit();
    }

    // jika item tertimpa enemy (memindahkan item)
    if ((int)xEnemy == xItem && (int)yEnemy == yItem)
    {
      dispItem();
    }

    // Displaying Hero & Enemy
    dispHeroEnemy();

    // Deteksi Keyboard
    keyDetection();

    // Movement Hero & Enemy
    heroMovement();
    enemyMovement();

    // Lidah
    lidahHero();

    // Eating Fruit & Item
    eatItem(0, 0);
    eatFruit(0, 0);

    // Game over
    if (gameOver(0, 0) == 1)
    {
      delNyawa();
      dispNyawa();
      if (isEmpty())
      {
        endGame("over");
        isOver = 1;
      }
      else
      {
        init2();
      }
    }
    if (isOver == 1)
    {
      break;
    }

    slow();

  } while (clickedKey != 27);

  if (clickedKey == 27)
  {
    endGame("exit");
  }

  gotoxy(0, 29);

  return 0;
}

/*
  Fungsi-fungsi Internal
*/

// Fungsi inisialisasi (Awal)
void init()
{
  srand(time(0));

  // Loading screen
  clearCMD();
  printMenu();
  loadingScreen();

  // Mengambil data high score
  highestScore = getHighScore();
  if (highestScore >= 10)
  {
    xHighestScore--;
  }
  if (highestScore >= 100)
  {
    xHighestScore--;
  }

  // Insert Nyawa
  for (int i = 0; i < 3; i++)
  {
    insNyawa();
  }
  jmlNyawa = 3;

  // Set arena
  clearArena();

  // Tampil score
  dispScore();

  // Tampil score
  dispNyawa();

  // Tampil fruit
  dispFruit();
}

// Fungsi mengambil data high score
int getHighScore()
{
  FILE *readFile;
  int highScore;

  // Membuka file
  readFile = fopen("high_score.txt", "r");

  // Mengecek apakah file ada
  if (!readFile)
  {
    return 0;
  }
  else
  {
    // Menuju baris terakhir
    while (!feof(readFile))
    {
      // Dan mengambil data yang ada dlm file
      fscanf(readFile, "%d", &highScore);
      fflush(stdin);
    }
    // Menutup file
    fclose(readFile);
  }
  return highScore;
}

// Fungsi menyimpan data high score
void pushHighScore(int score)
{
  FILE *writeFile;
  // Membuka file
  writeFile = fopen("high_score.txt", "w");

  // Mengecek apakah file ada
  if (!writeFile)
  {
  }
  else
  {
    // Menulis data score tertinggi ke dlm file
    fprintf(writeFile, "%d", score);
  }
  // Menutup file
  fclose(writeFile);
}

// Fungsi menampilkan Score
void dispScore()
{
  gotoxy(84, 6);
  printf("000");
  gotoxy(84, 8);
  printf("000");

  gotoxy(xScore, 6);
  printf("%d ", score);
  gotoxy(xHighestScore, 8);
  printf("%d ", highestScore);
}

// Fungsi mendeteksi keyboard
void keyDetection()
{
  if (kbhit())
  {
    clickedKeyTemp = clickedKey;
    clickedKey = getch();
  }
}

// Fungsi mengecek nyawa
bool isEmpty()
{
  return head == NULL;
}

// Fungsi menambah nyawa
void insNyawa()
{
  if (isEmpty())
  {
    nyawa *bantuan = new nyawa();
    bantuan->value = 2;
    bantuan->next = NULL;

    head = tail = bantuan;
  }
  else
  {
    nyawa *temp = new nyawa();
    temp->value = 2;
    temp->next = NULL;

    tail->next = temp;
    tail = temp;
  }
}

// Fungsi mengurangi nyawa
void delNyawa()
{
  if (isEmpty())
  {
  }
  else
  {
    struct nyawa *key = head;
    struct nyawa *previous = NULL;
    int posisi = 0;

    while (key != NULL)
    {
      if (key->value == 2)
      {
        if (posisi == 0)
        {
          previous = key;
          previous = previous->next;
          head = previous;
          jmlNyawa--;
          free(key);
          break;
        }
        else if (key->next == NULL)
        {
          previous->next = NULL;
          tail = previous;
          jmlNyawa--;
          free(key);
          break;
        }
        else
        {
          previous->next = key->next;
          tail = previous;
          jmlNyawa--;
          free(key);
          break;
        }
      }
      else
      {
      }
      previous = key;
      key = key->next;
      posisi++;
    }
  }
}

// Fungsi Menampilkan nyawa
void dispNyawa()
{
  nyawa *key = head;

  int xNyawa = 88;
  for (int i = 0; i < 3; i++)
  {
    gotoxy(xNyawa + i, 3);
    printf(" ");
  }

  while (key != NULL)
  {
    gotoxy(xNyawa, 3);
    printf("%c", key->value);
    xNyawa++;
    key = key->next;
  }
}

// Fungsi menampilkan hero dan enemy
void dispHeroEnemy()
{
  // Menghilangkan jejak Hero dan Enemy
  gotoxy(xHeroPrev, yHeroPrev);
  printf(" ");
  gotoxy(xEnemyPrev, yEnemyPrev);
  printf(" ");

  // Memunculkan Hero dan Enemy
  gotoxy(xHero, yHero);
  printf("%c", charHero);
  gotoxy(xEnemy, yEnemy);
  printf("%c", charEnemy);
}

// Fungsi mengerakkan hero dgn keyboard
void heroMovement()
{
  if (toupper(clickedKey) == 'W') // ke atas
  {
    xHeroPrev = xHero;
    yHeroPrev = yHero;
    charHero = 202;
    yHero--;
  }
  if (toupper(clickedKey) == 'A') // ke kiri
  {
    xHeroPrev = xHero;
    yHeroPrev = yHero;
    charHero = 185;
    xHero--;
  }
  if (toupper(clickedKey) == 'S') // ke bawah
  {
    xHeroPrev = xHero;
    yHeroPrev = yHero;
    charHero = 203;
    yHero++;
  }
  if (toupper(clickedKey) == 'D') // ke kanan
  {
    xHeroPrev = xHero;
    yHeroPrev = yHero;
    charHero = 204;
    xHero++;
  }
}

// Fungsi mngerakkan enemy untuk mengejar hero
void enemyMovement()
{
  if (yEnemy < yHero + lEnemy) // enemy di atas hero
  {
    yEnemyPrev = yEnemy;
    yEnemy += lEnemy;
  }
  else if (yEnemy > yHero) // enemy di bawah kero
  {
    yEnemyPrev = yEnemy;
    yEnemy -= lEnemy;
  }

  if (xEnemy < xHero + lEnemy) // enemy di kiri hero
  {
    xEnemyPrev = xEnemy;
    xEnemy += lEnemy;
    charEnemy = 62;
  }
  else if (xEnemy > xHero) // enemy di kanan hero
  {
    xEnemyPrev = xEnemy;
    xEnemy -= lEnemy;
    charEnemy = 60;
  }
}

// Fungsi untuk mengeluarkan lidah hero
void lidahHero()
{
  if (clickedKey == 32)
  {
    if (toupper(clickedKeyTemp) == 'W') // ke atas
    {
      gotoxy(xHero, yHero - 1); // Atas
      printf("%c", 186);
      eatItem(0, -1);
      eatFruit(0, -1);
      if (gameOver(0, -1) == 1)
      {
        delNyawa();
        dispNyawa();
        gotoxy(xHero, tAtas);
        printf("%c", 205);
        if (isEmpty())
        {
          endGame("over");
          isOver = 1;
        }
        else
        {
          init2();
        }
      }
    }
    if (toupper(clickedKeyTemp) == 'A') // ke kiri
    {
      gotoxy(xHero - 1, yHero); // Kiri
      printf("%c", 205);
      eatItem(-1, 0);
      eatFruit(-1, 0);
      if (gameOver(-1, 0) == 1)
      {
        delNyawa();
        dispNyawa();
        gotoxy(tKiri, yHero);
        printf("%c", 186);
        if (isEmpty())
        {
          endGame("over");
          isOver = 1;
        }
        else
        {
          init2();
        }
      }
    }
    if (toupper(clickedKeyTemp) == 'S') // ke bawah
    {
      gotoxy(xHero, yHero + 1); // Bawah
      printf("%c", 186);
      eatItem(0, 1);
      eatFruit(0, 1);
      if (gameOver(0, 1) == 1)
      {
        delNyawa();
        dispNyawa();
        gotoxy(xHero, tBawah);
        printf("%c", 205);
        if (isEmpty())
        {
          endGame("over");
          isOver = 1;
        }
        else
        {
          init2();
        }
      }
    }
    if (toupper(clickedKeyTemp) == 'D') // ke kanan
    {
      gotoxy(xHero + 1, yHero); // Kanan
      printf("%c", 205);
      eatItem(1, 0);
      eatFruit(1, 0);
      if (gameOver(0, 1) == 1)
      {
        delNyawa();
        dispNyawa();
        gotoxy(tKanan, yHero);
        printf("%c", 186);
        if (isEmpty())
        {
          endGame("over");
          isOver = 1;
        }
        else
        {
          init2();
        }
      }
    }

    Sleep(50);

    clickedKey = clickedKeyTemp;
    heroMovement();
  }
}

// Fungsi menampilkan fruit secara acak
void dispFruit()
{
  xFruit = xAcak();
  yFruit = yAcak();
  gotoxy(xFruit, yFruit);
  printf("*");
}

// Fungsi saat hero memakan fruit
void eatFruit(int x, int y)
{
  if (xHero + x == xFruit && yHero + y == yFruit)
  {
    if (score + scoreAdd == 10 || score + scoreAdd == 100)
    {
      xScore--;
    }
    if ((scoreAdd == 2 && score + scoreAdd == 11) || (scoreAdd == 2 && score + scoreAdd == 101))
    {
      xScore--;
    }
    score += scoreAdd;
    dispScore();

    dispFruit();

    timer = 0;
  }
}

// Fungsi jika gameover / exitgame
void endGame(string game)
{

  clearArena();
  dispHeroEnemy();
  gotoxy(34, 13);
  if (game == "over")
  {
    printf("Game Over!!");
  }
  else
  {
    printf("Exit Game!!");
  }
  gotoxy(32, 14);
  printf("Your Score : %d", score);
  gotoxy(32, 15);
  printf("High Score : %d", highestScore);
  if (score > highestScore)
  {
    highestScore = score;
    dispScore();
    gotoxy(20, 16);
    printf("Congrats!! You beat the highest score..");
    pushHighScore(score);
  }
}

// Fungsi menampilkan timer
void dispTimer()
{
  timer += 0.1;
  gotoxy(81, 3);
  printf("%.0f ", timer);
}

// Fungsi kondisi game over
int gameOver(int x, int y)
{
  if (yHero + y == tAtas)
  {
    yHero += (1 + y);
    return 1;
  }
  else if (xHero + x == tKiri)
  {
    xHero += (1 + x);
    return 1;
  }
  else if (yHero + y == tBawah)
  {
    yHero -= (1 - y);
    return 1;
  }
  else if (xHero + x == tKanan)
  {
    xHero -= (1 - x);
    return 1;
  }
  else if (xHero + x == (int)xEnemy && yHero + y == (int)yEnemy)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// Fungsi setelah nyawa dikurang
void init2()
{
  charHero = 206;
  xHero = 39;
  yHero = 14;
  xHeroPrev = xHero + 1;
  yHeroPrev = yHero;

  charEnemy = 60;
  xEnemy = 76;
  yEnemy = 26;
  xEnemyPrev = xEnemy;
  yEnemyPrev = yEnemy;

  clearArena();
  gotoxy(32, 15);
  printf("Sisa nyawa : ");
  for (int i = 0; i < jmlNyawa; i++)
  {
    printf("%c", 2);
  }

  loadingScreen();
  clearArena();
  dispFruit();
  dispItem();
  dispHeroEnemy();
}

// Fungsi pengurangan score jika timer > 10
void overTime()
{
  if ((int)timer >= 10)
  {
    if (score > 0)
    {
      score--;
    }
    if (score == 9 || score == 99)
    {
      xScore++;
    }
    dispScore();

    timer = 0;
  }
}

// Fungsi algoritma item
void itemAlgorithm()
{
  if (isCountdown == 1)
  {
    itemCountdown -= 0.1;
  }

  if (isCooldown == 1)
  {
    itemCooldown -= 0.1;
    gotoxy(79, 22);
    printf("%c ", charItem);
    for (int i = 0; i <= (int)itemCooldown; i++)
    {
      gotoxy(81 + i, 22);
      printf("%c ", 254);
    }
  }

  if ((int)itemCountdown == 0)
  {
    itemCountdown = rand() % 10 + 10;
    isCountdown = 0;

    dispItem();
  }

  if ((int)itemCooldown == 0)
  {
    itemCooldown = 11;
    isCountdown = 1;
    isCooldown = 0;
    // Reset item
    scoreAdd = 1;
    lEnemy = 0.2;
    gotoxy(79, 22);
    printf("   ");
  }
}

// Fungsi menampilkan item
void dispItem()
{
  xItem = xAcak();
  yItem = yAcak();
  if (rand() % 10 < 5)
  {
    charItem = 83;
  }
  else
  {
    charItem = 50;
  }
  gotoxy(xItem, yItem);
  printf("%c", charItem);
}

// Fungsi saat memakan item
void eatItem(int x, int y)
{
  if (xHero + x == xItem && yHero + y == yItem)
  {
    isCooldown = 1;
    if (charItem == 50)
    {
      scoreAdd = 2;
    }
    if (charItem == 83)
    {
      lEnemy = 0.1;
    }
  }
}