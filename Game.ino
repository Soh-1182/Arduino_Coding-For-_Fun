/* 
 *  ======================================================================
 *  COPYRIGHT NOTICE
 *  ======================================================================
 *  Copyright (C) 2026 Sohan Krishna Golkonda. All Rights Reserved.
 *  
 *  Project Name: Space Dodger for Arduino Uno R4 WiFi
 *  Creation Date: May 25, 2026
 *  Author: Sohan Krishna Golkonda
 *  
 *  LEGAL TERMS AND CONDITIONS:
 *  This software and its source code are the exclusive intellectual 
 *  property of the author. 
 *  
 *  1. PLAGIARISM IS STRICTLY PROHIBITED. You may not copy, re-upload, 
 *     or distribute this code under your own name or claim authorship.
 *  2. You may use and modify this code solely for your own personal, 
 *     private, and non-commercial educational use.
 *  3. Any public exhibition or sharing of this project must explicitly 
 *     credit Sohan Krishna Golkonda as the original author.
 *  ======================================================================
 */
// Vist: 
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

const int WIDTH = 12;
const int HEIGHT = 8;

// Ship variables
const int shipX = 1;
int shipY = 3; 

// Shield variables
bool shieldActive = false;
bool shieldOnCooldown = false;
unsigned long shieldStartTime = 0;
unsigned long shieldCooldownStartTime = 0;

const unsigned long shieldDuration = 800;      
const unsigned long shieldCooldownTime = 3000;  

// Obstacle variables - FIXED array dimensions explicitly set here
int obsX[3];
int obsY[3];
bool obsActive[3] = {false, false, false};
int obstacleSpeed = 2; 

unsigned long lastUpdate = 0;
const int frameDelay = 50; 

bool gameOver = false;
int score = 0;

void setup() {
  matrix.begin(); 
  
  pinMode(A1, INPUT);        
  pinMode(A0, INPUT_PULLUP); 
  
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);

  // Play custom animated opening sequence at startup
  showTitleScreen();
  resetGame();
}

void loop() {
  int yVal = analogRead(A1);
  bool stickClicked = (digitalRead(A0) == LOW); 

  // 1. Ship Movement 
  if (yVal < 200 && shipY > 0) {
    shipY--; 
    delay(30); 
  } else if (yVal > 800 && shipY < (HEIGHT - 1)) {
    shipY++; 
    delay(30); 
  }

  // 2. Shield Logic
  unsigned long currentMillis = millis();

  if (shieldActive && (currentMillis - shieldStartTime >= shieldDuration)) {
    shieldActive = false;
    shieldOnCooldown = true;
    shieldCooldownStartTime = currentMillis; 
  }

  if (shieldOnCooldown && (currentMillis - shieldCooldownStartTime >= shieldCooldownTime)) {
    shieldOnCooldown = false; 
  }

  if (stickClicked && !shieldActive && !shieldOnCooldown) {
    shieldActive = true;
    shieldStartTime = currentMillis;
  }

  // 3. Main game loop frame timer
  if (currentMillis - lastUpdate >= frameDelay) {
    lastUpdate = currentMillis;

    if (!gameOver) {
      updateObstacles();
      checkCollisions();
      renderFrame();
    } else {
      showGameOver();
      // Restart game sequence when joystick is clicked or tilted
      if (yVal < 200 || yVal > 800 || stickClicked) {
        showTitleScreen(); 
        resetGame();
      }
    }
  }
}

// FIXED: Using a safe animated graphic instead of unstable text library extensions
void showTitleScreen() {
  // An animation of an opening hyperspace gateway grid bracket
  uint8_t introFrame[HEIGHT][WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1}
  };
  
  matrix.renderBitmap(introFrame, HEIGHT, WIDTH);
  delay(600);
  
  // Clear screen frame
  uint8_t blankFrame[HEIGHT][WIDTH] = {0};
  matrix.renderBitmap(blankFrame, HEIGHT, WIDTH);
  delay(200);
}

void updateObstacles() {
  for (int i = 0; i < 3; i++) {
    if (!obsActive[i]) {
      if (random(0, 100) < 8) {
        obsX[i] = (WIDTH - 1) * 10; 
        obsY[i] = random(0, HEIGHT);
        obsActive[i] = true;
      }
    } else {
      obsX[i] -= obstacleSpeed;

      if (obsX[i] < 0) {
        obsActive[i] = false;
        score++;
        
        if (score % 5 == 0 && obstacleSpeed < 6) {
          obstacleSpeed += 1;
        }
      }
    }
  }
}

void checkCollisions() {
  if (shieldActive) return; 

  for (int i = 0; i < 3; i++) {
    if (obsActive[i]) {
      int realX = obsX[i] / 10;
      if (realX == shipX && obsY[i] == shipY) {
        gameOver = true;
      }
    }
  }
}

void renderFrame() {
  uint8_t frame[HEIGHT][WIDTH] = {0};

  for (int i = 0; i < 3; i++) {
    if (obsActive[i]) {
      int realX = constrain(obsX[i] / 10, 0, WIDTH - 1);
      frame[obsY[i]][realX] = 1;
    }
  }

  bool drawShip = true;
  if (shieldActive) {
    drawShip = (millis() % 100 < 50); 
  } else if (shieldOnCooldown) {
    drawShip = (millis() % 400 < 200); 
  }

  if (drawShip) {
    frame[shipY][shipX] = 1;
  }

  matrix.renderBitmap(frame, HEIGHT, WIDTH);
}

void resetGame() {
  shipY = 3;
  shieldActive = false;
  shieldOnCooldown = false;
  gameOver = false;
  score = 0;
  obstacleSpeed = 2;

  for (int i = 0; i < 3; i++) {
    obsActive[i] = false;
  }
}

void showGameOver() {
  uint8_t skull[HEIGHT][WIDTH] = {
    {0,0,0,1,1,1,1,1,1,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,0,0},
    {0,0,1,0,1,1,1,1,0,1,0,0},
    {0,0,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,0,0,1,1,0,0,0},
    {0,0,0,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,1,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0}
  };
  matrix.renderBitmap(skull, HEIGHT, WIDTH);
}
