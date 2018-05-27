#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/time.h>
#include <cstdint>

typedef enum
{
  kNothing = 0,
  kExit = 1
} Command;

Command actual_command = kNothing;
bool quit_game_ = false;

void draw() {

}

void inputService()
{
	if(ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape))
	{
    actual_command = kExit;
	}
}

void update(int32_t dt)
{
  if (kExit == actual_command) quit_game_ = true;
}

int ESAT::main(int argc, char **argv) {
  //Maximum time for a frequency of 60 frames per second 
  const int32_t time_step_ = 16;


	ESAT::WindowInit(1280, 720);
  double current_time = Time();
	// main loop
	while (!quit_game_) {
		inputService();
    double accum_time = Time() - current_time;
    while (accum_time >= time_step_)
    {
      update(time_step_);
      current_time += time_step_;
      accum_time = Time() - current_time;
    }
		draw();
		ESAT::WindowFrame();
	}
	return 0;
}