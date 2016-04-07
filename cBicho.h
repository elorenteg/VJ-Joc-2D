#pragma once

#include "cTexture.h"
#include "cScene.h"
#include "Globals.h"

#define BICHO_WIDTH		TILE_SIZE*3
#define BICHO_HEIGHT	TILE_SIZE*2

#define PROJ_WIDTH		27
#define	PROJ_HEIGHT		7
#define PROJ_SPEED		5
#define PROJ_TIME		15

#define DIR_NONE		0
#define	DIR_UP			1
#define DIR_DOWN		-1
#define	DIR_LEFT		-1
#define DIR_RIGHT		1

#define FRAME_DELAY		12
#define STEP_LENGTH		TILE_SIZE/4

#define MAX_FRAMES	5
#define FRAME_0		0
#define FRAME_1		1
#define FRAME_2		2
#define FRAME_3		3
#define FRAME_4		4

#define MAX_FRAMES_DEAD	7
#define FRAME_5			5
#define FRAME_6			6

typedef struct Projectile {
	float x;
	float y;
	int state_color;
	int time_color;
	int time_stamp;
	int type;
};

typedef struct TexCoords {
	float xo;
	float xf;
	float yo;
	float yf;
};

class cRect
{
public:
	int left, top, right, bottom;
};

class cPlayer;

class cBicho
{
public:
	cBicho(void);
	cBicho(float x, float y, int w, int h);
	~cBicho(void);

	void SetPosition(float x, float y);
	void SetTile(int tx, int ty);
	void SetWidthHeight(int w, int h);
	void SetZ(float z);
	void SetXWindow(float xWindow);
	void SetMapValue(Matrix& map, int tile_x, int tile_y, int value);
	void SetProjectiles(vector<Projectile>& projs, int dir);
	void SetWidthHeightProjectiles(int w, int h);
	void SetIsDead(bool dead);

	float GetX();
	float GetY();
	float GetXWindow();
	int GetWidth();
	int GetHeight();
	vector<Projectile> GetProjectiles(int dir);
	bool GetIsDead();
	int GetWProj();
	int GetHProj();

	void MoveRight(Matrix& map);
	void MoveLeft(Matrix& map);
	void MoveUp(Matrix& map);
	void MoveDown(Matrix& map);

	virtual void Draw(int tex_id);
	virtual void Logic(Matrix& map, float cameraXScene);

	bool isEnemy(Matrix& map, int tile_x, int tile_y);
	bool isScene(Matrix& map, int tile_x, int tile_y);

	virtual void Shoot(Matrix& map);
	void DrawProjectiles(int tex_id);
	virtual bool LogicProjectiles(Matrix& map, int level, int total_levels);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();

protected:
	float x, y, z;
	int w, h;
	int state;
	float xWindow;
	int state_lookat;
	int w_proj;
	int h_proj;
	float speed_proj;
	vector<Projectile> projsLeft;
	vector<Projectile> projsRight;
	bool isDead;
	bool definitiveDead;
	int freq_shoots;

	TexCoords TextureCoordinates();
	TexCoords BubblesTextureCoordinates();
	virtual TexCoords ChildYCoords();
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf);
	void DrawProjectiles(int tex_id, vector<Projectile>& projectiles, int dir);

	bool MapCollidesUp(Matrix& map, float step);
	bool MapCollidesDown(Matrix& map, float step);
	bool MapCollidesLeft(Matrix& map, float step);
	bool MapCollidesRight(Matrix& map, float step);

	virtual bool canMove(Matrix& map, int tx, int ty);
	virtual int maxFramesProjectiles();
	float xo_coords(int state_color, int dir);
	float xf_coords(int state_color, int dir);
	float yo_coords(int state_color);
	float yf_coords(int state_color);

	virtual Projectile InitShoot();
	virtual void MoveProjectiles(Matrix& map);
	virtual int maxFreqProjectiles(int level, int total_levels);
	bool frequencyShoot(Matrix& map, int level, int total_levels);

	bool canShoot();
	virtual bool canMove(float step);

	virtual bool lookAtRight();
	bool isInScene();

private:
	int seq, delay;

	vector<Projectile> MoveProjectiles(Matrix& map, vector<Projectile>& projs, int dirX);
};
