#include <allegro.h>
#include "resource.h"

volatile bool Close=false;
void Handler(){Close=true;}

BITMAP* farmer; 
PALETTE paleta; 
BITMAP* background;
BITMAP* background_menu;
BITMAP* background_over;
BITMAP* background_win;
BITMAP* fox;
BITMAP* food;
BITMAP* sheep;
BITMAP* farmerBoat;
BITMAP* foxBoat;
BITMAP* foodBoat;
BITMAP* sheepBoat;
BITMAP* farmerFox;
BITMAP* farmerSheep;
BITMAP* farmerFood;
SAMPLE* splash;
SAMPLE* blop;
SAMPLE* win;
SAMPLE* wolfSAMPLE;
SAMPLE* sheepSAMPLE;
SAMPLE* foodSAMPLE;
SAMPLE* backgroundMusic;

int farmerX=60;
int farmerY=340;
int farmerW=110;
int farmerH=126;
int foxX=2;
int foxY=250;
int foodX=75;
int foodY=250;
int sheepX=140;
int sheepY=290;
int windowW=640;
int windowH=480;  
int grabbed=0;
int main_stage=0;
int stat=0;
bool firstTimeRiver=true;
int firstDrawTitle=true;

void checkGame(){
    
    int half_screen=windowW/2;
    bool foxP=false;
    bool foodP=false;
    bool sheepP=false;
    bool farmerP=false;
    
    if( foxX<half_screen ){
        foxP=false;
    }else{
        foxP=true;   
    }
    
    if( foodX<half_screen ){
        foodP=false;   
    }else{
        foodP=true;   
    }
    
    if( sheepX<half_screen ){
        sheepP=false;
    }else{
        sheepP=true;   
    }  
    
    if( farmerX<half_screen ){
        farmerP=false;   
    }else{
        farmerP=true;   
    }
    
    
    //================== PROGRESS ===========================
    
    if( foxX<half_screen && sheepX<half_screen && farmerX>half_screen ){
        //set_window_title("El zorro se comio a la oveja del lado izquierdo."); 
        stat=1;  
        main_stage=2;
    }
    
    if( sheepX<half_screen && foodX<half_screen && farmerX>half_screen ){
        //set_window_title("La oveja se comio la comida del lado izquierdo.");   
        stat=2;
        main_stage=2;
    }
    
    if( foxX>half_screen && sheepX>half_screen && farmerX<half_screen ){
        //set_window_title("El zorro se comio a la oveja del lado derecho."); 
        stat=3;  
        main_stage=2;
    }
    
    if( sheepX>half_screen && foodX>half_screen && farmerX<half_screen ){
        //set_window_title("La oveja se comio la comida del lado derecho.");   
        stat=4;
        main_stage=2;
    }
   
    // ====================== WIN ==========================
    
    if( farmerX>(half_screen+100) && foxX>half_screen && foodX>half_screen && sheepX>half_screen ){
        //allegro_message("Gano");   
        stat=10;
        main_stage=2;
    }
    
}



void moveGrabbedObject(char direction, char operation){
            
            switch(grabbed){
                
                case 1:
                    if(direction=='x'){
                           if(operation=='+'){
                                foxX+=10;
                            }else{
                                foxX-=10;
                            }
                    }else{
                           if(operation=='+'){
                                foxY+=10;
                            }else{
                                foxY-=10;
                            }
                    }
                break;
                
                
                case 2:
                    if(direction=='x'){
                           if(operation=='+'){
                                foodX+=10;
                            }else{
                                foodX-=10;
                            }
                    }else{
                           if(operation=='+'){
                                foodY+=10;
                            }else{
                                foodY-=10;
                            }
                    }
                break;
                
                
                case 3:
                    if(direction=='x'){
                           if(operation=='+'){
                                sheepX+=10;
                            }else{
                                sheepX-=10;
                            }
                    }else{
                           if(operation=='+'){
                                sheepY+=10;
                            }else{
                                sheepY-=10;
                            }
                    }
                break;
        }
}
        
        
        
        
        
        
        bool isOverObject(int gx,int gy){
            
            if( (gx>(foxX-fox->w/2)) && (gx<(foxX+fox->w/2)) && (gy>(foxY-fox->h/2)) && (gy<(foxY+fox->h/2)) ){
                   grabbed=1;
                   foxX=farmerX;
                   foxY=farmerY;
                   play_sample(wolfSAMPLE, 255, 128, 1000, 0);
                   return true;
            } 
            
            if( (gx>(foodX-food->w/2)) && (gx<(foodX+food->w/2)) && (gy>(foodY-food->h/2)) && (gy<(foodY+food->h/2)) ){
                   grabbed=2;
                   foodX=farmerX;
                   foodY=farmerY;
                   play_sample(foodSAMPLE, 255, 128, 1000, 0);
                   return true;
            } 
            
            if( (gx>(sheepX-sheep->w/2)) && (gx<(sheepX+sheep->w/2)) && (gy>(sheepY-sheep->h/2)) && (gy<(sheepY+sheep->h/2)) ){
                   grabbed=3;
                   sheepX=farmerX;
                   sheepY=farmerY;
                   play_sample(sheepSAMPLE, 255, 128, 1000, 0);
                   return true;
            } 
    
}





