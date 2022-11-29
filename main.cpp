#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "header.h"

using namespace std;

int xScore = 84;
int xHighestScore = 84;
int score = 0;
int highestScore = 0;

void dispScore();

// Posisi hero, enemy, fruit
// Posisi awal hero
int xHero = 38;
int yHero = 13;
int xHeroPrev = xHero + 1;
int yHeroPrev = yHero;

// Batas Gerak
int tAtas = 0;
int tKiri = 0;
int tBawah = 26;
int tKanan = 76;

// Posisi awal enemy
float xEnemy = 75;
float yEnemy = 25;
float xEnemyPrev = xEnemy;
float yEnemyPrev = yEnemy;

// langkah enemy
float lEnemy = 0.2;

// Posisi awal fruit
int xFruit = xAcak();
int yFruit = yAcak();

void dispFruit();

// Displaying dan Movement hero & enemy
void dispHeroEnemy();
void heroMovement();
void enemyMovement();

// Untuk menerima inputan keyboard
char clickedKey;

// Untuk menghitung detik
float timer = 0;

int main()
{
  srand(time(0));

  // set arena
  clearCMD();
  printMenu();
  clearArena();
  dispScore();

  // tampil fruit pertama
  dispFruit();

  // start the game
  do
  {
    // menghitung detik
    timer += 0.1;
    gotoxy(84, 2);
    printf("%.0f ", timer);

    // jika tidak makan selama 10 detik (-1 score)
    if ((int)timer >= 10)
    {
      if (score > 0)
      {
        score--;
      }
      dispScore();

      timer = 0;
    }

    // jika fruit tertimpa enemy (memindahkan fruit)
    if ((int)xEnemy == xFruit && (int)yEnemy == yFruit)
    {
      dispFruit();
    }

    // Displaying Hero & Enemy
    dispHeroEnemy();

    // Movement Hero & Enemy
    heroMovement();
    enemyMovement();

    // Jika hero makan fruit (+1 score)
    if (xHero == xFruit && yHero == yFruit)
    {
      score++;
      if (score > highestScore)
      {
        highestScore++;
      }
      dispScore();

      dispFruit();

      timer = 0;
    }

    slow();

  } while (clickedKey != 27);

  gotoxy(0, 28);

  return 0;
}

// Menampilkan score
void dispScore()
{
  if (score > 99)
  {
    xScore--;
  }
  if (highestScore > 99)
  {
    xHighestScore--;
  }

  gotoxy(xScore, 5);
  printf("%d ", score);
  gotoxy(xHighestScore, 7);
  printf("%d ", highestScore);
}

// Menampilkan fruit secara acak
void dispFruit()
{
  xFruit = xAcak();
  yFruit = yAcak();
  gotoxy(xFruit, yFruit);
  printf("*");
}

// Menampilkan hero dan enemy
void dispHeroEnemy()
{
  // Menghilangkan jejak Hero dan Enemy
  gotoxy(xHeroPrev, yHeroPrev);
  printf(" ");
  gotoxy(xEnemyPrev, yEnemyPrev);
  printf(" ");

  // Memunculkan Hero dan Enemy
  gotoxy(xHero, yHero);
  printf("H");
  gotoxy(xEnemy, yEnemy);
  printf("O");
}

// Mengerakkan hero dgn keyboard
void heroMovement()
{
  // Deteksi keyboard
  if (kbhit())
  {
    clickedKey = getch();
  }

  if (toupper(clickedKey) == 'W') // ke atas
  {
    xHeroPrev = xHero;
    yHeroPrev = yHero;
    yHero--;
    if (yHero <= tAtas)
      yHero = tAtas + 1;
  }
  if (toupper(clickedKey) == 'A') // ke kiri
  {
    xHeroPrev = xHero;
    yHeroPrev = yHero;
    xHero--;
    if (xHero <= tKiri)
      xHero = tKiri + 1;
  }
  if (toupper(clickedKey) == 'S') // ke bawah
  {
    xHeroPrev = xHero;
    yHeroPrev = yHero;
    yHero++;
    if (yHero >= tBawah)
      yHero = tBawah - 1;
  }
  if (toupper(clickedKey) == 'D') // ke kanan
  {
    xHeroPrev = xHero;
    yHeroPrev = yHero;
    xHero++;
    if (xHero >= tKanan)
      xHero = tKanan - 1;
  }
}

// Mengerakkan enemy untuk mengejar hero
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
  }
  else if (xEnemy > xHero) // enemy di kanan hero
  {
    xEnemyPrev = xEnemy;
    xEnemy -= lEnemy;
  }
}