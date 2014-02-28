//SFML includes.
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//std includes.
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <sstream>
#include <vector>


//FONT - BIG.
//http://patorjk.com/software/taag/


//  _____        _          _                         
// |  __ \      | |        | |                        
// | |  | | __ _| |_ __ _  | |_ _   _ _ __   ___  ___ 
// | |  | |/ _` | __/ _` | | __| | | | '_ \ / _ \/ __|
// | |__| | (_| | || (_| | | |_| |_| | |_) |  __/\__ \
// |_____/ \__,_|\__\__,_|  \__|\__, | .__/ \___||___/
//                               __/ | |              
//                              |___/|_|   
//

//Attributes.
struct attributes {

     int							strength;				//Carry weight, melee damage. 
     int							endurance;				//HP, resistances.
     int							agility;				//Speed, ranged damage.
     int							intelligence;			//MP, magic damage.
     int							luck;					//Dodge chance, critical damage chance.

};

//Resistances.
struct resistances {

     int							poison;
     int							paralize;
     int							lightning;
     int							fire;
     int							ice;
     int							earth;

};

//Health bar.
struct healthBar {

	sf::Sprite						mSprite;
	int								mWidth;
	int								mHeight;

};

//Structure used for storing config values (your C.O.).
struct config {

	float							invincibilityTime;		
	int								playerStartingX;					
	int								playerStartingY;			
	int								mapHeight;				
	int								mapWidth;				
	int								tileSize;						
	int								screenWidth;					
	int								screenHeight;
	int								gameSpeed;
	float							offsetX;				//Map scrolling
	float							offsetY;				//offset.
	std::string						levelMapName;

};


//PROTOTYPES.
class World;
class Player {
public:

									Player(sf::Texture&, sf::Texture&, int, int, sf::Font&);
	void							update(float, std::vector<std::vector<int>>, struct config*, World&);
	void							getMessage(int);
	void							takeDamage(float);
	void							heal(float);
	void							showStats(std::ostringstream*, std::ostringstream*);

	sf::FloatRect					getRect();
	sf::Sprite						getSprite();
	sf::Sprite						getHpSprite();
	sf::Text						getTextName();
	float							getSpeed();
	sf::Vector2f					getMovement();

	void							setSpeed(float);
	void							setMovement(sf::Vector2f);

private:

	//InputComponent					mInput;

	sf::Vector2f					mMovement;
	float							mSpeed;

	sf::FloatRect					mRect;
	sf::Sprite						mSprite;
	sf::Sprite						mHpSprite;
	sf::String						mName;
	sf::Text						mTextName;

	float							mCurrentFrame;
	float							mAnimationSpeed;
	static const int				mFrameCount = 10;

	bool							mIsAlive;
	float							mHP;
	float							mMaxHp;
	int								mMP;

	std::vector<int>				mMessages;	
	
};

//Work in progress (stupid AI).
//AI is to be represented as a set of private methods.
class Enemy {
public:

									Enemy(sf::Texture&, int, int, sf::Font&);

	void							update(float, std::vector<std::vector<int>>, struct config*, World&);
	void							collision(std::vector<std::vector<int>>, struct config*);
	void							dealDamage(Player&);
	void							detectTargets(World&);
	void							getMessage(int);

	sf::FloatRect					getRect();
	sf::Sprite						getSprite();
	sf::Text						getTextName();
	bool							isReadyToAttack();

private:

	sf::Vector2f					mMovement;
	int								mDirection;
	float							mSpeed;

	sf::FloatRect					mRect;
	sf::Sprite						mSprite;

	float							mCurrentFrame;
	float							mAnimationSpeed;
	static const int				mFrameCount = 10;

	bool							mIsAlive;
	int								mHP;

	sf::Clock						mDamageClock;
	sf::Clock						mMovementClock;
	float							mDamage;

	sf::String						mName;
	sf::Text						mTextName;

	std::vector<int>				mMessages;

};

class DropItem {
public:

									DropItem(sf::Texture&, std::string, int, int, int);
	void							update(float);
	void							action(Player&);

	sf::FloatRect					getRect();

	sf::Sprite						getSprite();

	bool							isMarkedForRemoval();

private:

