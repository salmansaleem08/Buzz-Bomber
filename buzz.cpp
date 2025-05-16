#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>
using namespace std;
using namespace sf;

const int resolutionX = 960;
const int resolutionY = 640;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionY / boxPixelsY;
const int gameColumns = resolutionX / boxPixelsX; 


int gameGrid[gameRows][gameColumns] = {};


void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock, bool& collisionStopFlag, bool& birdCollisionStopFlag);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite);
void menu(bool& levelOne, bool& levelTwo, bool& levelThree, bool& bossLevel, bool& quit, bool& highScore);

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Write your functions declarations here. Some have been written for you. //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
void movePlayer(float& player_x, float& player_y, RectangleShape& healthRectangle, int decreaseLevelVariable, float flowerLocation[][11], bool flowerVisible[]);
void fireBullet(bool& bullet_exists, float& bullet_x, float& bullet_y, float player_x, float player_y, int& totalSprayFired, RectangleShape& healthRectangle, int& decreaseLevelVariable, int& sprayLeft);
void drawOtherSprayCans(int sprayLeft, RenderWindow& window, Sprite spraySprite[]);
void loadNewCan(RectangleShape& healthRectangle, int& totalSprayFired, int& decreaseLevelVariable, int& sprayLeft, float player_x, float player_y);


void drawWorkerBee(RenderWindow& window, float workerBeeLocations[][32], Sprite workerBeeSprite[32], int& totalBees, bool honeyCombDestroyed[]);
void moveWorkerBees(bool directionsBees[3][32], float workerBeeLocations[][32], int& totalBees, int tier[32], bool isHoneyComb[], bool honeyCombDestroyed[], bool occasionallyStop[], bool plantedFlower[], Sprite workerBeeSprite[32], float fastBeeLocations[][18], bool isFastBeeHoneyComb[], bool fastBeeHoneyCombDestroyed[], int totalFastBees, int stuckCounter[4][32], int indexStuckCounter[], bool isBeeHive[], Texture workerBeeTexture[], bool leftTheGame[]);
void checkWorkerBeeCollisionWithBullet(float workerBeeLocations[][32], int& totalBees, bool isHoneyComb[], float& bullet_x, float& bullet_y, Sprite workerBeeSprite[], Texture workerBeeTexture[], bool honeyCombDestroyed[], bool& collisionStopFlag, bool plantedFlower[] , long long & scoreGameplay);
void randomStopGenerator(Clock& clock, int& totalBees, bool occasionallyStop[], bool& stopMovementForWhile , bool plantedFlower[]);


void drawFlowers(RenderWindow& window, float flowerLocation[][11], Sprite flowerSprite[11], const int& totalFlowers , bool flowerVisible[]);
void plantFlowers(float workerBeeLocations[][32], int& totalBees, bool isHoneyComb[], int currentFlowersOnScreen, bool flowerVisible[], bool plantedFlower[], float& player_x, float& player_y, float flowerLocation[][11]);
void playerOnNewPlace(float& player_x, float& player_y, float flowerLocation[][11], bool flowerVisible[]);


void drawFastBee(RenderWindow& window, float fastBeeLocations[][18], Sprite fastBeeSprite[18], int& totalBees, bool fastBeeHoneyCombDestroyed[]);
void moveFastBees(bool directionsFastBees[3][18], float fastBeeLocations[][18], int& totalBees, int tierFastBees[], bool isFastBeeHoneyComb[], bool fastBeeHoneyCombDestroyed[], bool fastBeePlantedFlower[], Sprite fastBeeSprite[18], bool fastBeeLeftTheGame[]);
void checkFastBeeCollisionWithBullet(float fastBeeLocations[][18], int& totalBees, bool isFastBeeHoneyComb[], float& bullet_x, float& bullet_y, Sprite fastBeeSprite[], Texture fastBeeTexture[], bool fastBeeHoneyCombDestroyed[], bool& collisionStopFlag, bool fastBeePlantedFlower[], long long& scoreGameplay);
void fastBeePlantFlowers(float fastBeeLocations[][18], int& totalBees, bool isFastBeeHoneyComb[], int currentFlowersOnScreen, bool flowerVisible[], bool fastBeePlantedFlower[], float& player_x, float& player_y, float flowerLocation[][11]);


void spawnBird(Clock& birdClock, bool &birdVisible);
void selectHoneyComb(float fastBeeLocations[][18], bool isFastBeeHoneyComb[], float workerBeeLocations[][32], bool isHoneyComb[], int totalWorkerBees, int totalFastBees, float& next_x, float& next_y);
bool moveBird(float& bird_x, float& bird_y, float next_x, float next_y);
void drawBird(RenderWindow& window, float& bird_x, float& bird_y, Sprite& birdSprite, bool birdVisible);
void checkBulletandBirdCollision(float& bullet_x, float& bullet_y, float& bird_x, float& bird_y, float& bird_xNext, float& bird_yNext, int& countBulletHit, bool& birdCollisionStopFlag);

void showHighScores();

void calculateHummingBordScore(float& bird_x, float& bird_y, float workerBeeLocations[2][32], bool isHoneyComb[], bool isFastBeeHoneyComb[], float fastBeeLocations[][18], int totalBees, int totalFastBees, long long& scoreGameplay);
void checkAllFlowersPlanted(bool flowerVisible[], int& sprayLeft, int& decreaseLevelVariable, int& totalSprayFired);

void addHighScore(string newName, long long newScore);

bool incrementLevel(bool isHoneyComb[], int& totalBees, bool isFastBeeHoneyComb[], bool leftTheGame[], int totalFastBees, bool fastBeeLeftTheGame[]);

void calculateBeeHiveScore(long long& scoreGameplay, float workerBeeLocations[2][32], bool isBeeHive[], int& totalBees, bool honeyCombDestroyed[]);

