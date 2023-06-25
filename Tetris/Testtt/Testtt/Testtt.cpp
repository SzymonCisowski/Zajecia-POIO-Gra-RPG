#include <SFML/Graphics.hpp>
#include <time.h>
#include <string.h>
using namespace sf;

sf::Text text;
sf::Text text2;

sf::Font font;


const int M = 22;
const int N = 12;

int mapa[M][N] = { 0 };
int punkty = 0;
bool stop = false;
struct Punkt
{
    int x, y;
};

Punkt a[4], b[4];

int ksztalty[7][4] =
{
    1,3,5,7, 
    2,4,5,7, 
    3,5,4,6, 
    3,5,4,7, 
    2,3,5,7, 
    3,5,7,6, 
    2,3,4,5, 
};

bool sprawdz_kolizje()
{
    for (int i = 0;i < 4;i++)
    {
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
        else if (mapa[a[i].y][a[i].x]) return 0;
    }

    return 1;
};

void przesun(int krok)
{
    for (int i = 0;i < 4;i++) 
    { 
        b[i] = a[i]; 
        a[i].x += krok; 
    }
    if (!sprawdz_kolizje())
    {
        for (int i = 0;i < 4;i++)
        {
            a[i] = b[i];
        }
        
    }
    
};

void obroc()
{
    Punkt p = a[1];
    for (int i = 0;i < 4;i++)
    {
        int x = a[i].y - p.y;
        int y = a[i].x - p.x;
        a[i].x = p.x - x;
        a[i].y = p.y + y;
    }
    if (!sprawdz_kolizje())
    {
        for (int i = 0;i < 4;i++)
        {
            a[i] = b[i];
        }
        
    }

};

void sprawdz_linie(int k)
{
    for (int i = M - 1;i > 0;i--)
    {
        int count = 0;
        for (int j = 0;j < N;j++)
        {
            if (mapa[i][j])
            {
                count++;
                
            }
            mapa[k][j] = mapa[i][j];
        }
        if (count < N)
        {
            k--;
            
        }
        else
        {
            punkty++;
        }
        
    }
};


int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(1200, 1185), "Witaj w Grze Tetris!");

    Texture t1, t2,t3;

    t1.loadFromFile("images/tiles_v4.png");
    t2.loadFromFile("images/background_v3.png");
    t3.loadFromFile("images/score.png");

    Sprite s(t1), background(t2), score_frame(t3);

    int kolor = 1;
    float timer = 0, delay = 0.3;

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::Up) obroc();
                else if (e.key.code == Keyboard::Left) przesun(-1);
                else if (e.key.code == Keyboard::Right) przesun(1);
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;

        
        if (timer > delay and stop != true)
        {
            for (int g = 0; g < N; g++)
            {
                if (mapa[2][g] != 0)
                {
                    text.setCharacterSize(50);
                    text.setString("Game over !!!");
                    text.setPosition(780, 500);
                    window.draw(text);
                    window.display();
                    stop = true;
                    

                }
            }
            for (int i = 0;i < 4;i++) 
            { 
                b[i] = a[i]; 
                a[i].y += 1; 
            }


            if (!sprawdz_kolizje())
            {
                for (int i = 0;i < 4;i++)
                {
                    mapa[b[i].y][b[i].x] = kolor;
                }
                

                kolor = 1 + rand() % 7;
                int n = rand() % 7;
                for (int i = 0;i < 4;i++)
                {
                    a[i].x = ksztalty[n][i] % 2;
                    a[i].y = ksztalty[n][i] / 2;

  
                }
            }

            timer = 0;
        }

        if (stop != true)
        {
            int k = M - 1;
        sprawdz_linie(k);

        delay = 0.3;

        
        window.clear(Color::White);
        window.draw(background);

        for (int i = 0;i < M;i++)
            for (int j = 0;j < N;j++)
            {
                if (mapa[i][j] == 0) continue;
                s.setTextureRect(IntRect(mapa[i][j] * 54-54, 0, 54, 54));
                s.setPosition(j * 54, i * 54);
                s.move(0, 0);
                window.draw(s);
            }

        for (int i = 0;i < 4;i++)
        {
            s.setTextureRect(IntRect(kolor * 54-54, 0, 54, 54));
            s.setPosition(a[i].x * 54, a[i].y * 54);
            s.move(0, 0); 
            window.draw(s);
        }

        text.setPosition(830, 230);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Magenta);
        text.setStyle(sf::Text::Bold);
        text.setString("Zdobyte Punkty:");
        font.loadFromFile("arial.ttf");
        text.setFont(font);

        text2.setPosition(920, 270);
        text2.setCharacterSize(40);
        text2.setFillColor(sf::Color::Magenta);
        text2.setStyle(sf::Text::Bold);
        char buf[128];
        sprintf_s(buf, "%d", punkty);
        std::string out = buf;
        text2.setString(out);
        text2.setFont(font);

        score_frame.setPosition(750, 100);
        window.draw(score_frame);
        window.draw(text);
        window.draw(text2);
        window.display();


        }
        
        
    }

    return 0;
}
