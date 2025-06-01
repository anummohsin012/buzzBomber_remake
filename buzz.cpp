
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <fstream>

using namespace std;
using namespace sf;

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.

const int resolutionX = 960;
const int resolutionY = 640;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionY / boxPixelsY; // Total 20 rows on grid
const int gameColumns = resolutionX / boxPixelsX; // Total 30 columns on grid

// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = { 0 };

//declaring functions
void drawMenu(RenderWindow& window, Font& font, int selectedOption, Sprite& menuSprite);
int menuLoop(RenderWindow& window, Sprite& menuSprite);
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite);
void movePlayer(float& player_x, float& player_y, Clock& playerClock, const Sprite& playerSprite, int gameGrid[20][30], int boxPixelsY, int boxPixelsX);
void fireBullet(bool& bullet_exists, float& bullet_x, float player_x, float& bullet_y, float player_y, int& bullets, bool& space_pressed);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite);
void drawSpray2(RenderWindow& window, float& spray2_x, float& spray2_y, Sprite& spray2sprite);
void drawSpray3(RenderWindow& window, float& spray3_x, float& spray3_y, Sprite& spray3sprite);
void decrement_sprays(int& bullets, int& sprays);
void drawkiller(RenderWindow& window, float killer_x[], float killer_y[], bool movingRight[], Sprite& killerSprite, Sprite& killerrevSprite, bool killer_exists[], int numBees);
void movekiller(float killer_x[], float killer_y[], bool movingRight[], int currentRow[], Clock killerClock[], int beeIndex, int gameColumns, int boxPixelsX, int boxPixelsY, int gameGrid[20][30], bool killer_exists[], int& beesRemainingl4, Sprite& hiveSprite, RenderWindow& window, float& hive_x, float& hive_y);
void drawworker(RenderWindow& window, float worker_x[], float worker_y[], bool movingRight[], Sprite& workerSprite, Sprite& workerrevSprite, bool worker_exists[], int numBees);
void moveworker(float worker_x[], float worker_y[], bool movingRight[], int currentRow[], Clock workerClock[], int beeIndex, int gameColumns, int boxPixelsX, int boxPixelsY, int gameGrid[20][30], bool worker_exists[], int& beesRemainingl4, Sprite& hiveSprite, RenderWindow& window, float& hive_x, float& hive_y);
void drawflowers(RenderWindow& window, int flowers_x, int flowers_y, Sprite& flowersSprite);
void drawyellow(RenderWindow& window, float bullet_x, float bullet_y, float worker_x[], float worker_y[], bool worker_exists[], Sprite& yellowSprite, float player_x, float player_y, int gameGrid[20][30], int boxPixelsY, int boxPixelsX, int& score, int& bees1, const int MaxBees, bool bullet_exists);
void drawred(RenderWindow& window, float bullet_x, float bullet_y, float killer_x[], float killer_y[], bool killer_exists[], Sprite& redSprite, float player_x, float player_y, int gameGrid[20][30], int boxPixelsY, int boxPixelsX, int& score, int& bees1, const int MaxBees, bool bullet_exists);
void generateHoneycombs(int gameGrid[20][30], int gameRows, int gameColumns, int boxPixelsY, int boxPixelsX, int numHoneycombs);
void moveHummingbird(float& humming_x, float& humming_y, float& target_x, float& target_y, int gameRows, int gameColumns, int boxPixelsX, int boxPixelsY, bool& movingRight, Clock& movementClock, Clock& pauseClock, bool& paused);
void checkAndEatHoneycomb(int gameGrid[20][30], float humming_x, float humming_y, int boxPixelsX, int boxPixelsY, int& score);
void checkingsprayedbird(bool& isSprayed, float& bullet_x, float& bullet_y, bool& bullet_exists, float player_x, float player_y, int& sprayedBird, bool& humming_sick, Clock& sickClock, float humming_x, float humming_y);
Sprite& birdSpriteUsed(bool movingRight, bool humming_sick, Sprite& hummingSprite, Sprite& hummingrevSprite, Sprite& invisibleSprite, Clock& sickClock);
void drawHummingbird(RenderWindow& window, float humming_x, float humming_y, Sprite& hummingSprite, Sprite& hummingrevSprite, bool movingRight, bool humming_sick, Sprite& invisibleSprite, Clock& sickClock);
void displayhighscore(RenderWindow& window, Sprite& highscoreSprite,const int max_displayed, string highscore_file, const Font& font);
void updatedHighscores(RenderWindow& window, Sprite& highscoreSprite,const int max_displayed, string highscore_file, const Font& font, int score);
void sethive(bool bee_exists[], int gameGrid[20][30], float bee_x[], float bee_y[], Sprite hiveSprite, int beeIndex, float& hive_x, float& hive_y, int& beesRemainingl4);
void drawhive(RenderWindow& window, int gameGrid[20][30], float hive_x, float hive_y, Sprite& hiveSprite);
void destroyhive(float& bullet_x, float& bullet_y, bool bullet_exists, float player_x, float player_y, float hive_x, float hive_y, int gameGrid[20][30]);
void generateHives(int gameGrid[20][30], int numHives, float& hive_x, float& hive_y);

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Write your functions declarations here. Some have been written for you. //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


