#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <allegro5/allegro_audio.h>
//#include <allegro5/allegro_acodec.h>//allows .wav, .flac, .ogg, .it, .mod, .s3m, .xm
#include <allegro5/allegro_primitives.h>
using namespace std;



class Brick{
public:
	Brick(); //default constructor
	int collision (int ball_x, int ball_y, int ball_w, int ball_h);
	bool dead;
	void initBrick(int w, int h, float x, float y);
	void draw();
	void printinfo();
	bool isDead();
	void killBrick();
	
private:	
	int height;
	int width;
	float Bx; 
	float By; 

};


int bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h);
//using constants in this game so you have sensible words, not unknown numbers in code
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 520;

//an enumeration is like a user-defined variable, with all the given values it can hold
enum MYKEYS {
  KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int main(int argc, char **argv)
{
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL;
  ALLEGRO_BITMAP *paddle = NULL;
  float paddle_x = 400;   
  float paddle_y = 500;
  bool key[4] = { false, false, false, false };
  bool redraw = true;
  bool doexit = false;
  ALLEGRO_BITMAP *ball = NULL;
  float ball_x = 160;
  float ball_y = 120;
  float ball_dx = -4.0, ball_dy = 4.0;
  int score= 0;

  //variables for Bricks
  Brick Brick1;
  Brick1.initBrick(20, 70, 90, 350);

  Brick Brick2;
  Brick2.initBrick(20, 70, 100, 500);

  Brick Brick3;
  Brick3.initBrick(20, 70, 170, 200);

  Brick Brick4;
  Brick4.initBrick(20, 70, 270, 360);

  Brick Brick5;
  Brick5.initBrick(20, 70, 420, 250);

  Brick Brick6;
  Brick6.initBrick(20, 70, 380, 330);

  Brick Brick7;
  Brick7.initBrick(20, 70, 450, 90);

  Brick Brick8;
  Brick8.initBrick(20, 70, 520, 120);

   Brick Brick9;
  Brick9.initBrick(20, 70, 50, 300);

  Brick Brick10;
  Brick10.initBrick(20, 70, 150, 400);

  Brick Brick11;
  Brick11.initBrick(20, 70, 170, 200);

  Brick Brick12;
  Brick12.initBrick(20, 70, 230, 360);

 if (bool dead = 1){
		 al_destroy_bitmap;
 }


   //audio stuff
 //  ALLEGRO_SAMPLE *sample=NULL;
 //  ALLEGRO_SAMPLE *sample2=NULL;
 //  ALLEGRO_SAMPLE *sample3=NULL;
 //  ALLEGRO_SAMPLE *sample4=NULL;
 ///  al_install_audio();
 
   //al_init_acodec_addon();
 //
//  al_reserve_samples(3);
   


 // sample = al_load_sample( "Bleep.flac" );
//  sample2 = al_load_sample("Bloop.wav");
 // sample3 = al_load_sample("pallet.wav");
  //sample4 = al_load_sample("sad.wav");
 
   //al_rest(10.0);







  //including some error messages to help debug
  if(!al_init()) {
     fprintf(stderr, "failed to initialize allegro!\n");
     return -1;
  }
  if(!al_install_keyboard()) {
     fprintf(stderr, "failed to initialize the keyboard!\n");
     return -1;
  }
  timer = al_create_timer(1.0 / FPS);
  if(!timer) {
     fprintf(stderr, "failed to create timer!\n");
     return -1;
  }
  display = al_create_display(SCREEN_W, SCREEN_H);
  if(!display) {
     fprintf(stderr, "failed to create display!\n");
     al_destroy_timer(timer);
     return -1;
  }

  //hook up fonts for on-screen text
  al_init_primitives_addon();
  al_init_font_addon();
  al_init_ttf_addon();
  ALLEGRO_FONT *font = al_load_ttf_font("Candara.ttf",35,0 );
  
  paddle = al_create_bitmap(50, 20);
  
 
  
 
  
  ball = al_create_bitmap(20, 20);

  

  al_set_target_bitmap(paddle);
  al_clear_to_color(al_map_rgb(430, 32, 64));

 
 
  al_set_target_bitmap(ball);
  al_clear_to_color(al_map_rgb(430, 32, 64));


  al_set_target_bitmap(al_get_backbuffer(display));
  //set up your event queue
  event_queue = al_create_event_queue();
  if(!event_queue) {
     fprintf(stderr, "failed to create event_queue!\n");
     al_destroy_bitmap(paddle);
     al_destroy_display(display);
     al_destroy_timer(timer);
     return -1;
  }
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  //draw the initial screen, start up the timer
  al_clear_to_color(al_map_rgb(0,0,0));
  al_flip_display();
  al_start_timer(timer);
  while(!doexit)
  {
     ALLEGRO_EVENT ev;
     al_wait_for_event(event_queue, &ev);
	  //if a clock ticks, check if we should be moving a square (by checking key or key2)
     if(ev.type == ALLEGRO_EVENT_TIMER) {

	

	  //sets this part of the game to run on the clicks of the timer
     if(ev.type == ALLEGRO_EVENT_TIMER) {
		  //if the box hits the left wall OR the right wall
        if(ball_x < 30 || ball_x > 640 -40) {
			 //flip the x direction
           ball_dx = -ball_dx;
        }
			//if the box hits the top wall OR the bottom wall
        if(ball_y < 90 || ball_y > 500 ) {
			 //flip the y direction
           ball_dy = -ball_dy;
        }
		
		
        ball_x += ball_dx;
        ball_y += ball_dy;
		
		 
        redraw = true;
     }


        if((key[KEY_LEFT]) && !(paddle_x < 32)) {
           paddle_x -= 6.0;
        }
        if(key[KEY_RIGHT] && paddle_x <= SCREEN_W -102) {
           paddle_x += 6.0;
        }
        redraw = true;
     }


	  //kill program if window "X" has been clicked
     else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        break;
     }

	  //update key/key2 if a key has been pressed
     else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(ev.keyboard.keycode) {

           case ALLEGRO_KEY_LEFT:
              key[KEY_LEFT] = true;
              break;
           case ALLEGRO_KEY_RIGHT:
              key[KEY_RIGHT] = true;
              break;

        }
     }
	  //update key/key2 if a key has been released
     else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
        switch(ev.keyboard.keycode) {

           
           case ALLEGRO_KEY_LEFT:
              key[KEY_LEFT] = false;
              break;
           case ALLEGRO_KEY_RIGHT:
              key[KEY_RIGHT] = false;
              break;

        }
     }
    

			//take all the above information and update screen
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(paddle, paddle_x, paddle_y, 0);

		

		 al_draw_bitmap(ball, ball_x, ball_y, 0);

		

		 //call the bounding box function. if it returns 1, print out your collision message
		if (bounding_box_collision(ball_x, ball_y, 10, 10, paddle_x, paddle_y, 70, 10)==0)
	 {
		 ball_dy = -ball_dy;
		
	 }
		

		
	 if(Brick1.isDead()==0)
		Brick1.draw();
	 if(Brick2.isDead()==0)
		Brick2.draw();
	 if(Brick3.isDead()==0)
		Brick3.draw();
	 if(Brick4.isDead()==0)
		Brick4.draw();
	 if(Brick5.isDead()==0)
		Brick5.draw();
	 if(Brick6.isDead()==0)
		Brick6.draw();
	 if(Brick7.isDead()==0)
		Brick7.draw();
	 if(Brick8.isDead()==0)
		Brick8.draw();
	 if(Brick9.isDead()==0)
		Brick9.draw();
	 if(Brick10.isDead()==0)
		Brick10.draw();
	 if(Brick11.isDead()==0)
		Brick11.draw();
	 if(Brick12.isDead()==0)
		Brick12.draw();

		  if(!Brick1.dead && Brick1.collision(ball_x, ball_y, 10, 10)==0){
			ball_dy = -ball_dy;
			//al_play_sample(sample, 1.0, 0.0,5,ALLEGRO_PLAYMODE_ONCE,NULL);
			redraw = false;
			Brick1.killBrick();
			score++;
	   }
	
	 if(!Brick2.dead &&Brick2.collision(ball_x, ball_y, 10, 10)==0){
			ball_dy = -ball_dy;
			//al_play_sample(sample, 1.0, 0.0,5,ALLEGRO_PLAYMODE_ONCE,NULL);
			redraw = false;
			Brick2.killBrick();
			//bool dead = 1;
			score++;
	   
	 }
	  if(!Brick3.dead &&Brick3.collision(ball_x, ball_y, 10, 10)==0){
			ball_dy = -ball_dy;
			//al_play_sample(sample, 1.0, 0.0,5,ALLEGRO_PLAYMODE_ONCE,NULL); 
			redraw = false;
			Brick3.killBrick();
			// bool dead = 1;
			score++;
	   }
	 
	 if(!Brick4.dead &&Brick4.collision(ball_x, ball_y, 10, 10)==0){
			ball_dy = -ball_dy;
			//al_play_sample(sample, 1.0, 0.0,5,ALLEGRO_PLAYMODE_ONCE,NULL); 
			Brick4.killBrick();
			redraw = false;
			//  bool dead = 1;
			score++;
	   }
	 
	 if(!Brick5.dead &&Brick5.collision(ball_x, ball_y, 10, 10)==0){
			ball_dy = -ball_dy;
			//al_play_sample(sample, 1.0, 0.0,5,ALLEGRO_PLAYMODE_ONCE,NULL); 
			Brick5.killBrick();
			redraw = false;
			//  bool dead = 1;
			score++;
	   }
	 
	 if(!Brick6.dead &&Brick6.collision(ball_x, ball_y, 10, 10)==0){
			ball_dy = -ball_dy;
			//al_play_sample(sample, 1.0, 0.0,5,ALLEGRO_PLAYMODE_ONCE,NULL); 
			Brick6.killBrick();
			redraw = false;
			//  bool dead = 1;
			score++;
	   }
	 
	 if(!Brick7.dead &&Brick7.collision(ball_x, ball_y, 10, 10)==0){
			ball_dy = -ball_dy;
			//al_play_sample(sample, 1.0, 0.0,5,ALLEGRO_PLAYMODE_ONCE,NULL); 
			Brick7.killBrick();
			redraw = false;
			// bool dead = 1;
			score++;
	   }
	 
	 if(!Brick8.dead &&Brick8.collision(ball_x, ball_y, 10, 10)==0){
			ball_dy = -ball_dy;
			//al_play_sample(sample, 1.0, 0.0,5,ALLEGRO_PLAYMODE_ONCE,NULL); 
			Brick8.killBrick();
			//  bool dead = 1;
			score++;
	   }
	
	  if(!Brick9.dead && Brick1.collision(ball_x, ball_y, 10, 10)==0){
			ball_dy = -ball_dy;
			//al_play_sample(sample, 1.0, 0.0,5,ALLEGRO_PLAYMODE_ONCE,NULL);
			redraw = false;
			Brick9.killBrick();
			score++;
	   }
	
	 if(!Brick10.dead &&Brick2.collision(ball_x, ball_y, 10, 10)==0){
			ball_dy = -ball_dy;
			//al_play_sample(sample, 1.0, 0.0,5,ALLEGRO_PLAYMODE_ONCE,NULL);
			redraw = false;
			Brick10.killBrick();
			//bool dead = 1;
			score++;
	   
	 }
	  if(!Brick11.dead &&Brick3.collision(ball_x, ball_y, 10, 10)==0){
			ball_dy = -ball_dy;
			//al_play_sample(sample, 1.0, 0.0,5,ALLEGRO_PLAYMODE_ONCE,NULL); 
			redraw = false;
			Brick11.killBrick();
			// bool dead = 1;
			score++;
	   }
	 
	 if(!Brick12.dead &&Brick4.collision(ball_x, ball_y, 10, 10)==0){
			ball_dy = -ball_dy;
			//al_play_sample(sample, 1.0, 0.0,5,ALLEGRO_PLAYMODE_ONCE,NULL); 
			Brick12.killBrick();
			redraw = false;
			//  bool dead = 1;
			score++;
	   }




		 else
			 cout<<"No collision"<<endl;

		al_draw_textf(font, al_map_rgb(255,255,255), (640/2), 15,ALLEGRO_ALIGN_CENTRE, "%d", score);
		 if (score > 7){
		 al_clear_to_color(al_map_rgb(0,0,0));
		 cout<<"CONGRATULATIONS"<<endl;
		 al_draw_textf(font, al_map_rgb(255,255,255), 640/2, (70/4),ALLEGRO_ALIGN_CENTRE, "Boooooooooooooo");
		 ball_dx = 0, ball_dy = 0;
		}
		if (ball_y > 500){
			Brick1.killBrick();
			Brick2.killBrick();
			Brick3.killBrick();
			Brick4.killBrick();
			Brick5.killBrick();
			Brick6.killBrick();
			Brick7.killBrick();
			Brick8.killBrick();
			Brick9.killBrick();
			Brick10.killBrick();
			Brick11.killBrick();
			Brick12.killBrick();

			al_destroy_bitmap(paddle);
		 al_clear_to_color(al_map_rgb(0,0,0));
		 al_draw_textf(font, al_map_rgb(0,0,255), 640/2, (70/4),ALLEGRO_ALIGN_CENTRE, "loser");
		 al_destroy_timer(timer);

		}

         al_flip_display();
     
   }
 
   al_destroy_bitmap(paddle);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
