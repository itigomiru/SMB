#pragma once

class Title : public Scene
{
	public:
	void Init() override;
	void Update() override;
	void Render() override;
	~Title() override {
	}
};