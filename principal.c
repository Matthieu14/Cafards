#include "pages.h"


int main() {

  int nVis, btndown,deltay, deltax, newX, newY;
  SDL_Surface *floor = NULL;
  SDL_Surface *ecran = init ( "floor.bmp", &floor );
  SDL_Surface *sprites = LoadSprites ( "roach.bmp" );
  SDL_Surface *tapis = LoadImage ( "bathmat.bmp", X_INIT_TAPIS, Y_INIT_TAPIS);
  Roach *roaches = CreateRoaches ( ecran, sprites, MAX_ROACHES );
  SDL_Flip(ecran);
  int continuer = 1;
  SDL_Event event;
  while ( continuer ) {

    while ( SDL_PollEvent ( &event ) ) { // tant qu'il y a un évènement
    switch ( event.type ) {
      case SDL_QUIT :
      continuer = 0;
      break;
      case SDL_MOUSEBUTTONDOWN:
      if (event.button.button == SDL_BUTTON_LEFT && PointInRect( event.button.x, event.button.y,tapis->clip_rect.x,tapis->clip_rect.y,  tapis->w,tapis->h)){
            /* Clic sur le tapis */
            btndown = 1;
            // Ecart entre clic et coin sup gauche tapis
            deltax = event.button.x - tapis->clip_rect.x;
            deltay = event.button.y - tapis->clip_rect.y;
          }
          break;
          case SDL_MOUSEMOTION :
          if ( btndown ) { // Drag and drop
            // "Nettoyage" du tapis (2 options )
            SDL_BlitSurface(floor,NULL, ecran,NULL);//option 1
            //CleanSurf ( tapis, ecran, floor );// option 2
            // Mise à jour position du tapis
            newX=event.button.x - deltax;
            newY=event.button.y - deltay;
            if (TapisInRect(newX, newY, 0, 0, ecran->w, ecran->h)) {
              tapis->clip_rect.x = event.button.x - deltax;
              tapis->clip_rect.y = event.button.y - deltay;
            }

          }
          break;
          case SDL_MOUSEBUTTONUP :
          btndown = 0;
          break;
        }
      }
      nVis = MarkHiddenRoaches(roaches, MAX_ROACHES, tapis);
      if (nVis!=0) {
        SDL_BlitSurface(floor, NULL, ecran, NULL);
        MoveRoaches( roaches,MAX_ROACHES, ROACH_SPEED, ecran);
        DrawRoaches ( roaches,MAX_ROACHES, ecran );

      }
      DrawImage ( tapis, ecran );
      SDL_Flip(ecran);
      SDL_Delay(DELAI_P_TOUR);
    }
    SDL_Quit ();

    return 0;
  }
