// sdlrender.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include "types.hpp"
#include <SDL.h>
#include <SDL_image.h>

#include <SDL_ttf.h>
#include <thread>
#include "renderz.hpp"
#include <chrono>
cgl::Object3 obj;
cgl::Object3 objj;
cgl::Object3 obbjj;
double scrolled = 1;
TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
SDL_Color White = { 255, 255, 255 };
std::chrono::high_resolution_clock c;
SDL_Texture *t;
int m_x, m_y;
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        printf("IMG_Load Error: %s\n", IMG_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
/*void getinput(char* carr) {
    carr
}*/
void renderPolygon(SDL_Renderer* renderer, cgl::poly2 p) {
    for (int i = 0; i < 3 - 1; ++i) {
        SDL_RenderDrawLine(renderer, p.p[i].x, p.p[i].y, p.p[i + 1].x, p.p[i + 1].y);
    }
    // Close the polygon
    SDL_RenderDrawLine(renderer, p.p[3 - 1].x, p.p[0].x, p.p[0].x, p.p[0].y);
}
void renderthings(SDL_Renderer* renderer) {
    auto t1 = c.now();
    //but i wont be dealing with it right now because its too l8 11.10.2024
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    cgl::poly3 MESH[12] = {//well... this took some time!

        cgl::poly3(cgl::vec3(0, 0, 0), cgl::vec3(11, 0, 0), cgl::vec3(11, 1, 0)),
        cgl::poly3(cgl::vec3(0, 0, 0), cgl::vec3(11, 1, 0), cgl::vec3(0, 1, 0)),

        cgl::poly3(cgl::vec3(0, 0, 1), cgl::vec3(11, 0, 1), cgl::vec3(11, 1, 1)),
        cgl::poly3(cgl::vec3(0, 0, 1), cgl::vec3(11, 1, 1), cgl::vec3(0, 1, 1)),

        cgl::poly3(cgl::vec3(0, 1, 0), cgl::vec3(11, 1, 0), cgl::vec3(11, 1, 1)),
        cgl::poly3(cgl::vec3(0, 1, 0), cgl::vec3(11, 1, 1), cgl::vec3(0, 1, 1)),

        cgl::poly3(cgl::vec3(0, 0, 0), cgl::vec3(11, 0, 0), cgl::vec3(11, 0, 1)),
        cgl::poly3(cgl::vec3(0, 0, 0), cgl::vec3(11, 0, 1), cgl::vec3(0, 0, 1)),

        cgl::poly3(cgl::vec3(0, 0, 0), cgl::vec3(0, 1, 0), cgl::vec3(0, 1, 1)),
        cgl::poly3(cgl::vec3(0, 0, 0), cgl::vec3(0, 1, 1), cgl::vec3(0, 0, 1)),

        cgl::poly3(cgl::vec3(11, 0, 0), cgl::vec3(11, 1, 0), cgl::vec3(11, 1, 1)),
        cgl::poly3(cgl::vec3(11, 0, 0), cgl::vec3(11, 1, 1), cgl::vec3(11, 0, 1)),
    };
    //obj.MESH = MESH;
    obbjj.setmesh(MESH, sizeof(MESH));
    objj.setmesh(MESH, sizeof(MESH));
    obj.setmesh(MESH,sizeof(MESH));
    //std::cout << sizeof(obj.MESH) << "\n";
   // obj.setmesh(MESH);
    
    obbjj.OBJTOSCR(renderer, sizeof(MESH), t, 24.95 * scrolled);
    objj.OBJTOSCR(renderer, sizeof(MESH), t, 50 * scrolled);
    obj.OBJTOSCR(renderer, sizeof(MESH), t, 100 * scrolled);
    /*cgl::poly3 p = cgl::poly3(cgl::vec3(m_x, m_y, scrolled), cgl::vec3(100, 500, 10), cgl::vec3(100, 200, 40));
    cgl::poly2 projected[12];
    double m = 100 * scrolled;
    for (int i = 0; i <= 11; i++) {
        projected[i].p[0] = cgl::multvecby(cgl::perspectiveProject(MESH[i].p[0], 90.0, 16 / 9, 0.1, 100.0), m);
        projected[i].p[1] = cgl::multvecby(cgl::perspectiveProject(MESH[i].p[1], 90.0, 16 / 9, 0.1, 100.0), m);
        projected[i].p[2] = cgl::multvecby(cgl::perspectiveProject(MESH[i].p[2], 90.0, 16 / 9, 0.1, 100.0), m);

    }
    for (int i = 0; i <= 11; i++) {
        projected[i].p2scr(renderer);//
    }*/
   // free(MESH);
   // free(projected);
   // cgl::vec3 complicated;
    //drawfilledcircle(renderer, {(float)m_x,(float)m_y}, 3);

    //complicated.x = 3;
   // complicated.z = 4;
   // SDL_RenderDrawPoint(renderer, cgl::perspectiveProject(complicated, 60, 4 / 3, 0, 10).x, cgl::perspectiveProject(complicated, 60, 4 / 3, 0, 10).y);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    auto t2 = c.now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    
   
    std::cout << 1000 / ms_double.count() << "FPS\n";
}
int main(int argc, char* argv[])
{
    SDL_Window* window = SDL_CreateWindow("hw", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//my screen doesnt have that big of a res i think
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    t = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 128, 128
    );
   // t = loadTexture("C:\\Users\\lenovo\\Desktop\\sides.png",renderer);
    SDL_Event e;
    while (SDL_PollEvent(&e) != SDL_QUIT) {
        if(e.type == SDL_MOUSEMOTION) 
        SDL_GetMouseState((int*) &m_x, (int*)&m_y);
        if (e.type == SDL_MOUSEWHEEL)//pretty cool!
            scrolled += e.wheel.y * 0.06;
       // getinput(charray);
        renderthings(renderer);
        //free(v);
        //SDL_FreeSurface(surfaceMessage);
        //SDL_DestroyTexture(Message);
    }

    cgl::vec3 a = cgl::vec3(10, 10, 10);
    cgl::normalise(&a);

    
    return 0;
}

// Programı çalıştır: Ctrl + F5 veya Hata Ayıkla > Hata Ayıklamadan Başlat menüsü
// Programda hata ayıkla: F5 veya Hata Ayıkla > Hata Ayıklamayı Başlat menüsü

// Kullanmaya Başlama İpuçları: 
//   1. Dosyaları eklemek/yönetmek için Çözüm Gezgini penceresini kullanın
//   2. Kaynak denetimine bağlanmak için Takım Gezgini penceresini kullanın
//   3. Derleme çıktısını ve diğer iletileri görmek için Çıktı penceresini kullanın
//   4. Hataları görüntülemek için Hata Listesi penceresini kullanın
//   5. Yeni kod dosyaları oluşturmak için Projeye Git > Yeni Öğe ekle veya varolan kod dosyalarını projeye eklemek için Proje > Var Olan Öğeyi Ekle adımlarını izleyin
//   6. Bu projeyi daha sonra yeniden açmak için Dosya > Aç > Proje'ye gidip .sln uzantılı dosyayı seçin
