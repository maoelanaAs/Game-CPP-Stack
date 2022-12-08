#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include "header.h"

using namespace std;

int xScore = 85;
int xHighestScore = 85;
int score = 0;
int highestScore = 0;
int scoreAdd = 1;

void dispScore();

// Posisi hero, enemy, fruit
// Posisi awal hero
int charHero = 206;
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
int charEnemy = 60;
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
void eatFruit();
void overTime();

// Displaying dan Movement hero & enemy
void dispHeroEnemy();
void heroMovement();
void enemyMovement();

// Untuk menerima inputan keyboard
char clickedKey;

// Game over
int gameOver();

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

    // overtime (timer > 10 tp tdk makan)
    overTime();

    // jika fruit tertimpa enemy (memindahkan fruit)
    if ((int)xEnemy == xFruit && (int)yEnemy == yFruit)
    {
      dispFruit();
    }

    // Displaying Hero & Enemy
    dispHeroEnemy();

    // Deteksi Keyboard
    if (kbhit())
    {
      clickedKey = getch();
    }

    // Movement Hero & Enemy
    heroMovement();
    enemyMovement();

    // Eating Fruit
    eatFruit();

    // (1) game over
    if (gameOver() == 1)
    {
      clearArena();
      dispHeroEnemy();
      gotoxy(33, 13);
      printf("Game Over!!");
      break;
    }

    slow();

  } while (clickedKey != 27);

  gotoxy(0, 28);

  return 0;
}

// Menampilkan score
void dispScore()
{
  gotoxy(83, 5);
  printf("000");
  gotoxy(83, 7);
  printf("000");

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

// Saat hero memakan fruit
void eatFruit()
{
  if (xHero == xFruit && yHero == yFruit)
  {
    score += scoreAdd;
    if (score == 10 || score == 100)
    {
      xScore--;
      if ((highestScore + scoreAdd) == 10 || (highestScore + scoreAdd) == 100)
      {
        xHighestScore--;
      }
    }
    if (score > highestScore)
    {
      highestScore = score;
    }
    dispScore();

    dispFruit();

    timer = 0;
  }
}

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
  printf("%c", charHero);
  gotoxy(xEnemy, yEnemy);
  printf("%c", charEnemy);
}

// Mengerakkan hero dgn keyboard
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
    charEnemy = 62;
  }
  else if (xEnemy > xHero) // enemy di kanan hero
  {
    xEnemyPrev = xEnemy;
    xEnemy -= lEnemy;
    charEnemy = 60;
  }
}

int gameOver()
{
  if (yHero == tAtas)
  {
    yHero += 1;
    return 1;
  }
  else if (xHero == tKiri)
  {
    xHero += 1;
    return 1;
  }
  else if (yHero == tBawah)
  {
    yHero -= 1;
    return 1;
  }
  else if (xHero == tKanan)
  {
    xHero -= 1;
    return 1;
  }
  else if (xHero == (int)xEnemy && yHero == (int)yEnemy)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}