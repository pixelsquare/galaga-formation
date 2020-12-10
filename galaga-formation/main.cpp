#include "glutSetup.h"

#define DEG2RAD 3.14159265359/180

class Vector3 {
public:
	Vector3() { 
		this->X = 0.0f;
		this->Y = 0.0f;
		this->Z = 0.0f;
	}

	Vector3(float x, float y, float z) {
		this->X = x;
		this->Y = y;
		this->Z = z;
	}
	~Vector3() { }

	Vector3 &operator=(const Vector3 &rhs)
	{
		this->X = rhs.X;
		this->Y = rhs.Y;
		this->Z = rhs.Z;

		return *this;
	}

	Vector3 &operator+=(const Vector3 &rhs)
	{
		this->X += rhs.X;
		this->Y += rhs.Y;
		this->Z += rhs.Z;

		return *this;
	}

	Vector3 operator+(const Vector3 &op)
	{
		Vector3 rhs;
		rhs.X = this->X + op.X;
		rhs.Y = this->Y + op.Y;
		rhs.Z = this->Z + op.Z;

		return rhs;
	}

	Vector3 &operator-=(const Vector3 &rhs)
	{
		this->X -= rhs.X;
		this->Y -= rhs.Y;
		this->Z -= rhs.Z;

		return *this;
	}

	Vector3 operator-(const Vector3 &op)
	{
		Vector3 rhs;
		rhs.X = this->X - op.X;
		rhs.Y = this->Y - op.Y;
		rhs.Z = this->Z - op.Z;

		return rhs;
	}

	Vector3 &operator*=(const float scalar)
	{
		this->X *= scalar;
		this->Y *= scalar;
		this->Z *= scalar;

		return *this;
	}

	Vector3 operator*(const float scalar)
	{
		Vector3 rhs;
		rhs.X = this->X * scalar;
		rhs.Y = this->Y * scalar;
		rhs.Z = this->Z * scalar;

		return rhs;
	}

	float X;
	float Y;
	float Z;
private:
protected:
};

class Object {
public:
	Object() { 
		this->radius = 10.0f;
		this->direction = Vector3(1.0f, 1.0f, 0.0f);
		this->origin = Vector3(0.0f, 0.0f, 0.0f);
	}
	~Object() { }

	void SetColor(float r, float g, float b) {
		this->R = r;
		this->G = g;
		this->B = b;
	}

	void DrawObject() {
		glPushMatrix();
		glColor3f(this->R, this->G, this->B);
		glTranslatef(this->position.X, this->position.Y, this->position.Z);
		glRotatef(this->step, 0.0f, 0.0f, 1.0f);
			glutSolidCube(1);
		glPopMatrix();
	}

	Vector3 position;
	Vector3 direction;
	Vector3 velocity;
	Vector3 origin;
	float radius;
	float step;
	float theta;
private:
	float R;
	float G;
	float B;
protected:
};

Object leader1;
Object follower;
float distance = 2;

void GamePlay()
{
	leader1.step += 1.0f;
	leader1.theta = leader1.step * DEG2RAD;
	//leader1.direction = Vector3(-cos(leader1.step * (DEG2RAD / 2)), -sin(leader1.step * (DEG2RAD / 2)), 0.0f);
	leader1.velocity = leader1.direction * leader1.radius;
	leader1.position.X = leader1.origin.X + leader1.velocity.X * cos(leader1.theta);
	leader1.position.Y = leader1.origin.Y + leader1.velocity.Y * sin(leader1.theta);
	leader1.SetColor(1.0f, 0.0f, 0.0f);
	leader1.DrawObject();

	follower.step = leader1.step;
	follower.position.X = distance * cos(leader1.theta + (DEG2RAD / 2)) + leader1.position.X;
	follower.position.Y = distance * sin(leader1.theta + (DEG2RAD / 2)) + leader1.position.Y;
	follower.SetColor(0.0f, 1.0f, 0.0f);
	follower.DrawObject();
}

void Scene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(LookX, LookY, LookZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glRotatef(AngleX, 1.0, 0.0, 0.0);
		glRotatef(AngleY, 0.0, 1.0, 0.0);
	/* Display Object on GLUT Window */
		glPushMatrix();

		GamePlay();

		glPopMatrix();

	glutSwapBuffers();
} 

void Keys(unsigned char key, int x, int y)
{
	KeyDown[key] = true;
  switch(key)
  {

// Others
	case 27:
		exit(0);
  }
}

void main(int argc, char **argv)
{
	GLUTmain(argc, argv, "Galaga Formation");
}	

	//angleRotation += 1;
	//position.X = center.X + radius * cos(DEG2RAD * angleRotation);
	//position.Y = center.Y + radius * sin(DEG2RAD * angleRotation);