	sf::FloatRect					mRect;
	sf::Sprite						mSprite;
	float							mCurrentFrame;
	int								mEffectValue;
	bool							mIsMarkedForRemoval;

};

//   _____                                             _       
//  / ____|                                           | |      
// | |     ___  _ __ ___  _ __   ___  _ __   ___ _ __ | |_ ___ 
// | |    / _ \| '_ ` _ \| '_ \ / _ \| '_ \ / _ \ '_ \| __/ __|
// | |___| (_) | | | | | | |_) | (_) | | | |  __/ | | | |_\__ \
//  \_____\___/|_| |_| |_| .__/ \___/|_| |_|\___|_| |_|\__|___/
//                       | |                                   
//                       |_|
//


/*
class InputComponent {
public:

	void update(Player& player) {

		sf::Vector2f movement = player.getMovement();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	movement.y -= player.getSpeed();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	movement.y += player.getSpeed();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	movement.x -= player.getSpeed();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	movement.x += player.getSpeed();

		player.setMovement(movement);

	}

private:
	

};
*/


//   _____ _                         
//  / ____| |                        
// | |    | | __ _ ___ ___  ___  ___ 
// | |    | |/ _` / __/ __|/ _ \/ __|
// | |____| | (_| \__ \__ \  __/\__ \
//  \_____|_|\__,_|___/___/\___||___/
//


//Use for Enemy / Player / DropItem shared methods.
//template<class T>;

//World.hpp
class World {
public:

									World();
									World(int, int);
	void							resolveCollision(sf::FloatRect& rect, sf::Vector2f movement, int direction, int tileSize);
	void							loadLevelMap(std::string);
	void							deleteLevelMap();

	std::vector<Enemy>&				getEnemies();
	std::vector<DropItem>&			getDrops();

	std::vector<std::vector<int>>	getLevelMap();
	int								getMapHeight();
	int								getMapWidth();

private:

	std::vector<std::vector<int>>	mLevelMap;
	int								mMapHeight;
	int								mMapWidth;

	//Player							mPlayer;
	std::vector<Enemy>				mEnemies;
	std::vector<DropItem>			mDrops;

};

//Default constructor.
World::World() {

	mMapHeight = 0;
	mMapWidth = 0;

}

World::World(int mapHeight, int mapWidth) {

	mMapHeight = mapHeight;
	mMapWidth = mapWidth;

}

//World.cpp
void World::resolveCollision(sf::FloatRect& rect, sf::Vector2f movement, int direction, int tileSize) {

	for(int i = rect.top / tileSize; i < (rect.top + rect.height) / tileSize; ++i)
		for(int j = rect.left / tileSize; j < (rect.left + rect.width) / tileSize; ++j) {

			if(mLevelMap[i][j] == 'B') {
					if((movement.x > 0) && (direction == 0)) rect.left = j * tileSize - rect.width;
					if((movement.x < 0) && (direction == 0)) rect.left = j * tileSize + tileSize;
					if((movement.y > 0) && (direction == 1)) rect.top = i * tileSize - rect.height;
					if((movement.y < 0) && (direction == 1)) rect.top = i * tileSize + tileSize;
			}

		}

}

void World::loadLevelMap(std::string filename) {

	std::ifstream inputFile(filename);

	inputFile >> mMapHeight >> mMapWidth;

	//Resizing the array.
	mLevelMap.resize(mMapHeight);
	for(int i = 0; i < mMapHeight; ++i)
		mLevelMap[i].resize(mMapWidth);

	inputFile.get();
	for(int i = 0; i < mMapHeight; ++i) {
		for(int j = 0; j < mMapWidth; ++j) {
			char temp = inputFile.get();
			mLevelMap[i][j] = int(temp);
		}
		inputFile.get();
	}

	inputFile.close();

}

void World::deleteLevelMap() {
	mLevelMap.clear();
	mEnemies.clear();
	mDrops.clear();
}

std::vector<Enemy>& World::getEnemies() {
	return mEnemies;
}

std::vector<DropItem>& World::getDrops() {
	return mDrops;
}

std::vector<std::vector<int>> World::getLevelMap() {
	return mLevelMap;
}

