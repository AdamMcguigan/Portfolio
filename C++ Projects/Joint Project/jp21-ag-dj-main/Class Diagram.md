```
@startuml
class Game{
Game();
void run();
}
class Ship{
Ship(sf::Texture const& texture, std::vector<sf::Sprite>& t_wallSprites);
sf::Texture shipTexture;
sf::Sprite m_shipBase;
void update(double dt, sf::Vector2f& pos);
void render(sf::RenderWindow& window);
void deflect();
void handleKeyInput();
sf::Vector2f getShipPosition() const;
float getTurretRotation();
sf::Vector2f getTurretPosition();
sf::Sprite getBaseSprite() const;
}
class Projectile{
Projectile();
void initializeBullet();
void update(double dt, sf::Vector2f& playerPos, float t_rot); 
void render(sf::RenderWindow& window); 
void collisionWithWalls(std::vector<sf::Sprite>& t_wallSprites);

int m_shotsFired = 0; 
sf::Vector2f m_offScreenPosition{ 20000,20000 }; 

sf::Sprite m_bulletSprite;
}

class Enemy
{
Enemy();
void update(double dt, sf::Vector2f& pos);
void render(sf::RenderWindow& window);
void collisionWithWalls(std::vector<sf::Sprite>& t_wallSprites);

float m_timeForEnemy = 0.0f; 
bool b_enemyReady = false;
static constexpr float  TIMER_DUR_THOR = 5.0f; 

sf::Vector2f offScreenPos{ 9999,9999 }; 
sf::Vector2f m_currentScale{ 0.05f,0.05f };

sf::Sprite m_targetSprite;
sf::Clock m_clockToSpawnTarget;
thor::Timer m_enemyTimer;
}

class EnemyShipAI
{
EnemyShipAI(std::vector<sf::Sprite> & wallSprites);
void update(Ship const & playerShip, double dt);
void render(sf::RenderWindow & window);
void init(sf::Vector2f position);
bool collidesWithPlayer(Ship const& playerShip) const;
sf::Sprite m_AiShipBase;
}

class MenuButton
{
sf::Sprite buttonSprite;
sf::RectangleShape shape;
ButtonState state = ButtonState::READY;
void Init(sf::Vector2f pos, sf::Font& font);
void Update(sf::RenderWindow& window);
sf::Text text;
bool pressed = false;
}

class Collectible
{
enum class RubyAnimationState { ruby };
sf::Sprite& spriteSheetRuby;
Collectible(sf::Sprite& spheetCoin);
void InitAnimationData();
void startAnimaton(RubyAnimationState t_animationStateRuby);
void drawRuby(sf::RenderWindow& win);
}
class HUD
{
HUD(sf::Font& hudFont);
void update(GameState const& gameState);
void render(sf::RenderWindow& window);
}
class AnimationSheet
{
Animation curAnimation;
void Init(int _pixelWidth, int _pixelHeight, int _numRows, int _numCols);
void StartAnimation(Animation curAnimation);
void nextFrame();
sf::IntRect GetFrame();
}
class CollisionDetector
{
bool static collisions(const sf::Sprite& object1, const sf::Sprite& object2);
}
class Grid
{
void drawGrid(sf::RenderWindow& window, int rows, int cols);
}
class ScreenSize
{
static const int s_width{ 1440 };
static const int s_height{ 900 };
}

class Cell
{
Cell(sf::Vector2f t_position);
Cell();
void draw(sf::RenderWindow& t_window);
void changeEndColor();
void update(double dt);
void setRow(int t_row);
void setCol(int t_col);
void setVisited(bool t_changeValue);
void setTraversable(bool t_changeValue);
void setParent(int t_parent);
bool getTraversable();
bool getVisited();
int getRow();
int getCol();
int getParent();

int returnParentCell();
int returnID();
bool checkMark();
void setParentCell(int t_cellID);
void mark(bool t_marked);

sf::RectangleShape getRect();
}

Game <-- Ship
Game <-- Projectile
Ship -- Projectile
Game <-- Enemy
Game <-- EnemyShipAI
Ship  -- EnemyShipAI
Game <-- MenuButton
Game <-- Collectible
Collectible <-- AnimationSheet
Game <-- CollisionDetector
EnemyShipAI <-- CollisionDetector
Ship <-- CollisionDetector
Projectile <-- CollisionDetector
Enemy <-- CollisionDetector
Game <-- HUD
Game <-- Grid
Grid <-- Cell
@enduml
```
![alt text](https://github.com/ITCGamesProg2/jp21-ag-dj/blob/main/Class-Diagram.png "Class diagram")
