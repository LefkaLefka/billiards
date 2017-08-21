#pragma once
#include "CPoint.h"
#include "Ball.h"
#include "Game.h"
#include "SData.h"
#include "Helper.h"
#include "SDataBalls.h"
#include "HelperGame.h"

#include "cstdlib"
#include "algorithm"

namespace billiards {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;

	/// <summary>
	/// —водка дл€ MainForm
	/// </summary>
public ref class MainForm : public System::Windows::Forms::Form
{
public:
	MainForm(void)
	{
		InitializeComponent();
		//
		//TODO: добавьте код конструктора
		//
	}

protected:
	/// <summary>
	/// ќсвободить все используемые ресурсы.
	/// </summary>
	~MainForm()
	{
		if (components)
		{
			delete components;
		}
	}
private: System::Windows::Forms::Button^  buttonNewGame;
private: System::Windows::Forms::PictureBox^  pictureBox;
private: System::Windows::Forms::Label^  label;


private: Bitmap^ image;
private: Graphics^ graphics;
private: System::Threading::Thread^ gameThread;
private: Game* game;
private: SDataBalls^ ballsData;

private:
	/// <summary>
	/// ќб€зательна€ переменна€ конструктора.
	/// </summary>
	System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
	/// <summary>
	/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
	/// содержимое этого метода с помощью редактора кода.
	/// </summary>
	void InitializeComponent(void)
	{
		this->buttonNewGame = (gcnew System::Windows::Forms::Button());
		this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
		this->label = (gcnew System::Windows::Forms::Label());
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
		this->SuspendLayout();
		// 
		// buttonNewGame
		// 
		this->buttonNewGame->Location = System::Drawing::Point(13, 13);
		this->buttonNewGame->Name = L"buttonNewGame";
		this->buttonNewGame->Size = System::Drawing::Size(75, 23);
		this->buttonNewGame->TabIndex = 0;
		this->buttonNewGame->Text = L"New game";
		this->buttonNewGame->UseVisualStyleBackColor = true;
		this->buttonNewGame->Click += gcnew System::EventHandler(this, &MainForm::buttonNewGame_Click);
		// 
		// pictureBox
		// 
		this->pictureBox->BackColor = System::Drawing::Color::White;
		this->pictureBox->Location = System::Drawing::Point(13, 43);
		this->pictureBox->Name = L"pictureBox";
		this->pictureBox->Size = System::Drawing::Size(700, 400);
		this->pictureBox->TabIndex = 1;
		this->pictureBox->TabStop = false;
		this->pictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::pictureBox_Paint);
		this->pictureBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBox_MouseDown);
		this->pictureBox->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBox_MouseMove);
		this->pictureBox->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBox_MouseUp);
		// 
		// label
		// 
		this->label->AutoSize = true;
		this->label->Location = System::Drawing::Point(126, 18);
		this->label->Name = L"label";
		this->label->Size = System::Drawing::Size(116, 13);
		this->label->TabIndex = 2;
		this->label->Text = L"Player1: 0 --- Player2: 0";
		// 
		// MainForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(725, 455);
		this->Controls->Add(this->label);
		this->Controls->Add(this->pictureBox);
		this->Controls->Add(this->buttonNewGame);
		this->Name = L"MainForm";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"billiards";
		this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
		this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();

	}
