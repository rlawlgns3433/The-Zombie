#pragma once
/// <summary>
/// sf::RenderWindow�� ���� ������ �Ѵ�.
/// ������ ���� ������ â ũ�Ⱑ �����ȴ�.
/// ������ create���� �� ��������.
/// </summary>
class RenderWindowRBR : public sf::RenderWindow
{
protected:
	bool isResizing = false;

	sf::Vector2u sizeRatio;
	sf::Vector2u preSize;

	void onCreate() override;
	void onResize() override;

};