int World::getMapHeight() {
	return mMapHeight;
}

int World::getMapWidth() {
	return mMapWidth;
}



//Game.hpp
class Game {
public:

									Game();
	void							run();
	void							update(sf::Time);
	void							processEvents();
	void							render();

private:

	sf::RenderWindow				mWindow;
	int								mScreenWidth;					
	int								mScreenHeight;

	float							mInvincibilityTime;
	sf::Clock						mGameClock;
	sf::Clock						mInvincibilityClock;
	sf::Clock						mSpawnClock;
	const static sf::Time			mTimePerFrame;

	std::vector<std::vector<int>>	mLevelMap;
			
	int								mTileSize;						
	int								mGameSpeed;
	float							mOffsetX;				//Map scrolling
	float							mOffsetY;				//offset.

	World							mWorld;

};
/*
void Game::run() {

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while(mWindow.isOpen()) {

		sf::Time elapsedTime = mGameClock.restart();
		timeSinceLastUpdate = elapsedTime;
		while(timeSinceLastUpdate > mTimePerFrame) {
			timeSinceLastUpdate -= mTimePerFrame;

			processEvents();
			update(mTimePerFrame);
		}

	}

}
*/
void Game::processEvents() {

}

void Game::update(sf::Time) {

}

void Game::render() {

}


//Player.cpp
//Player constructor.
Player::Player(sf::Texture& texture, sf::Texture& hpImage, int x, int y, sf::Font& font) {

	mSprite.setTexture(texture);
	mRect = sf::FloatRect(x, y, 120, 110);					//Character x, y, width, height.
		
	mName = "Player 1";
	mTextName.setString(mName);
	mTextName.setFont(font);
	mTextName.setCharacterSize(30);
	mTextName.setStyle(sf::Text::Bold);
	mTextName.setColor(sf::Color::Red);
		
	mHpSprite.setTexture(hpImage);
	mHpSprite.setTextureRect(sf::IntRect(0, 0, 100, 10));

	mSprite.setTextureRect(sf::IntRect(0, 15, 120, 110));
	
	mSpeed = 0.1;
	mMovement.x = 0;
	mMovement.y = 0;

	mCurrentFrame = 0;
	mAnimationSpeed = 0.005;

	mIsAlive = true;
	mHP = 100;
	mMaxHp = 100;
	mMP = 100;
}

//Player update.
void Player::update(float deltaTime, std::vector<std::vector<int>> levelMap, struct config* config, World& world) {

	//Player controls (testing).
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	mMovement.y -= mSpeed;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	mMovement.y += mSpeed;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	mMovement.x -= mSpeed;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	mMovement.x += mSpeed;
	//mInput.update(*this);


	//Movement and resolving colisions (via the World class).
	mRect.left += mMovement.x * deltaTime;
	world.resolveCollision(mRect, mMovement, 0, config->tileSize);
	mRect.top += mMovement.y * deltaTime;
	world.resolveCollision(mRect, mMovement, 1, config->tileSize);

	//Player animation.
	mCurrentFrame += mAnimationSpeed * deltaTime;
	if(mCurrentFrame > mFrameCount) mCurrentFrame -= mFrameCount;

	if(mMovement.x > 0) mSprite.setTextureRect(sf::IntRect(mRect.width * int(mCurrentFrame), 925, mRect.width, mRect.height));
	if(mMovement.x < 0) mSprite.setTextureRect(sf::IntRect(mRect.width * int(mCurrentFrame), 667, mRect.width, mRect.height));
	if(mMovement.y > 0) mSprite.setTextureRect(sf::IntRect(mRect.width * int(mCurrentFrame), 535, mRect.width, mRect.height));
	if(mMovement.y < 0) mSprite.setTextureRect(sf::IntRect(mRect.width * int(mCurrentFrame), 787, mRect.width, mRect.height));

	mSprite.setPosition(mRect.left, mRect.top);

	//HP.
	if(mHP / mMaxHp >= 0.6)
		mHpSprite.setColor(sf::Color::Green);
	else if((mHP / mMaxHp >= 0.35) && (mHP / mMaxHp < 0.6))
		mHpSprite.setColor(sf::Color::Yellow);
	else if(mHP / mMaxHp < 0.35)
		mHpSprite.setColor(sf::Color::Red);

	mHpSprite.setTextureRect(sf::IntRect(100 * (1 - mHP / mMaxHp), 0, 100, 10));
	mHpSprite.setPosition(mRect.left, mRect.top + mRect.height);
	mTextName.setPosition(mRect.left, mRect.top - mTextName.getCharacterSize());						//-

	//Stopping the player.
	mMovement.x = 0;
	mMovement.y = 0;

}