void drop(){
    grabbed=0;   
}


void grab(int gx,int gy){
    //play_sample(blop, 255, 128, 1000, 0);
    if(grabbed){
        drop();
    }else{
         if(isOverObject(gx,gy)){
                if(grabbed==1){
                    //allegro_message("Grabbed: Fox");
                }else if(grabbed==2){
                    //allegro_message("Grabbed: Food");   
                }else if(grabbed==3){
                    //allegro_message("Grabbed: Sheep");   
                }
        }  
    }
    rest(20);
}








void drawGame(){
    clear_keybuf(); 
    acquire_screen(); 
    clear(screen);
    
    if(key[KEY_UP] && (farmerY!=180) ){
        farmerY-=10; 
        moveGrabbedObject('y','-');
    }else if (key[KEY_LEFT] && (farmerX!=0) ){
        farmerX-=10; 
        moveGrabbedObject('x','-');
    }else if (key[KEY_RIGHT] && (farmerX!=windowW-farmerW) ){
        farmerX+=10; 
        moveGrabbedObject('x','+');
    }else if (key[KEY_DOWN] && (farmerY!=windowH-farmerW) ){
        farmerY+=10; 
        moveGrabbedObject('y','+');
    }else if (key[KEY_SPACE]){
          grab(farmerX,farmerY);
    }
    
    checkGame();
    
    blit(background, screen, 0, 0, 0, 0, background->w, background->h);
    
    int half_screen=windowW/2;
    
    if(farmerX>180 && farmerX<half_screen+50){
        if(firstTimeRiver){
            play_sample(splash, 255, 128, 1000, 0);  
            firstTimeRiver=false; 
        }
        
        if(grabbed==1){
            draw_sprite_ex(screen,foxBoat,farmerX,farmerY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }else{
            draw_sprite_ex(screen,fox,foxX,foxY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }
        
        //comida
        if(grabbed==2){
            draw_sprite_ex(screen,foodBoat,farmerX,farmerY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }else{
            draw_sprite_ex(screen,food,foodX,foodY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }
        
        //oveja
        if(grabbed==3){
            draw_sprite_ex(screen,sheepBoat,farmerX,farmerY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }else{
            draw_sprite_ex(screen,sheep,sheepX,sheepY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }
        
        
        //granjero
        if(grabbed==0){
            draw_sprite_ex(screen,farmerBoat,farmerX,farmerY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }
        
    }else{
        firstTimeRiver=true;
        //zorro
        if(grabbed==1){
            draw_sprite_ex(screen,farmerFox,farmerX,farmerY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }else{
            draw_sprite_ex(screen,fox,foxX,foxY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }
        
        //comida
        if(grabbed==2){
            draw_sprite_ex(screen,farmerFood,farmerX,farmerY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }else{
            draw_sprite_ex(screen,food,foodX,foodY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }
        
        //oveja
        if(grabbed==3){
            draw_sprite_ex(screen,farmerSheep,farmerX,farmerY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }else{
            draw_sprite_ex(screen,sheep,sheepX,sheepY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }
        
        
        //granjero
        if(grabbed==0){
            draw_sprite_ex(screen,farmer,farmerX,farmerY,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }
    }
    
    release_screen();   
}





void setupGame(){
    if(install_keyboard()==-1){
        allegro_message("Keyboard error.");                          
    } 
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, windowW, windowH, 0 ,0);
    set_window_title("Juego del Granjero");    
    LOCK_FUNCTION(Handler);
    set_close_button_callback(Handler);
    blop = load_sample("recursos/audio/blop.wav");
    splash = load_sample("recursos/audio/splash.wav");
    win = load_sample("recursos/audio/win.wav");
    wolfSAMPLE = load_sample("recursos/audio/wolf.wav");
    sheepSAMPLE = load_sample("recursos/audio/sheep.wav");
    foodSAMPLE = load_sample("recursos/audio/food.wav");
    backgroundMusic = load_sample("recursos/audio/main.wav");
    farmer = load_bmp("recursos/granjero.bmp",paleta);
    background = load_bitmap("recursos/background.bmp",paleta);
    background_menu = load_bitmap("recursos/main_menu.bmp",paleta);
    background_over = load_bitmap("recursos/game_over.bmp",paleta);
    background_win = load_bitmap("recursos/background_win.bmp",paleta);
    fox = load_bitmap("recursos/lobo.bmp", paleta);
    food = load_bitmap("recursos/comida.bmp", paleta);
    sheep = load_bitmap("recursos/oveja.bmp", paleta);
    sheepBoat = load_bitmap("recursos/granjero_en_barco_con_oveja.bmp", paleta);
    foodBoat = load_bitmap("recursos/granjero_en_barco_con_comida.bmp", paleta);
    foxBoat = load_bitmap("recursos/granjero_en_barco_con_lobo.bmp", paleta);
    farmerBoat = load_bitmap("recursos/granjero_en_barco.bmp", paleta);
    farmerFox = load_bitmap("recursos/granjero_con_lobo.bmp", paleta);
    farmerFood = load_bitmap("recursos/granjero_con_comida.bmp", paleta);
    farmerSheep = load_bitmap("recursos/granjero_con_oveja.bmp", paleta);
    
    play_sample(backgroundMusic, 255, 180, 1000, 1);
    
}







void gameOver(){
    clear_keybuf(); 
    acquire_screen(); 
    clear(screen);
    
    if(stat!=10){
        blit(background_over, screen, 0, 0, 0, 0, background_over->w, background_over->h);
    }
    
    switch(stat){
        case 1:
            //set_window_title("El zorro se comio a la oveja del lado izquierdo."); 
            textout_ex(screen, font, "El zorro se comio a la oveja del lado izquierdo.", 10, 415, makecol(255, 255, 255), -1);
        break;   
        
        case 2:
            //set_window_title("La oveja se comio la comida del lado izquierdo.");  
            textout_ex(screen, font, "La oveja se comio la comida del lado izquierdo.", 10, 415, makecol(255, 255, 255), -1);
        break;
        
        case 3:
            //set_window_title("El zorro se comio a la oveja del lado derecho."); 
            textout_ex(screen, font, "El zorro se comio a la oveja del lado derecho.", 10, 415, makecol(255, 255, 255), -1);
        break;
        
        case 4:
            //set_window_title("La oveja se comio la comida del lado derecho.");  
            textout_ex(screen, font, "La oveja se comio la comida del lado derecho.", 10, 415, makecol(255, 255, 255), -1);
        break;
        
        case 10:
            //Ganó el juego
            //play_sample(win, 255, 180, 1000, 0); 
            blit(background_win, screen, 0, 0, 0, 0, background_win->w, background_win->h);
        break;
    }
    
    

   
    // ====================== WIN ==========================
    
    
    release_screen();   
}





void drawTitle(){
    if(firstDrawTitle){
        blit(background_menu, screen, 0, 0, 0, 0, background_menu->w, background_menu->h);
        textout_ex(screen, font, "Flechas->Mover granjero.", 450, 415, makecol(0, 0, 255), -1);
        textout_ex(screen, font, "Espacio->Tomar/Soltar.", 450, 425, makecol(0, 0, 255), -1);
        textout_ex(screen, font, "Esc->Salir.", 450, 435, makecol(0, 0, 255), -1);
        firstDrawTitle=false;
    }else{
        if(key[KEY_ENTER]){
            main_stage++;
        }  
    }
}



int main(){ 
    allegro_init();
    setupGame();    
    while(!key[KEY_ESC]){
        if(Close){
            break;
        }
        switch(main_stage){
            case 0:
                drawTitle();
            break;
            
            case 1:
                drawGame();
                rest(50);   
            break;
            
            case 2:
                gameOver();
                rest(50);
            break;
        }          
    }
    return 0;
} 
END_OF_MAIN();





