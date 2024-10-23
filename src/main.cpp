#include "raylib.h"
#include <cstddef>

// Global Variables
const int screenWidth = 800;
const int screenHeight = 450;
Texture2D grassSprite;
bool musicPaused = false;
Music music;

// Define custom colors
struct Colors {
  static const Color TEAL;
};

const Color Colors::TEAL = {147, 211, 196, 255};

class Player {
private:
  Texture2D playerTexture;  // sprite sheet
  Rectangle playerSrc;      // sprite sheet region
  Rectangle playerDest;     // on-screen position and size
  Vector2 origin;           // origin point
  float speed;              // movement speed of the player

  // text path
  static const char* texturePath;

public:
  // initialize player properties
  Player(Vector2 position, Vector2 size) {
      // load player sprite sheet
      playerTexture = LoadTexture(texturePath);
      playerSrc = {0, 0, 48, 48};                // initial frame from sprite sheet
      playerDest = {position.x, position.y, size.x, size.y};  // set position and size
      origin = {0, 0};                           // origin top left corner
      speed = 200.0f;                            // movement speed

      // check if texture was loaded successfully
      if (playerTexture.id == 0) {
          TraceLog(LOG_ERROR, "Player texture could not be loaded");
      }
  }

  // destructor
  ~Player() {
      UnloadTexture(playerTexture);
  }

  // WASD keyboard input
  void update(float deltaTime) {
    if (IsKeyDown(KEY_D)) playerDest.x += speed * deltaTime;
    if (IsKeyDown(KEY_A))  playerDest.x -= speed * deltaTime;
    if (IsKeyDown(KEY_W))    playerDest.y -= speed * deltaTime;
    if (IsKeyDown(KEY_S))  playerDest.y += speed * deltaTime;
    if (IsKeyPressed(KEY_Q)) musicPaused = !musicPaused;
  }

  // draw player on the screen
  void draw() const {
    DrawTexturePro(
        playerTexture,   
        playerSrc,       
        playerDest,      
        origin,          
        0.0f,            
        WHITE            
    );
  }
};

// Initialize static member outside the class
const char* Player::texturePath = "../assets/Characters/BasicCharakterSpritesheet.png";

// placeholder for game logic
void drawScene() {};
void updateGameLoop() {};

bool initMusic() {
  InitAudioDevice ();  // Initialize audio
  music = LoadMusicStream("../assets/music/farm.mp3");  // Load music file
  musicPaused = false;

  //check
  if (music.stream.buffer == NULL || music.ctxData == NULL) {
    TraceLog(LOG_ERROR, "Music could not be loaded");
    return false;
  }
  PlayMusicStream(music);
  return true;
}

void initGame() {
  InitWindow(screenWidth, screenHeight, "I DUNNO WUT IM DOING");
  SetExitKey(0);  // Press X to close game
  SetTargetFPS(60);

  // Load the grass texture
  grassSprite = LoadTexture("../assets/Tilesets/Grass.png");
  if (grassSprite.id == 0) {
    TraceLog(LOG_ERROR, "Grass texture could not be loaded");
  }

  if (!initMusic()) {
    TraceLog(LOG_ERROR, "Music could not be loaded");
  }
}



void renderGame(Player& player) {
  BeginDrawing();
  ClearBackground(Colors::TEAL);

  // Draw the grass background
  if (grassSprite.id != 0) {
      DrawTexture(grassSprite, 0, 0, WHITE);  // Draw grass background at (0, 0)
  }

  // Draw the player
  player.draw();

  //play and pause music
  UpdateMusicStream(music);
  if (musicPaused) {
    PauseMusicStream(music);
  } else {
    ResumeMusicStream(music);
  }

  drawScene();
  EndDrawing();
}

void closeGame() {
  UnloadTexture(grassSprite);  // Unload the grass texture
  UnloadMusicStream(music);    // Unload the music stream
  CloseAudioDevice();          // Close the audio device
  CloseWindow();               // Close the stream
}

int main() {
  initGame();

  // Create a player instance (position at 200, 200 and size of 100x100 pixels)
  Player player({200, 200}, {100, 100});

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();  // Time in seconds for one frame

        //userInput();
        //updateGameLoop();
        
        // Update the player position based on input
        player.update(deltaTime);

        // Render the game and player
        renderGame(player);
    }

    closeGame();
    return 0;
}

