#include "PacMan.h"

MapObjects PacMan::Collides(MapObject& o) const
{
    MapObjects object = MapObjects::Nothing;
    if (o.object == MapObjects::Dot || o.object == MapObjects::PowerBullet)
    {
        if (sprite.getGlobalBounds().intersects(o.sprite.getGlobalBounds()))
        {
            Map::DotsNumber--;
            object = o.object;
            o.object = MapObjects::Nothing;
            o.sprite.setTexture(*Resources::mapTexture);
            o.sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
        }
    }
    return object;
}

bool PacMan::CheckBoundary(sf::Vector2f vec) const
{
    int c = (vec.x) / (MapObjectScale * 15);
    int r = (vec.y) / (MapObjectScale * 15);
    float temp = 15 * MapObjectScale;
    switch (setDirection)
    {
    case Direction::Up:
    case Direction::Down:
        temp = vec.x - temp * c - CharacterScale * 15 / 2;
        break;
    case Direction::Left:
    case Direction::Right:
        temp = vec.y - temp * r - CharacterScale * 15 / 2;
        break;
    default:
        temp = -1.0f;
    }
    if (0 <= temp && temp <= 2 * Padding)
        return true;
    return false;
}

MapObjects PacMan::Valid(Direction dir, sf::Vector2f& vec)
{
    int c = (vec.x) / (MapObjectScale * 15);
    int r = (vec.y) / (MapObjectScale * 15);
    if (c >= 27 && dir == Direction::Right)
    {
        if (c > 27)
            vec.x = -CharacterScale * 15 / 2;
        return MapObjects::Nothing;
    }
    if (c <= 0 && dir == Direction::Left)
    {
        if (c < 0)
            vec.x = 28 * MapObjectScale * 15;
        return MapObjects::Nothing;
    }
    MapObjects object = MapObjects::Nothing;
    switch (dir)
    {
    case Direction::Up:
        if (Map::Objects[r - 1][c].object == MapObjects::Wall
            && Map::Objects[r - 1][c].sprite.getPosition().y + 15 * (MapObjectScale + CharacterScale / 2) + Padding
            >= sprite.getPosition().y)
        {
            vec.y = Map::Objects[r - 1][c].sprite.getPosition().y + 15 * (MapObjectScale + CharacterScale / 2) + Padding;
            object = MapObjects::Wall;
        }
        break;
    case Direction::Left:
        if (Map::Objects[r][c - 1].object == MapObjects::Wall
            && Map::Objects[r][c - 1].sprite.getPosition().x + 15 * (MapObjectScale + CharacterScale / 2) + Padding
            >= sprite.getPosition().x)
        {
            vec.x = Map::Objects[r][c - 1].sprite.getPosition().x + 15 * (MapObjectScale + CharacterScale / 2) + Padding;
            object = MapObjects::Wall;
        }
        break;
    case Direction::Right:
        if (Map::Objects[r][c + 1].object == MapObjects::Wall
            && Map::Objects[r][c + 1].sprite.getPosition().x - 15 * CharacterScale / 2 - Padding <= sprite.getPosition().x)
        {
            vec.x = Map::Objects[r][c + 1].sprite.getPosition().x - 15 * CharacterScale / 2 - Padding;
            object = MapObjects::Wall;
        }
        break;
    case Direction::Down:
        if ((Map::Objects[r + 1][c].object == MapObjects::Wall || Map::Objects[r + 1][c].object == MapObjects::Gate)
            && Map::Objects[r + 1][c].sprite.getPosition().y - 15 * CharacterScale / 2 - Padding <= sprite.getPosition().y)
        {
            vec.y = Map::Objects[r + 1][c].sprite.getPosition().y - 15 * CharacterScale / 2 - Padding;
            object = Map::Objects[r + 1][c].object;
        }
        break;
    }
    return object;
}

