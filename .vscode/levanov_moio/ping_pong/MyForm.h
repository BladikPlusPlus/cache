#pragma once

namespace pingpong {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		Timer^ timer;

		float ball_x, ball_y;
		float velocity_x, velocity_y;
		float ball_speed;
		int ball_size = 10;

		float left_paddle_y, right_paddle_y;
		int left_paddle_x = 20, right_paddle_x;

		int paddle_width = 15, paddle_hieght = 80;
		int field_width, field_hieght;

		int score_left = 0, score_right = 0;

		bool keyW = false, keyS = false, keyUp = false, keyDown = false, isPause = false;

		Label^ labelPause;

		Random^ rnd;
		Button^ buttonSettings;

		System::Drawing::Font^ FScore;
	public:
		MyForm(void)
		{
			InitializeComponent();
			field_hieght = this->ClientSize.Height;
			field_width = this->ClientSize.Width;

			right_paddle_x = field_width - 20 - paddle_width;
			
			initGame();
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

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
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);

			rnd = gcnew Random;

			this->KeyDown += gcnew KeyEventHandler(this, &MyForm::OnKeyDown);
			this->KeyUp += gcnew KeyEventHandler(this, &MyForm::OnKeyUp);
			this->Paint += gcnew PaintEventHandler(this, &MyForm::OnPaint);