int main()
{
    srand(static_cast<unsigned>(time(0)));

    // Declaring RenderWindow.
    RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);

    // Used to position your window on every launch. Use according to your needs.
    window.setPosition(Vector2i(500, 200));

    // Initializing Background Music.
    Music bgMusicLevel1;
    Music bgMusicLevel2;
    Music bgMusicLevel3;


    if (!bgMusicLevel1.openFromFile("Music/Music1.ogg") ||
        !bgMusicLevel2.openFromFile("Music/Music2.ogg") ||
        !bgMusicLevel3.openFromFile("Music/Music3.ogg"))
    {
        cout << "Error loading music files!" << endl;
        return -1;
    }
    bgMusicLevel1.setVolume(30);
    bgMusicLevel2.setVolume(30);
    bgMusicLevel3.setVolume(30);
    bgMusicLevel1.setLoop(true);
    bgMusicLevel2.setLoop(true);
    bgMusicLevel3.setLoop(true);

    bool bgmusicplayed1 = false;
    bool bgmusicplayed2 = false;
    bool bgmusicsplayed3 = false;
    bool bgmusicplayed4 = false;

    // Initializing Player and Player Sprites.
    Clock playerClock;
    float player_x = (gameColumns / 2) * boxPixelsX;
    float player_y = (gameRows - 3) * boxPixelsY;

    Texture playerTexture;
    Sprite playerSprite;
    playerTexture.loadFromFile("Textures/spray.png");
    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(1, 1);
    //playerSprite.setTextureRect(IntRect(0, 0, boxPixelsX, boxPixelsY));

    // Initializing Bullet and Bullet Sprites
    // Data for bullet / Spray pellet

    float bullet_x = player_x;
    float bullet_y = player_y;
    bool bullet_exists = true;
    bool space_pressed = false;


    int bullets = 56;
    Clock bulletClock;
    Texture bulletTexture;
    Sprite bulletSprite;
    bulletTexture.loadFromFile("Textures/bullet.png");
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setScale(3, 3);
    bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

    // The ground on which player moves

    RectangleShape groundRectangle(Vector2f(960, 64));
    groundRectangle.setPosition(0, (gameRows - 2) * boxPixelsX);
    groundRectangle.setFillColor(sf::Color(34, 139, 34));


    //the extra two spray cans

    float spray2_x = 10;
    float spray2_y = (gameRows - 1.75) * boxPixelsY;

    Texture spray2Texture;
    Sprite spray2Sprite;
    spray2Texture.loadFromFile("Textures/spray.png");
    spray2Sprite.setTexture(spray2Texture);
    spray2Sprite.setScale(0.75, 0.75);


    float spray3_x = 40;
    float spray3_y = (gameRows - 1.75) * boxPixelsY;

    Texture spray3Texture;
    Sprite spray3Sprite;
    spray3Texture.loadFromFile("Textures/spray.png");
    spray3Sprite.setTexture(spray3Texture);
    spray3Sprite.setScale(0.75, 0.75);


    //bonuses
    bool extracan1 = false;
    bool extracan2 = false;
    bool extracan3 = false;

    int sprays = 3;

    //variables for hummingbird

    float humming_x = (rand() % gameColumns - 2) * boxPixelsX;
    float humming_y = (rand() % (gameRows - 4)) * boxPixelsY; // Stay above the grass
    float target_x = humming_x;
    float target_y = humming_y; // game starts with hummingbird on random position
    bool humming_sick = false;
    int sprayedbird = 0;
    bool birdmovingRight;
    bool isSprayed;
    Clock movementClock;
    Clock sickClock;
    Clock pauseClock;
    bool paused = false;




    //moving left
    Texture hummingTexture;
    Sprite hummingSprite;
    hummingTexture.loadFromFile("Textures/birdrev.png");
    hummingSprite.setTexture(hummingTexture);
    hummingSprite.setScale(2, 2);
    hummingSprite.setTextureRect(sf::IntRect(boxPixelsX, 0, boxPixelsX, boxPixelsY));

    //moving right
    Texture hummingrevTexture;
    Sprite hummingrevSprite;
    hummingrevTexture.loadFromFile("Textures/bird.png");
    hummingrevSprite.setTexture(hummingrevTexture);
    hummingrevSprite.setScale(2, 2);
    hummingrevSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

    //for when the humming bird is sick
    Texture invisibleTexture;
    Sprite invisibleSprite;
    invisibleTexture.loadFromFile("Texture/invisibleSprite.png");
    invisibleSprite.setTexture(invisibleTexture);
    invisibleSprite.setScale(2, 2);
    invisibleSprite.setTextureRect(IntRect(0, 0, boxPixelsX, boxPixelsY));
    invisibleSprite.setColor(Color::Transparent);

    //killer bees for level 2
    const int MaxKBees2 = 5;
    float killer_x2[MaxKBees2], killer_y2[MaxKBees2];
    bool movingRightK2[MaxKBees2];
    bool killer_existsK2[MaxKBees2] = { false };
    int currentRowK2[MaxKBees2] = { 0 };
    Clock killerClockK2[MaxKBees2];
    // Array for random spawn intervals
    float beeSpawnIntervalsK2[MaxKBees2];
    int KbeeSpawnCountl2 = 0;

    //killer bees for level 3
    const int MaxKBees3 = 10;
    float killer_x3[MaxKBees3], killer_y3[MaxKBees3];
    bool movingRightK3[MaxKBees3];
    bool killer_existsK3[MaxKBees3] = { false };
    int currentRowK3[MaxKBees3] = { 0 };
    Clock killerClockK3[MaxKBees3];
    // Array for random spawn intervals
    float beeSpawnIntervalsK3[MaxKBees3];
    int KbeeSpawnCountl3 = 0;

    //killer bees for level 4
    const int MaxKBees4 = 15;
    float killer_x4[MaxKBees4], killer_y4[MaxKBees4];
    bool movingRightK4[MaxKBees4];
    bool killer_existsK4[MaxKBees4] = { false };
    int currentRowK4[MaxKBees4] = { 0 };
    Clock killerClockK4[MaxKBees4];
    // Array for random spawn intervals
    float beeSpawnIntervalsK4[MaxKBees4];
    int KbeeSpawnCountl4 = 0;

    //random spawning time of bees
    for (int i = 0; i < MaxKBees2; ++i)
    {
        beeSpawnIntervalsK2[i] = 0.5f + static_cast<float>(rand() % 100) / 100.0f;
    }

    for (int i = 0; i < MaxKBees3; ++i)
    {
        beeSpawnIntervalsK3[i] = 0.5f + static_cast<float>(rand() % 100) / 100.0f;
    }

    for (int i = 0; i < MaxKBees4; ++i)
    {
        beeSpawnIntervalsK4[i] = 0.5f + static_cast<float>(rand() % 100) / 100.0f;
    }


    //killer moving left
    Texture killerTexture;
    Sprite killerSprite;
    killerTexture.loadFromFile("Textures/Fast_bee.png");
    killerSprite.setTexture(killerTexture);
    killerSprite.setScale(1, 1);
    killerSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX * 2, boxPixelsY));

    //killer moving right
    Texture killerrevTexture;
    Sprite killerrevSprite;
    killerrevTexture.loadFromFile("Textures/Fast_beerev.png");
    killerrevSprite.setTexture(killerrevTexture);
    killerrevSprite.setScale(1, 1);
    killerrevSprite.setTextureRect(sf::IntRect(0.5 * boxPixelsX, 0, boxPixelsX * 2, boxPixelsY));


    //for worker_bees

    // Maximum number of bees for level 1
    const int MaxWBees1 = 20;
    float worker_x[MaxWBees1], worker_y[MaxWBees1];
    bool movingRight[MaxWBees1];
    bool worker_exists[MaxWBees1] = { false };
    int currentRow[MaxWBees1] = { 0 };
    Clock workerClock[MaxWBees1], beeSpawnClock;
    int beeSpawnCountl1 = 0;
    // Array for random spawn intervals
    float beeSpawnIntervals[MaxWBees1]; // (trueleft, falseright)
    bool spawnFromLeft = true;

    //max number for worker level2
    const int MaxWBees2 = 15;
    float worker_x2[MaxWBees2], worker_y2[MaxWBees2];
    bool movingRight2[MaxWBees2];
    bool worker_exists2[MaxWBees2] = { false };
    int currentRow2[MaxWBees2] = { 0 };
    Clock workerClock2[MaxWBees2];
    float beeSpawnIntervals2[MaxWBees2];
    int beeSpawnCountl2 = 0;

    //max number for worker level3
    const int MaxWBees3 = 20;
    float worker_x3[MaxWBees3], worker_y3[MaxWBees3];
    bool movingRight3[MaxWBees3];
    bool worker_exists3[MaxWBees3] = { false };
    int currentRow3[MaxWBees3] = { 0 };
    Clock workerClock3[MaxWBees3];
    float beeSpawnIntervals3[MaxWBees3];
    int beeSpawnCountl3 = 0;

    //max number for workers level 4
    const int MaxWBees4 = 20;
    float worker_x4[MaxWBees4], worker_y4[MaxWBees4];
    bool movingRight4[MaxWBees4];
    bool worker_exists4[MaxWBees4] = { false };
    int currentRow4[MaxWBees4] = { 0 };
    Clock workerClock4[MaxWBees4];
    float beeSpawnIntervals4[MaxWBees4];
    int beeSpawnCountl4 = 0;

    // random spawn intervals between 1.0 and 4.0 seconds for each bee
    for (int i = 0; i < MaxWBees1; ++i)
    {
        beeSpawnIntervals[i] = 0.5f + static_cast<float>(rand() % 100) / 100.0f;
    }

    for (int i = 0; i < MaxWBees2; ++i)
    {
        beeSpawnIntervals2[i] = 0.5f + static_cast<float>(rand() % 100) / 100.0f;
    }

    for (int i = 0; i < MaxWBees3; ++i)
    {
        beeSpawnIntervals3[i] = 0.5f + static_cast<float>(rand() % 100) / 100.0f;
    }

    for (int i = 0; i < MaxWBees4; ++i)
    {
        beeSpawnIntervals4[i] = 0.5f + static_cast<float>(rand() % 100) / 100.0f;
    }


    //bee moving left
    Texture workerTexture;
    Sprite workerSprite;
    workerTexture.loadFromFile("Textures/normalrev.png");
    workerSprite.setTexture(workerTexture);
    workerSprite.setScale(1, 1);
    workerSprite.setTextureRect(sf::IntRect(8.5 * boxPixelsX, 0, boxPixelsX, boxPixelsY));


    //for bee moving right
    Texture workerrevTexture;
    Sprite workerrevSprite;
    workerrevTexture.loadFromFile("Textures/normal.png");
    workerrevSprite.setTexture(workerrevTexture);
    workerrevSprite.setScale(1, 1);
    workerrevSprite.setTextureRect(sf::IntRect(0.5 * boxPixelsX, 0, boxPixelsX, boxPixelsY));

    //red honeycomb
    Texture redTexture;
    Sprite redSprite;
    redTexture.loadFromFile("Textures/honeycomb_red.png");
    redSprite.setTexture(redTexture);
    redSprite.setScale(1, 1);
    redSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX * 2, boxPixelsY * 2));

    //yellow honeycomb
    bool honeycombsGenerated = false; //for pre generated
    Texture yellowTexture;
    Sprite yellowSprite;
    yellowTexture.loadFromFile("Textures/honeycomb.png");
    yellowSprite.setTexture(yellowTexture);
    yellowSprite.setScale(1, 1);
    yellowSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX * 2, boxPixelsY * 2));

    //hive
    float hive_x;
    float hive_y;

    bool hivesgenerated = false;

    Texture hiveTexture;
    Sprite hiveSprite;
    hiveTexture.loadFromFile("Textures/hive.png");
    hiveSprite.setTexture(hiveTexture);
    hiveSprite.setScale(1, 1);
    hiveSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX * 2, boxPixelsY * 2));

    //obstacle flowers
    Texture flowersTexture;
    Sprite flowersSprite;
    flowersTexture.loadFromFile("Textures/obstacles.png");
    flowersSprite.setTexture(flowersTexture);
    flowersSprite.setScale(2, 2);
    flowersSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY * 2));

    //menu background
    Texture menuTexture;
    Sprite menuSprite;
    menuTexture.loadFromFile("Textures/menu.jpg");
    menuSprite.setTexture(menuTexture);
    menuSprite.setScale(1, 1);
    menuSprite.setTextureRect(sf::IntRect(0, 0, 960, 640));

    //for level changes
    Clock transitionClock;

    //level 1 bg
    Texture level1Texture;
    Sprite level1Sprite;
    level1Texture.loadFromFile("Textures/level1.jpg");
    level1Sprite.setTexture(level1Texture);
    level1Sprite.setScale(1, 1);
    level1Sprite.setTextureRect(sf::IntRect(0, 0, 960, 640));

    //level 2 bg
    Texture level2Texture;
    Sprite level2Sprite;
    level2Texture.loadFromFile("Textures/level2.jpg");
    level2Sprite.setTexture(level2Texture);
    level2Sprite.setScale(1, 1);
    level2Sprite.setTextureRect(sf::IntRect(0, 0, 960, 640));

    //level 3 bg
    Texture level3Texture;
    Sprite level3Sprite;
    level3Texture.loadFromFile("Textures/level3.jpg");
    level3Sprite.setTexture(level3Texture);
    level3Sprite.setScale(1, 1);
    level3Sprite.setTextureRect(sf::IntRect(0, 0, 960, 640));

    //level 4 bg
    Texture level4Texture;
    Sprite level4Sprite;
    level4Texture.loadFromFile("Textures/level4.jpg");
    level4Sprite.setTexture(level4Texture);
    level4Sprite.setScale(1, 1);
    level4Sprite.setTextureRect(sf::IntRect(0, 0, 960, 640));

    //for navigating menu options
    int level = menuLoop(window, menuSprite); //level5 means highscore option on menu
    if (level == -1)
        return 0; //in the case exit is chosen



    //for scores
    int score = 0;

    Font font;
    if (!font.loadFromFile("Fonts/arialceb.ttf"))
    {
        cout << "Error loading font!" << endl;
    }
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(sf::Color::White);


    int bees1 = 0; //ignore
    int yellows = 0; //ignore

    //condition for total bees to end level
    int beesRemainingl1 = 20;
    int beesRemainingl2 = 20;
    int beesRemainingl3 = 30;
    int beesRemainingl4 = 35;


    // for highscoring
    const int max_displayed = 10;
    const string highscore_file = "highscores.txt";
    Texture highscoreTexture;
    Sprite highscoreSprite;
    highscoreTexture.loadFromFile("Textures/highscore.jpg");
    highscoreSprite.setTexture(highscoreTexture);
    highscoreSprite.setScale(1, 1);
    highscoreSprite.setTextureRect(sf::IntRect(0, 0, 960, 640));
    bool displayedHS = false;

    while (window.isOpen())
    {

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                return 0;
            }
        }

        ///////////////////////////////////////////////////////////////
        //                                                           //
        // Call Your Functions Here. Some have been written for you. //
        // Be vary of the order you call them, SFML draws in order.  //
        //                                                           //
        /////////////////////////////////////////////////////////////// 



    //setting music for each level 
        if (level == 1)
        {
            if (!bgmusicplayed1)
            {
                bgMusicLevel1.play();
                bgmusicplayed1 = true;
            }
        }
        else if (level == 2)
        {
            if (!bgmusicplayed2)
            {
                bgMusicLevel1.stop();
                bgMusicLevel2.play();
                bgmusicplayed2 = true;
            }
        }
        else if (level == 3)
        {
            if (!bgmusicsplayed3)
            {
                bgMusicLevel2.stop();
                bgMusicLevel3.play();
                bgmusicsplayed3 = true;
            }
        }
        else if (level == 4)
        {
            if (!bgmusicplayed4)
            {
                bgMusicLevel3.stop();
                bgMusicLevel2.play();
                bgmusicplayed4 = true;
            }
        }





        //the first level 


        if (level == 1)
        {
            if (beesRemainingl1 > 0 && sprays > 0)
            {
                // Draw Level Background
                window.draw(level1Sprite);


                //To generate 3 random honeycombs
                if (!honeycombsGenerated)
                {
                    generateHoneycombs(gameGrid, gameRows, gameColumns, boxPixelsY, boxPixelsX, 3); // Generate 3 honeycombs
                    honeycombsGenerated = true; //can not generate more
                }


                // Spawn worker Bees
                if (beeSpawnCountl1 < MaxWBees1 && beeSpawnClock.getElapsedTime().asSeconds() >= beeSpawnIntervals[beeSpawnCountl1])
                {
                    worker_exists[beeSpawnCountl1] = true;  // Activate the next bee
                    movingRight[beeSpawnCountl1] = spawnFromLeft; // Determine spawn direction

                    // Set initial position based on spawn direction
                    if (spawnFromLeft)
                    {
                        worker_x[beeSpawnCountl1] = 0;  // Spawn from the left
                    }
                    else
                    {
                        worker_x[beeSpawnCountl1] = (gameColumns - 1) * boxPixelsX; // Spawn from the right
                    }
                    worker_y[beeSpawnCountl1] = 0; // Always start at the top


                    spawnFromLeft = !spawnFromLeft; // Toggle spawn direction
                    beeSpawnClock.restart();              // Reset the timer
                    beeSpawnCountl1++;                   // Increment the count
                }



                // Handle Bee Movement and Drawing
                for (int i = 0; i < MaxWBees1; ++i)
                {
                    if (worker_exists[i])
                    {
                        moveworker(worker_x, worker_y, movingRight, currentRow, workerClock, i, gameColumns, boxPixelsX, boxPixelsY, gameGrid, worker_exists, beesRemainingl1, hiveSprite, window, hive_x, hive_y);
                        drawworker(window, worker_x, worker_y, movingRight, workerSprite, workerrevSprite, worker_exists, MaxWBees1);
                        // If the bee reaches the ground, draw flowers
                        if (worker_y[i] == (gameRows - 3) * boxPixelsY)
                        {
                            float flowers_x = worker_x[i];
                            float flowers_y = worker_y[i] - boxPixelsY;
                            gameGrid[static_cast<int>(flowers_y / boxPixelsY)][static_cast<int>(flowers_x / boxPixelsX)] = 1;  // Update grid with flower

                            worker_exists[i] = false; //deleting that bee
                            beesRemainingl1--;
                        }
                    }

                }

                destroyhive(bullet_x, bullet_y, bullet_exists, player_x, player_y, hive_x, hive_y, gameGrid);


                //drawing the flowers due to bee pollinating grass
                for (int i = 0; i < gameRows; ++i)
                {
                    for (int j = 0; j < gameColumns; ++j)
                    {
                        if (gameGrid[i][j] == 1)  // Flower exists
                        {
                            float flowers_x = j * boxPixelsX;
                            float flowers_y = i * boxPixelsY;
                            flowersSprite.setPosition(flowers_x, flowers_y);
                            window.draw(flowersSprite);
                        }
                    }
                }



                // Draw Honeycombs according to set positions in drawyellow function
                for (int row = 0; row < gameRows; ++row)
                {
                    for (int col = 0; col < gameColumns; ++col)
                    {
                        if (gameGrid[row][col] == 2)  // Check for honeycomb
                        {
                            const float honeycomb_x = col * boxPixelsX;
                            const float honeycomb_y = row * boxPixelsY;

                            if (bullet_exists && gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] == 2)
                            {
                                // Destroy honeycomb
                                gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] = 0;
                                // Reset bullet to player's position
                                bullet_x = player_x;
                                bullet_y = player_y;
                                bullet_exists = false;
                            }
                            if (gameGrid[row][col] == 2)
                            {
                                yellowSprite.setPosition(honeycomb_x, honeycomb_y);
                                window.draw(yellowSprite);  // Draw honeycomb
                            }
                        }
                    }
                }



                // Draw Ground
                window.draw(groundRectangle);


                //bonus cans
                if (score > 20000)
                {
                    if (!extracan1)
                    {
                        sprays += 1;
                        extracan1 = true;
                    }
                }
                if (score > 40000)
                {
                    if (!extracan2)
                    {
                        sprays += 1;
                        extracan2 = true;
                    }
                }
                if (score > 80000)
                {
                    if (!extracan3)
                    {
                        sprays += 1;
                        extracan3 = true;
                    }
                }


                // Draw Sprays
                if (sprays == 3)
                {
                    if (bullets > 48)
                    {
                        drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
                        drawSpray3(window, spray3_x, spray3_y, spray3Sprite);
                    }
                    else if (bullets <= 48 && bullets > 0)
                    {
                        int i = (48 - bullets) / 7;
                        int height_offset = boxPixelsY * 2 - i * (boxPixelsY * 2 / 7);

                        drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
                        spray3Sprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX * 2, height_offset));
                        drawSpray3(window, spray3_x, spray3_y, spray3Sprite);
                    }
                }
                else if (sprays == 2)
                {
                    if (bullets > 48)
                    {
                        drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
                    }
                    else if (bullets <= 48 && bullets > 7)
                    {
                        int i = (48 - bullets) / 7;
                        int height_offset = boxPixelsY * 2 - i * (boxPixelsY * 2 / 7);
                        spray2Sprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX * 2, height_offset));
                        drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
                    }
                }



                // Handle Bullets
                fireBullet(bullet_exists, bullet_x, player_x, bullet_y, player_y, bullets, space_pressed);
                if (bullet_exists)
                {
                    moveBullet(bullet_y, bullet_exists, bulletClock);
                    drawBullet(window, bullet_x, bullet_y, bulletSprite);
                }





                // Detect Bullet Collision with Bees
                for (int i = 0; i < MaxWBees1; ++i)
                {
                    if (worker_exists[i])
                    {
                        drawyellow(window, bullet_x, bullet_y, worker_x, worker_y, worker_exists, yellowSprite, player_x, player_y, gameGrid, boxPixelsY, boxPixelsX, score, beesRemainingl1, MaxWBees1, bullet_exists);
                    }
                }



                // Draw and Move Player
                drawPlayer(window, player_x, player_y, playerSprite);
                movePlayer(player_x, player_y, playerClock, playerSprite, gameGrid, boxPixelsY, boxPixelsX);



                // Reset the space_pressed flag when space is released
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    space_pressed = false;
                }



                // Decrement sprays based on bullets
                decrement_sprays(bullets, sprays);


                //hummingbird funtions
                moveHummingbird(humming_x, humming_y, target_x, target_y, gameRows, gameColumns, boxPixelsX, boxPixelsY, birdmovingRight, movementClock, pauseClock, paused);
                checkAndEatHoneycomb(gameGrid, humming_x, humming_y, boxPixelsX, boxPixelsY, score);
                checkingsprayedbird(isSprayed, bullet_x, bullet_y, bullet_exists, player_x, player_y, sprayedbird, humming_sick, sickClock, humming_x, humming_y);
                birdSpriteUsed(birdmovingRight, humming_sick, hummingSprite, hummingrevSprite, invisibleSprite, sickClock);
                drawHummingbird(window, humming_x, humming_y, hummingSprite, hummingrevSprite, birdmovingRight, humming_sick, invisibleSprite, sickClock);



                // Display Score
                scoreText.setPosition(750.f, 590.f);
                scoreText.setString("SCORE: " + std::to_string(score));
                window.draw(scoreText);
                window.display();
            }




            else if (beesRemainingl1 == 0 && sprays > 0)//level 1 complete 

            {
                //checking for hives and adding to the total score
                for (int i = 0; i < gameRows; ++i)
                {
                    for (int j = 0; j < gameColumns; ++j)
                    {
                        if (gameGrid[i][j] == 4)  // Flower exists
                        {
                            if (i == 0 || i == 1)
                            {
                                score += 2000;
                            }
                            else if (i == 3 || i == 4 || i == 5)
                            {
                                score += 1600;
                            }
                            else
                            {
                                score += 1000;
                            }
                        }
                    }
                }


                //making gamegrid empty again for next level
                for (int i = 0; i < gameRows; ++i)
                {
                    for (int j = 0; j < gameColumns; ++j)
                    {
                        gameGrid[i][j] = 0;
                    }
                }


                honeycombsGenerated = false; //so pregenerated honeycombs can be made in next level

                sleep(seconds(2));
                //pause screen for 2 seconds

                window.clear(); //clear the screen


                // Draw Level Background
                window.draw(level1Sprite);
                scoreText.setPosition(resolutionX / 2 - 300, 300);
                scoreText.setCharacterSize(30);
                scoreText.setFillColor(Color::Yellow);
                scoreText.setString(" LEVEL 1 PASSED WITH SCORE: " + std::to_string(score));
                window.draw(scoreText);
                window.display();
                sleep(seconds(2));

                window.clear(); //clear the screen

                // Draw next Level Background
                window.draw(level2Sprite);
                Text level2dec;
                level2dec.setFont(font);
                level2dec.setString("LEVEL 2");
                level2dec.setCharacterSize(80);
                level2dec.setFillColor(Color::Yellow);
                level2dec.setPosition(resolutionX / 2 - 150, 500);
                window.draw(level2dec);
                window.display();

                sleep(seconds(2));

                //increment level
                level++;
            }

            else if (sprays == 0) //level 1 failed
            {

                if (!displayedHS)
                {
                    window.clear();
                    Text failed;
                    failed.setFont(font);
                    failed.setString("LEVEL1 FAILED");
                    failed.setCharacterSize(80);
                    failed.setFillColor(Color::Yellow);
                    failed.setPosition(resolutionX / 2 - 300, 300);
                    window.draw(failed);
                    window.display();
                    sleep(seconds(2));

                    updatedHighscores(window, highscoreSprite, max_displayed, highscore_file, font, score);
                    displayedHS = true;

                    for (int i = 0; i < gameRows; ++i) {
                        for (int j = 0; j < gameColumns; ++j) {
                            gameGrid[i][j] = 0;
                        }
                    }
                    honeycombsGenerated = false;
                    displayedHS = false;
                    sprays = 3;
                    level = menuLoop(window, menuSprite);

                }
            }

        }




        //level 2 condition
        else if (level == 2)
        {


            if (beesRemainingl2 > 0)
            {

                // Draw Level Background
                window.draw(level2Sprite);



                //To generate 3 random honeycombs
                if (!honeycombsGenerated)
                {
                    generateHoneycombs(gameGrid, gameRows, gameColumns, boxPixelsY, boxPixelsX, 9);
                    honeycombsGenerated = true; //can not generate more
                }




                // Spawn worker Bees
                if (beeSpawnCountl2 < MaxWBees2 && beeSpawnClock.getElapsedTime().asSeconds() >= beeSpawnIntervals2[beeSpawnCountl2])
                {
                    worker_exists2[beeSpawnCountl2] = true;  // Activate the next bee
                    movingRight2[beeSpawnCountl2] = spawnFromLeft; // Determine direction

                    // Set position based on direction
                    if (spawnFromLeft)
                    {
                        worker_x2[beeSpawnCountl2] = 0;  // from the left
                    }
                    else
                    {
                        worker_x2[beeSpawnCountl2] = (gameColumns - 1) * boxPixelsX; //from the right
                    }
                    worker_y2[beeSpawnCountl2] = 0; // Always start at the top


                    spawnFromLeft = !spawnFromLeft; // Toggle direction
                    beeSpawnClock.restart();              // Reset the timer
                    beeSpawnCountl2++;                   // Increment the count
                }



                // Spawn killer Bees
                if (KbeeSpawnCountl2 < MaxKBees2 && beeSpawnClock.getElapsedTime().asSeconds() >= beeSpawnIntervalsK2[beeSpawnCountl2])
                {
                    killer_existsK2[KbeeSpawnCountl2] = true;  // Activate the next bee
                    movingRightK2[KbeeSpawnCountl2] = spawnFromLeft; // Determine direction

                    //initial position based on direction
                    if (spawnFromLeft)
                    {
                        killer_x2[KbeeSpawnCountl2] = 0;  // Spawn from the left
                    }
                    else
                    {
                        killer_x2[KbeeSpawnCountl2] = (gameColumns - 1) * boxPixelsX; // Spawn from the right
                    }
                    killer_y2[KbeeSpawnCountl2] = 0; // Always start at the top


                    spawnFromLeft = !spawnFromLeft; // Toggle spawn direction
                    beeSpawnClock.restart();              // Reset the timer
                    KbeeSpawnCountl2++;                   // Increment the count
                }




                // Handle killer Bee Movement and Drawing
                for (int i = 0; i < MaxKBees2; ++i)
                {
                    if (killer_existsK2[i])
                    {
                        movekiller(killer_x2, killer_y2, movingRightK2, currentRowK2, killerClockK2, i, gameColumns, boxPixelsX, boxPixelsY, gameGrid, killer_existsK2, beesRemainingl2, hiveSprite, window, hive_x, hive_y);
                        drawkiller(window, killer_x2, killer_y2, movingRightK2, killerSprite, killerrevSprite, killer_existsK2, MaxKBees2);
                        // If the bee reaches the ground, mark flowers
                        if (killer_y2[i] == (gameRows - 3) * boxPixelsY)
                        {
                            int flowers_x = killer_x2[i];
                            int flowers_y = killer_y2[i] - boxPixelsY;
                            gameGrid[flowers_y / boxPixelsY][flowers_x / boxPixelsX] = 1;  // Update grid with flower
                            killer_existsK2[i] = false;
                            beesRemainingl2--;
                        }
                    }

                }



                // Handle worker Bee Movement and Drawing
                for (int i = 0; i < MaxWBees2; ++i)
                {
                    if (worker_exists2[i])
                    {
                        moveworker(worker_x2, worker_y2, movingRight2, currentRow2, workerClock2, i, gameColumns, boxPixelsX, boxPixelsY, gameGrid, worker_exists2, beesRemainingl2, hiveSprite, window, hive_x, hive_y);
                        drawworker(window, worker_x2, worker_y2, movingRight2, workerSprite, workerrevSprite, worker_exists2, MaxWBees2);
                        // If the bee reaches the ground, mark flowers
                        if (worker_y2[i] == (gameRows - 3) * boxPixelsY)
                        {
                            int flowers_x = worker_x2[i];
                            int flowers_y = worker_y2[i] - boxPixelsY;
                            gameGrid[flowers_y / boxPixelsY][flowers_x / boxPixelsX] = 1;  // Update grid with flower
                            worker_exists[i] = false;
                            beesRemainingl2--;
                        }
                    }

                }

                destroyhive(bullet_x, bullet_y, bullet_exists, player_x, player_y, hive_x, hive_y, gameGrid);

                //drawing flowers on marked areas 
                for (int i = 0; i < gameRows; ++i)
                {
                    for (int j = 0; j < gameColumns; ++j)
                    {
                        if (gameGrid[i][j] == 1)  // Flower exists
                        {
                            float flowers_x = j * boxPixelsX;
                            float flowers_y = i * boxPixelsY;
                            flowersSprite.setPosition(flowers_x, flowers_y);
                            window.draw(flowersSprite);
                        }
                    }
                }



                // Draw Honeycombs according to set positions in drawyellow function
                for (int row = 0; row < gameRows; ++row)
                {
                    for (int col = 0; col < gameColumns; ++col)
                    {
                        if (gameGrid[row][col] == 2)  // Check for honeycomb
                        {
                            const float honeycomb_x = col * boxPixelsX;
                            const float honeycomb_y = row * boxPixelsY;

                            if (bullet_exists && gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] == 2)
                            {
                                // Destroy honeycomb
                                gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] = 0;
                                // Reset bullet to player's position
                                bullet_x = player_x;
                                bullet_y = player_y;
                                bullet_exists = false;
                            }
                            if (gameGrid[row][col] == 2)
                            {
                                yellowSprite.setPosition(honeycomb_x, honeycomb_y);
                                window.draw(yellowSprite);  // Draw honeycomb
                            }
                        }
                    }
                }



                // Draw Red Honeycombs according to set positions in drawred function
                for (int row = 0; row < gameRows; ++row)
                {
                    for (int col = 0; col < gameColumns; ++col)
                    {
                        if (gameGrid[row][col] == 3)  // Check for honeycomb
                        {
                            const float honeycomb_x = col * boxPixelsX;
                            const float honeycomb_y = row * boxPixelsY;

                            if (bullet_exists && gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] == 3)
                            {
                                // Destroy honeycomb
                                gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] = 0;
                                // Reset bullet to player's position
                                bullet_x = player_x;
                                bullet_y = player_y;
                                bullet_exists = false;
                            }
                            if (gameGrid[row][col] == 3)
                            {
                                redSprite.setPosition(honeycomb_x, honeycomb_y);
                                window.draw(redSprite);  // Draw honeycomb
                            }
                        }
                    }
                }


                // Draw Ground
                window.draw(groundRectangle);


                //bonus cans
                if (score > 20000)
                {
                    if (!extracan1)
                    {
                        sprays += 1;
                        extracan1 = true;
                    }
                }
                if (score > 40000)
                {
                    if (!extracan2)
                    {
                        sprays += 1;
                        extracan2 = true;
                    }
                }
                if (score > 80000)
                {
                    if (!extracan3)
                    {
                        sprays += 1;
                        extracan3 = true;
                    }
                }



                // Draw Sprays
                if (sprays == 3)
                {
                    if (bullets > 48)
                    {
                        drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
                        drawSpray3(window, spray3_x, spray3_y, spray3Sprite);
                    }
                    else if (bullets <= 48 && bullets > 0)
                    {
                        int i = (48 - bullets) / 7;
                        int height_offset = boxPixelsY * 2 - i * (boxPixelsY * 2 / 7);

                        drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
                        spray3Sprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX * 2, height_offset));
                        drawSpray3(window, spray3_x, spray3_y, spray3Sprite);
                    }
                }
                else if (sprays == 2)
                {
                    if (bullets > 48)
                    {
                        drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
                    }
                    else if (bullets <= 48 && bullets > 7)
                    {
                        int i = (48 - bullets) / 7;
                        int height_offset = boxPixelsY * 2 - i * (boxPixelsY * 2 / 7);
                        spray2Sprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX * 2, height_offset));
                        drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
                    }
                }



                // Handle Bullets
                fireBullet(bullet_exists, bullet_x, player_x, bullet_y, player_y, bullets, space_pressed);

                if (bullet_exists)
                {
                    moveBullet(bullet_y, bullet_exists, bulletClock);
                    drawBullet(window, bullet_x, bullet_y, bulletSprite);
                }




                // Detect Bullet Collision with Worker Bees
                for (int i = 0; i < MaxWBees2; ++i)
                {
                    if (worker_exists2[i])
                    {
                        drawyellow(window, bullet_x, bullet_y, worker_x2, worker_y2, worker_exists2, yellowSprite, player_x, player_y, gameGrid, boxPixelsY, boxPixelsX, score, beesRemainingl2, MaxWBees2, bullet_exists);
                    }
                }

                // Detect Bullet Collision with Killer Bees
                for (int i = 0; i < MaxKBees2; ++i)
                {
                    if (killer_existsK2[i])
                    {
                        drawred(window, bullet_x, bullet_y, killer_x2, killer_y2, killer_existsK2, redSprite, player_x, player_y, gameGrid, boxPixelsY, boxPixelsX, score, beesRemainingl2, MaxKBees2, bullet_exists);
                    }
                }



                // Draw and Move Player
                drawPlayer(window, player_x, player_y, playerSprite);
                movePlayer(player_x, player_y, playerClock, playerSprite, gameGrid, boxPixelsY, boxPixelsX);



                // Reset the space_pressed flag when space is released
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    space_pressed = false;
                }



                // Decrement sprays based on bullets
                decrement_sprays(bullets, sprays);


                //hummingbird movement anf behvaiour functions
                moveHummingbird(humming_x, humming_y, target_x, target_y, gameRows, gameColumns, boxPixelsX, boxPixelsY, birdmovingRight, movementClock, pauseClock, paused);
                checkAndEatHoneycomb(gameGrid, humming_x, humming_y, boxPixelsX, boxPixelsY, score);
                checkingsprayedbird(isSprayed, bullet_x, bullet_y, bullet_exists, player_x, player_y, sprayedbird, humming_sick, sickClock, humming_x, humming_y);
                birdSpriteUsed(birdmovingRight, humming_sick, hummingSprite, hummingrevSprite, invisibleSprite, sickClock);
                drawHummingbird(window, humming_x, humming_y, hummingSprite, hummingrevSprite, birdmovingRight, humming_sick, invisibleSprite, sickClock);


                // Display Score
                scoreText.setPosition(750.f, 590.f);
                scoreText.setString("SCORE: " + std::to_string(score));
                window.draw(scoreText);
                window.display();
            }




            else if (beesRemainingl2 == 0 && sprays > 0)//level 2 complete



            {
                //checking for hives and adding to the total score
                for (int i = 0; i < gameRows; ++i)
                {
                    for (int j = 0; j < gameColumns; ++j)
                    {
                        if (gameGrid[i][j] == 4)  // Flower exists
                        {
                            if (i == 0 || i == 1)
                            {
                                score += 2000;
                            }
                            else if (i == 3 || i == 4 || i == 5)
                            {
                                score += 1600;
                            }
                            else
                            {
                                score += 1000;
                            }
                        }
                    }
                }



                //making gamegrid empty again for next level
                for (int i = 0; i < gameRows; ++i)
                {
                    for (int j = 0; j < gameColumns; ++j)
                    {
                        gameGrid[i][j] = 0;
                    }
                }



                honeycombsGenerated = false; //so pregenerated honeycombs can be made in next level


                sleep(seconds(2));
                //pause screen for 2 seconds

                window.clear(); //clear the screen

                // Draw Level Background
                window.draw(level2Sprite);
                scoreText.setPosition(resolutionX / 2 - 300, 300);
                scoreText.setCharacterSize(30);
                scoreText.setFillColor(Color::Yellow);
                scoreText.setString(" LEVEL 2 PASSED WITH SCORE: " + std::to_string(score));
                window.draw(scoreText);
                window.display();
                sleep(seconds(2));


                window.clear(); //clear the screen

                // Draw next Level Background
                window.draw(level3Sprite);
                Text level3dec;
                level3dec.setFont(font);
                level3dec.setString("LEVEL 3");
                level3dec.setCharacterSize(80);
                level3dec.setFillColor(Color::Yellow);
                level3dec.setPosition(resolutionX / 2 - 150, 500);
                window.draw(level3dec);
                window.display();

                sleep(seconds(2));
                level++; //incrment to next level

            }

            else if (sprays == 0) //level 2 failed
            {

                if (!displayedHS)
                {
                    Text failed;
                    failed.setFont(font);
                    failed.setString("LEVEL2 FAILED");
                    failed.setCharacterSize(80);
                    failed.setFillColor(Color::Yellow);
                    failed.setPosition(resolutionX / 2 - 300, 300);
                    window.draw(failed);
                    window.display();
                    sleep(seconds(2));

                    updatedHighscores(window, highscoreSprite, max_displayed, highscore_file, font, score);
                    displayedHS = true;

                    for (int i = 0; i < gameRows; ++i) {
                        for (int j = 0; j < gameColumns; ++j) {
                            gameGrid[i][j] = 0;
                        }
                    }
                    honeycombsGenerated = false;
                    displayedHS = false;
                    sprays = 3;
                    level = menuLoop(window, menuSprite);

                }
            }
        }



        //level 3 condition
        else if (level == 3)
        {



            if (beesRemainingl3 > 0)
            {
                // Draw Level Background
                window.draw(level3Sprite);


                //To generate 15 random honeycombs
                if (!honeycombsGenerated)
                {
                    generateHoneycombs(gameGrid, gameRows, gameColumns, boxPixelsY, boxPixelsX, 15);
                    honeycombsGenerated = true; //can not generate more
                }



                // Spawn worker Bees
                if (beeSpawnCountl3 < MaxWBees3 && beeSpawnClock.getElapsedTime().asSeconds() >= beeSpawnIntervals3[beeSpawnCountl3])
                {
                    worker_exists3[beeSpawnCountl3] = true;  // Activate the next bee
                    movingRight3[beeSpawnCountl3] = spawnFromLeft; // Determine direction

                    // Set position based on direction
                    if (spawnFromLeft)
                    {
                        worker_x3[beeSpawnCountl3] = 0;  // Spawn from the left
                    }
                    else
                    {
                        worker_x3[beeSpawnCountl3] = (gameColumns - 1) * boxPixelsX; // Spawn from the right
                    }
                    worker_y3[beeSpawnCountl3] = 0; // Always start at the top


                    spawnFromLeft = !spawnFromLeft; // Toggle spawn direction
                    beeSpawnClock.restart();              // Reset the timer
                    beeSpawnCountl3++;                   // Increment the count
                }



                // Spawn killer Bees
                if (KbeeSpawnCountl3 < MaxKBees3 && beeSpawnClock.getElapsedTime().asSeconds() >= beeSpawnIntervalsK3[beeSpawnCountl3])
                {
                    killer_existsK3[KbeeSpawnCountl3] = true;  // Activate the next bee
                    movingRightK3[KbeeSpawnCountl3] = spawnFromLeft; // Determine direction

                    // Set position based on direction
                    if (spawnFromLeft)
                    {
                        killer_x3[KbeeSpawnCountl3] = 0;  // Spawn from the left
                    }
                    else
                    {
                        killer_x3[KbeeSpawnCountl3] = (gameColumns - 1) * boxPixelsX; // Spawn from the right
                    }
                    killer_y3[KbeeSpawnCountl3] = 0; // Always start at the top


                    spawnFromLeft = !spawnFromLeft; // Toggle spawn direction
                    beeSpawnClock.restart();              // Reset the timer
                    KbeeSpawnCountl3++;                   // Increment the count
                }




                // Handle worker Bee Movement and Drawing
                for (int i = 0; i < MaxWBees3; ++i)
                {
                    if (worker_exists3[i])
                    {
                        moveworker(worker_x3, worker_y3, movingRight3, currentRow3, workerClock3, i, gameColumns, boxPixelsX, boxPixelsY, gameGrid, worker_exists3, beesRemainingl3, hiveSprite, window, hive_x, hive_y);
                        drawworker(window, worker_x3, worker_y3, movingRight3, workerSprite, workerrevSprite, worker_exists3, MaxWBees3);
                        // If the bee reaches the ground, draw flowers
                        if (worker_y3[i] == (gameRows - 3) * boxPixelsY)
                        {
                            int flowers_x = worker_x3[i];
                            int flowers_y = worker_y3[i] - boxPixelsY;
                            gameGrid[flowers_y / boxPixelsY][flowers_x / boxPixelsX] = 1;  // Update grid with flower
                            worker_exists3[i] = false;
                            beesRemainingl3--;
                        }
                    }

                }



                // Handle killer Bee Movement and Drawing
                for (int i = 0; i < MaxKBees3; ++i)
                {
                    if (killer_existsK3[i])
                    {
                        movekiller(killer_x3, killer_y3, movingRightK3, currentRowK3, killerClockK3, i, gameColumns, boxPixelsX, boxPixelsY, gameGrid, killer_existsK3, beesRemainingl3, hiveSprite, window, hive_x, hive_y);
                        drawkiller(window, killer_x3, killer_y3, movingRightK3, killerSprite, killerrevSprite, killer_existsK3, MaxKBees3);
                        // If the bee reaches the ground, draw flowers
                        if (killer_y3[i] == (gameRows - 3) * boxPixelsY)
                        {
                            int flowers_x = killer_x3[i];
                            int flowers_y = killer_y3[i] - boxPixelsY;
                            gameGrid[flowers_y / boxPixelsY][flowers_x / boxPixelsX] = 1;  // Update grid with flower
                            killer_existsK3[i] = false;
                            beesRemainingl3--;
                        }
                    }

                }

                destroyhive(bullet_x, bullet_y, bullet_exists, player_x, player_y, hive_x, hive_y, gameGrid);

                //draw and display the flowers    
                for (int i = 0; i < gameRows; ++i)
                {
                    for (int j = 0; j < gameColumns; ++j)
                    {
                        if (gameGrid[i][j] == 1)  // Flower exists
                        {
                            float flowers_x = j * boxPixelsX;
                            float flowers_y = i * boxPixelsY;
                            flowersSprite.setPosition(flowers_x, flowers_y);
                            window.draw(flowersSprite);
                        }
                    }
                }



                // Draw yellow honeycombs according to set positions in drawyellow function
                for (int row = 0; row < gameRows; ++row)
                {
                    for (int col = 0; col < gameColumns; ++col)
                    {
                        if (gameGrid[row][col] == 2)  // Check for honeycomb
                        {
                            const float honeycomb_x = col * boxPixelsX;
                            const float honeycomb_y = row * boxPixelsY;

                            if (bullet_exists && gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] == 2)
                            {
                                // Destroy honeycomb
                                gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] = 0;
                                // Reset bullet to player's position
                                bullet_x = player_x;
                                bullet_y = player_y;
                                bullet_exists = false;
                            }
                            if (gameGrid[row][col] == 2)
                            {
                                yellowSprite.setPosition(honeycomb_x, honeycomb_y);
                                window.draw(yellowSprite);  // Draw honeycomb
                            }
                        }
                    }
                }



                // Draw Red Honeycombs according to set positions in drawred function
                for (int row = 0; row < gameRows; ++row)
                {
                    for (int col = 0; col < gameColumns; ++col)
                    {
                        if (gameGrid[row][col] == 3)  // Check for honeycomb
                        {
                            const float honeycomb_x = col * boxPixelsX;
                            const float honeycomb_y = row * boxPixelsY;

                            if (bullet_exists && gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] == 3)
                            {
                                // Destroy honeycomb
                                gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] = 0;
                                // Reset bullet to player's position
                                bullet_x = player_x;
                                bullet_y = player_y;
                                bullet_exists = false;
                            }
                            if (gameGrid[row][col] == 3)
                            {
                                redSprite.setPosition(honeycomb_x, honeycomb_y);
                                window.draw(redSprite);  // Draw honeycomb
                            }
                        }
                    }
                }



                // Draw Ground
                window.draw(groundRectangle);


                //bonus cans
                if (score > 20000)
                {
                    if (!extracan1)
                    {
                        sprays += 1;
                        extracan1 = true;
                    }
                }
                if (score > 40000)
                {
                    if (!extracan2)
                    {
                        sprays += 1;
                        extracan2 = true;
                    }
                }
                if (score > 80000)
                {
                    if (!extracan3)
                    {
                        sprays += 1;
                        extracan3 = true;
                    }
                }



                // Draw Sprays
                if (sprays == 3)
                {
                    if (bullets > 48)
                    {
                        drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
                        drawSpray3(window, spray3_x, spray3_y, spray3Sprite);
                    }
                    else if (bullets <= 48 && bullets > 0)
                    {
                        int i = (48 - bullets) / 8;
                        int height_offset = boxPixelsY * 2 - i * (boxPixelsY * 2 / 8);

                        drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
                        spray3Sprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX * 2, height_offset));
                        drawSpray3(window, spray3_x, spray3_y, spray3Sprite);
                    }
                }
                else if (sprays == 2)
                {
                    if (bullets > 48)
                    {
                        drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
                    }
                    else if (bullets <= 48 && bullets > 7)
                    {
                        int i = (48 - bullets) / 8;
                        int height_offset = boxPixelsY * 2 - i * (boxPixelsY * 2 / 8);
                        spray2Sprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX * 2, height_offset));
                        drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
                    }
                }




                // Handle Bullets
                fireBullet(bullet_exists, bullet_x, player_x, bullet_y, player_y, bullets, space_pressed);

                if (bullet_exists)
                {
                    moveBullet(bullet_y, bullet_exists, bulletClock);
                    drawBullet(window, bullet_x, bullet_y, bulletSprite);
                }




                // Detect Bullet Collision with Bees
                for (int i = 0; i < MaxWBees3; ++i)
                {
                    if (worker_exists3[i])
                    {
                        drawyellow(window, bullet_x, bullet_y, worker_x3, worker_y3, worker_exists3, yellowSprite, player_x, player_y, gameGrid, boxPixelsY, boxPixelsX, score, beesRemainingl3, MaxWBees3, bullet_exists);
                    }
                }




                // Detect Bullet Collision with Killer Bees
                for (int i = 0; i < MaxKBees3; ++i)
                {
                    if (killer_existsK3[i])
                    {
                        drawred(window, bullet_x, bullet_y, killer_x3, killer_y3, killer_existsK3, redSprite, player_x, player_y, gameGrid, boxPixelsY, boxPixelsX, score, beesRemainingl3, MaxKBees3, bullet_exists);
                    }
                }



                // Draw and Move Player
                drawPlayer(window, player_x, player_y, playerSprite);
                movePlayer(player_x, player_y, playerClock, playerSprite, gameGrid, boxPixelsY, boxPixelsX);



                // Reset the space_pressed flag when space is released
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    space_pressed = false;
                }



                // Decrement sprays based on bullets
                decrement_sprays(bullets, sprays);



                //functions to move and tackle behaviour of hummingbird
                moveHummingbird(humming_x, humming_y, target_x, target_y, gameRows, gameColumns, boxPixelsX, boxPixelsY, birdmovingRight, movementClock, pauseClock, paused);
                checkAndEatHoneycomb(gameGrid, humming_x, humming_y, boxPixelsX, boxPixelsY, score);
                checkingsprayedbird(isSprayed, bullet_x, bullet_y, bullet_exists, player_x, player_y, sprayedbird, humming_sick, sickClock, humming_x, humming_y);
                birdSpriteUsed(birdmovingRight, humming_sick, hummingSprite, hummingrevSprite, invisibleSprite, sickClock);
                drawHummingbird(window, humming_x, humming_y, hummingSprite, hummingrevSprite, birdmovingRight, humming_sick, invisibleSprite, sickClock);


                // Display Score
                scoreText.setPosition(750.f, 590.f);
                scoreText.setString("SCORE: " + std::to_string(score));
                window.draw(scoreText);
                window.display();
            }


            else if (beesRemainingl3 == 0 && sprays > 0)//level 3 complete


            {
                ////checking for hives and adding to the total score
                //for (int i = 0; i < gameRows; ++i)
                //{
                //    for (int j = 0; j < gameColumns; ++j)
                //    {
                //        if (gameGrid[i][j] == 4)  // Flower exists
                //        {
                //            if (i == 0 || i == 1)
                //            {
                //                score += 2000;
                //            }
                //            else if (i == 3 || i == 4 || i == 5)
                //            {
                //                score += 1600;
                //            }
                //            else
                //            {
                //                score += 1000;
                //            }
                //        }
                //    }
                //}



                ////making gamegrid empty again for next level
                //for (int i = 0; i < gameRows; ++i)
                //{
                //    for (int j = 0; j < gameColumns; ++j)
                //    {
                //        gameGrid[i][j] = 0;
                //    }
                //}


                //honeycombsGenerated = false; //so pregernated honeycombs can be made in next level


                //sleep(seconds(2));
                ////pause screen for 2 seconds

                //window.clear(); //clear the screen

                //// Draw Level Background
                //window.draw(level3Sprite);
                //scoreText.setPosition(resolutionX / 2 - 300, 300);
                //scoreText.setCharacterSize(30);
                //scoreText.setFillColor(Color::Yellow);
                //scoreText.setString(" LEVEL 3 PASSED WITH SCORE: " + std::to_string(score));
                //window.draw(scoreText);
                //window.display();
                //sleep(seconds(2));

                //window.clear(); //clear the screen


                //// Draw Level Background
                //window.draw(level4Sprite);
                //Text level4dec;
                //level4dec.setFont(font);
                //level4dec.setString("LEVEL 4");
                //level4dec.setCharacterSize(80);
                //level4dec.setFillColor(Color::Yellow);
                //level4dec.setPosition(resolutionX / 2 - 150, 500);
                //window.draw(level4dec);
                //window.display();

                //sleep(seconds(2));

                //level++; //increment level


                    sleep(seconds(2));
                    //pause screen for 2 seconds

                    window.clear(); //clear the screen

                    // Draw Level Background
                    window.draw(level3Sprite);
                    scoreText.setPosition(resolutionX / 2 - 300, 300);
                    scoreText.setCharacterSize(40);
                    scoreText.setFillColor(Color::Yellow);
                    scoreText.setString(" GAME PASSED WITH SCORE: " + std::to_string(score));
                    window.draw(scoreText);
                    window.display();
                    sleep(seconds(2));
                    window.clear();
                    window.draw(level3Sprite);

                    Text head;
                    head.setPosition(resolutionX / 2 - 300, 300);
                    head.setCharacterSize(40);
                    head.setFillColor(Color::Yellow);
                    head.setString(" ENTER NAME ON TERMINAL ");
                    window.draw(head);
                    window.display();
                    sleep(seconds(2));

                    updatedHighscores(window, highscoreSprite, max_displayed, highscore_file, font, score);
                    displayedHS = true;

                    // Reset game state before returning to menu
                    for (int i = 0; i < gameRows; ++i) {
                        for (int j = 0; j < gameColumns; ++j) {
                            gameGrid[i][j] = 0;
                        }
                    }
                    honeycombsGenerated = false;
                    displayedHS = false;
                    sprays = 3;
                    level = menuLoop(window, menuSprite);

            }


            else if ( sprays == 0) //level 3 failed
            {

                if (!displayedHS)
                {
                    window.clear();
                    Text failed;
                    failed.setFont(font);
                    failed.setString("LEVEL3 FAILED");
                    failed.setCharacterSize(80);
                    failed.setFillColor(Color::Yellow);
                    failed.setPosition(resolutionX / 2 - 300, 300);
                    window.draw(failed);
                    window.display();
                    sleep(seconds(2));

                    updatedHighscores(window, highscoreSprite, max_displayed, highscore_file, font, score);
                    displayedHS = true;

                    // Reset game state before returning to menu
                    for (int i = 0; i < gameRows; ++i) {
                        for (int j = 0; j < gameColumns; ++j) {
                            gameGrid[i][j] = 0;
                        }
                    }
                    honeycombsGenerated = false;
                    displayedHS = false;
                    sprays = 3;
                    level = menuLoop(window, menuSprite);


                }
            }

        }



        else if (level == 4)
            

        {
            cout << "Level 4\n";
            level = menuLoop(window, menuSprite);
            //if (beesRemainingl4 > 0)
            //{
            //    // Draw Level Background
            //    window.draw(level4Sprite);


            //    //To generate 5 random hives
            //    if (!hivesgenerated)
            //    {
            //        generateHives(gameGrid, 5, hive_x, hive_y);
            //        hivesgenerated = true; //can not generate more

            //    }

            //    //draw hives according to positions set
            //    drawhive(window, gameGrid, hive_x, hive_y, hiveSprite);

            //    //To generate 15 random honeycombs
            //    if (!honeycombsGenerated)
            //    {
            //        generateHoneycombs(gameGrid, gameRows, gameColumns, boxPixelsY, boxPixelsX, 15);
            //        honeycombsGenerated = true; //can not generate more
            //    }


            //    // Spawn worker Bees
            //    if (beeSpawnCountl4 < MaxWBees4 && beeSpawnClock.getElapsedTime().asSeconds() >= beeSpawnIntervals4[beeSpawnCountl4])
            //    {
            //        worker_exists4[beeSpawnCountl4] = true;  // Activate the next bee
            //        movingRight4[beeSpawnCountl4] = spawnFromLeft; // Determine direction

            //        // Set position based on direction
            //        if (spawnFromLeft)
            //        {
            //            worker_x4[beeSpawnCountl4] = 0;  // Spawn from the left
            //        }
            //        else
            //        {
            //            worker_x4[beeSpawnCountl4] = (gameColumns - 1) * boxPixelsX; // Spawn from the right
            //        }
            //        worker_y4[beeSpawnCountl4] = 0; // Always start at the top


            //        spawnFromLeft = !spawnFromLeft; // Toggle spawn direction
            //        beeSpawnClock.restart();              // Reset the timer
            //        beeSpawnCountl4++;                   // Increment the count
            //    }



            //    // Spawn killer Bees
            //    if (KbeeSpawnCountl4 < MaxKBees4 && beeSpawnClock.getElapsedTime().asSeconds() >= beeSpawnIntervalsK4[beeSpawnCountl4])
            //    {
            //        killer_existsK4[KbeeSpawnCountl4] = true;  // Activate the next bee
            //        movingRightK4[KbeeSpawnCountl4] = spawnFromLeft; // Determine direction

            //        // Set position based on direction
            //        if (spawnFromLeft)
            //        {
            //            killer_x4[KbeeSpawnCountl4] = 0;  // Spawn from the left
            //        }
            //        else
            //        {
            //            killer_x4[KbeeSpawnCountl4] = (gameColumns - 1) * boxPixelsX; // Spawn from the right
            //        }
            //        killer_y4[KbeeSpawnCountl4] = 0; // Always start at the top


            //        spawnFromLeft = !spawnFromLeft; // Toggle spawn direction
            //        beeSpawnClock.restart();              // Reset the timer
            //        KbeeSpawnCountl4++;                   // Increment the count
            //    }


            //    // Handle worker Bee Movement and Drawing
            //    for (int i = 0; i < MaxWBees4; ++i)
            //    {
            //        if (worker_exists4[i])
            //        {
            //            moveworker(worker_x4, worker_y4, movingRight4, currentRow4, workerClock4, i, gameColumns, boxPixelsX, boxPixelsY, gameGrid, worker_exists4, beesRemainingl4, hiveSprite, window, hive_x, hive_y);
            //            drawworker(window, worker_x4, worker_y4, movingRight4, workerSprite, workerrevSprite, worker_exists4, MaxWBees4);
            //            // If the bee reaches the ground, draw flowers
            //            if (worker_y4[i] == (gameRows - 3) * boxPixelsY)
            //            {
            //                int flowers_x = worker_x4[i];
            //                int flowers_y = worker_y4[i] - boxPixelsY;
            //                gameGrid[flowers_y / boxPixelsY][flowers_x / boxPixelsX] = 1;  // Update grid with flower
            //                worker_exists4[i] = false;
            //                beesRemainingl4--;
            //            }
            //        }

            //    }

            //    // Handle killer Bee Movement and Drawing
            //    for (int i = 0; i < MaxKBees4; ++i)
            //    {
            //        if (killer_existsK4[i])
            //        {
            //            movekiller(killer_x4, killer_y4, movingRightK4, currentRowK4, killerClockK4, i, gameColumns, boxPixelsX, boxPixelsY, gameGrid, killer_existsK3, beesRemainingl4, hiveSprite, window, hive_x, hive_y);
            //            drawkiller(window, killer_x4, killer_y4, movingRightK4, killerSprite, killerrevSprite, killer_existsK4, MaxKBees4);
            //            // If the bee reaches the ground, draw flowers
            //            if (killer_y4[i] == (gameRows - 3) * boxPixelsY)
            //            {
            //                int flowers_x = killer_x4[i];
            //                int flowers_y = killer_y4[i] - boxPixelsY;
            //                gameGrid[flowers_y / boxPixelsY][flowers_x / boxPixelsX] = 1;  // Update grid with flower
            //                killer_existsK4[i] = false;
            //                beesRemainingl4--;
            //            }
            //        }

            //    }


            //    //to handle hive collision with bullet   
            //    destroyhive(bullet_x, bullet_y, bullet_exists, player_x, player_y, hive_x, hive_y, gameGrid);

            //    //draw and display the flowers    
            //    for (int i = 0; i < gameRows; ++i)
            //    {
            //        for (int j = 0; j < gameColumns; ++j)
            //        {
            //            if (gameGrid[i][j] == 1)  // Flower exists
            //            {
            //                float flowers_x = j * boxPixelsX;
            //                float flowers_y = i * boxPixelsY;
            //                flowersSprite.setPosition(flowers_x, flowers_y);
            //                window.draw(flowersSprite);
            //            }
            //        }
            //    }


            //    // Draw yellow honeycombs according to set positions in drawyellow function
            //    for (int row = 0; row < gameRows; ++row)
            //    {
            //        for (int col = 0; col < gameColumns; ++col)
            //        {
            //            if (gameGrid[row][col] == 2)  // Check for honeycomb
            //            {
            //                const float honeycomb_x = col * boxPixelsX;
            //                const float honeycomb_y = row * boxPixelsY;

            //                if (bullet_exists && gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] == 2)
            //                {
            //                    // Destroy honeycomb
            //                    gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] = 0;
            //                    // Reset bullet to player's position
            //                    bullet_x = player_x;
            //                    bullet_y = player_y;
            //                    bullet_exists = false;
            //                }
            //                if (gameGrid[row][col] == 2)
            //                {
            //                    yellowSprite.setPosition(honeycomb_x, honeycomb_y);
            //                    window.draw(yellowSprite);  // Draw honeycomb
            //                }
            //            }
            //        }
            //    }


            //    // Draw Red Honeycombs according to set positions in drawred function
            //    for (int row = 0; row < gameRows; ++row)
            //    {
            //        for (int col = 0; col < gameColumns; ++col)
            //        {
            //            if (gameGrid[row][col] == 3)  // Check for honeycomb
            //            {
            //                const float honeycomb_x = col * boxPixelsX;
            //                const float honeycomb_y = row * boxPixelsY;

            //                if (bullet_exists && gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] == 3)
            //                {
            //                    // Destroy honeycomb
            //                    gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] = 0;
            //                    // Reset bullet to player's position
            //                    bullet_x = player_x;
            //                    bullet_y = player_y;
            //                    bullet_exists = false;
            //                }
            //                if (gameGrid[row][col] == 3)
            //                {
            //                    redSprite.setPosition(honeycomb_x, honeycomb_y);
            //                    window.draw(redSprite);  // Draw honeycomb
            //                }
            //            }
            //        }
            //    }


            //    // Draw Ground
            //    window.draw(groundRectangle);

            //    //bonus cans
            //    if (score > 20000)
            //    {
            //        if (!extracan1)
            //        {
            //            sprays += 1;
            //            extracan1 = true;
            //        }
            //    }
            //    if (score > 40000)
            //    {
            //        if (!extracan2)
            //        {
            //            sprays += 1;
            //            extracan2 = true;
            //        }
            //    }
            //    if (score > 80000)
            //    {
            //        if (!extracan3)
            //        {
            //            sprays += 1;
            //            extracan3 = true;
            //        }
            //    }


            //    // Draw Sprays
            //    if (sprays == 3)
            //    {
            //        if (bullets > 48)
            //        {
            //            drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
            //            drawSpray3(window, spray3_x, spray3_y, spray3Sprite);
            //        }
            //        else if (bullets <= 48 && bullets > 0)
            //        {
            //            int i = (48 - bullets) / 8;
            //            int height_offset = boxPixelsY * 2 - i * (boxPixelsY * 2 / 8);

            //            drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
            //            spray3Sprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX * 2, height_offset));
            //            drawSpray3(window, spray3_x, spray3_y, spray3Sprite);
            //        }
            //    }
            //    else if (sprays == 2)
            //    {
            //        if (bullets > 48)
            //        {
            //            drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
            //        }
            //        else if (bullets <= 48 && bullets > 7)
            //        {
            //            int i = (48 - bullets) / 8;
            //            int height_offset = boxPixelsY * 2 - i * (boxPixelsY * 2 / 8);
            //            spray2Sprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX * 2, height_offset));
            //            drawSpray2(window, spray2_x, spray2_y, spray2Sprite);
            //        }
            //    }


            //    // Handle Bullets
            //    fireBullet(bullet_exists, bullet_x, player_x, bullet_y, player_y, bullets, space_pressed);

            //    if (bullet_exists)
            //    {
            //        moveBullet(bullet_y, bullet_exists, bulletClock);
            //        drawBullet(window, bullet_x, bullet_y, bulletSprite);
            //    }



            //    // Detect Bullet Collision with Bees
            //    for (int i = 0; i < MaxWBees4; ++i)
            //    {
            //        if (worker_exists4[i])
            //        {
            //            drawyellow(window, bullet_x, bullet_y, worker_x4, worker_y4, worker_exists4, yellowSprite, player_x, player_y, gameGrid, boxPixelsY, boxPixelsX, score, beesRemainingl4, MaxWBees4, bullet_exists);
            //        }
            //    }

            //    for (int i = 0; i < MaxKBees4; ++i)
            //    {
            //        if (killer_existsK4[i])
            //        {
            //            drawred(window, bullet_x, bullet_y, killer_x4, killer_y4, killer_existsK4, redSprite, player_x, player_y, gameGrid, boxPixelsY, boxPixelsX, score, beesRemainingl4, MaxKBees4, bullet_exists);
            //        }
            //    }



            //    // Draw and Move Player
            //    drawPlayer(window, player_x, player_y, playerSprite);
            //    movePlayer(player_x, player_y, playerClock, playerSprite, gameGrid, boxPixelsY, boxPixelsX);



            //    // Reset the space_pressed flag when space is released
            //    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            //    {
            //        space_pressed = false;
            //    }



            //    // Decrement sprays based on bullets
            //    decrement_sprays(bullets, sprays);



            //    //functions to move and tackle behaviour of hummingbird
            //    moveHummingbird(humming_x, humming_y, target_x, target_y, gameRows, gameColumns, boxPixelsX, boxPixelsY, birdmovingRight, movementClock, pauseClock, paused);
            //    checkAndEatHoneycomb(gameGrid, humming_x, humming_y, boxPixelsX, boxPixelsY, score);
            //    checkingsprayedbird(isSprayed, bullet_x, bullet_y, bullet_exists, player_x, player_y, sprayedbird, humming_sick, sickClock, humming_x, humming_y);
            //    birdSpriteUsed(birdmovingRight, humming_sick, hummingSprite, hummingrevSprite, invisibleSprite, sickClock);
            //    drawHummingbird(window, humming_x, humming_y, hummingSprite, hummingrevSprite, birdmovingRight, humming_sick, invisibleSprite, sickClock);


            //    // Display Score
            //    scoreText.setPosition(750.f, 590.f);
            //    scoreText.setString("SCORE: " + std::to_string(score));
            //    window.draw(scoreText);
            //    window.display();

            //}
            //else if (beesRemainingl4 == 0 && sprays > 0)//level 4 complete


            //{
            //    if (!displayedHS)
            //    {
            //        sleep(seconds(2));
            //        //pause screen for 2 seconds

            //        window.clear(); //clear the screen

            //        // Draw Level Background
            //        window.draw(level4Sprite);
            //        scoreText.setPosition(resolutionX / 2 - 300, 300);
            //        scoreText.setCharacterSize(40);
            //        scoreText.setFillColor(Color::Yellow);
            //        scoreText.setString(" GAME PASSED WITH SCORE: " + std::to_string(score));
            //        window.draw(scoreText);
            //        window.display();
            //        sleep(seconds(2));
            //        window.clear();
            //        window.draw(level4Sprite);

            //        Text head;
            //        head.setPosition(resolutionX / 2 - 300, 300);
            //        head.setCharacterSize(40);
            //        head.setFillColor(Color::Yellow);
            //        head.setString(" ENTER NAME ON TERMINAL ");
            //        window.draw(head);
            //        window.display();
            //        sleep(seconds(2));

            //        updatedHighscores(window, highscoreSprite, max_displayed, highscore_file, font, score);
            //        sleep(seconds(30));
            //        displayedHS = true;
            //        level = 0;
            //        sleep(seconds(60));
            //        window.clear(); //clear the screen


            //        break;
            //    }
            //}
        }
        else if (level == 5) //meaning menu chosen highscore 
        {
            if (!displayedHS)
            {
                displayhighscore(window, highscoreSprite, max_displayed, highscore_file, font);
                level = menuLoop(window, menuSprite);
            }
        }

        window.clear();
    }
}




