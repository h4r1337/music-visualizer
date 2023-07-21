#include <stdio.h>
#include <raylib.h>

#define BG (Color){ 29, 32, 33, 1 }

int main() {
  InitWindow(800, 600, "Music Visualizer");
  SetTargetFPS(60);

  InitAudioDevice();
  Music music = LoadMusicStream("./audio/7th Floor Tango - Silent Partner.mp3");
  PlayMusicStream(music);

  while (!WindowShouldClose()) {

    UpdateMusicStream(music);
    
    if (IsKeyPressed(KEY_SPACE)) {
      if (IsMusicStreamPlaying(music)) {
        PauseMusicStream(music);
      } else {
        ResumeMusicStream(music);
      }
    }



    BeginDrawing();
    ClearBackground(BG);
    EndDrawing();
  }

  return 0;
}