//   al_destroy_sample(sample);
 
   return 0;
}


Brick::Brick() //default constructor
{
	dead = 0;
	width = 0;
	height = 0;
	Bx = 0;
	By = 0;
}

int Brick::collision(int b2_x, int b2_y, int b2_w, int b2_h){
    if ((Bx > b2_x + b2_w - 1) || // is b1 on the right side of b2?
        (By > b2_y + b2_h - 1) || // is b1 under b2?
        (b2_x > Bx + 70) || // is b2 on the right side of b1?
        (b2_y > By+ 20)&& // is b2 under b1?
		(dead==0))
	{		 
       //no collision
		
       return 1;
    }
	
	else
     //collision
	 cout<<"collision!"<<endl;
    return 0;
}

void Brick::draw(){

	al_draw_filled_rectangle(Bx, By, Bx+height, By+width, al_map_rgb(472, 352, 312));

}

void Brick::printinfo(){

	cout<<"Width and height are "<<width<<" "<<height<<endl;
	cout<<"Position is "<<Bx<<" "<<By<<endl;
}

void Brick::initBrick(int w, int h, float x, float y){

	width = w;
	height = h;
	Bx = x;
	By = y;
}
int bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h){
    if ((b1_x > b2_x + b2_w - 1) || // is b1 on the right side of b2?
        (b1_y > b2_y + b2_h - 1) || // is b1 under b2?
        (b2_x > b1_x + b1_w - 1) || // is b2 on the right side of b1?
        (b2_y > b1_y + b1_h - 1))  // is b2 under b1?
	{		 
       //no collision
		
       return 1;
    }
	
	else
     //collision
	 cout<<"collision!"<<endl;
    return 0;
}
bool Brick::isDead(){

	return dead;
}

void Brick::killBrick(){

	dead = 1;

}
