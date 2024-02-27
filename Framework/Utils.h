#pragma once

class Utils
{
public:
	static float Clamp(float v, float min, float max);
	static sf::Vector2f Clamp(const sf::Vector2f& v, const sf::FloatRect& rect);

	static sf::FloatRect ResizeRect(const sf::FloatRect& rect, const sf::Vector2f& delta);

	// Random
	static float RandomValue(); // 0.0f ~ 1.0f
	static float RandomRange(float min, float max);
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();
	static int RandomRange(int min, int maxExclude);


	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins originPreset);

	//Math
	static float SqrMagnitude(const sf::Vector2f& vec); //����^2
	static float Magnitude(const sf::Vector2f& vec); //����
	static sf::Vector2f GetNormalize(const sf::Vector2f& vec); //��������
	static void Normalize(sf::Vector2f& vec); //����ȭ
	static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2);
	static float DistancePointAndLineSegment(const sf::Vector2f& p1, const sf::Vector2f& lineP1, const sf::Vector2f& lineP2);
	static float DistancePointAndLineSegmentMin(const sf::Vector2f& p1, const sf::Vector2f& lineP1, const sf::Vector2f& lineP2);

	static float RadianToDegree(float radian);
	static float DegreeToRadian(float degree);
	static float Angle(const sf::Vector2f& vec);
	static void Rotate(sf::Vector2f& vec, float degree); //ȸ��
	static float Lerp(float min, float max, float t); //��������
	static sf::Vector2f Lerp(const sf::Vector2f& min, const sf::Vector2f& max, float t); //��������


	//�浹
	static void ElasticCollision(float& coord, float border, float cor = 1.f);
	static float GetElasticCollision(float coord, float border, float cor = 1.f);
	static bool IsCollideWithLineSegment(const sf::Vector2f& p1, const sf::Vector2f& lineP1, const sf::Vector2f& lineP2, float radius);


	
};