////////////////////////////////////////////////////////////////////////////
//                                                                        //
// Write your functions definitions here. Some have been written for you. //
//                                                                        //
////////////////////////////////////////////////////////////////////////////


//drawing the designing of the menu
void drawMenu(RenderWindow& window, Font& font, int selectedOption, Sprite& menuSprite)
{
    //starting with a blank window
    window.clear(Color::Black);
    window.draw(menuSprite);

    //titel
    Text title;
    title.setFont(font);
    title.setString("BUZZ BOMBERS");
    title.setCharacterSize(80); // Larger font for the title
    title.setFillColor(Color::Yellow);
    title.setPosition(resolutionX / 2 - 300, 40);

    Text options[6];
    string menuItems[6] = { "START", "LEVEL 2", "LEVEL 3", "LEVEL 4","HIGHSCORE", "EXIT" }; //menu options

    //setting design of menu options
    for (int i = 0; i < 6; ++i)
    {
        options[i].setFont(font);
        options[i].setString(menuItems[i]);
        options[i].setCharacterSize(45);
        //for highlighting selected option
        options[i].setFillColor(i == selectedOption ? Color::Yellow : Color::White);
        if (i == 4)
            options[i].setPosition(resolutionX / 2 - 150, 160 + i * 70);
        else if (i == 5)
            options[i].setPosition(resolutionX / 2 - 75, 155 + i * 70);
        else if (i == 0)
            options[i].setPosition(resolutionX / 2 - 90, 160 + i * 70);
        else
            options[i].setPosition(resolutionX / 2 - 110, 160 + i * 70);
        window.draw(options[i]);
    }
    window.draw(title);

    window.display();
}