PacMan::PacMan()
    : currentImageX(3), direction(Direction::Stop), setDirection(Direction::Stop), face(Direction::Right)
{
    sprite.setTexture(Resources::pacmanTexture);
    sprite.setTextureRect(sf::IntRect(currentImageX * 15, 0, 15, 15));
    sprite.setSize(sf::Vector2f(CharacterScale * 15, CharacterScale * 15));
    sprite.setOrigin(sprite.getSize().x / 2.0f, sprite.getSize().y / 2.0f);
}

MapObjects PacMan::Move(float dt)
{
    const float* vector = DirectionOffset[static_cast<int>(direction)];
    sprite.move(vector[0] * dt, vector[1] * dt);
    sf::Vector2f vec = sprite.getPosition();
    MapObjects object = Valid(setDirection, vec);
    int c = (vec.x) / (MapObjectScale * 15);
    int r = (vec.y) / (MapObjectScale * 15);
    if (object == MapObjects::Nothing && CheckBoundary(sprite.getPosition()))
    {
        if ((setDirection == Direction::Up || setDirection == Direction::Down)
            && (direction == Direction::Left || direction == Direction::Right))
        {
            vec.x = Map::Objects[r][c].sprite.getPosition().x + 15 * CharacterScale / 2 + Padding;
        }
        if ((setDirection == Direction::Left || setDirection == Direction::Right)
            && (direction == Direction::Up || direction == Direction::Down))
        {
            vec.y = Map::Objects[r][c].sprite.getPosition().y + 15 * CharacterScale / 2 + Padding;
        }
        sprite.setPosition(vec);
        direction = setDirection;
    }
    else
    {
        vec = sprite.getPosition();
        object = Valid(direction, vec);
        if (object == MapObjects::Gate || object == MapObjects::Wall)
            setDirection = direction = Direction::Stop;
        sprite.setPosition(vec);
    }
    if (object == MapObjects::Nothing)
        object = Collides(Map::Objects[r][c]);
    return object;
}

sf::Vector2i PacMan::GetTile() const
{
    sf::Vector2i tile;
    sf::Vector2f vec = sprite.getPosition();
    tile.x = (vec.x) / (MapObjectScale * 15);
    tile.y = (vec.y) / (MapObjectScale * 15);
    return tile;
}

Direction PacMan::GetDirection() const
{
	return face;
}

bool PacMan::Hit(Ghost& ghost) const
{
    return sprite.getGlobalBounds().intersects(ghost.sprite.getGlobalBounds());
}

void PacMan::SetPosition(sf::Vector2f InitialPosition)
{
    currentImageX = 3;
    direction = Direction::Stop;
    setDirection = Direction::Stop;
    face = Direction::Right;
    sprite.setRotation(0.0f);
    sf::Vector2f v = sprite.getScale();
    sprite.setScale(std::abs(v.x), std::abs(v.y));
    sprite.setTextureRect(sf::IntRect(currentImageX * 15, 0, 15, 15));
    sprite.setPosition(InitialPosition);
}

void PacMan::SetDirection(Direction dir)
{
    setDirection = dir;
}

void PacMan::Animate(float dt)
{
    if (direction == Direction::Stop)
        return;
    currentImageX += AnimationRate * 2 * dt;
    int temp = static_cast<int>(currentImageX);
    if (temp > 3)
    {
        currentImageX -= 4;
        temp -= 4;
    }
    sprite.setTextureRect(sf::IntRect(temp * 15, 0, 15, 15));
    sf::Vector2f v = sprite.getScale();
    switch (direction)
    {
    case Direction::Up:
        sprite.setScale(std::abs(v.x), std::abs(v.y));
        sprite.setRotation(-90.0f);
        break;
    case Direction::Left:
        sprite.setScale(std::abs(v.x), -std::abs(v.y));
        sprite.setRotation(180.0f);
        break;
    case Direction::Right:
        sprite.setScale(std::abs(v.x), std::abs(v.y));
        sprite.setRotation(0.0f);
        break;
    case Direction::Down:
        sprite.setScale(std::abs(v.x), std::abs(v.y));
        sprite.setRotation(90.0f);
        break;
    }
    face = direction;
}

void PacMan::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
