#pragma once
class AbstractInterface {
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
};