//to choose level or to exit
int menuLoop(RenderWindow& window, Sprite& menuSprite)
{
    Font font;
    if (!font.loadFromFile("Fonts/arialceb.ttf"))
    {
        cout << "Error loading font!" << endl;
        return -1; // Error code
    }

    int selectedOption = 0;

    //setting its background music
    Music bgMusic;
    if (!bgMusic.openFromFile("Music/Music1.ogg")) {
        cout << "Error: Could not load music file!" << endl;
    }
    bgMusic.setVolume(50);
    bgMusic.setLoop(true);
    bgMusic.play();


    while (window.isOpen())
    {
        drawMenu(window, font, selectedOption, menuSprite);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                return -1; // Exit signal
            }

            if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case Keyboard::Up:
                    if (selectedOption > 0) selectedOption--;
                    break;
                case Keyboard::Down:
                    if (selectedOption < 5) selectedOption++;
                    break;
                case Keyboard::Enter:
                    if (selectedOption == 5)
                    { // EXIT
                        window.close();
                        return -1;
                    }
                    else
                    {
                        return selectedOption + 1; // Return the selected level
                    }
                }
            }
        }
    }
    return -1; // Default exit
}





//drawing function onto window
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite)
{
    playerSprite.setPosition(player_x, player_y);
    window.draw(playerSprite);
}