void Player::getMessage(int message) {
	mMessages.push_back(message);
}

//Taking damage.
void Player::takeDamage(float damage) {
	mHP -= damage;
}

void Player::heal(float hp) {
	mHP += hp;
}

//On-screen stats.
//sf::Text should be used to display stats.
void Player::showStats(std::ostringstream* hudHealth, std::ostringstream* hudMana) {
	*hudHealth << mHP;
	*hudMana << mMP;
}

//Getters.
sf::FloatRect Player::getRect() {
	return mRect;
}

sf::Sprite Player::getSprite() {
	return mSprite;
}

sf::Sprite Player::getHpSprite() {
	return mHpSprite;
}

sf::Text Player::getTextName() {
	return mTextName;
}

float Player::getSpeed() {
	return mSpeed;
}

sf::Vector2f Player::getMovement() {
	return mMovement;
}

//Setters.
void Player::setSpeed(float speed) {
	mSpeed = speed;
}

void Player::setMovement(sf::Vector2f movement) {
	mMovement = movement;
}


//Enemy.cpp
//Enemy constructor.
Enemy::Enemy(sf::Texture& texture, int x, int y, sf::Font& font) {
	mSprite.setTexture(texture);
	mRect = sf::FloatRect(x, y, 120, 110);					//Character x, y, width, height.

	mName = "Enemy";
	mTextName.setString(mName);
	mTextName.setFont(font);
	mTextName.setCharacterSize(30);
	mTextName.setStyle(sf::Text::Bold);
	mTextName.setColor(sf::Color::Magenta);

	mSprite.setTextureRect(sf::IntRect(0, 15, 120, 110));

	mDirection = rand() % 4;
	mSpeed = 0.05;

	mCurrentFrame = 0;
	mAnimationSpeed = mSpeed * 0.05;

	mIsAlive = true;
	mHP = 100;

	mDamage = 30;
}

//Enemy update.
void Enemy::update(float deltaTime, std::vector<std::vector<int>> levelMap, struct config* config, World& world) {

	if(mMovementClock.getElapsedTime().asSeconds() > 5) {
		mDirection = rand() % 4;
		mMovementClock.restart();
	}

	if(mDirection == 0) {mMovement.x = 0;		mMovement.y = -mSpeed;}
	if(mDirection == 1) {mMovement.x = mSpeed;	mMovement.y = 0;}
	if(mDirection == 2) {mMovement.x = 0;		mMovement.y = mSpeed;}
	if(mDirection == 3) {mMovement.x = -mSpeed;	mMovement.y = 0;}

	mRect.left += mMovement.x * deltaTime;
	collision(levelMap, config);
	//world.resolveCollision(mRect, mMovement, 0, config->tileSize);
	mRect.top += mMovement.y * deltaTime;
	collision(levelMap, config);
	//world.resolveCollision(mRect, mMovement, 1, config->tileSize);

	//Enemy animation.
	mCurrentFrame += mAnimationSpeed * deltaTime;
	if(mCurrentFrame > mFrameCount) mCurrentFrame -= mFrameCount;

	if(mMovement.x > 0) mSprite.setTextureRect(sf::IntRect(mRect.width * int(mCurrentFrame), 925, mRect.width, mRect.height));
	if(mMovement.x < 0) mSprite.setTextureRect(sf::IntRect(mRect.width * int(mCurrentFrame), 667, mRect.width, mRect.height));
	if(mMovement.y > 0) mSprite.setTextureRect(sf::IntRect(mRect.width * int(mCurrentFrame), 535, mRect.width, mRect.height));
	if(mMovement.y < 0) mSprite.setTextureRect(sf::IntRect(mRect.width * int(mCurrentFrame), 787, mRect.width, mRect.height));

	mSprite.setPosition(mRect.left, mRect.top);
	mTextName.setPosition(mRect.left, mRect.top - mTextName.getCharacterSize());

}
	