int main()
{

	cout << "Enter Your Name : ";
	string name; cin >> name;


	long long scoreGameplay = 0;

	bool levelOne = false; bool levelTwo = true;
	bool levelThree = false; bool bossLevel = false; 
	
	bool quit = false; 
	bool highScore = false;
	srand(time(0));

	menu(levelOne , levelTwo, levelThree , bossLevel, quit, highScore);
	
	RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);
	window.setPosition(Vector2i(500, 200));

	/////////////////////////////////////////////////////////////////////////////
	//// Music and Background for each Level....
	while (1) {  // LeveL increment Loop
		
		if (quit) return 0;

		Music bgMusic;
		Texture backgroundTexture;
		Sprite backgroundSprite;
		if (levelOne) {
			bgMusic.openFromFile("Music/Music3.ogg");
			backgroundTexture.loadFromFile("Textures/background1.jpg");
			
		}
		else if (levelTwo) {
			bgMusic.openFromFile("Music/risk.ogg");
			backgroundTexture.loadFromFile("Textures/background2.jpg");
		}
		else if (levelThree) {
			bgMusic.openFromFile("Music/magical_journey.ogg");
			backgroundTexture.loadFromFile("Textures/background3.jpg");
		}
		else if (bossLevel) {
			bgMusic.openFromFile("Music/risk.ogg");
			backgroundTexture.loadFromFile("Textures/background3.jpg");
		}

		backgroundSprite.setTexture(backgroundTexture);
		//backgroundSprite.setTextureRect(IntRect(0, 0, resolutionX, resolutionY));
		// Get original image size
		Vector2u textureSize = backgroundTexture.getSize(); // width and height of the image
		float scaleX = static_cast<float>(resolutionX) / textureSize.x;
		float scaleY = static_cast<float>(resolutionY) / textureSize.y;

		// Scale the sprite
		backgroundSprite.setScale(scaleX, scaleY);


		bgMusic.setVolume(50);
		bgMusic.setLoop(true);
		bgMusic.play();

		/////////////////////////////////////////////////////////////////////////////
		/// Player And Bullet 


		float player_x = 450;
		float player_y = 540;

		Texture playerTexture;
		Sprite playerSprite;

		playerTexture.loadFromFile("Textures/spray.png");
		playerSprite.setTexture(playerTexture);

		Texture sprayTexture[2];
		Sprite spraySprite[2];
		for (int i = 0; i < 2; i++) {
			sprayTexture[i].loadFromFile("Textures/spray.png");
			spraySprite[i].setTexture(sprayTexture[i]);
			spraySprite[i].setScale(0.60, 0.60);
		}



		float bullet_x = player_x;
		float bullet_y = player_y;

		bool bullet_exists = false;
		int sprayLeft = 2;
		int totalSprayFired = 0;
		int decreaseLevelVariable = 0;


		Clock bulletClock;
		Texture bulletTexture;

		Sprite bulletSprite;
		bulletTexture.loadFromFile("Textures/bullet.png");
		bulletSprite.setTexture(bulletTexture);
		bulletSprite.setScale(2, 2);
		bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
		bool collisionStopFlag = false;
		bool birdCollisionStopFlag = false;


		RectangleShape groundRectangle(Vector2f(resolutionX, 60));
		groundRectangle.setPosition(0, resolutionY - 38);
		groundRectangle.setFillColor(Color::Green);


		RectangleShape healthRectangle(Vector2f(20, 30));
		healthRectangle.setPosition(player_x + 22, player_y + 36 + (decreaseLevelVariable * 4));
		healthRectangle.setFillColor(Color::White);
		////////////////////////////////////////////////////////////////////////////////////////////////
		// 
		////////////////////////////////////////////////////////////////////////////////////////////////
		////// BEES Implementation
		const int totalBees = 32;
		Texture workerBeeTexture[totalBees];
		int tier[totalBees];
		Sprite workerBeeSprite[totalBees];
		float workerBeeLocations[2][totalBees];

		bool isHoneyComb[totalBees];

		bool honeyCombDestroyed[totalBees];

		bool isBeeHive[totalBees];

		bool directionsBees[3][totalBees];

		bool occasionallyStop[totalBees];

		bool stopMovementForWhile = false;

		bool plantedFlower[totalBees];

		int stuckCounter[4][totalBees];
		int indexStuckCounter[totalBees];
		bool leftTheGame[totalBees];
		Clock clock;

		for (int i = 0; i < totalBees; i++) {
			workerBeeTexture[i].loadFromFile("Textures/Regular_bee.png");
			workerBeeSprite[i].setTexture(workerBeeTexture[i]);

			workerBeeLocations[0][i] = 30 * (i + 1);
			if (bossLevel)
				workerBeeLocations[0][i] = 30 * (1 + rand() % totalBees);// i + 1;

			int randomVariable = 1 + rand() % 3;
			if (randomVariable == 1) {
				workerBeeLocations[1][i] = 100;
			}
			else if (randomVariable == 2) {
				workerBeeLocations[1][i] = 200;
			}
			else if (randomVariable == 3) {
				workerBeeLocations[1][i] = 150;
			}

			directionsBees[0][i] = rand() % 2; // Randomize initial direction   // right
			directionsBees[1][i] = !directionsBees[0][i];   // left 
			directionsBees[2][i] = false; // down 


			isHoneyComb[i] = false;
			honeyCombDestroyed[i] = false;
			occasionallyStop[i] = false;
			plantedFlower[i] = false;

			tier[i] = 0;
			isBeeHive[i] = false;
			stuckCounter[0][i] = -1;
			stuckCounter[1][i] = -1;
			stuckCounter[2][i] = -1;
			stuckCounter[3][i] = -1;
			indexStuckCounter[i] = 0;
			leftTheGame[i] = false;
		}

		int totalRegularBeesAccToLevel = 0;
		if (levelOne) {
			totalRegularBeesAccToLevel = 23;
			isHoneyComb[12] = true;
			isHoneyComb[20] = true;
			isHoneyComb[7] = true;

			workerBeeTexture[12].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[12].setTexture(workerBeeTexture[12]);
			workerBeeSprite[12].setTextureRect(IntRect(0, 0, workerBeeTexture[12].getSize().x, workerBeeTexture[12].getSize().y));

			workerBeeTexture[20].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[20].setTexture(workerBeeTexture[20]);
			workerBeeSprite[20].setTextureRect(IntRect(0, 0, workerBeeTexture[20].getSize().x, workerBeeTexture[20].getSize().y));

			workerBeeTexture[7].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[7].setTexture(workerBeeTexture[7]);
			workerBeeSprite[7].setTextureRect(IntRect(0, 0, workerBeeTexture[7].getSize().x, workerBeeTexture[7].getSize().y));
		}
		else if (levelTwo) {
			totalRegularBeesAccToLevel = 20;
			isHoneyComb[5] = true;
			isHoneyComb[9] = true;
			isHoneyComb[15] = true;
			isHoneyComb[19] = true;
			isHoneyComb[12] = true;

			workerBeeTexture[5].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[5].setTexture(workerBeeTexture[5]);
			workerBeeSprite[5].setTextureRect(IntRect(0, 0, workerBeeTexture[5].getSize().x, workerBeeTexture[5].getSize().y));

			workerBeeTexture[9].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[9].setTexture(workerBeeTexture[9]);
			workerBeeSprite[9].setTextureRect(IntRect(0, 0, workerBeeTexture[9].getSize().x, workerBeeTexture[9].getSize().y));

			workerBeeTexture[15].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[15].setTexture(workerBeeTexture[15]);
			workerBeeSprite[15].setTextureRect(IntRect(0, 0, workerBeeTexture[15].getSize().x, workerBeeTexture[15].getSize().y));

			workerBeeTexture[19].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[19].setTexture(workerBeeTexture[19]);
			workerBeeSprite[19].setTextureRect(IntRect(0, 0, workerBeeTexture[19].getSize().x, workerBeeTexture[19].getSize().y));

			workerBeeTexture[12].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[12].setTexture(workerBeeTexture[12]);
			workerBeeSprite[12].setTextureRect(IntRect(0, 0, workerBeeTexture[12].getSize().x, workerBeeTexture[12].getSize().y));

		}
		else if (levelThree) {
			totalRegularBeesAccToLevel = 27;
			isHoneyComb[12] = true;
			isHoneyComb[20] = true;
			isHoneyComb[7] = true;
			isHoneyComb[5] = true;
			isHoneyComb[9] = true;
			isHoneyComb[15] = true;
			isHoneyComb[19] = true;

			workerBeeTexture[12].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[12].setTexture(workerBeeTexture[12]);
			workerBeeSprite[12].setTextureRect(IntRect(0, 0, workerBeeTexture[12].getSize().x, workerBeeTexture[12].getSize().y));

			workerBeeTexture[20].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[20].setTexture(workerBeeTexture[20]);
			workerBeeSprite[20].setTextureRect(IntRect(0, 0, workerBeeTexture[20].getSize().x, workerBeeTexture[20].getSize().y));

			workerBeeTexture[7].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[7].setTexture(workerBeeTexture[7]);
			workerBeeSprite[7].setTextureRect(IntRect(0, 0, workerBeeTexture[7].getSize().x, workerBeeTexture[7].getSize().y));

			workerBeeTexture[5].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[5].setTexture(workerBeeTexture[5]);
			workerBeeSprite[5].setTextureRect(IntRect(0, 0, workerBeeTexture[5].getSize().x, workerBeeTexture[5].getSize().y));

			workerBeeTexture[9].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[9].setTexture(workerBeeTexture[9]);
			workerBeeSprite[9].setTextureRect(IntRect(0, 0, workerBeeTexture[9].getSize().x, workerBeeTexture[9].getSize().y));

			workerBeeTexture[15].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[15].setTexture(workerBeeTexture[15]);
			workerBeeSprite[15].setTextureRect(IntRect(0, 0, workerBeeTexture[15].getSize().x, workerBeeTexture[15].getSize().y));

			workerBeeTexture[19].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[19].setTexture(workerBeeTexture[19]);
			workerBeeSprite[19].setTextureRect(IntRect(0, 0, workerBeeTexture[19].getSize().x, workerBeeTexture[19].getSize().y));

		}
		else if (bossLevel) {
			totalRegularBeesAccToLevel = 32;

			isHoneyComb[12] = true;
			isHoneyComb[20] = true;
			isHoneyComb[7] = true;
			isHoneyComb[5] = true;
			isHoneyComb[9] = true;
			isHoneyComb[15] = true;
			isHoneyComb[19] = true;

			isHoneyComb[2] = true;
			isHoneyComb[25] = true;
			isHoneyComb[28] = true;
			isHoneyComb[17] = true;
			isHoneyComb[12] = true;

			isBeeHive[2] = true;
			isBeeHive[25] = true;
			isBeeHive[28] = true;
			isBeeHive[17] = true;
			isBeeHive[12] = true;

			workerBeeTexture[12].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[12].setTexture(workerBeeTexture[12]);
			workerBeeSprite[12].setTextureRect(IntRect(0, 0, workerBeeTexture[12].getSize().x, workerBeeTexture[12].getSize().y));

			workerBeeTexture[20].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[20].setTexture(workerBeeTexture[20]);
			workerBeeSprite[20].setTextureRect(IntRect(0, 0, workerBeeTexture[20].getSize().x, workerBeeTexture[20].getSize().y));

			workerBeeTexture[7].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[7].setTexture(workerBeeTexture[7]);
			workerBeeSprite[7].setTextureRect(IntRect(0, 0, workerBeeTexture[7].getSize().x, workerBeeTexture[7].getSize().y));

			workerBeeTexture[5].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[5].setTexture(workerBeeTexture[5]);
			workerBeeSprite[5].setTextureRect(IntRect(0, 0, workerBeeTexture[5].getSize().x, workerBeeTexture[5].getSize().y));

			workerBeeTexture[9].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[9].setTexture(workerBeeTexture[9]);
			workerBeeSprite[9].setTextureRect(IntRect(0, 0, workerBeeTexture[9].getSize().x, workerBeeTexture[9].getSize().y));

			workerBeeTexture[15].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[15].setTexture(workerBeeTexture[15]);
			workerBeeSprite[15].setTextureRect(IntRect(0, 0, workerBeeTexture[15].getSize().x, workerBeeTexture[15].getSize().y));

			workerBeeTexture[19].loadFromFile("Textures/honeycomb.png");
			workerBeeSprite[19].setTexture(workerBeeTexture[19]);
			workerBeeSprite[19].setTextureRect(IntRect(0, 0, workerBeeTexture[19].getSize().x, workerBeeTexture[19].getSize().y));

			workerBeeTexture[2].loadFromFile("Textures/hive.png");
			workerBeeSprite[2].setTexture(workerBeeTexture[2]);
			workerBeeSprite[2].setTextureRect(IntRect(0, 0, workerBeeTexture[2].getSize().x, workerBeeTexture[2].getSize().y));

			workerBeeTexture[28].loadFromFile("Textures/hive.png");
			workerBeeSprite[28].setTexture(workerBeeTexture[28]);
			workerBeeSprite[28].setTextureRect(IntRect(0, 0, workerBeeTexture[28].getSize().x, workerBeeTexture[28].getSize().y));

			workerBeeTexture[25].loadFromFile("Textures/hive.png");
			workerBeeSprite[25].setTexture(workerBeeTexture[25]);
			workerBeeSprite[25].setTextureRect(IntRect(0, 0, workerBeeTexture[25].getSize().x, workerBeeTexture[25].getSize().y));

			workerBeeTexture[17].loadFromFile("Textures/hive.png");
			workerBeeSprite[17].setTexture(workerBeeTexture[17]);
			workerBeeSprite[17].setTextureRect(IntRect(0, 0, workerBeeTexture[17].getSize().x, workerBeeTexture[17].getSize().y));

			workerBeeTexture[12].loadFromFile("Textures/hive.png");
			workerBeeSprite[12].setTexture(workerBeeTexture[12]);
			workerBeeSprite[12].setTextureRect(IntRect(0, 0, workerBeeTexture[12].getSize().x, workerBeeTexture[12].getSize().y));

		}

		///////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////////////////
		/// Fast Bees
		const int totalFastBees = 18;
		Texture fastBeeTexture[totalFastBees];
		int tierFastBees[totalFastBees];
		Sprite fastBeeSprite[totalFastBees];
		float fastBeeLocations[2][totalFastBees];
		bool isFastBeeHoneyComb[totalFastBees];
		bool fastBeeHoneyCombDestroyed[totalFastBees];
		bool directionsFastBees[3][totalFastBees];
		bool occasionallyFastStop[totalFastBees];
		bool stopMovementForWhileFastBee = false;
		bool fastBeePlantedFlower[totalFastBees];
		bool fastBeeLeftTheGame[totalFastBees];


		Clock clockFastBees;
		for (int i = 0; i < totalFastBees; i++) {
			fastBeeTexture[i].loadFromFile("Textures/Fast_bee.png");
			fastBeeSprite[i].setTexture(fastBeeTexture[i]);
			fastBeeLocations[0][i] = 50 * i + 1;
			int randomVariable = 1 + rand() % 3;
			if (randomVariable == 1) {
				fastBeeLocations[1][i] = 125;
				//tier[i] = 3;
			}
			else if (randomVariable == 2) {
				fastBeeLocations[1][i] = 225;
				//tier[i] = 5;
			}
			else if (randomVariable == 3) {
				fastBeeLocations[1][i] = 325;
				//tier[i] = 4;
			}
			randomVariable = 1 + rand() % 2;
			if (randomVariable == 1) {
				directionsFastBees[0][i] = true;
				directionsFastBees[1][i] = false;
				directionsFastBees[2][i] = false;
			}
			else {
				directionsFastBees[0][i] = false;
				directionsFastBees[1][i] = true;
				directionsFastBees[2][i] = false;
			}


			isFastBeeHoneyComb[i] = false;
			fastBeeHoneyCombDestroyed[i] = false;
			occasionallyFastStop[i] = false;
			fastBeePlantedFlower[i] = false;
			tierFastBees[i] = 0;
			fastBeeLeftTheGame[i] = false;
		}


		int totalFastBeesAccToLevel = 0;
		if (levelOne) {
			totalFastBeesAccToLevel = 0;
		}
		else if (levelTwo) {
			totalFastBeesAccToLevel = 9;
			isFastBeeHoneyComb[4] = true;
			isFastBeeHoneyComb[8] = true;
			isFastBeeHoneyComb[0] = true;

			fastBeeTexture[4].loadFromFile("Textures/honeycomb_red.png");
			fastBeeSprite[4].setTexture(fastBeeTexture[4]);
			fastBeeSprite[4].setTextureRect(IntRect(0, 0, fastBeeTexture[4].getSize().x, fastBeeTexture[4].getSize().y));

			fastBeeTexture[8].loadFromFile("Textures/honeycomb_red.png");
			fastBeeSprite[8].setTexture(fastBeeTexture[8]);
			fastBeeSprite[8].setTextureRect(IntRect(0, 0, fastBeeTexture[8].getSize().x, fastBeeTexture[8].getSize().y));

			fastBeeTexture[0].loadFromFile("Textures/honeycomb_red.png");
			fastBeeSprite[0].setTexture(fastBeeTexture[0]);
			fastBeeSprite[0].setTextureRect(IntRect(0, 0, fastBeeTexture[0].getSize().x, fastBeeTexture[0].getSize().y));

		}
		else if (levelThree) {
			totalFastBeesAccToLevel = 18;
			isFastBeeHoneyComb[4] = true;
			isFastBeeHoneyComb[8] = true;
			isFastBeeHoneyComb[0] = true;
			isFastBeeHoneyComb[17] = true;
			isFastBeeHoneyComb[14] = true;
			isFastBeeHoneyComb[10] = true;
			isFastBeeHoneyComb[11] = true;
			isFastBeeHoneyComb[6] = true;
			fastBeeTexture[4].loadFromFile("Textures/honeycomb_red.png");
			fastBeeSprite[4].setTexture(fastBeeTexture[4]);
			fastBeeSprite[4].setTextureRect(IntRect(0, 0, fastBeeTexture[4].getSize().x, fastBeeTexture[4].getSize().y));
			fastBeeTexture[8].loadFromFile("Textures/honeycomb_red.png");
			fastBeeSprite[8].setTexture(fastBeeTexture[8]);
			fastBeeSprite[8].setTextureRect(IntRect(0, 0, fastBeeTexture[8].getSize().x, fastBeeTexture[8].getSize().y));
			fastBeeTexture[0].loadFromFile("Textures/honeycomb_red.png");
			fastBeeSprite[0].setTexture(fastBeeTexture[0]);
			fastBeeSprite[0].setTextureRect(IntRect(0, 0, fastBeeTexture[0].getSize().x, fastBeeTexture[0].getSize().y));
			fastBeeTexture[17].loadFromFile("Textures/honeycomb_red.png");
			fastBeeSprite[17].setTexture(fastBeeTexture[17]);
			fastBeeSprite[17].setTextureRect(IntRect(0, 0, fastBeeTexture[17].getSize().x, fastBeeTexture[17].getSize().y));
			fastBeeTexture[14].loadFromFile("Textures/honeycomb_red.png");
			fastBeeSprite[14].setTexture(fastBeeTexture[14]);
			fastBeeSprite[14].setTextureRect(IntRect(0, 0, fastBeeTexture[14].getSize().x, fastBeeTexture[14].getSize().y));
			fastBeeTexture[10].loadFromFile("Textures/honeycomb_red.png");
			fastBeeSprite[10].setTexture(fastBeeTexture[10]);
			fastBeeSprite[10].setTextureRect(IntRect(0, 0, fastBeeTexture[10].getSize().x, fastBeeTexture[10].getSize().y));
			fastBeeTexture[11].loadFromFile("Textures/honeycomb_red.png");
			fastBeeSprite[11].setTexture(fastBeeTexture[11]);
			fastBeeSprite[11].setTextureRect(IntRect(0, 0, fastBeeTexture[11].getSize().x, fastBeeTexture[11].getSize().y));
			fastBeeTexture[6].loadFromFile("Textures/honeycomb_red.png");
			fastBeeSprite[6].setTexture(fastBeeTexture[6]);
			fastBeeSprite[6].setTextureRect(IntRect(0, 0, fastBeeTexture[6].getSize().x, fastBeeTexture[6].getSize().y));
		}
		else if (bossLevel) {
			totalFastBeesAccToLevel = 18;
		}
		//////////////////////////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////////////////////////
		/// Humming bird
		Texture birdTexture;
		Sprite birdSprite;
		birdTexture.loadFromFile("Textures/bird1.png");
		birdSprite.setTexture(birdTexture);
		birdSprite.setScale(1.25, 1.25);

		bool birdVisible = false;
		float bird_x = 0.0;
		float bird_y = 0.0;
		int countBulletHit = 0;

		Clock birdClock, birdNextDirectionClock;

		float next_xBird;
		float next_yBird;

		bool birdNotMoving = false;

		/////////////////////////////////////////////////////////////////////////////////////////////



		////////////////////////////////////////////////////////////////////////////////////////////////
		////// FLOWER Implementation
		const int totalFlowers = 11;
		Texture flowerTexture;
		flowerTexture.loadFromFile("Textures/obstacles.png");
		Sprite flowerSprite[totalFlowers];
		bool flowerVisible[totalFlowers];
		float flowerLocation[2][totalFlowers];
		int currentFlowersOnScreen = 0;
		for (int i = 0; i < totalFlowers; i++) {
			flowerSprite[i].setTexture(flowerTexture);
			flowerSprite[i].setScale(3.0, 2);

			flowerVisible[i] = false;

			flowerLocation[0][i] = (i) * 85;
			flowerLocation[1][i] = resolutionY - 100;

			flowerSprite[i].setPosition(flowerLocation[0][i], flowerLocation[1][i]);
		}

		///////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////
		//// Score
		Font font;
		font.loadFromFile("fonts/Grind_Demolished.ttf");
		Text scoreText;
		scoreText.setFont(font);                           // Set the font
		scoreText.setCharacterSize(30);                   // Set the font size
		scoreText.setFillColor(sf::Color::White);         // Set the text color
		scoreText.setPosition(540, 600);
		scoreText.setString("Score : " + to_string(scoreGameplay));

		//////////////////////////////////////////////////////////////////////////////////////////////



		while (window.isOpen()) {

			Event e;
			while (window.pollEvent(e)) {
				if (e.type == Event::Closed) {

					addHighScore(name, scoreGameplay);
					return 0;
				}
			}

			window.draw(backgroundSprite);

			window.draw(healthRectangle);
			window.draw(groundRectangle);

			movePlayer(player_x, player_y, healthRectangle, decreaseLevelVariable, flowerLocation, flowerVisible);
			fireBullet(bullet_exists, bullet_x, bullet_y, player_x, player_y, totalSprayFired, healthRectangle, decreaseLevelVariable, sprayLeft);
			drawOtherSprayCans(sprayLeft, window, spraySprite);

			drawWorkerBee(window, workerBeeLocations, workerBeeSprite, totalRegularBeesAccToLevel, honeyCombDestroyed);
			moveWorkerBees(directionsBees, workerBeeLocations, totalRegularBeesAccToLevel, tier, isHoneyComb, honeyCombDestroyed, occasionallyStop, plantedFlower, workerBeeSprite, fastBeeLocations, isFastBeeHoneyComb, fastBeeHoneyCombDestroyed, totalFastBees, stuckCounter, indexStuckCounter, isBeeHive, workerBeeTexture , leftTheGame);

			checkWorkerBeeCollisionWithBullet(workerBeeLocations, totalRegularBeesAccToLevel, isHoneyComb, bullet_x, bullet_y, workerBeeSprite, workerBeeTexture, honeyCombDestroyed, collisionStopFlag, plantedFlower, scoreGameplay);
			randomStopGenerator(clock, totalRegularBeesAccToLevel, occasionallyStop, stopMovementForWhile, plantedFlower);

			plantFlowers(workerBeeLocations, totalRegularBeesAccToLevel, isHoneyComb, currentFlowersOnScreen, flowerVisible, plantedFlower, player_x, player_y, flowerLocation);
			drawFlowers(window, flowerLocation, flowerSprite, totalFlowers, flowerVisible);


			drawFastBee(window, fastBeeLocations, fastBeeSprite, totalFastBeesAccToLevel, fastBeeHoneyCombDestroyed);
			moveFastBees(directionsFastBees, fastBeeLocations, totalFastBeesAccToLevel, tierFastBees, isFastBeeHoneyComb, fastBeeHoneyCombDestroyed, fastBeePlantedFlower, fastBeeSprite , fastBeeLeftTheGame);
			checkFastBeeCollisionWithBullet(fastBeeLocations, totalFastBeesAccToLevel, isFastBeeHoneyComb, bullet_x, bullet_y, fastBeeSprite, fastBeeTexture, fastBeeHoneyCombDestroyed, collisionStopFlag, fastBeePlantedFlower, scoreGameplay);
			fastBeePlantFlowers(fastBeeLocations, totalFastBeesAccToLevel, isFastBeeHoneyComb, currentFlowersOnScreen, flowerVisible, fastBeePlantedFlower, player_x, player_y, flowerLocation);

			checkAllFlowersPlanted(flowerVisible, sprayLeft, decreaseLevelVariable, totalSprayFired);



			if (!birdVisible) {
				spawnBird(birdClock, birdVisible);
				if (birdVisible) {
					selectHoneyComb(fastBeeLocations, isFastBeeHoneyComb, workerBeeLocations, isHoneyComb, totalRegularBeesAccToLevel, totalFastBeesAccToLevel, next_xBird, next_yBird);
				}
			}
			if (birdVisible) {
				if (moveBird(bird_x, bird_y, next_xBird, next_yBird)) {
					if (bird_x == 960 && bird_y == 440) {
						birdClock.restart();
						birdVisible = false;
						cout << "Reached";
						bird_x = 0.0;
						bird_y = 0.0;
						countBulletHit = 0;
					}
					else if (!birdNotMoving) {
						birdNextDirectionClock.restart();
						birdNotMoving = true;
						calculateHummingBordScore(bird_x, bird_y, workerBeeLocations, isHoneyComb, isFastBeeHoneyComb, fastBeeLocations, totalRegularBeesAccToLevel, totalFastBeesAccToLevel, scoreGameplay);
					}

				}
				checkBulletandBirdCollision(bullet_x, bullet_y, bird_x, bird_y, next_xBird, next_yBird, countBulletHit, birdCollisionStopFlag);
			}
			if (birdNotMoving && birdNextDirectionClock.getElapsedTime().asSeconds() >= 3.0f) {
				birdNotMoving = false;
				selectHoneyComb(fastBeeLocations, isFastBeeHoneyComb, workerBeeLocations, isHoneyComb, totalRegularBeesAccToLevel, totalFastBeesAccToLevel, next_xBird, next_yBird);
			}


			if (bullet_exists == true)
			{
				moveBullet(bullet_y, bullet_exists, bulletClock, collisionStopFlag, birdCollisionStopFlag);
				drawBullet(window, bullet_x, bullet_y, bulletSprite);
			}
			drawBird(window, bird_x, bird_y, birdSprite, birdVisible);
			drawPlayer(window, player_x, player_y, playerSprite);

			scoreText.setString("Score : " + to_string(scoreGameplay));
			window.draw(scoreText);
			window.display();
			window.clear();


			/// End Game and Level incrementing Logic Starts Here
			if (sprayLeft == 0) {
				addHighScore(name, scoreGameplay);
				break;
			}
			
			if (incrementLevel(isHoneyComb, totalRegularBeesAccToLevel, isFastBeeHoneyComb, leftTheGame, totalFastBeesAccToLevel, fastBeeLeftTheGame)) {
				if (levelOne) {
					levelOne = false;
					levelTwo = true; 
					
				}
				else if (levelTwo) {
					levelTwo = false;
					levelThree = true; 
				}
				else if (levelThree) {
					levelThree = false;
					bossLevel = true;
				}
				else if (bossLevel) {
					quit = true;
				}
				calculateBeeHiveScore(scoreGameplay, workerBeeLocations, isBeeHive, totalRegularBeesAccToLevel, honeyCombDestroyed);
				break;
			}

		}

		

		if (quit || sprayLeft == 0) {
			addHighScore(name, scoreGameplay);
			break;
		}



	}
}
void menu(bool& levelOne, bool& levelTwo, bool& levelThree, bool& bossLevel, bool& quit, bool& highScore) {
	RenderWindow window(VideoMode(960, 540), "Menu");

	Font font;
	font.loadFromFile("fonts/Grind_Demolished.ttf");

	int buttonWidth = 200;
	int buttonHeight = 50;
	int centerX = (960 - buttonWidth) / 2;


	Text levelOneText("LEVEL 1", font, 30);
	levelOneText.setFillColor(Color::Green);
	levelOneText.setPosition(centerX + 20, 105);

	Text levelTwoText("LEVEL 2", font, 30);
	levelTwoText.setFillColor(Color::Green);
	levelTwoText.setPosition(centerX + 20, 175);

	Text levelThreeText("LEVEL 3", font, 30);
	levelThreeText.setFillColor(Color::Green);
	levelThreeText.setPosition(centerX + 20, 245);

	Text levelFourText("BOSS LEVEL", font, 30);
	levelFourText.setFillColor(Color::Green);
	levelFourText.setPosition(centerX, 315);

	Text stopButtonText("QUIT", font, 30);
	stopButtonText.setFillColor(Color::Green);
	stopButtonText.setPosition(centerX + 50, 385);

	Text highScoreText("HIGHSCORE", font, 30);
	highScoreText.setFillColor(Color::Green);
	highScoreText.setPosition(centerX + 10, 455);


	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				return;
			}
		}

		if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {
			Vector2i mousePosition = Mouse::getPosition(window);


			if (mousePosition.x >= centerX && mousePosition.x <= centerX + buttonWidth) {
				if (mousePosition.y >= 100 && mousePosition.y <= 100 + buttonHeight) {
					levelOne = true;
					window.close();
					return;
				}
				else if (mousePosition.y >= 170 && mousePosition.y <= 170 + buttonHeight) {
					levelTwo = true;
					window.close();
					return;
				}
				else if (mousePosition.y >= 240 && mousePosition.y <= 240 + buttonHeight) {
					levelThree = true;
					window.close();
					return;
				}
				else if (mousePosition.y >= 310 && mousePosition.y <= 310 + buttonHeight) {
					bossLevel = true;
					window.close();
					return;
				}
				else if (mousePosition.y >= 380 && mousePosition.y <= 380 + buttonHeight) {
					quit = true;
					window.close();
					return;
				}
				else if (mousePosition.y >= 450 && mousePosition.y <= 450 + buttonHeight) {
					showHighScores();
				}
			}
		}


		window.clear(Color::Black);
		window.draw(levelOneText);
		window.draw(levelTwoText);
		window.draw(levelThreeText);
		window.draw(levelFourText);
		window.draw(highScoreText);
		window.draw(stopButtonText);


		window.display();
	}

}
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite) {
	playerSprite.setPosition(player_x, player_y);
	window.draw(playerSprite);
}
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock , bool &collisionStopFlag , bool & birdCollisionStopFlag) {
	bullet_y -= 0.6;
	if (bullet_y < -32) {
		bullet_exists = false;
		collisionStopFlag = false;
		birdCollisionStopFlag = false;
	}
}
void drawBullet(sf::RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite) {
	bulletSprite.setPosition(bullet_x, bullet_y);
	window.draw(bulletSprite);
}
void movePlayer(float &player_x,float& player_y , RectangleShape& healthRectangle , int decreaseLevelVariable, float flowerLocation[][11] , bool flowerVisible[]) {

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		
		bool collide = false;
		for (int i = 0; i < 11; i++) {
			if (flowerVisible[i]) {
				float start = flowerLocation[0][i];
				float end = start + 80;

				if (player_x + 40 >= start && player_x < end) {
					collide = true;
					break;
				}
			}
		}

		if (collide || player_x >= 900) return;
		player_x += 0.1;
		
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		bool collide = false;
		for (int i = 0; i < 11; i++) {
			if (flowerVisible[i]) {
				float start = flowerLocation[0][i];
				float end = start + 80;
				if (player_x - 10 <= end && player_x > start) {
					collide = true;
					break;
				}
			}
		}
		if (collide) return;
		if (player_x <= 10) return;
		player_x -= 0.1;
		//healthRectangle.setPosition(player_x + 22, player_y + 36 + (decreaseLevelVariable * 4));
	}
	healthRectangle.setPosition(player_x + 22, player_y + 36 + (decreaseLevelVariable * 4));
}
void fireBullet(bool & bullet_exists , float &bullet_x , float &bullet_y , float player_x, float player_y , int &totalSprayFired , RectangleShape& healthRectangle , int& decreaseLevelVariable , int& sprayLeft) {
	if (bullet_exists)
		return;
	
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		bullet_exists = true;
		bullet_x = player_x;
		bullet_y = player_y;
		
		totalSprayFired++;
		
		if (totalSprayFired % 8 == 0) {
			decreaseLevelVariable++;
			healthRectangle.setSize(Vector2f(20, 30 - (decreaseLevelVariable * 4)));
			healthRectangle.setPosition(player_x + 22, player_y + 36 + (decreaseLevelVariable * 4));
		}
		loadNewCan(healthRectangle, totalSprayFired, decreaseLevelVariable, sprayLeft , player_x,player_y);
	}
}
void drawOtherSprayCans(int sprayLeft , RenderWindow& window, Sprite spraySprite[]) {
	for (int i = 0; i < sprayLeft; i++) {
		spraySprite[i].setPosition(5+(i)*30 , 600);
		window.draw(spraySprite[i]);
	}
}
void loadNewCan(RectangleShape& healthRectangle, int & totalSprayFired , int & decreaseLevelVariable, int &sprayLeft , float player_x, float player_y) {
	if (totalSprayFired < 56)
		return;
	
	sprayLeft--;
	decreaseLevelVariable = 0;

	totalSprayFired = 0;
	healthRectangle.setSize(Vector2f(20, 30 - (decreaseLevelVariable * 4)));
	healthRectangle.setPosition(player_x + 22, player_y + 36 + (decreaseLevelVariable * 4));
}
void drawWorkerBee(RenderWindow& window, float workerBeeLocations[][32], Sprite workerBeeSprite[32],  int& totalBees, bool honeyCombDestroyed[]) {
	for (int i = 0; i < totalBees; i++) {
		workerBeeSprite[i].setPosition(workerBeeLocations[0][i], workerBeeLocations[1][i]);
		
		if(!honeyCombDestroyed[i])
		window.draw(workerBeeSprite[i]);
	}
}
void moveWorkerBees(bool directionsBees[3][32],float workerBeeLocations[][32] ,  int & totalBees , int tier[32], bool isHoneyComb[] , bool honeyCombDestroyed[] , bool occasionallyStop[] , bool plantedFlower[], Sprite workerBeeSprite[32], float fastBeeLocations[][18] , bool isFastBeeHoneyComb[], bool fastBeeHoneyCombDestroyed[] , int totalFastBees, int stuckCounter[4][32] , int indexStuckCounter[] , bool isBeeHive[], Texture workerBeeTexture[] , bool leftTheGame[]) {
	
	for (int i = 0; i < totalBees; i++) {
		
		if (occasionallyStop[i] || isHoneyComb[i]) {
			continue;
		}

		if (plantedFlower[i] || workerBeeLocations[1][i] >= 550) {
			if (directionsBees[0][i]) {
				workerBeeLocations[0][i] -= 0.1;
				if (workerBeeLocations[0][i] <= 0) {
					leftTheGame[i] = true;
				}
				continue;
			}
			else if(directionsBees[1][i]) {
				workerBeeLocations[0][i] += 0.1;
				if (workerBeeLocations[0][i] >=900) {
					leftTheGame[i] = true;
				}
				continue;
			}
		}
		
		
		if (stuckCounter[0][i] == 0 && stuckCounter[1][i] == 500 && stuckCounter[2][i] == 0 && stuckCounter[3][i] == 500) {
			isBeeHive[i] = true; isHoneyComb[i] = true;
			workerBeeTexture[i].loadFromFile("Textures/hive.png");
			workerBeeSprite[i].setTexture(workerBeeTexture[i]);
			workerBeeSprite[i].setTextureRect(IntRect(0, 0, workerBeeTexture[i].getSize().x, workerBeeTexture[i].getSize().y));
		}
		

		if (tier[i] > 0) {
			workerBeeLocations[1][i] += 0.05;
			tier[i]--; 
			if (tier[i] < 400) {
				stuckCounter[indexStuckCounter[i] % 4][i] = tier[i];
				indexStuckCounter[i]++;
				if (indexStuckCounter[i] == 4) indexStuckCounter[i] = 0;
			}
			bool flag = true;
			for (int j = 0; j < totalBees; j++) {
				if (i == j || !isHoneyComb[j] || honeyCombDestroyed[j]) {
					continue;
				}

				if (workerBeeLocations[0][j] + 42 > workerBeeLocations[0][i] && workerBeeLocations[0][i] > workerBeeLocations[0][j] - 42) {
					if (workerBeeLocations[1][j] + 70 > workerBeeLocations[1][i] && workerBeeLocations[1][i] > workerBeeLocations[1][j] - 60) {
						while(workerBeeLocations[0][j] + 42 > workerBeeLocations[0][i] && workerBeeLocations[0][i] > workerBeeLocations[0][j] - 42 && workerBeeLocations[1][j] + 70 > workerBeeLocations[1][i] && workerBeeLocations[1][i] > workerBeeLocations[1][j] - 60)
						workerBeeLocations[1][i] -= 0.05;
						tier[i] = 0;
						stuckCounter[indexStuckCounter[i] % 4][i] = tier[i];
						//indexStuckCounter[i]++;
						flag = false;
						if (indexStuckCounter[i] == 4) indexStuckCounter[i] = 0;
						directionsBees[0][i] = rand() % 2;
						directionsBees[1][i] = !directionsBees[0][i];
					}
				}
			}

			for (int j = 0; j < totalFastBees; j++) {
				if (!isFastBeeHoneyComb[j] || fastBeeHoneyCombDestroyed[j]) {
					continue;
				}

				if (fastBeeLocations[0][j] + 42 > workerBeeLocations[0][i] && workerBeeLocations[0][i] > fastBeeLocations[0][j] - 42) {
					if (fastBeeLocations[1][j] + 70 > workerBeeLocations[1][i] && workerBeeLocations[1][i] > fastBeeLocations[1][j] - 60) {
						while (fastBeeLocations[0][j] + 42 > workerBeeLocations[0][i] && workerBeeLocations[0][i] > fastBeeLocations[0][j] - 42 && fastBeeLocations[1][j] + 70 > workerBeeLocations[1][i] && workerBeeLocations[1][i] > fastBeeLocations[1][j] - 60)
							workerBeeLocations[1][i] -= 0.05;
						tier[i] = 0;
						stuckCounter[indexStuckCounter[i] % 4][i] = tier[i];
						//indexStuckCounter[i]++;
						flag = false;
						if (indexStuckCounter[i] == 4) indexStuckCounter[i] = 0;
						directionsBees[0][i] = rand() % 2;
						directionsBees[1][i] = !directionsBees[0][i];
					}
				}
			}
			if (!flag) {
				indexStuckCounter[i]++;
				if (indexStuckCounter[i] == 4) indexStuckCounter[i] = 0;
			}

			if (tier[i] == 0) {
				directionsBees[0][i] = ((rand() % 100) %2);
				directionsBees[1][i] = !directionsBees[0][i];
			}
			workerBeeSprite[i].setPosition(workerBeeLocations[0][i], workerBeeLocations[1][i]);
		}
		if (tier[i] == 0) {
			if (directionsBees[0][i]) {
				workerBeeLocations[0][i] -= 0.05; bool flag = true;
				if (workerBeeLocations[0][i] <= 0) {
					tier[i] = 500;
					
					stuckCounter[indexStuckCounter[i] % 4][i] = tier[i];
					//indexStuckCounter[i]++;
					flag = false;
					if (indexStuckCounter[i] == 4) indexStuckCounter[i] = 0;
					
					directionsBees[0][i] = false; // not 
				}
				for (int j = 0; j < totalBees; j++) {
					if (i == j || !isHoneyComb[j] || honeyCombDestroyed[j]) {
						continue;
					}

					if (workerBeeLocations[0][j] + 42 > workerBeeLocations[0][i] && workerBeeLocations[0][i] > workerBeeLocations[0][j] - 42) {
						if (workerBeeLocations[1][j] + 70 > workerBeeLocations[1][i] && workerBeeLocations[1][i] > workerBeeLocations[1][j] - 60) {
							while (workerBeeLocations[0][j] + 42 > workerBeeLocations[0][i] && workerBeeLocations[0][i] > workerBeeLocations[0][j] - 42 && workerBeeLocations[1][j] + 70 > workerBeeLocations[1][i] && workerBeeLocations[1][i] > workerBeeLocations[1][j] - 60)
							workerBeeLocations[0][i] += 0.05;
							tier[i] = 500;
							stuckCounter[indexStuckCounter[i] % 4][i] = tier[i];
							//indexStuckCounter[i]++;
							flag = false;
							if (indexStuckCounter[i] == 4) indexStuckCounter[i] = 0;
							directionsBees[0][i] = false;
						}
					}
				}

				for (int j = 0; j < totalFastBees; j++) {
					if (!isFastBeeHoneyComb[j] || fastBeeHoneyCombDestroyed[j]) {
						continue;
					}

					if (fastBeeLocations[0][j] + 42 > workerBeeLocations[0][i] && workerBeeLocations[0][i] > fastBeeLocations[0][j] - 42) {
						if (fastBeeLocations[1][j] + 70 > workerBeeLocations[1][i] && workerBeeLocations[1][i] > fastBeeLocations[1][j] - 60) {
							while (fastBeeLocations[0][j] + 42 > workerBeeLocations[0][i] && workerBeeLocations[0][i] > fastBeeLocations[0][j] - 42 && fastBeeLocations[1][j] + 70 > workerBeeLocations[1][i] && workerBeeLocations[1][i] > fastBeeLocations[1][j] - 60)
								workerBeeLocations[0][i] += 0.05;
							tier[i] = 500;
							stuckCounter[indexStuckCounter[i]][i] = tier[i];
							//indexStuckCounter[i]++;
							flag = false;
							if (indexStuckCounter[i] == 4) indexStuckCounter[i] = 0;
							directionsBees[0][i] = false;
						}
					}
				}
				if (!flag) {
					indexStuckCounter[i]++;
					if (indexStuckCounter[i] == 4) indexStuckCounter[i] = 0;
					directionsBees[0][i] = false;
				}
				workerBeeSprite[i].setPosition(workerBeeLocations[0][i], workerBeeLocations[1][i]);
			}
			else if (directionsBees[1][i]) {
				workerBeeLocations[0][i] += 0.05; bool flag = true;
				if (workerBeeLocations[0][i] >=900) {
					tier[i] = 500;
					stuckCounter[indexStuckCounter[i] % 4][i] = tier[i];
					//indexStuckCounter[i]++;
					flag = false;
					if (indexStuckCounter[i] == 4) indexStuckCounter[i] = 0;
					directionsBees[1][i] = false;
				}

				for (int j = 0; j < totalBees; j++) {
					if (i == j || !isHoneyComb[j] || honeyCombDestroyed[j]) {
						continue;
					}

					if (workerBeeLocations[0][j] + 42 > workerBeeLocations[0][i] && workerBeeLocations[0][i] > workerBeeLocations[0][j] - 42) {
						if (workerBeeLocations[1][j] + 70 > workerBeeLocations[1][i] && workerBeeLocations[1][i] > workerBeeLocations[1][j] - 60) {
							while (workerBeeLocations[0][j] + 42 > workerBeeLocations[0][i] && workerBeeLocations[0][i] > workerBeeLocations[0][j] - 42 && workerBeeLocations[1][j] + 70 > workerBeeLocations[1][i] && workerBeeLocations[1][i] > workerBeeLocations[1][j] - 60)
							workerBeeLocations[0][i] -= 0.05;
							tier[i] = 500;
							stuckCounter[indexStuckCounter[i] % 4][i] = tier[i];
							//indexStuckCounter[i]++;
							flag = false;
							if (indexStuckCounter[i] == 4) indexStuckCounter[i] = 0;
							directionsBees[1][i] = false;
						}
	
					}
				}
				for (int j = 0; j < totalFastBees; j++) {
					if (!isFastBeeHoneyComb[j] || fastBeeHoneyCombDestroyed[j]) {
						continue;
					}

					if (fastBeeLocations[0][j] + 42 > workerBeeLocations[0][i] && workerBeeLocations[0][i] > fastBeeLocations[0][j] - 42) {
						if (fastBeeLocations[1][j] + 70 > workerBeeLocations[1][i] && workerBeeLocations[1][i] > fastBeeLocations[1][j] - 60) {
							while (fastBeeLocations[0][j] + 42 > workerBeeLocations[0][i] && workerBeeLocations[0][i] > fastBeeLocations[0][j] - 42 && fastBeeLocations[1][j] + 70 > workerBeeLocations[1][i] && workerBeeLocations[1][i] > fastBeeLocations[1][j] - 60)
								workerBeeLocations[0][i] -= 0.05;
							tier[i] = 500;
							stuckCounter[indexStuckCounter[i] % 4][i] = tier[i];
							//indexStuckCounter[i]++;
							flag = false;
							if (indexStuckCounter[i] == 4) indexStuckCounter[i] = 0;
							directionsBees[1][i] = false;
						}

					}
				}
				if (!flag) {
					indexStuckCounter[i]++;
					if (indexStuckCounter[i] == 4) indexStuckCounter[i] = 0;
					directionsBees[0][i] = false;
				}
				workerBeeSprite[i].setPosition(workerBeeLocations[0][i], workerBeeLocations[1][i]);
			}
		
		}

	}


}
void checkWorkerBeeCollisionWithBullet(float workerBeeLocations[][32], int& totalBees ,bool isHoneyComb[] , float& bullet_x, float& bullet_y, Sprite workerBeeSprite[], Texture workerBeeTexture[] , bool honeyCombDestroyed[] , bool &collisionStopFlag , bool plantedFlower[] , long long  & scoreGameplay) {
	if (collisionStopFlag) return;
	for (int i = 0; i < totalBees; i++) {
		if (plantedFlower[i]) continue;
		if (workerBeeLocations[0][i] + 30 > bullet_x && bullet_x > workerBeeLocations[0][i] - 30) {
			if (workerBeeLocations[1][i] + 15 > bullet_y && bullet_y > workerBeeLocations[1][i] - 15) {
				if (isHoneyComb[i] == false) {
					isHoneyComb[i] = true;
					
					workerBeeTexture[i].loadFromFile("Textures/honeycomb.png");
					workerBeeSprite[i].setTexture(workerBeeTexture[i]);
					workerBeeSprite[i].setTextureRect(IntRect(0, 0, workerBeeTexture[i].getSize().x, workerBeeTexture[i].getSize().y));
					
					collisionStopFlag = true;
					
					scoreGameplay += 100;
					return;
				}
				else {
					honeyCombDestroyed[i] = true;
				}
			}
		}
	}
}
void randomStopGenerator(Clock& clock, int& totalBees , bool occasionallyStop[], bool & stopMovementForWhile , bool plantedFlower[]) {
	
	if (clock.getElapsedTime().asSeconds() >= 12.0f) {
		clock.restart();
		stopMovementForWhile = false;
	}
	else if (clock.getElapsedTime().asSeconds() <= 2.0f) {
		for (int i = 0; i < totalBees; i++) {
			occasionallyStop[i] = false;
		}
	}

	else if (!stopMovementForWhile && clock.getElapsedTime().asSeconds() >= 10.0f ) {
		for (int i = 0; i < totalBees; i++) {
			
			if (plantedFlower[i]) continue;
			
			int random = 1+rand() % 100;
			if (random <=70) {
				occasionallyStop[i] = true;
			}
			else {
				occasionallyStop[i] = false;
			}
		}
		stopMovementForWhile = true;
	}
}
void drawFlowers(RenderWindow& window, float flowerLocation[][11], Sprite flowerSprite[11], const int& totalFlowers, bool flowerVisible[]) {
	for (int i = 0; i < totalFlowers; i++) {
		if (flowerVisible[i]) {
			flowerSprite[i].setPosition(flowerLocation[0][i], flowerLocation[1][i]);
			window.draw(flowerSprite[i]);
		}
	}
}
void plantFlowers(float workerBeeLocations[][32], int& totalBees , bool isHoneyComb[] , int currentFlowersOnScreen , bool flowerVisible[], bool plantedFlower[] , float& player_x , float& player_y, float flowerLocation[][11]) {
	for (int i = 0; i < totalBees; i++) {
		if (plantedFlower[i]) continue;
		if (workerBeeLocations[1][i]>= 540 && !isHoneyComb[i]) {
			
			if (workerBeeLocations[0][i] >= 0 && workerBeeLocations[0][i] <= 80) {
				if (flowerVisible[0]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[0] = true;
					flowerVisible[1] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[0] = true;
					currentFlowersOnScreen++;
				}
				plantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (workerBeeLocations[0][i] >= 80 && workerBeeLocations[0][i] <= 160) {
				if (flowerVisible[1]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[0] = true;
					flowerVisible[1] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[1] = true;
					currentFlowersOnScreen++;
				}
				plantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (workerBeeLocations[0][i] >= 160 && workerBeeLocations[0][i] <= 240) {
				if (flowerVisible[2]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[1] = true;
					flowerVisible[2] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[2] = true;
					currentFlowersOnScreen++;
				}
				plantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (workerBeeLocations[0][i] >= 240 && workerBeeLocations[0][i] <= 320) {
				if (flowerVisible[3]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[2] = true;
					flowerVisible[3] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[3] = true;
					currentFlowersOnScreen++;
				}
				plantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (workerBeeLocations[0][i] >= 320 && workerBeeLocations[0][i] <= 400) {
				if (flowerVisible[4]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[3] = true;
					flowerVisible[4] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[4] = true;
					currentFlowersOnScreen++;
				}
				plantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (workerBeeLocations[0][i] >= 400 && workerBeeLocations[0][i] <= 480) {
				if (flowerVisible[5]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[4] = true;
					flowerVisible[5] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[5] = true;
					currentFlowersOnScreen++;
				}
				plantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (workerBeeLocations[0][i] >= 480 && workerBeeLocations[0][i] <= 560) {
				if (flowerVisible[6]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[5] = true;
					flowerVisible[6] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[6] = true;
					currentFlowersOnScreen++;
				}
				plantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (workerBeeLocations[0][i] >= 560 && workerBeeLocations[0][i] <= 640) {
				if (flowerVisible[7]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[6] = true;
					flowerVisible[7] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[7] = true;
					currentFlowersOnScreen++;
				}
				plantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (workerBeeLocations[0][i] >= 640 && workerBeeLocations[0][i] <= 720) {
				if (flowerVisible[8]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[7] = true;
					flowerVisible[8] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[8] = true;
					currentFlowersOnScreen++;
				}
				plantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (workerBeeLocations[0][i] >= 720 && workerBeeLocations[0][i] <= 800) {
				if (flowerVisible[9]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[8] = true;
					flowerVisible[9] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[9] = true;
					currentFlowersOnScreen++;
				}
				plantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (workerBeeLocations[0][i] >= 800 && workerBeeLocations[0][i] <= 880) {
				if (flowerVisible[10]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[9] = true;
					flowerVisible[10] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[10] = true;
					currentFlowersOnScreen++;
				}
				plantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			
		}
	}
}
void playerOnNewPlace(float & player_x , float & player_y , float flowerLocation[][11] , bool flowerVisible[]) {
	bool collide = false;
	for (int i = 0; i < 10; i++) { 
		if (flowerVisible[i] ) { 
			float start = flowerLocation[0][i];
			float end = flowerLocation[0][i + 1];
			if (player_x > start && player_x < end+70) { 
				collide = true;
			}
		}
	}
	if (!collide) return;

	for (int i = 0; i < 10; i++) { 
		if (!flowerVisible[i]) { 
			float gapStart = flowerLocation[0][i];
			float gapEnd = flowerLocation[0][i + 1];
			player_x = (gapStart + gapEnd) / 2; 
			return;
		}
	}
	
}
void drawFastBee(RenderWindow& window, float fastBeeLocations[][18], Sprite fastBeeSprite[18], int& totalBees, bool fastBeeHoneyCombDestroyed[]) {
	for (int i = 0; i < totalBees; i++) {
		fastBeeSprite[i].setPosition(fastBeeLocations[0][i], fastBeeLocations[1][i]);
		if (!fastBeeHoneyCombDestroyed[i])
			window.draw(fastBeeSprite[i]);
	}
}
void moveFastBees(bool directionsFastBees[3][18], float fastBeeLocations[][18], int& totalBees, int tierFastBees[], bool isFastBeeHoneyComb[], bool fastBeeHoneyCombDestroyed[], bool fastBeePlantedFlower[], Sprite fastBeeSprite[18] ,bool fastBeeLeftTheGame[]) {

	for (int i = 0; i < totalBees; i++) {
		
		if (isFastBeeHoneyComb[i]) {
			continue;
		}

		if (fastBeePlantedFlower[i] || fastBeeLocations[1][i] >= 550) {
			if (directionsFastBees[0][i]) {
				fastBeeLocations[0][i] -= 0.1;
				if (fastBeeLocations[0][i] <= 0) {
					fastBeeLeftTheGame[i] = true;
				}
				continue;
			}
			else if (directionsFastBees[1][i]) {
				fastBeeLocations[0][i] += 0.1;
				if (fastBeeLocations[0][i] >=900) {
					fastBeeLeftTheGame[i] = true;
				}
				continue;
			}
		}

		if (tierFastBees[i] > 0) {
			fastBeeLocations[1][i] += 0.06;
			
			tierFastBees[i]--;

			if (tierFastBees[i] == 0) {
				directionsFastBees[0][i] = ((rand() % 100) % 2);    // 
				directionsFastBees[1][i] = !directionsFastBees[0][i];
			}
			fastBeeSprite[i].setPosition(fastBeeLocations[0][i], fastBeeLocations[1][i]);
		}

		if (tierFastBees[i] == 0) {
			if (directionsFastBees[0][i]) {
				fastBeeLocations[0][i] -= 0.1;
				if (fastBeeLocations[0][i] <= 0) {
					tierFastBees[i] = 500;
					directionsFastBees[0][i] = false;
				}


				fastBeeSprite[i].setPosition(fastBeeLocations[0][i], fastBeeLocations[1][i]);
			}
			else if (directionsFastBees[1][i]) {
				fastBeeLocations[0][i] += 0.1;
				if (fastBeeLocations[0][i] >= 900) {
					tierFastBees[i] = 500;
					directionsFastBees[1][i] = false;
				}
				fastBeeSprite[i].setPosition(fastBeeLocations[0][i], fastBeeLocations[1][i]);
			}
			else
				cout << "Fast No direction Specified\n";
			
		}
	}

}
void checkFastBeeCollisionWithBullet(float fastBeeLocations[][18], int& totalBees, bool isFastBeeHoneyComb[], float& bullet_x, float& bullet_y, Sprite fastBeeSprite[], Texture fastBeeTexture[], bool fastBeeHoneyCombDestroyed[], bool& collisionStopFlag, bool fastBeePlantedFlower[] , long long  & scoreGameplay) {
	if (collisionStopFlag) return;
	for (int i = 0; i < totalBees; i++) {
		if (fastBeePlantedFlower[i]) continue;
		if (fastBeeLocations[0][i] + 30 > bullet_x && bullet_x > fastBeeLocations[0][i] - 30) {
			if (fastBeeLocations[1][i] + 15 > bullet_y && bullet_y > fastBeeLocations[1][i] - 15) {
				if (isFastBeeHoneyComb[i] == false) {
					isFastBeeHoneyComb[i] = true;
					fastBeeTexture[i].loadFromFile("Textures/honeycomb_red.png");
					fastBeeSprite[i].setTexture(fastBeeTexture[i]);
					fastBeeSprite[i].setTextureRect(IntRect(0, 0, fastBeeTexture[i].getSize().x, fastBeeTexture[i].getSize().y));
					collisionStopFlag = true;
					scoreGameplay += 1000;
					return;
				}
				else {
					fastBeeHoneyCombDestroyed[i] = true;
				}
			}
		}
	}
}
void fastBeePlantFlowers(float fastBeeLocations[][18], int& totalBees, bool isFastBeeHoneyComb[], int currentFlowersOnScreen, bool flowerVisible[], bool fastBeePlantedFlower[], float& player_x, float& player_y, float flowerLocation[][11]) {
	for (int i = 0; i < totalBees; i++) {
		if (fastBeePlantedFlower[i]) continue;
		if (fastBeeLocations[1][i] >= 540 && !isFastBeeHoneyComb[i]) {
			if (fastBeeLocations[0][i] >= 0 && fastBeeLocations[0][i] <= 80) {
				if (flowerVisible[0]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[0] = true;
					flowerVisible[1] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[0] = true;
					currentFlowersOnScreen++;
				}
				fastBeePlantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (fastBeeLocations[0][i] >= 80 && fastBeeLocations[0][i] <= 160) {
				if (flowerVisible[1]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[0] = true;
					flowerVisible[1] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[1] = true;
					currentFlowersOnScreen++;
				}
				fastBeePlantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (fastBeeLocations[0][i] >= 160 && fastBeeLocations[0][i] <= 240) {
				if (flowerVisible[2]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[1] = true;
					flowerVisible[2] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[2] = true;
					currentFlowersOnScreen++;
				}
				fastBeePlantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (fastBeeLocations[0][i] >= 240 && fastBeeLocations[0][i] <= 320) {
				if (flowerVisible[3]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[2] = true;
					flowerVisible[3] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[3] = true;
					currentFlowersOnScreen++;
				}
				fastBeePlantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (fastBeeLocations[0][i] >= 320 && fastBeeLocations[0][i] <= 400) {
				if (flowerVisible[4]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[3] = true;
					flowerVisible[4] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[4] = true;
					currentFlowersOnScreen++;
				}
				fastBeePlantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (fastBeeLocations[0][i] >= 400 && fastBeeLocations[0][i] <= 480) {
				if (flowerVisible[5]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[4] = true;
					flowerVisible[5] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[5] = true;
					currentFlowersOnScreen++;
				}
				fastBeePlantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (fastBeeLocations[0][i] >= 480 && fastBeeLocations[0][i] <= 560) {
				if (flowerVisible[6]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[5] = true;
					flowerVisible[6] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[6] = true;
					currentFlowersOnScreen++;
				}
				fastBeePlantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (fastBeeLocations[0][i] >= 560 && fastBeeLocations[0][i] <= 640) {
				if(flowerVisible[7]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[6] = true;
					flowerVisible[7] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[7] = true;
					currentFlowersOnScreen++;
				}
				fastBeePlantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (fastBeeLocations[0][i] >= 640 && fastBeeLocations[0][i] <= 720) {
				if (flowerVisible[8]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[7] = true;
					flowerVisible[8] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[8] = true;
					currentFlowersOnScreen++;
				}
				fastBeePlantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (fastBeeLocations[0][i] >= 720 && fastBeeLocations[0][i] <= 800) {
				if (flowerVisible[9]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[8] = true;
					flowerVisible[9] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[9] = true;
					currentFlowersOnScreen++;
				}
				fastBeePlantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}
			else if (fastBeeLocations[0][i] >= 800 && fastBeeLocations[0][i] <= 880) {
				if (flowerVisible[10]) continue;
				if (currentFlowersOnScreen == 0) {
					flowerVisible[9] = true;
					flowerVisible[10] = true;
					currentFlowersOnScreen += 2;
				}
				else {
					flowerVisible[10] = true;
					currentFlowersOnScreen++;
				}
				fastBeePlantedFlower[i] = true;
				playerOnNewPlace(player_x, player_y, flowerLocation, flowerVisible);
			}

		}
	}
}
void spawnBird(Clock &birdClock , bool &birdVisible) {
	if (birdClock.getElapsedTime().asSeconds() >= 5.0f) {
		birdVisible = true;
	}
}
void selectHoneyComb(float fastBeeLocations[][18], bool isFastBeeHoneyComb[], float workerBeeLocations[][32], bool isHoneyComb[], int totalWorkerBees, int totalFastBees, float &next_x , float &next_y) {
	
	int randomNumber = 0;
	if (totalFastBees!=0) {
		int randomNumber = ((rand() % 100) % 2);
	}

	if (randomNumber == 0) { //worker bee
		int randomNumber = rand() % totalWorkerBees;
		int maxit = 10;
		while (!isHoneyComb[randomNumber]) {
			randomNumber = rand() % totalWorkerBees;
			
			if (maxit == 0) {
				next_x = 1 + rand() % 960;
				next_y = 1 + rand() & 640;
				break;
			}
			maxit--;
		}
		next_x = workerBeeLocations[0][randomNumber];
		next_y = workerBeeLocations[1][randomNumber];
	}

	else {  // fast bee
		int randomNumber = rand() % totalFastBees;
		int maxit = 10;
		while (!isFastBeeHoneyComb[randomNumber]) {
			randomNumber = rand() % totalFastBees;
			if (maxit == 0) {
				next_x = 1 + rand() % 960;
				next_y = 1 + rand() & 640;
				break;
			}
			maxit--;
		}
		next_x = fastBeeLocations[0][randomNumber];
		next_y = fastBeeLocations[1][randomNumber];
	}
}
bool moveBird(float& bird_x, float& bird_y, float next_x, float next_y) {
	float dx = next_x - bird_x;
	float dy = next_y - bird_y;
	float distance = std::sqrt(dx * dx + dy * dy);
	
	if (distance > 0.05) { 
		bird_x += 0.05 * (dx / distance);
		bird_y += 0.05 * (dy / distance);
	}
	else { 
		bird_x = next_x;
		bird_y = next_y;
		return true;
	}
	return false;
}
void drawBird(RenderWindow& window, float& bird_x, float& bird_y, Sprite& birdSprite , bool birdVisible) {
	if (birdVisible){
		birdSprite.setPosition(bird_x, bird_y);
		window.draw(birdSprite);
	}
}
void checkBulletandBirdCollision(float& bullet_x, float& bullet_y , float& bird_x, float& bird_y , float & bird_xNext , float & bird_yNext, int & countBulletHit , bool & birdCollisionStopFlag) {
	
	if (birdCollisionStopFlag) return;
	
	if ((bird_x + 30 > bullet_x && bullet_x > bird_x - 30)) {
		if (bird_y + 15 > bullet_y && bullet_y > bird_y - 15) {
			countBulletHit++;
			birdCollisionStopFlag = true;
		}
	}
	if (countBulletHit >= 3) {
		bird_xNext = 960;
		bird_yNext = 440;
	}
}
void calculateBeeHiveScore(long long & scoreGameplay , float workerBeeLocations[2][32] , bool isBeeHive[]  , int & totalBees, bool honeyCombDestroyed[] ) {

	for (int i = 0; i < totalBees; i++) {
		if (!isBeeHive[i] || honeyCombDestroyed[i]) {
			continue;
		}

		if (workerBeeLocations[1][i] < 300) {
			scoreGameplay += 2000;
		}
		else if (workerBeeLocations[1][i] < 400) {
			scoreGameplay += 1600;
		}
		else {
			scoreGameplay += 1000;
		}
	}

}
void calculateHummingBordScore(float & bird_x , float & bird_y , float workerBeeLocations[2][32] ,bool isHoneyComb[], bool isFastBeeHoneyComb[] , float fastBeeLocations[][18] , int totalBees , int totalFastBees , long long& scoreGameplay) {

	for (int i = 0; i < totalBees; i++) {
		if (isHoneyComb[i]) {
			if (bird_x == workerBeeLocations[0][i] && bird_y == workerBeeLocations[1][i]) {
				if (workerBeeLocations[1][i] < 300) {
					scoreGameplay += 1000;
				}
				else if (workerBeeLocations[1][i] < 400) {
					scoreGameplay += 800;
				}
				else {
					scoreGameplay += 500;
				}
			}
		}
	}
	for (int i = 0; i < totalFastBees; i++) {
		if (isFastBeeHoneyComb[i]) {
			if (bird_x == fastBeeLocations[0][i] && bird_y == fastBeeLocations[1][i]) {
				if (fastBeeLocations[1][i] < 300) {
					scoreGameplay += 2000;
				}
				else if (fastBeeLocations[1][i] < 400) {
					scoreGameplay += 1800;
				}
				else {
					scoreGameplay += 1500;
				}
			}
		}
	}
}
void showHighScores() {
	RenderWindow window(VideoMode(960, 540), "Menu");
	Font font;
	font.loadFromFile("fonts/Grind_Demolished.ttf");
	string names[5];
	long long scores[5] = { 0 };
	ifstream file("highscores.txt");
	if (file.is_open()) {
		for (int i = 0; i < 5; ++i) {
			if (!(file >> names[i] >> scores[i])) {
				break;
			}
		}
		file.close();
	}
	Text scoreTexts[5];
	for (int i = 0; i < 5 && scores[i] != 0; ++i) {
		
		scoreTexts[i].setFont(font);
		scoreTexts[i].setString(to_string(i+1) + ". " + names[i] + " - " + to_string(scores[i]));
		scoreTexts[i].setCharacterSize(30);
		scoreTexts[i].setFillColor(sf::Color::White);
		scoreTexts[i].setPosition(100.f, 100.f + i * 50.f); 
	}
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				return; 
			}
		}
		window.clear();
		for (int i = 0; i < 5 && scores[i] != 0; ++i) {
			window.draw(scoreTexts[i]);
		}
		window.display();
	}
}
void addHighScore(string newName, long long newScore) {
	string names[5 + 1];
	long long scores[5 + 1] = { 0 };

	ifstream file("highscores.txt");
	int count = 0;
	if (file.is_open()) {
		while (count < 5 && file >> names[count] >> scores[count]) {
			++count;
		}
		file.close();
	}
	names[count] = newName;
	scores[count] = newScore;
	++count;

	for (int i = 0; i < count - 1; ++i) {
		for (int j = i + 1; j < count; ++j) {
			if (scores[i] < scores[j]) {
				swap(scores[i], scores[j]);
				swap(names[i], names[j]);
			}
		}
	}
	ofstream outFile("highscores.txt");
	if (outFile.is_open()) {
		for (int i = 0; i < 5 && scores[i] != 0; ++i) {
			outFile << names[i] << " " << scores[i] << "\n";
		}
		outFile.close();
	}
}
void checkAllFlowersPlanted(bool flowerVisible[] , int & sprayLeft , int & decreaseLevelVariable , int & totalSprayFired) {

	for (int i = 0; i < 11; i++) {
		if (flowerVisible[i] == false) {
			return;
		}
	}
	sprayLeft--;
	decreaseLevelVariable=0;
	totalSprayFired = 0;
}
bool incrementLevel(bool isHoneyComb[], int & totalBees , bool isFastBeeHoneyComb[] , bool leftTheGame[] , int totalFastBees , bool fastBeeLeftTheGame[]) {
	for (int i = 0; i < totalBees; i++) {
		if (!(isHoneyComb[i] || leftTheGame[i])) {
			return false;
		}
	}

	for (int i = 0; i < totalFastBees; i++) {
		if (!(isFastBeeHoneyComb[i] || fastBeeLeftTheGame[i])) {
			return false;
		}
	}

	return true;
}