//moving function on window
void movePlayer(float& player_x, float& player_y, Clock& playerClock, const Sprite& playerSprite, int gameGrid[20][30], int boxPixelsY, int boxPixelsX)
{
    if (playerClock.getElapsedTime().asMilliseconds() < 5)
        return;
    playerClock.restart();

    // Get the sprite's width
    float spriteWidth = playerSprite.getGlobalBounds().width;

    if (Keyboard::isKeyPressed(Keyboard::Left) && player_x > 0 && gameGrid[static_cast<int>(player_y / boxPixelsY)][static_cast<int>(player_x / boxPixelsX - 1)] != 1)
    {
        player_x -= boxPixelsX / gameColumns; // Move left
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) && player_x < (resolutionX - spriteWidth) && gameGrid[static_cast<int>(player_y / boxPixelsY)][static_cast<int>(player_x / boxPixelsX + 1)] != 1)
    {
        player_x += boxPixelsX / gameColumns; // Move right
    }

}

//decrementing bullets and firing and returning position
void fireBullet(bool& bullet_exists, float& bullet_x, float player_x, float& bullet_y, float player_y, int& bullets, bool& space_pressed)
{
    if (Keyboard::isKeyPressed(Keyboard::Space) && bullet_exists == false && bullets > 0)
    {
        bullet_exists = true;        // Bullet now exists
        bullet_x = player_x;         // Position bullet at player's x
        bullet_y = player_y;
        bullets--; //decrementing bullets 
        space_pressed = true;
    }
}