void Enemy::collision(std::vector<std::vector<int>> levelMap, struct config* config) {
	for(int i = mRect.top / config->tileSize; i < (mRect.top + mRect.height) / config->tileSize; ++i)
		for(int j = mRect.left / config->tileSize; j < (mRect.left + mRect.width) / config->tileSize; ++j) {
				
			if(levelMap[i][j] == 'B') {
				if(mMovement.x > 0) mRect.left = j * config->tileSize - mRect.width;
				if(mMovement.x < 0) mRect.left = j * config->tileSize + config->tileSize;
				if(mMovement.y > 0) mRect.top = i * config->tileSize - mRect.height;
				if(mMovement.y < 0) mRect.top = i * config->tileSize + config->tileSize;
				int temp = rand() % 4;
				if(temp != mDirection) mDirection = temp;
				//direction = rand() % 4;		//???
			}
						
		}
}

void Enemy::dealDamage(Player& player) {
	float damage = rand() % int(mDamage);
	player.takeDamage(damage);
	mDamageClock.restart();
}

void detectTargets(World& world) {
	
}
	
//Inner communication between objects (between the components in the future).
void Enemy::getMessage(int message) {
	mMessages.push_back(message);
}

sf::FloatRect Enemy::getRect() {
	return mRect;
}

sf::Sprite Enemy::getSprite() {
	return mSprite;
}

sf::Text Enemy::getTextName() {
	return mTextName;
}

bool Enemy::isReadyToAttack() {
	if(mDamageClock.getElapsedTime().asSeconds() > mSpeed * 10)
		return true;
	else
		return false;
}

//DropItem.cpp
//Drop item constructor.
DropItem::DropItem(sf::Texture& texture, std::string type, int effect, int x, int y) {
	mSprite.setTexture(texture);
	mRect = sf::FloatRect(x, y, 32, 32);
	mSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	mCurrentFrame = 0;
	mEffectValue = effect;
	mIsMarkedForRemoval = false;
}

//Drop item update.
void DropItem::update(float time) {
	mSprite.setPosition(mRect.left, mRect.top);
}

void DropItem::action(Player& player) {
	player.heal(mEffectValue);
	mIsMarkedForRemoval = true;
}

sf::FloatRect DropItem::getRect() {
	return mRect;
}

sf::Sprite DropItem::getSprite() {
	return mSprite;
}

bool DropItem::isMarkedForRemoval() {
	return mIsMarkedForRemoval;
}



//  ______                _   _                 
// |  ____|              | | (_)                
// | |__ _   _ _ __   ___| |_ _  ___  _ __  ___ 
// |  __| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
// | |  | |_| | | | | (__| |_| | (_) | | | \__ \
// |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/
//                                             

//   _____           _                    __                  _   _                 
//  / ____|         | |                  / _|                | | (_)                
// | (___  _   _ ___| |_ ___ _ __ ___   | |_ _   _ _ __   ___| |_ _  ___  _ __  ___ 
//  \___ \| | | / __| __/ _ \ '_ ` _ \  |  _| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//  ____) | |_| \__ \ ||  __/ | | | | | | | | |_| | | | | (__| |_| | (_) | | | \__ \
// |_____/ \__, |___/\__\___|_| |_| |_| |_|  \__,_|_| |_|\___|\__|_|\___/|_| |_|___/
//          __/ |                                                                   
//         |___/  
//



//  ______             _               __                  _   _                 
// |  ____|           (_)             / _|                | | (_)                
// | |__   _ __   __ _ _ _ __   ___  | |_ _   _ _ __   ___| |_ _  ___  _ __  ___ 
// |  __| | '_ \ / _` | | '_ \ / _ \ |  _| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
// | |____| | | | (_| | | | | |  __/ | | | |_| | | | | (__| |_| | (_) | | | \__ \
// |______|_| |_|\__, |_|_| |_|\___| |_|  \__,_|_| |_|\___|\__|_|\___/|_| |_|___/
//                __/ |                                                          
//               |___
//


