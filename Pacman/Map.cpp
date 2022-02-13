#include "Map.h"

sf::Vector2f Map::PacmanInitialPosition;

sf::Vector2f Map::BlinkyInitialPosition;
sf::Vector2f Map::PinkyInitialPosition;
sf::Vector2f Map::InkyInitialPosition;
sf::Vector2f Map::ClydeInitialPosition;

int Map::DotsNumber = 0;

MapObject Map::Objects[31][28];

void SetObject(MapObject& obj, int offset)
{
	obj.sprite.setTexture(*Resources::mapTexture);
	obj.sprite.setScale(MapObjectScale, MapObjectScale);
	obj.sprite.setTextureRect(sf::IntRect(offset, 0, 15, 15));
}

bool Map::LoadMap()
{
	std::ifstream f;
	f.open("Resources/pacman_map.txt");
	if (!f.is_open())
		return false;
	int ghost = 0;
	char arr[60];
	int r = 0;
	while (f >> arr)
	{
		int c = 0;
		char* place = nullptr;
		char* ptr = strtok_s(arr, ",", &place);
		float rv = r * 15 * MapObjectScale;
		while (ptr != nullptr)
		{
			float cv = c * 15 * MapObjectScale;
			Objects[r][c].sprite.setPosition(cv, rv);
			switch (ptr[0])
			{
			case '0':
				SetObject(Objects[r][c], 0);
				break;
			case '1':
				Objects[r][c].object = MapObjects::Wall;
				SetObject(Objects[r][c], 45);
				break;
			case '2':
				Objects[r][c].object = MapObjects::Dot;
				SetObject(Objects[r][c], 15);
				DotsNumber++;
				break;
			case '3':
				Objects[r][c].object = MapObjects::PowerBullet;
				SetObject(Objects[r][c], 30);
				DotsNumber++;
				break;
			case '4':
				SetObject(Objects[r][c], 0);
				switch (ghost)
				{
				case 0:
					ClydeInitialPosition = { cv + Padding, rv + Padding };
					++ghost;
					break;
				case 1:
					PinkyInitialPosition = { cv + Padding, rv + Padding };
					++ghost;
					break;
				case 2:
					InkyInitialPosition = { cv + Padding, rv + Padding };
					++ghost;
					break;
				case 3:
					BlinkyInitialPosition = { cv + Padding, rv + Padding };
					++ghost;
					break;
				}
				break;
			case '5':
				Objects[r][c].object = MapObjects::Gate;
				SetObject(Objects[r][c], 60);
				break;
			case '6':
				SetObject(Objects[r][c], 0);
				PacmanInitialPosition = { cv + CharacterScale * 15 / 2.0f + Padding,
					rv + CharacterScale * 15 / 2.0f + Padding };
				break;
			}
			ptr = strtok_s(nullptr, ",", &place);
			++c;
		}
		++r;
	}
	f.close();
	return true;
}
