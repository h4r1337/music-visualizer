#include <raylib.h>
#include <stdio.h>

#define BG                                                                     \
  (Color) { 29, 32, 33, 1 }

int main() {
  InitWindow(800, 600, "Music Visualizer");
  SetTargetFPS(60);

  InitAudioDevice();
  Music music = LoadMusicStream("./audio/7th Floor Tango - Silent Partner.mp3");
  PlayMusicStream(music);

  float volume = 0.8f;

  while (!WindowShouldClose()) {

    SetMusicVolume(music, volume);
    UpdateMusicStream(music);

    if (IsKeyPressed(KEY_SPACE)) {
      if (IsMusicStreamPlaying(music)) {
        PauseMusicStream(music);
      } else {
        ResumeMusicStream(music);
      }
    }

    if (IsKeyPressed(KEY_VOLUME_UP) || IsKeyPressed(KEY_UP)) {
      if (volume < 1.0f)
        volume += 0.1f;
    }

    if (IsKeyPressed(KEY_VOLUME_DOWN) || IsKeyPressed(KEY_DOWN)) {
      if (volume > 0.0f)
        volume -= 0.1f;
    }

    BeginDrawing();
    ClearBackground(BG);
    EndDrawing();
  }

  return 0;
}