//Loads a config file.
void loadConfigFile(struct config* config, std::string filename = "config.txt") {

	std::ifstream inputFile(filename);
	inputFile >> config->screenWidth;
	inputFile >> config->screenHeight;
	inputFile >> config->tileSize;
	inputFile >> config->playerStartingX;
	inputFile >> config->playerStartingY;
	inputFile >> config->invincibilityTime;
	inputFile >> config->gameSpeed;
	inputFile >> config->levelMapName;
	inputFile.close();
	return;

}



//  __  __       _       
// |  \/  |     (_)      
// | \  / | __ _ _ _ __  
// | |\/| |/ _` | | '_ \ 
// | |  | | (_| | | | | |
// |_|  |_|\__,_|_|_| |_|
//                       

int main() {
	
	srand(time(NULL));

	//Loading config file.
	config config;
	loadConfigFile(&config, "config.txt");

	//Game game;
	//game.run();

	//World.
	std::string levelMapName = "./levels/level1.txt";

	World world;
	world.loadLevelMap(levelMapName);

	//Loading level map.
	std::vector<std::vector<int>> levelMap = world.getLevelMap();
	

	//Clocks.
	sf::Clock gameClock;
	sf::Clock invincibilityClock;
	sf::Clock spawnClock;




	//
	//GRAPHICS.
	//
	//
	//
	sf::RectangleShape rectangle(sf::Vector2f(config.tileSize, config.tileSize));	//For tiles (temporary).

	//Creating a font.
	sf::Font font;
	font.loadFromFile("sansation.ttf");

	//HUD Health.
	sf::Text textHealth("", font, 30);
	textHealth.setStyle(sf::Text::Bold);
	textHealth.setColor(sf::Color::Red);
	textHealth.setPosition(10, 10);

	//HUD Mana.
	sf::Text textMana("", font, 30);
	textMana.setStyle(sf::Text::Bold);
	textMana.setColor(sf::Color::Blue);
	textMana.setPosition(10, 45);

	//Enemy sound.
	sf::SoundBuffer emenyHitSoundBuffer;
	emenyHitSoundBuffer.loadFromFile("sound1.ogg");
	sf::Sound emenyHitSound(emenyHitSoundBuffer);

	//Loading and setting level tileset.
	//sf::Texture tileSet;
	//if(!tileSet.loadFromFile("./textures/testTileSet.png"))
	//	return EXIT_FAILURE;
	//sf::Sprite tile(tileSet);

	//HP bar.
	sf::Texture hpBar;
	if(!hpBar.loadFromFile("./textures/HPBar.png"))
		return EXIT_FAILURE;



	//
	//UNITS
	//
	//
	//Creating player.
	sf::Texture playerTexture;
	if(!playerTexture.loadFromFile("./textures/playerSpriteList.png"))
		return EXIT_FAILURE;
	Player player(playerTexture, hpBar, config.playerStartingX, config.playerStartingY, font);

	//Enemy texture.
	sf::Texture enemyTexture;
	if(!enemyTexture.loadFromFile("./textures/enemySpriteList.png"))
		return EXIT_FAILURE;

	//Creating test health potion.
	sf::Texture healthPotionTexture;
	if(!healthPotionTexture.loadFromFile("./textures/healthPotion.png")) {
		std::cin.ignore();
		std::cin.get();
		return EXIT_FAILURE;
	}


	//Object arrays.
	//std::vector<Enemy> enemies;
	std::vector<DropItem> drops = world.getDrops();
	std::vector<Enemy> enemies = world.getEnemies();
	//enemies.push_back(*(new Enemy(enemyTexture, 400, 360, font)));


	//Creating a window.
	sf::RenderWindow mWindow(sf::VideoMode(config.screenWidth, config.screenHeight), "Badass Tales of BADASSLAND!!!!111");
	sf::View mView;
	mView.reset(sf::FloatRect(0, 0, config.screenWidth, config.screenHeight));
	mView.setViewport(sf::FloatRect(0, 0, 1, 1));
	sf::Vector2f mViewPosition;

	//Game cycle.
	while(mWindow.isOpen()) {

		float time = gameClock.getElapsedTime().asMicroseconds();
		gameClock.restart();
		time /= config.gameSpeed;

		//Processing events.
		sf::Event event;
		while(mWindow.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				mWindow.close();
		}

		//Updating all objects.
		player.update(time, levelMap, &config, world);
		for(int i = 0; i < enemies.size(); ++i)	enemies[i].update(time, levelMap, &config, world);
		for(int i = 0; i < drops.size(); ++i)	drops[i].update(time);


		//Resolving collisions. Should move to World class methods.
		for(int i = 0; i < enemies.size(); ++i)
			//if((player.getRect().intersects(enemies[i].getRect())) && (invincibilityClock.getElapsedTime().asSeconds() > config.invincibilityTime)) {
			if((player.getRect().intersects(enemies[i].getRect())) && (enemies[i].isReadyToAttack())) {
				enemies[i].dealDamage(player);
				//invincibilityClock.restart();
			}

		for(int i = 0; i < drops.size(); ++i)
			if((player.getRect().intersects(drops[i].getRect())) && (~drops[i].isMarkedForRemoval()))
				drops[i].action(player);
	
		//Spawning elves.
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::G)) && (spawnClock.getElapsedTime().asSeconds() > 0.5)) {
			enemies.push_back(*(new Enemy(enemyTexture, 400, 360, font)));
			spawnClock.restart();
		}

		//Spawning health potions.
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::H)) && (spawnClock.getElapsedTime().asSeconds() > 0.5)) {
			drops.push_back(*(new DropItem(healthPotionTexture, "healthItem", 40, rand() % 400 + 120, rand() % 600 + 120)));
			spawnClock.restart();
		}


		//HUD display.
		std::ostringstream hudHealth;
		std::ostringstream hudMana;

		player.showStats(&hudHealth, &hudMana);

		textMana.setString(hudMana.str());
		textHealth.setString(hudHealth.str());


		//View.
		mViewPosition.x = player.getRect().left + config.tileSize / 2 - config.screenWidth / 2;
		mViewPosition.y = player.getRect().top + config.tileSize / 2 - config.screenHeight / 2;
		if(mViewPosition.x < 0)	mViewPosition.x = 0;
		if(mViewPosition.y < 0)	mViewPosition.y = 0;
		mView.reset(sf::FloatRect(mViewPosition.x, mViewPosition.y, config.screenWidth, config.screenHeight));
		mWindow.setView(mView);

		textHealth.setPosition(mViewPosition.x, mViewPosition.y);
		textMana.setPosition(mViewPosition.x, mViewPosition.y + 35);

		//Clearing the screen.
		mWindow.clear(sf::Color::White);

		//Rendering level map tiles.
		for(int i = 0; i < world.getMapHeight(); ++i) {
			for(int j = 0; j < world.getMapWidth(); ++j) {
				
				switch(levelMap[i][j]) {
					case 'B': rectangle.setFillColor(sf::Color::Black); break;
					case '0': rectangle.setFillColor(sf::Color::Green); break;
					default: continue;
				}

				rectangle.setPosition(config.tileSize * j, config.tileSize * i);
				mWindow.draw(rectangle);
				//tile.setPosition(tileSize * j - offsetX, tileSize * i - offsetY);
				//mWindow.draw(tile);

			}
		}


		//Rendering all the objects.
		for(int i = 0; i < enemies.size(); ++i) {
			mWindow.draw(enemies[i].getSprite());
			mWindow.draw(enemies[i].getTextName());
		}

		for(int i = 0; i < drops.size(); ++i)
			mWindow.draw(drops[i].getSprite());

		mWindow.draw(player.getSprite());
		mWindow.draw(player.getHpSprite());
		mWindow.draw(player.getTextName());

		mWindow.draw(textHealth);
		mWindow.draw(textMana);
		mWindow.display();

		//Deleting objects marked for removal.
		for(int i = 0; i < drops.size(); ++i)
			if(drops[i].isMarkedForRemoval()) {
				drops.erase(drops.begin() + i );
				--i;
			}

	}

	return 0;

}