			this->labelPause = gcnew Label();
			this->labelPause->Text = L"Pause";
			this->labelPause->AutoSize = true;
			this->labelPause->Location = Point(this->Width /2 - 10, this->Height / 2 - 10);
			this->labelPause->Size = System::Drawing::Size(200, 50);
			this->labelPause->Visible = false;
			this->labelPause->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif"
				, 40.f
				, System::Drawing::FontStyle::Bold
				, System::Drawing::GraphicsUnit::Point
				, static_cast<System::Byte>(204)));
			this->Controls->Add(this->labelPause);


			this->buttonSettings = gcnew Button();
			this->buttonSettings->Text = L"NAAA";
			this->buttonSettings->Location = Point(this->Width - this->buttonSettings->Width
				, this->Height - this->buttonSettings->Height);
			this->buttonSettings->Click += gcnew EventHandler(this, &MyForm::showSettings);
			this->Controls->Add(this->buttonSettings);

			timer = gcnew Timer();
			timer->Interval = 16;
			timer->Tick += gcnew EventHandler(this, &MyForm::gameLoop);
			timer->Start();
		}

		void initGame() {
			FScore = gcnew System::Drawing::Font(L"Arial", 40, FontStyle::Bold);
			left_paddle_y = (field_hieght - paddle_hieght) / 2.f;
			right_paddle_y = left_paddle_y;
			score_left = score_right = 0;
			resetBall();
		}

		void resetBall() {
			if (score_left == 2 || score_right == 2) {
				initGame();
			};

			ball_y = (field_hieght - ball_size) / 2.f;
			ball_x = (field_width - ball_size) / 2.f;
			float angle = (rnd->NextDouble() - 0.5f) * (3.14 / 4) / 2;
			float dir_x = (rnd->Next(2) == 0) ? 1.0f : -1.0f;
			ball_speed = 5.f;
			velocity_x = dir_x * ball_speed * Math::Cos(angle);
			velocity_y = ball_speed * Math::Sin(angle);
		}
		
		void OnKeyDown(Object^ sender, KeyEventArgs^ e) {
			if (e->KeyCode == Keys::W)			keyW = true;
			if (e->KeyCode == Keys::S)			keyS = true;
			if (e->KeyCode == Keys::Up)			keyUp = true;
			if (e->KeyCode == Keys::Down)		keyDown = true;
			e->SuppressKeyPress = true;

			if (e->KeyCode == Keys::Space) { isPause = !isPause; };
			if (isPause) {
				timer->Stop();
				labelPause->Visible = true;
			}
			else {
				timer->Start();
				labelPause->Visible = false;
			}
		}

		void OnKeyUp(Object^ sender, KeyEventArgs^ e) {
			if (e->KeyCode == Keys::W)			keyW = false;
			if (e->KeyCode == Keys::S)			keyS = false;
			if (e->KeyCode == Keys::Up)			keyUp = false;
			if (e->KeyCode == Keys::Down)		keyDown = false;
		}

		void OnPaint(Object^ sender, PaintEventArgs^ e) {
			Graphics^ graphics = e->Graphics;
			graphics->Clear(Color::DarkSeaGreen);
			graphics->FillRectangle(Brushes::DarkBlue, left_paddle_x, static_cast<int>(left_paddle_y), paddle_width, paddle_hieght);
			graphics->FillRectangle(Brushes::DarkRed, right_paddle_x, static_cast<int>(right_paddle_y), paddle_width, paddle_hieght);
			graphics->FillEllipse(Brushes::White, static_cast<int>(ball_x), static_cast<int>(ball_y), ball_size, ball_size);
			String^ scoreText = score_left.ToString() + " : " + score_right.ToString();
			graphics->DrawString(scoreText, FScore, Brushes::White, (field_width - 80) / 2, 20);
		}

		void gameLoop(Object^ sender, EventArgs^ e) {
			int paddle_move = 8;
			void pinpong::GameField::ShowSettings(Object ^ sender, EventArgs ^ e) {
				timer->Stop();
				this->Enabled = false;
				SettingsForm^ settings = gcnew SettingsForm();
				settings->Owner = this;
			}
			
			if (keyW)		left_paddle_y -= paddle_move;
			if (keyS)		left_paddle_y += paddle_move;
			if (keyUp)		right_paddle_y -= paddle_move;
			if (keyDown)	right_paddle_y += paddle_move;
			if (isPause) { this->Invalidate(); return; }

			if (left_paddle_y < 0) left_paddle_y = 0;
			if (left_paddle_y > field_hieght - paddle_hieght) left_paddle_y = field_hieght - paddle_hieght;
			if (right_paddle_y < 0) right_paddle_y = 0;
			if (right_paddle_y > field_hieght - paddle_hieght) right_paddle_y = field_hieght - paddle_hieght;
			float current_speed = Math::Sqrt(velocity_x * velocity_x + velocity_y * velocity_y);
			float new_speed = current_speed + 0.005f;
			velocity_x *= new_speed / current_speed;
			velocity_y *= new_speed / current_speed;
			ball_x += velocity_x;
			ball_y += velocity_y;

			if (ball_y <= 0 || ball_y >= field_hieght - ball_size) velocity_y = -velocity_y;

			if (ball_x <= left_paddle_x + paddle_width &&
				ball_x >= left_paddle_x &&
				ball_y + ball_size >= left_paddle_y &&
				ball_y <= left_paddle_y + paddle_hieght)
				if (velocity_x < 0) {
					velocity_x = -velocity_x;
					ball_x = left_paddle_x + paddle_width;
					adjustBallAngle(left_paddle_y);
				}

			if (ball_x + ball_size >= right_paddle_x &&
				ball_x <= right_paddle_x + paddle_width &&
				ball_y + ball_size >= right_paddle_y &&
				ball_y <= right_paddle_y + paddle_hieght)
				if(velocity_x > 0){
					velocity_x = -velocity_x;
					ball_x = right_paddle_x - ball_size;
					adjustBallAngle(right_paddle_y);
				}

			if (ball_x < 0) {
				++score_right;
				resetBall();
			}
			if (ball_x + ball_speed > field_width) {
				++score_left;
				resetBall();
			}
			this->Invalidate();
		}

		void adjustBallAngle(float paddle_pos) {
			float hit_pos = ((ball_y + ball_size) / 2.f - paddle_pos) / paddle_hieght;
			hit_pos = Math::Max(0.f, Math::Min(1.f, hit_pos));
			float angel = (hit_pos - 0.5f) * 2.f * (3.14 / 3);
			float speed = Math::Sqrt(velocity_x * velocity_x + velocity_y * velocity_y);
			float dir_x = (velocity_x > 0) ? 1.f : -1.f;
			velocity_x = dir_x * speed * Math::Cos(angel);
			velocity_y = speed * Math::Sin(angel);
			if (velocity_y == 0) velocity_y = 1;
		}

#pragma endregion
	};
}