//changing position of bullet  
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock)
{
    if (bulletClock.getElapsedTime().asMilliseconds() < 20)
        return;

    bulletClock.restart();

    bullet_y -= 32;
    if (bullet_y < -32)
        bullet_exists = false;


}

//drawing bullet onto screen
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite)
{
    bulletSprite.setPosition(bullet_x, bullet_y);
    window.draw(bulletSprite);
}

//drawing extra spray 1
void drawSpray2(RenderWindow& window, float& spray2_x, float& spray2_y, Sprite& spray2sprite)
{
    spray2sprite.setPosition(spray2_x, spray2_y);
    window.draw(spray2sprite);
}

//drawing extra spray 2
void drawSpray3(RenderWindow& window, float& spray3_x, float& spray3_y, Sprite& spray3sprite)
{
    spray3sprite.setPosition(spray3_x, spray3_y);
    window.draw(spray3sprite);
}

//works as loop to decrease sprays until 0
void decrement_sprays(int& bullets, int& sprays)
{
    if (bullets == 0 && sprays > 0)
    {
        sprays--;
        bullets = 56;
    }
}

//display the worker bee
void drawworker(RenderWindow& window, float worker_x[], float worker_y[], bool movingRight[], Sprite& workerSprite, Sprite& workerrevSprite, bool worker_exists[], int numBees)
{
    for (int i = 0; i < numBees; ++i)
    {
        if (!worker_exists[i])
            continue;

        if (worker_y[i] < (gameRows - 3) * boxPixelsY)
        {
            if (movingRight[i])
            {
                workerrevSprite.setPosition(worker_x[i], worker_y[i]);
                window.draw(workerrevSprite);
            }
            else
            {
                workerSprite.setPosition(worker_x[i], worker_y[i]);
                window.draw(workerSprite);
            }
        }
    }

}

//display the killer bee
void drawkiller(RenderWindow& window, float killer_x[], float killer_y[], bool movingRight[], Sprite& killerSprite, Sprite& killerrevSprite, bool killer_exists[], int numBees)
{
    for (int i = 0; i < numBees; ++i)
    {
        if (!killer_exists[i])
            continue;

        if (killer_y[i] < (gameRows - 3) * boxPixelsY)
        {
            if (movingRight[i])
            {
                killerrevSprite.setPosition(killer_x[i], killer_y[i]);
                window.draw(killerrevSprite);
            }
            else
            {
                killerSprite.setPosition(killer_x[i], killer_y[i]);
                window.draw(killerSprite);
            }
        }
    }
}


