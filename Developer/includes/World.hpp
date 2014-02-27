//World.hpp
class World {
public:

								World();
	void						resolveCollision(sf::FloatRect& rect, sf::Vector2f movement, int direction, int tileSize);
	void						loadLevelMap(std::string filename);

	int							getMapHeight();
	int							getMapWidth();

private:

	char**						mLevelMap;
	int							mMapHeight;
	int							mMapWidth;

};