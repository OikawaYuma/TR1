#include <Novice.h>

const char kWindowTitle[] = "LE2B_05_オイカワユウマ";

struct Vector2 {
	double x;
	double y;
};
struct Ball {
	Vector2 pos;
	Vector2 size;
	Vector2 velo;
	float mass;
};
enum change {
	ONE,
	TWO

};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };



	Ball player;
	player.pos = { 500,500 };
	player.size = { 30,30, };
	player.velo = { 0,0, };
	player.mass = 1;

	Ball mob;
	mob.pos = { 300,500 };
	mob.size = { 30,30 };
	mob.velo = { 0,0 };
	mob.mass = 1;

	int num = 0;
	int change = ONE;
	bool flag = false;

	bool upDownFlag = true;;


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
			player.velo.x = -1;
		}
		if (keys[DIK_R] && preKeys[DIK_R] == 0) {
			change = ONE;
			player.pos.x = 500;
			mob.pos.x = 300;
			player.velo.x = 0;
			mob.velo.x = 0;
			player.mass = 1;
			mob.mass = 1;
			flag = false;
			upDownFlag = true;
			num = 0;
		}

		if (keys[DIK_RIGHTARROW] && preKeys[DIK_RIGHTARROW] == 0 && player.mass == mob.mass) {
			player.mass *= 100;
			change = TWO;
			upDownFlag = false;
		}
		else if (keys[DIK_RIGHTARROW] && preKeys[DIK_RIGHTARROW] == 0 && player.mass == mob.mass * 100) {
			player.mass *= 100;
			upDownFlag = false;
		}
		if (keys[DIK_LEFTARROW] && preKeys[DIK_LEFTARROW] == 0 && player.mass == mob.mass * 10000) {
			player.mass /= 100;
			upDownFlag = false;
		}
		else if (keys[DIK_LEFTARROW] && preKeys[DIK_LEFTARROW] == 0 && player.mass == mob.mass * 100) {
			player.mass /= 100;
			change = ONE;
			upDownFlag = false;
		}

		if (keys[DIK_O] && preKeys[DIK_O] == 0 ) {
			player.mass = 1000000;
			change = TWO;
			upDownFlag = false;
		}

		if (keys[DIK_P] && preKeys[DIK_P] == 0) {
			player.mass = 100000000;
			change = TWO;
			upDownFlag = false;
		}

		if (keys[DIK_UPARROW] && upDownFlag) {
			player.mass++;
			mob.mass++;
		}
		else if (keys[DIK_DOWNARROW] && upDownFlag) {
			player.mass--;
			mob.mass--;
			if (mob.mass < 1) {
				player.mass += 1;
				mob.mass += 1;

			}
		}

		if (keys[DIK_A] ) {
			mob.pos.x -= 5;
		}
		else if (keys[DIK_D] ) {
			mob.pos.x += 5;
		}

		if (keys[DIK_J]) {
			player.pos.x -= 5;
		}
		else if (keys[DIK_L]) {
			player.pos.x += 5;
		}




		//}

		switch (change) {
		case ONE:
			if ((player.pos.x - mob.pos.x) * (player.pos.x - mob.pos.x) < (player.size.x + mob.size.x) * (player.size.x + mob.size.x) && flag == false) {//&&flag == true) {
				mob.velo.x = 2 * player.mass / (player.mass + mob.mass) * player.velo.x;
				player.velo.x = (player.mass - mob.mass) / (player.mass + mob.mass) * player.velo.x;
				num++;
				flag = true;
			}
			else if ((player.pos.x - mob.pos.x) * (player.pos.x - mob.pos.x) < (player.size.x + mob.size.x) * (player.size.x + mob.size.x) && flag == true) {//&&flag == true) {
				player.velo.x = 2 * mob.mass / (mob.mass + player.mass) * mob.velo.x;
				mob.velo.x = (mob.mass - player.mass) / (mob.mass + player.mass) * mob.velo.x;
				num++;
				flag = false;
			}
			break;
		case TWO:
			if ((player.pos.x - mob.pos.x) * (player.pos.x - mob.pos.x) < (player.size.x + mob.size.x) * (player.size.x + mob.size.x)) {//&&flag == true) {
				player.velo.x = (player.mass - mob.mass) / (player.mass + mob.mass) * player.velo.x + 2 * mob.mass / (player.mass + mob.mass) * mob.velo.x;
				mob.velo.x = 2 * player.mass / (player.mass + mob.mass) * player.velo.x - (player.mass - mob.mass) / (player.mass + mob.mass) * mob.velo.x;
				player.pos.x = mob.pos.x + mob.size.x + player.size.x;
				//flag = false;
				num++;
			}
			break;
		}
		/*if (mob->pos_.x + mob->size_.x >= player->pos_.x - player->size_.x) {

		}*/

		if (mob.pos.x - mob.size.x <= 150) {
			mob.velo.x *= -1;
			num++;
		}

		/*if (pos_.x + size_.x >= pos.x - size.x) {

		}*/
		player.pos.x += player.velo.x;
		mob.pos.x += mob.velo.x;
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		/// 


		Novice::DrawBox(0, 0, 1280, 720, 0.0f, WHITE, kFillModeSolid);
		Novice::DrawBox(0, 0, 150, 720, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawBox(150, 0, 1130, 200, 0.0f, 0x00000099, kFillModeSolid);
		Novice::DrawBox(150, 0, 1130, 200, 0.0f, BLACK, kFillModeWireFrame);
		Novice::DrawEllipse((int)player.pos.x, (int)player.pos.y, (int)player.size.x, (int)player.size.y, 0.0f, BLACK, kFillModeSolid);
		Novice::DrawEllipse((int)mob.pos.x, (int)mob.pos.y, (int)mob.size.x, (int)mob.size.y, 0.0f, BLACK, kFillModeSolid);
		//Novice::ScreenPrintf(0, 0, "%d", flag);


		Novice::ScreenPrintf(170, 20, "MOB.MASS:%f   :   PLAYER.MASS:%f", mob.mass, player.mass);
		Novice::ScreenPrintf(170, 65, "reflectNum : %d", num); Novice::ScreenPrintf(400, 65, "mode: %d", change);
		Novice::ScreenPrintf(170, 100, "leftEnergy:%f  :  rightEnergy:%f  :  EnergyAdd:%f", mob.velo.x * mob.mass, player.velo.x * player.mass, mob.velo.x * mob.mass + player.velo.x * player.mass);

		Novice::ScreenPrintf(800, 20,"MOB MOVE A or D");
		Novice::ScreenPrintf(800, 40, "PLAYER MOVE J or L");

		Novice::ScreenPrintf(800, 80, "MASS CHANGE 100 LEFT or RIGHT ARROW");
		Novice::ScreenPrintf(800, 100, "MASS CHANGE  1  UP   or DOWN  ARROW");

		Novice::ScreenPrintf(800, 140, "SHOT  SPACE keys");
		Novice::ScreenPrintf(800, 160, "Reset  R keys");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