//initialize and move worker bee
void moveworker(float worker_x[], float worker_y[], bool movingRight[], int currentRow[], Clock workerClock[], int beeIndex, int gameColumns, int boxPixelsX, int boxPixelsY, int gameGrid[20][30], bool worker_exists[], int& beesRemainingl4, Sprite& hiveSprite, RenderWindow& window, float& hive_x, float& hive_y)
{
    if (workerClock[beeIndex].getElapsedTime().asMilliseconds() < 5)
        return;

    workerClock[beeIndex].restart();


    if (!worker_exists[beeIndex])  //incase of accidental toggling
    {
        worker_x[beeIndex] = (beeIndex % 2 == 0) * ((gameColumns - 2) * boxPixelsX) + (beeIndex % 2 != 0) * ((2) * boxPixelsX);  // Starting x position
        worker_y[beeIndex] = 0;                              // Starting y position (top of the screen)
        worker_exists[beeIndex] = true;                      // Mark as existing
        cout << "Worker bee #" << beeIndex << " initialized at: (" << worker_x[beeIndex] << ", " << worker_y[beeIndex] << ")\n"; //for checking errors
    }


    if (worker_y[beeIndex] < (gameRows - 3) * boxPixelsY)  //ie not on grass
    {
        if (movingRight[beeIndex])
        {
            worker_x[beeIndex] += boxPixelsX / gameColumns;  // Move right
            //to draw hive in three possibilities of bee getting stuck
            if ((gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY)]
                [static_cast<int>(worker_x[beeIndex] / boxPixelsX + 1)] != 0 && gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY)]
                [static_cast<int>(worker_x[beeIndex] / boxPixelsX - 1)] != 0 && gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY + 1)]
                [static_cast<int>(worker_x[beeIndex] / boxPixelsX)] != 0) || (worker_x[beeIndex] >= (gameColumns - 2) * boxPixelsX && gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY)]
                    [static_cast<int>(worker_x[beeIndex] / boxPixelsX - 1)] != 0 && gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY + 1)]
                    [static_cast<int>(worker_x[beeIndex] / boxPixelsX)] != 0) || worker_x[beeIndex] <= 0 && (gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY)]
                        [static_cast<int>(worker_x[beeIndex] / boxPixelsX + 1)] != 0 && gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY + 1)]
                        [static_cast<int>(worker_x[beeIndex] / boxPixelsX)] != 0))
            {
                sethive(worker_exists, gameGrid, worker_x, worker_y, hiveSprite, beeIndex, hive_x, hive_y, beesRemainingl4);
                drawhive(window, gameGrid, hive_x, hive_y, hiveSprite);

            }

            else if (worker_x[beeIndex] >= (gameColumns - 2) * boxPixelsX ||
                gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY)]
                [static_cast<int>(worker_x[beeIndex] / boxPixelsX + 1)] != 0)
            {
                movingRight[beeIndex] = false;          // Reverse direction
                worker_y[beeIndex] += boxPixelsY;       // Move down a row
                currentRow[beeIndex]++;
            }
        }
        else
        {
            worker_x[beeIndex] -= boxPixelsX / gameColumns;  // Move left
            //to draw hive in three possibilities of bee getting stuck
            if ((gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY)]
                [static_cast<int>(worker_x[beeIndex] / boxPixelsX + 1)] != 0 && gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY)]
                [static_cast<int>(worker_x[beeIndex] / boxPixelsX - 1)] != 0 && gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY + 1)]
                [static_cast<int>(worker_x[beeIndex] / boxPixelsX)] != 0) || (worker_x[beeIndex] >= (gameColumns - 2) * boxPixelsX && gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY)]
                    [static_cast<int>(worker_x[beeIndex] / boxPixelsX - 1)] != 0 && gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY + 1)]
                    [static_cast<int>(worker_x[beeIndex] / boxPixelsX)] != 0) || worker_x[beeIndex] <= 0 && (gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY)]
                        [static_cast<int>(worker_x[beeIndex] / boxPixelsX + 1)] != 0 && gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY + 1)]
                        [static_cast<int>(worker_x[beeIndex] / boxPixelsX)] != 0))
            {
                sethive(worker_exists, gameGrid, worker_x, worker_y, hiveSprite, beeIndex, hive_x, hive_y, beesRemainingl4);
                drawhive(window, gameGrid, hive_x, hive_y, hiveSprite);
            }

            else if (worker_x[beeIndex] <= 0 ||
                gameGrid[static_cast<int>(worker_y[beeIndex] / boxPixelsY)]
                [static_cast<int>(worker_x[beeIndex] / boxPixelsX - 1)] != 0)
            {
                movingRight[beeIndex] = true;           // Reverse direction
                worker_y[beeIndex] += boxPixelsY;       // Move down a row
                currentRow[beeIndex]++;
            }
        }
    }

}

//initialize and move killer bee
void movekiller(float killer_x[], float killer_y[], bool movingRight[], int currentRow[], Clock killerClock[], int beeIndex, int gameColumns, int boxPixelsX, int boxPixelsY, int gameGrid[20][30], bool killer_exists[], int& beesRemainingl4, Sprite& hiveSprite, RenderWindow& window, float& hive_x, float& hive_y)
{
    if (killerClock[beeIndex].getElapsedTime().asMilliseconds() < 2)
        return;
    killerClock[beeIndex].restart();



    if (!killer_exists[beeIndex]) //incase of accidental toggling, resets positions
    {
        killer_x[beeIndex] = (beeIndex % 2 == 0) * ((gameColumns - 2) * boxPixelsX) + (beeIndex % 2 != 0) * ((2) * boxPixelsX);  // Starting x position
        killer_y[beeIndex] = 0;                              // Starting y position (top of the screen)
        killer_exists[beeIndex] = true;                      // Mark as existing
        cout << "Killer bee #" << beeIndex << " initialized at: (" << killer_x[beeIndex] << ", " << killer_y[beeIndex] << ")\n";
    }



    if (killer_y[beeIndex] < (gameRows - 3) * boxPixelsY)
    {
        // Move horizontally
        if (movingRight[beeIndex])
        {
            killer_x[beeIndex] += boxPixelsX / gameColumns; // Move right

            //to draw hive in three possibilities of bee getting stuck
            if ((gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY)]
                [static_cast<int>(killer_x[beeIndex] / boxPixelsX + 1)] != 0 && gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY)]
                [static_cast<int>(killer_x[beeIndex] / boxPixelsX - 1)] != 0 && gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY + 1)]
                [static_cast<int>(killer_x[beeIndex] / boxPixelsX)] != 0) || (killer_x[beeIndex] >= (gameColumns - 2) * boxPixelsX && gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY)]
                    [static_cast<int>(killer_x[beeIndex] / boxPixelsX - 1)] != 0 && gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY + 1)]
                    [static_cast<int>(killer_x[beeIndex] / boxPixelsX)] != 0) || killer_x[beeIndex] <= 0 && (gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY)]
                        [static_cast<int>(killer_x[beeIndex] / boxPixelsX + 1)] != 0 && gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY + 1)]
                        [static_cast<int>(killer_x[beeIndex] / boxPixelsX)] != 0))
            {
                sethive(killer_exists, gameGrid, killer_x, killer_y, hiveSprite, beeIndex, hive_x, hive_y, beesRemainingl4);
                drawhive(window, gameGrid, hive_x, hive_y, hiveSprite);
            }

            // Check if it hits the right boundary
            else if (killer_x[beeIndex] >= (gameColumns - 2) * boxPixelsX)
            {
                movingRight[beeIndex] = false;          // Reverse direction
                killer_y[beeIndex] += boxPixelsY;       // Move down a row
                currentRow[beeIndex]++;                // Increment row count
            }
            else if (gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY)]
                [static_cast<int>(killer_x[beeIndex] / boxPixelsX + 1)] != 0)
            {
                movingRight[beeIndex] = false;          // Reverse direction
            }
        }
        else
        {
            killer_x[beeIndex] -= boxPixelsX / gameColumns; // Move left

            //to draw hive in three possibilities of bee getting stuck
            if ((gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY)]
                [static_cast<int>(killer_x[beeIndex] / boxPixelsX + 1)] != 0 && gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY)]
                [static_cast<int>(killer_x[beeIndex] / boxPixelsX - 1)] != 0 && gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY + 1)]
                [static_cast<int>(killer_x[beeIndex] / boxPixelsX)] != 0) || (killer_x[beeIndex] >= (gameColumns - 2) * boxPixelsX && gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY)]
                    [static_cast<int>(killer_x[beeIndex] / boxPixelsX - 1)] != 0 && gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY + 1)]
                    [static_cast<int>(killer_x[beeIndex] / boxPixelsX)] != 0) || killer_x[beeIndex] <= 0 && (gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY)]
                        [static_cast<int>(killer_x[beeIndex] / boxPixelsX + 1)] != 0 && gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY + 1)]
                        [static_cast<int>(killer_x[beeIndex] / boxPixelsX)] != 0))
            {
                sethive(killer_exists, gameGrid, killer_x, killer_y, hiveSprite, beeIndex, hive_x, hive_y, beesRemainingl4);
                drawhive(window, gameGrid, hive_x, hive_y, hiveSprite);
            }

            // Check if it hits the left boundary
            else if (killer_x[beeIndex] <= 0)
            {
                movingRight[beeIndex] = true;           // Reverse direction
                killer_y[beeIndex] += boxPixelsY;       // Move down a rwo
                currentRow[beeIndex]++;                // Increment row count
            }
            else if (gameGrid[static_cast<int>(killer_y[beeIndex] / boxPixelsY)]
                [static_cast<int>(killer_x[beeIndex] / boxPixelsX - 1)] != 0)
            {
                movingRight[beeIndex] = false;          // Reverse direction
            }
        }

    }

}



//setting positions of yellow honeycombs
void drawyellow(RenderWindow& window, float bullet_x, float bullet_y, float worker_x[], float worker_y[], bool worker_exists[], Sprite& yellowSprite, float player_x, float player_y, int gameGrid[20][30], int boxPixelsY, int boxPixelsX, int& score, int& beesRemaining, const int MaxBees, bool bullet_exists)
{
    // Replace the current implementation with:
    vector<bool> honeycombPending(MaxBees, false);  // Dynamically sized
    vector<Clock> honeycombClock(MaxBees);            // Stack allocation instead of heap
    // Remove the delete[] lines
    for (int i = 0; i < MaxBees; ++i)
    {
        if (worker_exists[i])
        {
            if (bullet_exists && bullet_x >= worker_x[i] - boxPixelsX / 4 && bullet_x <= worker_x[i] + boxPixelsX && bullet_y >= worker_y[i] && bullet_y <= worker_y[i])
            {
                SoundBuffer buffer;
                if (!buffer.loadFromFile("Sound Effects/hit.wav"))
                {
                    cout << "Error: Could not load sound file!" << endl;
                    return;
                }
                Sound beeHitSound;
                beeHitSound.setBuffer(buffer);
                beeHitSound.setVolume(100.f);
                beeHitSound.play();
                // Collision Detected
                worker_exists[i] = false; // Bee is no longer active
                //a grid positions horizontal offset in drawing honeycomb to prevent honeycomb being destroyed at the same time as bee is killed
                float yellow_x = worker_x[i] - boxPixelsX - boxPixelsX / 4;
                float yellow_y = worker_y[i];

                // Update the grid with honeycomb position
                gameGrid[static_cast<int>(yellow_y / boxPixelsY)][static_cast<int>(yellow_x / boxPixelsX)] = 2;

                // Reset bullet to player's position
                bullet_x = player_x;
                bullet_y = player_y;
                bullet_exists = false;

                score += 100;
                beesRemaining--;
            }
        }
    }

}

//initiliazing the red honeycombs
void drawred(RenderWindow& window, float bullet_x, float bullet_y, float killer_x[], float killer_y[], bool killer_exists[], Sprite& redSprite, float player_x, float player_y, int gameGrid[20][30], int boxPixelsY, int boxPixelsX, int& score, int& beesRemaining, const int MaxBees, bool bullet_exists)
{
    // Replace the current implementation with:
    vector<bool> honeycombPending(MaxBees, false);  // Dynamically sized
    vector<Clock> honeycombClock(MaxBees);       // Stack allocation instead of heap
    // Remove the delete[] lines
    for (int i = 0; i < MaxBees; ++i)
    {
        if (killer_exists[i])
        {
            if (bullet_exists && bullet_x >= killer_x[i] - boxPixelsX / 4 && bullet_x <= killer_x[i] + boxPixelsX && bullet_y >= killer_y[i] && bullet_y <= killer_y[i])
            {
                SoundBuffer buffer;
                if (!buffer.loadFromFile("Sound Effects/hit.wav"))
                {
                    cout << "Error: Could not load sound file!" << endl;
                    return;
                }
                Sound beeHitSound;
                beeHitSound.setBuffer(buffer);
                beeHitSound.setVolume(100.f);
                beeHitSound.play();
                // Collision Detected
                killer_exists[i] = false; // Bee is no longer active
                //a grid positions horizontal offset in drawing honeycomb to prevent honeycomb being destroyed at the same time as bee is killed
                float red_x = killer_x[i] - boxPixelsX - boxPixelsX / 4;
                float red_y = killer_y[i];

                // Update the grid with honeycomb position
                gameGrid[static_cast<int>(red_y / boxPixelsY)][static_cast<int>(red_x / boxPixelsX)] = 3;

                // Reset bullet to player's position
                bullet_x = player_x;
                bullet_y = player_y;
                bullet_exists = false;

                score += 1000;
                beesRemaining--;
            }
        }
    }

}



//gerenate the pre generated honeycombs
void generateHoneycombs(int gameGrid[20][30], int gameRows, int gameColumns, int boxPixelsY, int boxPixelsX, int numHoneycombs)
{
    srand(static_cast<unsigned>(time(nullptr))); //random number generator

    int generated = 0;
    while (generated < numHoneycombs)
    {
        int randomRow = rand() % (gameRows - 4); // Avoid grass
        int randomCol = rand() % gameColumns;

        if (gameGrid[randomRow][randomCol] == 0)
        { // Ensure no obstacles
            gameGrid[randomRow][randomCol] = 2;   // Place honeycomb
            generated++;
        }
    }
}

void generateHives(int gameGrid[20][30], int numHives, float& hive_x, float& hive_y)
{

    srand(static_cast<unsigned>(time(nullptr))); //random number generator

    int generated = 0;
    while (generated < numHives)
    {
        int randomRow = rand() % (gameRows - 4); // Avoid grass
        int randomCol = rand() % gameColumns;


        if (gameGrid[randomRow][randomCol] == 0)
        { // Ensure no obstacles
            gameGrid[randomRow][randomCol] = 4;   // Place honeycomb
            generated++;
        }

    }
}


//draw and display hive
void sethive(bool bee_exists[], int gameGrid[20][30], float bee_x[], float bee_y[], Sprite hiveSprite, int beeIndex, float& hive_x, float& hive_y, int& beesRemaining)
{
    hive_x = bee_x[beeIndex];
    hive_y = bee_y[beeIndex];

    //update gamegrid with hive position
    gameGrid[static_cast<int>(hive_y / boxPixelsY)][static_cast<int>(hive_x / boxPixelsX)] = 4;

    bee_exists[beeIndex] = false;
    beesRemaining--;


}