#pragma endregion
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) 
{
	image = gcnew Bitmap(
		pictureBox->ClientSize.Width,
		pictureBox->ClientSize.Height,
		System::Drawing::Imaging::PixelFormat::Format32bppArgb);
}
private: System::Void pictureBox_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
{
	e->Graphics->DrawImage(image, 0, 0, image->Width, image->Height);
}
private: System::Void buttonNewGame_Click(System::Object^  sender, System::EventArgs^  e)
{
	label->Text = "Player1: 0 --- Player2: 0";

	image = gcnew Bitmap(SData::WIDHT_CANVAS, SData::HEIGTH_CANVAS);
	graphics = Graphics::FromImage(image);
	graphics->FillRectangle(gcnew SolidBrush(System::Drawing::Color::FromArgb(0, 205, 102)), 
		0, 0, SData::WIDHT_CANVAS, SData::HEIGTH_CANVAS);
	DrawHolesAndBorders();
	pictureBox->Invalidate();

	ballsData = gcnew SDataBalls();
	game = new Game();

	if (gameThread != nullptr)
	{
		game->IsGame = false;
		while (gameThread->IsAlive)
			System::Threading::Thread::Sleep(50);
	}

	game->IsGame = true;
	gameThread = gcnew System::Threading::Thread(
		gcnew System::Threading::ThreadStart(this, &MainForm::GameCycle));
	gameThread->Start();

	game->IsProgress = true;
}
private: System::Void GameCycle()
{
	while (game->IsGame)
	{
		Render();

		HelperGame* buff = new HelperGame();
		buff->Player1->IsProgress = game->Player1->IsProgress;
		buff->Player1->BallsCount = game->Player1->BallsCount;
		buff->Player2->IsProgress = game->Player2->IsProgress;
		buff->Player2->BallsCount = game->Player2->BallsCount;
		buff->IsProgress = game->IsProgress;

		buff = Helper::ReCalculate(ballsData->Balls, buff);

		if (buff->IsBlack == true)
		{
			game->IsGame = false;
			label->Invoke(gcnew Action<int>(this, &MainForm::Info), 1);
			return;
		}

		if (buff->Player1->BallsCount == game->Player1->BallsCount && buff->Player2->BallsCount == game->Player2->BallsCount)
		{
			game->Player1->IsProgress = buff->Player2->IsProgress;
			game->Player2->IsProgress = buff->Player1->IsProgress;
		}
		if (buff->Player1->BallsCount > game->Player1->BallsCount)
		{
			game->Player1->BallsCount = buff->Player1->BallsCount;
			game->Player1->IsProgress = true;
			game->Player2->IsProgress = false;
		}
		if (buff->Player2->BallsCount > game->Player2->BallsCount)
		{
			game->Player2->BallsCount = buff->Player2->BallsCount;
			game->Player1->IsProgress = false;
			game->Player2->IsProgress = true;
		}
		if (buff->SetWhiteBall)
		{
			game->SetWhiteBall = buff->SetWhiteBall;
			ballsData->Balls[0]->IsVisible = true;
			ballsData->Balls[0]->Speed = 0;
			ballsData->Balls[0]->End = nullptr;
		}
			
		if (buff->IsProgress)
			game->IsProgress = buff->IsProgress;

		game->Player1->BallsCount = buff->Player1->BallsCount;
		game->Player2->BallsCount = buff->Player2->BallsCount;

		label->Invoke(gcnew Action<int>(this, &MainForm::Info), 0);
		
		System::Threading::Thread::Sleep(5);
	}
}
private: System::Void Info(int value) 
{
	if (value == 0)
		label->Text = "Player1: " + game->Player1->BallsCount.ToString() + " --- " + "Player2: " + game->Player2->BallsCount.ToString();
	if (value == 1)
		label->Text = game->Player1->IsProgress ? "Player 1 lose" : "Player 2 lose";
}
private: System::Void Render()
{
	try
	{
		graphics->FillRectangle(gcnew SolidBrush(System::Drawing::Color::FromArgb(0, 205, 102)),
			0, 0, SData::WIDHT_CANVAS, SData::HEIGTH_CANVAS);
		DrawHolesAndBorders();

		for (int i = 0; i < SData::BALLS_COUNT; ++i)
		{
			if (ballsData->Balls[i]->IsVisible)
			{
				if (ballsData->Balls[i]->IsStriped)
					graphics->FillEllipse(
						gcnew HatchBrush(HatchStyle::Horizontal, SData::STRIP_COLOR(), ballsData->Balls[i]->Color),
						ballsData->Balls[i]->X,
						ballsData->Balls[i]->Y,
						(float)SData::DIAMETER_BALL,
						(float)SData::DIAMETER_BALL);
				else
					graphics->FillEllipse(
						gcnew SolidBrush(ballsData->Balls[i]->Color),
						ballsData->Balls[i]->X,
						ballsData->Balls[i]->Y,
						(float)SData::DIAMETER_BALL,
						(float)SData::DIAMETER_BALL);
			}
		}
		
		if (game->IsProgress && game->Cue != nullptr)
		{
			Pen^ penCue = gcnew Pen(System::Drawing::Color::Brown, 5);

			graphics->DrawLine(penCue, game->Cue->CueStart->X, game->Cue->CueStart->Y,
				game->Cue->CueEnd->X, game->Cue->CueEnd->Y);

			delete penCue;
		}

		pictureBox->Invalidate();
	}
	catch (Exception^ e)
	{
	}
	finally
	{
		GC::Collect();
	}
}
private: System::Void DrawHolesAndBorders()
{
	array<CPoint*>^ HOLES = SData::HOLES();
	// Draw canvas border
	Pen^ penBorder = gcnew Pen(System::Drawing::Color::FromArgb(0, 139, 69), (float)SData::THICKNESS_BORDER);
	graphics->DrawLine(penBorder, 0, 0, SData::WIDHT_CANVAS, 0);
	graphics->DrawLine(penBorder, 0, SData::HEIGTH_CANVAS, SData::WIDHT_CANVAS, SData::HEIGTH_CANVAS);
	graphics->DrawLine(penBorder, 0, 0, 0, SData::HEIGTH_CANVAS);
	graphics->DrawLine(penBorder, SData::WIDHT_CANVAS, 0, SData::WIDHT_CANVAS, SData::HEIGTH_CANVAS);
	// Draw holes
	Brush^ brush = gcnew SolidBrush(System::Drawing::Color::FromArgb(47, 79, 79));

	for (int i = 0; i < SData::HOLES_COUNT; ++i)
		graphics->FillEllipse(brush, HOLES[i]->X, SData::HOLES()[i]->Y, (float)SData::DIAMETER_HOLE, (float)SData::DIAMETER_HOLE);
	
	delete brush;
	delete penBorder;
}
private: System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	if (game != nullptr)
		game->IsGame = false;
	if (gameThread != nullptr)
		gameThread->Abort();
}
private: System::Void pictureBox_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (game == nullptr)
		return;
	
	if (game->IsProgress == false)
		return;

	float buffStartCue = SData::START_CUE;

	if (game->SetWhiteBall)
	{
		ballsData->Balls[0]->X = e->X - SData::RADIUS_BALL;
		ballsData->Balls[0]->Y = e->Y - SData::RADIUS_BALL;
		return;
	}

	if (game->IsCuePressed)
		if (game->PointOnCue != nullptr)
		{
			buffStartCue = (float)Math::Sqrt((game->PointOnCue->X - (float)e->X) * (game->PointOnCue->X - (float)e->X) +
				(game->PointOnCue->Y - (float)e->Y) * (game->PointOnCue->Y - (float)e->Y));

			buffStartCue = (buffStartCue > SData::START_CUE && buffStartCue < SData::MAX_CUE_LENGTH) ? buffStartCue :
				buffStartCue >= SData::MAX_CUE_LENGTH ? (float)SData::MAX_CUE_LENGTH : (float)SData::START_CUE;

			game->PointOnCue = Helper::PointFromLength(ballsData->Balls[0]->Center()->X, ballsData->Balls[0]->Center()->Y,
				(float)e->X, (float)e->Y,
				buffStartCue);

			game->LengthForSpeed = buffStartCue;
		}

	// €кщо ми не в кул≥
	if ((e->X - ballsData->Balls[0]->Center()->X) * (e->X - ballsData->Balls[0]->Center()->X) +
		(e->Y - ballsData->Balls[0]->Center()->Y) * (e->Y - ballsData->Balls[0]->Center()->Y) >
		buffStartCue * buffStartCue)
		game->Cue = new Cue(ballsData->Balls[0]->Center(), new CPoint((float)e->X, (float)e->Y), buffStartCue);
}
private: System::Void pictureBox_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (game == nullptr)
		return;

	if (game->IsProgress == false)
		return;

	if (game->SetWhiteBall)
		return;

	game->PointOnCue = new CPoint((float)e->X, (float)e->Y);
	game->IsCuePressed = true;
}
private: System::Void pictureBox_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (game == nullptr)
		return;

	if (game->IsProgress == false)
		return;

	if (game->SetWhiteBall)
	{
		game->SetWhiteBall = false;
		return;
	}

	game->IsProgress = false;
	game->IsCuePressed = false;
	game->PointOnCue = nullptr;
	
	ballsData->Balls[0]->Speed = Helper::SpeedFromCue(game->LengthForSpeed);
	ballsData->Balls[0]->End = Helper::EndOfLine(game->Cue->CueStart, ballsData->Balls[0]->Center(), ballsData->Balls[0]->End);
}
};
}
