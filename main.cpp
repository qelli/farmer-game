#include <allegro.h>

BITMAP *fondo;
BITMAP *granjero;
BITMAP *granjero_lobo;
BITMAP *granjero_gallina;
BITMAP *granjero_comida;
BITMAP *lobo;
BITMAP *comida;
BITMAP *gallina;
BITMAP *ganar;
BITMAP *perder;
BITMAP *buffer;

int tiene=0;
int lados[4]={0,0,0,0};
bool visibles[4]={true,true,true,true};
bool fin=false;
int estado=0;

void iniciar();
void dibujar_personajes();
void agarrar_lobo();
void agarrar_gallina();
void agarrar_comida();
void cambiar_lado();
void progreso_juego();
void menu_final();

int main() 
{	
	iniciar();
	
	while(!key[KEY_ESC] && fin!=true){
        clear_bitmap(buffer);
        if(key[KEY_1]){
            agarrar_lobo();
        }
        
        if(key[KEY_2]){
            agarrar_gallina();
        }
        
        if(key[KEY_3]){
            agarrar_comida();
        }
        
        if(key[KEY_ENTER]){
            cambiar_lado();
        }
        
        draw_sprite(buffer,fondo,0,0);
        dibujar_personajes();
        textout_ex(buffer,font,"Controles",800,10,makecol(0,0,255),-1);
        textout_ex(buffer,font,"ESC -> Salir",790,20,makecol(0,0,255),-1);
        textout_ex(buffer,font,"1 -> Lobo",800,30,makecol(0,0,255),-1);
        textout_ex(buffer,font,"2 -> Gallina",790,40,makecol(0,0,255),-1);
        textout_ex(buffer,font,"3 -> Comida",795,50,makecol(0,0,255),-1);
        textout_ex(buffer,font,"ENTER -> Granjero",765,60,makecol(0,0,255),-1);
        progreso_juego();
        
        blit(buffer, screen, 0,0,0,0,900,654);
        
        rest(90);
    }
    
    
    if(estado!=0){
        while(!key[KEY_ENTER]){
               
        }
    }
	
	return 0;
}
END_OF_MAIN();







void iniciar(){
    allegro_init();
	install_keyboard();
	
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 900, 654, 0, 0);
    
    fondo=load_bitmap("imagen/fondo.bmp",NULL);   
    granjero=load_bitmap("imagen/granjero.bmp",NULL);
    granjero_gallina=load_bitmap("imagen/granjero_gallina.bmp",NULL);
    granjero_comida=load_bitmap("imagen/granjero_comida.bmp",NULL);
    granjero_lobo=load_bitmap("imagen/granjero_lobo.bmp",NULL);
    lobo=load_bitmap("imagen/lobo.bmp",NULL);
    gallina=load_bitmap("imagen/gallina.bmp",NULL);
    comida=load_bitmap("imagen/comida.bmp",NULL);
    ganar=load_bitmap("imagen/ganar.bmp",NULL);
    perder=load_bitmap("imagen/perder.bmp",NULL);
    buffer=create_bitmap(900,654);
    
    
}

void dibujar_personajes(){
    
    int gr,g,c,l;
    
    if(lados[0]==0){
        gr=400;
    }else{
        gr=170;   
    }
    
    if(lados[1]==0){
        l=780;
    }else{
        l=10;
    }
    
    if(lados[2]==0){
        g=660;
    }else{
        g=155;
    }
    
    if(lados[3]==0){
        c=730;   
    }else{
        c=70;
    }
    
    
    switch(tiene){
        case 0:
            draw_sprite(buffer,granjero,gr,430);
        break;   
        
        case 1:
            draw_sprite(buffer,granjero_lobo,gr,430);
        break;
        
        case 2:
            draw_sprite(buffer,granjero_gallina,gr,430);
        break;
        
        case 3:
            draw_sprite(buffer,granjero_comida,gr,430);
        break;
        
    }
        
        if(visibles[1]){
            draw_sprite(buffer,lobo,l,520);
        }
        
        if(visibles[2]){
            draw_sprite(buffer,gallina,g,450);
        }
       
        if(visibles[3]){
            draw_sprite(buffer,comida,c,490);
        }
       
}



void agarrar_lobo(){
    if(lados[1]==lados[0]){
        if(tiene!=1){
            tiene=1;
            visibles[1]=false;
            visibles[2]=true;
            visibles[3]=true;
        }else{
            tiene=0;
            visibles[1]=true;
        }
    }
}

void agarrar_gallina(){
    if(lados[2]==lados[0]){
        if(tiene!=2){
            tiene=2;
            visibles[1]=true;
            visibles[2]=false;
            visibles[3]=true;
        }else{
            tiene=0;
            visibles[2]=true;
        }
    }
}

void agarrar_comida(){
    if(lados[3]==lados[0]){
        if(tiene!=3){
            tiene=3;
            visibles[1]=true;
            visibles[2]=true;
            visibles[3]=false;
        }else{
            tiene=0;
            visibles[3]=true;
        }
    }
}

void cambiar_lado(){
    if(lados[0]==0){
        lados[0]=1;
        lados[tiene]=1;
    }else{
        lados[0]=0;
        lados[tiene]=0;
    }
}

void progreso_juego(){
    if( lados[1]==lados[2] && lados[0]!=lados[1] ){
        //lobo - gallina  
        fin=true;
        estado=1;
        draw_sprite(buffer,perder,200,50);
    }
        
    if( lados[2]==lados[3] && lados[0]!=lados[2] ){
        //gallina - comida  
        fin=true;
        estado=1; 
        draw_sprite(buffer,perder,200,50);
    }
    
    if( lados[0]==1 && lados[1]==1 && lados[2]==1 && lados[3]==1 ){
        //Ganó
        fin=true;
        estado=2;   
        draw_sprite(buffer,ganar,200,50);
    }
}