//draw hive
void drawhive(RenderWindow& window, int gameGrid[20][30], float hive_x, float hive_y, Sprite& hiveSprite)
{
    //if hive exists
    for (int i = 0; i < gameRows; ++i)
    {
        for (int j = 0; j < gameColumns; ++j)
        {
            if (gameGrid[i][j] == 4)  // hive exists
            {
                float x = i * boxPixelsX;
                float y = j * boxPixelsY;
                hiveSprite.setPosition(x, y);
                window.draw(hiveSprite);
            }
        }
    }
}

//destroy hive 
void destroyhive(float& bullet_x, float& bullet_y, bool bullet_exists, float player_x, float player_y, float hive_x, float hive_y, int gameGrid[20][30])
{
    int grid_x = static_cast<int>(bullet_x / boxPixelsX);
    int grid_y = static_cast<int>(bullet_y / boxPixelsY);

    if (gameGrid[static_cast<int>(bullet_y / boxPixelsY)][static_cast<int>(bullet_x / boxPixelsX)] == 4)
    {

        //bullet used up
        bullet_x = player_x;
        bullet_y = player_y;
        bullet_exists = false;

        //for the case that they were made by bee movement
        gameGrid[static_cast<int>(hive_y / boxPixelsY)][static_cast<int>(hive_x / boxPixelsX)] = 0;
        //for the case that they were pregenerated
        gameGrid[grid_y][grid_x] = 0;

    }
}


// Random movement of hummingbird
void moveHummingbird(float& humming_x, float& humming_y, float& target_x, float& target_y, int gameRows, int gameColumns, int boxPixelsX, int boxPixelsY, bool& movingRight, Clock& movementClock, Clock& pauseClock, bool& paused)
{
    if (paused)
    {
        if (pauseClock.getElapsedTime().asSeconds() >= 2.0f) //pauses for 2 seconds
        {
            paused = false;
            pauseClock.restart();
        }
        return;
    }

    if (movementClock.getElapsedTime().asMilliseconds() < 50)
    {
        return;
    }

    movementClock.restart();

    // Check if the hummingbird reached its target
    if ((humming_x - target_x) * (humming_x - target_x) + (humming_y - target_y) * (humming_y - target_y) < 1)  //nearly 0?
    {
        target_x = (rand() % (gameColumns - 2)) * boxPixelsX;
        target_y = (rand() % (gameRows - 4)) * boxPixelsY; //avoiding grass
        movingRight = (target_x > humming_x);
        paused = true;
        pauseClock.restart();
    }

    // Move horizontally towards target_x
    if (humming_x < target_x) {
        humming_x += 32; // Move right
        if (humming_x > target_x) {
            humming_x = target_x; // equals target
        }
    }
    else if (humming_x > target_x) {
        humming_x -= 32; // Move left
        if (humming_x < target_x) {
            humming_x = target_x; // equals  target
        }
    }

    // Move vertically towards target_y
    if (humming_y < target_y) {
        humming_y += 32; // Move down
        if (humming_y > target_y) {
            humming_y = target_y; //  equals target
        }
    }
    else if (humming_y > target_y) {
        humming_y -= 32; // Move up
        if (humming_y < target_y) {
            humming_y = target_y; // Equals target
        }
    }
}


// Check and eat honeycomb
void checkAndEatHoneycomb(int gameGrid[20][30], float humming_x, float humming_y, int boxPixelsX, int boxPixelsY, int& score)
{

    if (gameGrid[static_cast<int>(humming_y / boxPixelsY)][static_cast<int>(humming_x / boxPixelsX)] == 2)   //yellow honeycomb encounntered
    {
        if (static_cast<int>(humming_y / boxPixelsY) < 2)  //first two rows
        {
            score += 1000;
        }
        else if (static_cast<int>(humming_y / boxPixelsY) < 5) //rows 3,4,5
        {
            score += 800;
        }
        else
        {
            score += 500;
        }
        gameGrid[static_cast<int>(humming_y / boxPixelsY)][static_cast<int>(humming_x / boxPixelsX)] = 0; // honeycomb removed
    }
    else if (gameGrid[static_cast<int>(humming_y / boxPixelsY)][static_cast<int>(humming_x / boxPixelsX)] == 3)  //red honeycomb encountered
    {
        if (static_cast<int>(humming_y / boxPixelsY) < 2) //rows 1,2
        {
            score += 2000;
        }
        else if (static_cast<int>(humming_y / boxPixelsY) < 5) //rows 3,4,5
        {
            score += 1600;
        }
        else
        {
            score += 1000;
        }
        gameGrid[static_cast<int>(humming_y / boxPixelsY)][static_cast<int>(humming_x / boxPixelsX)] = 0; // removed honeycomb
    }
}


// Handle sick bird
void checkingsprayedbird(bool& isSprayed, float& bullet_x, float& bullet_y, bool& bullet_exists, float player_x, float player_y, int& sprayedBird, bool& humming_sick, Clock& sickClock, float humming_x, float humming_y)
{
    if (bullet_x >= humming_x - boxPixelsX && bullet_x <= humming_x + boxPixelsX && bullet_y == humming_y)
    {
        //bullet collides with hummingbird
        bullet_x = player_x;
        bullet_y = player_y;
        bullet_exists = false;
        isSprayed = true;
    }
    else
    {
        isSprayed = false;
    }

    if (isSprayed)
    {
        sprayedBird++;
        if (sprayedBird > 3)
        {
            humming_sick = true;
            sickClock.restart();
        }
    }

    if (humming_sick && sickClock.getElapsedTime().asSeconds() >= 5.0f)
    {
        humming_sick = false;  // Recover after 5 seconds
        sprayedBird = 0;
    }
}


// to choose if hummingbird moving right or left and its respective sprite
Sprite& birdSpriteUsed(bool movingRight, bool humming_sick, Sprite& hummingSprite, Sprite& hummingrevSprite, Sprite& invisibleSprite, Clock& sickClock)
{
    if (humming_sick)
    {
        //time since the hummingbird was sprayed
        float elapsedTime = sickClock.getElapsedTime().asSeconds();

        // show green hummingbird for first second
        if (elapsedTime <= 1.0f)
        {
            if (movingRight)
                return hummingrevSprite;
            else
                return hummingSprite;
        }
        // After 1 second, hide the hummingbird 
        else if (elapsedTime <= 5.0f)
        {
            // Make the hummingbird invisible 
            return invisibleSprite;
        }
    }

    //choosing sprite for when bird is healthy
    if (movingRight)
    {
        return hummingrevSprite;
    }
    else
    {
        return hummingSprite;
    }
}


//draw the hummingbird
void drawHummingbird(RenderWindow& window, float humming_x, float humming_y, Sprite& hummingSprite, Sprite& hummingrevSprite, bool movingRight, bool humming_sick, Sprite& invisibleSprite, Clock& sickClock)
{
    Sprite& currentSprite = birdSpriteUsed(movingRight, humming_sick, hummingSprite, hummingrevSprite, invisibleSprite, sickClock);

    // if sick will be green
    if (&currentSprite != &invisibleSprite)
    {
        currentSprite.setColor(humming_sick ? Color::Green : Color::White);
    }

    currentSprite.setPosition(humming_x, humming_y);
    window.draw(currentSprite);
}

//menu highscores list
void displayhighscore(RenderWindow& window, Sprite& highscoreSprite,const int max_displayed, string highscore_file, const Font& font)
{
    window.clear();

    window.draw(highscoreSprite);
    //window.display();

    vector<string> names(max_displayed);
    vector<int> scores(max_displayed); //array that will contain the scores 
    int scoreCount = 0; //the line on highscore list

    // Read high scores from file
    ifstream read(highscore_file);
    if (read.is_open())
    {
        while (scoreCount < max_displayed)
        {
            string name;
            int score;

            read >> name >> score;
            if (read.fail())
            {
                break;
            }

            names[scoreCount] = name;
            scores[scoreCount] = score;
            scoreCount++;
        }
        read.close();
    }
    else
    {
        cout << "Error: Unable to open file " << highscore_file << "\n";
        return;
    }


    //Display heading
    Text heading;
    heading.setFont(font);
    heading.setCharacterSize(40);
    heading.setFillColor(Color::Black);
    heading.setPosition(960 / 2 - 110, 20);
    heading.setString("HIGH SCORES");
    window.draw(heading);



    // Display scores in the window
    Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(26);
    highScoreText.setFillColor(Color::Black);

    int verticalgap = 80;
    for (int i = 0; i < scoreCount; ++i) {
        string display_score = to_string(i + 1) + " " + names[i] + " " + to_string(scores[i]);
        highScoreText.setString(display_score);
        highScoreText.setPosition(960 / 2 - 80, verticalgap);

        window.draw(highScoreText);
        verticalgap += 35;
    }

    window.display();
    sleep(seconds(5.0));

}


//editable highscore after game lost or won
//void updatedHighscores(RenderWindow& window, Sprite& highscoreSprite,const int max_displayed, string highscore_file, const Font& font, int score)
//{
//    window.clear();
//
//    window.draw(highscoreSprite);
//    window.display();
//
//    vector<string> names(max_displayed);
//    vector<int> scores(max_displayed); //allows containing new score
//    int scoreCount = 0; //the line on highscore list
//
//    // Read high scores from file
//    ifstream read(highscore_file);
//    if (read.is_open())
//    {
//        while (scoreCount < max_displayed)
//        {
//            string name;
//            int score;
//
//            read >> name >> score;
//            if (read.fail())
//            {
//                break;
//            }
//
//            names[scoreCount] = name;
//            scores[scoreCount] = score;
//            scoreCount++;
//        }
//        read.close();
//    }
//    else
//    {
//        cout << "Error: Unable to open file " << highscore_file << "\n";
//        return;
//    }
//
//    string name;
//    cout << "Enter user name\n";
//    cin >> name;
//
//    //adding current name and scores to the arrays 
//    names[scoreCount] = name;
//    scores[scoreCount] = score;
//
//    //sorting if or all 11 of them into order 
//
//    for (int i = 0; i < scoreCount - 1; ++i)
//    {
//        for (int j = 0; j < scoreCount - i - 1; ++j)
//        {
//            if (scores[j] < scores[j + 1])
//            {
//                // Swap scores
//                scores[j] ^= scores[j + 1];
//                scores[j + 1] ^= scores[j];
//                scores[j] ^= scores[j + 1];
//
//                // Swap names
//                string temp = names[j];
//                names[j] = names[j + 1];
//                names[j + 1] = temp;
//            }
//        }
//    }
//
//    if (scoreCount > max_displayed)  //keeping only the top 10
//    {
//        scoreCount = max_displayed;
//    }
//
//    ofstream write(highscore_file);
//
//    if (write.is_open())
//    {
//        for (int i = 0; i < scoreCount; ++i)
//        {
//            write << names[i] << " " << scores[i] << "\n";
//        }
//        write.close();
//    }
//    else
//    {
//        cout << "Error: Unable to open file for writing " << highscore_file << endl;
//        return;
//    }
//
//    //Display heading
//    Text heading;
//    heading.setFont(font);
//    heading.setCharacterSize(40);
//    heading.setFillColor(Color::Black);
//    heading.setPosition(960 / 2 - 110, 20);
//    heading.setString("HIGH SCORES");
//    window.draw(heading);
//
//
//
//    // Display scores in the window
//    Text highScoreText;
//    highScoreText.setFont(font);
//    highScoreText.setCharacterSize(26);
//    highScoreText.setFillColor(Color::Black);
//
//    int verticalgap = 80;
//
//    for (int i = 0; i < scoreCount; ++i)
//    {
//        highScoreText.setString(to_string(i + 1) + " " + names[i] + " " + to_string(scores[i]));
//        highScoreText.setPosition(960 / 2 - 80, verticalgap);
//
//        window.draw(highScoreText);
//        verticalgap += 35;
//    }
//
//    window.display();
//
//}


void updatedHighscores(RenderWindow& window, Sprite& highscoreSprite, const int max_displayed, string highscore_file, const Font& font, int score) {
    window.clear();
    window.draw(highscoreSprite);
    window.display();

    vector<pair<int, string>> scores; 


    ifstream read(highscore_file);
    if (read.is_open()) {
        string name;
        int oldScore;
        while (read >> name >> oldScore) {
            scores.emplace_back(oldScore, name);
        }
        read.close();
    }
    else {
        cout << "Warning: Could not open " << highscore_file << " for reading. Creating new file.\n";
    }

 \
    string name;
    cout << "Enter your name (no spaces): ";
    while (true) {
        cin >> name;
        if (!name.empty()) break;
        cout << "Invalid name. Try again: ";
    }


    scores.emplace_back(score, name);
    sort(scores.begin(), scores.end(), greater<pair<int, string>>());


    if (scores.size() > max_displayed) {
        scores.resize(max_displayed);
    }

   
    ofstream write(highscore_file);
    if (write.is_open()) {
        for (const auto& entry : scores) {
            write << entry.second << " " << entry.first << "\n";
        }
        write.close();
    }
    else {
        cout << "Error: Could not save high scores to " << highscore_file << "\n";
    }

    //Display updated high scores
    window.clear();
    window.draw(highscoreSprite);

    Text heading("HIGH SCORES", font, 40);
    heading.setFillColor(Color::Black);
    heading.setPosition(960 / 2 - 110, 20);
    window.draw(heading);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(26);
    scoreText.setFillColor(Color::Black);

    int yPos = 80;
    for (size_t i = 0; i < scores.size() && i < max_displayed; ++i) {
        string displayText = to_string(i + 1) + ". " + scores[i].second + " - " + to_string(scores[i].first);
        scoreText.setString(displayText);
        scoreText.setPosition(960 / 2 - 100, yPos);
        window.draw(scoreText);
        yPos += 35;
    }

    window.display();
    sleep(seconds(5)); 
}