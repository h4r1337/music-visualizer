#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BG (Color) { 29, 32, 33, 1 }

#define ARRAY_LEN(xs) sizeof(xs)/sizeof(xs[0])

uint32_t global_frames[1024] = {0};
size_t global_frames_count = 0;

void callback(void *bufferData, unsigned int frames) {
  if (frames > ARRAY_LEN(global_frames)/2) {
    frames = ARRAY_LEN(global_frames)/2;
  }
  memcpy(global_frames, bufferData, sizeof(uint32_t)*frames*2);
  global_frames_count = frames*2;
}

int main() {
  InitWindow(800, 600, "Music Visualizer");
  SetTargetFPS(60);

  InitAudioDevice();
  Music music = LoadMusicStream("./audio/7th Floor Tango - Silent Partner.mp3");
  printf("music.frameCount = %u\n", music.frameCount);
  printf("music.stream.sampleRate = %u\n", music.stream.sampleRate);
  printf("music.stream.sampleSize = %u\n", music.stream.sampleSize);
  printf("music.stream.channels = %u\n", music.stream.channels);

  PlayMusicStream(music);

  float volume = 0.8f;

  AttachAudioStreamProcessor(music.stream, callback);

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

    int w = GetRenderWidth();
    int h = GetRenderHeight();

    BeginDrawing();
    ClearBackground(BG);
    float cell_width = (float)w/global_frames_count;
    for (size_t i = 0; i < global_frames_count; i++) {
      int16_t sample = *(int16_t*)&global_frames[i];
      if (sample > 0) {
        float t = (float)sample/INT16_MAX;
        DrawRectangle(i*cell_width, h/2 - h/2*t, cell_width, h/2*t, RED);
      } else {
        float t = (float)sample/INT16_MIN;
        DrawRectangle(i*cell_width, h/2, cell_width, h/2*t, RED);
      }
    }
    // if (global_frames_count > 0) exit(0);
    EndDrawing();
  }

  return 0;
}
