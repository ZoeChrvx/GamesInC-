#include "Vector2.h"
#include "Maths.h"

const Vector2 Vector2::zero(0, 0);
const Vector2 Vector2::unitX(1.0f, 0.0f);
const Vector2 Vector2::unitY(0.0f, 1.0f);

void Vector2::Set(float xP, float yP) {
	x = xP;
	y = yP;
}

float Vector2::LengthSq() const {
	return x * x + y * y;
}

float Vector2::Length() const {
	return Maths::sqrt(LengthSq());
}

void Vector2::Normalize(){
	float len = Length();
	x /= len;
	y /= len;
}