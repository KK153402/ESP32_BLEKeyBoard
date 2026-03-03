#include <Arduino.h>

/*
 * ESP32 Dev Module 動作確認用 BLEキーボード (ENTERキー)
 * 
 * 必要なライブラリ:
 * - ESP32-BLE-Keyboard by T-vK
 *   Arduino IDEのライブラリマネージャーからインストール可能
 * 
 * 配線:
 * - タクトスイッチの片側: GPIO4
 * - タクトスイッチのもう片側: GND
 * - 内蔵LED: GPIO2（自動的に使用されます）
 */

#include <BleKeyboard.h>

// ピン設定
const int BUTTON_PIN = 4;           // タクトスイッチを接続するGPIOピン
const int LED_PIN = 2;              // 内蔵LED（多くのESP32 Dev Moduleで使用可能）

// チャタリング防止用の設定
const unsigned long DEBOUNCE_DELAY = 50;  // 50ミリ秒
unsigned long lastDebounceTime = 0;
int lastButtonState = HIGH;
int buttonState = HIGH;

// 接続状態の管理
bool wasConnected = false;

// BLEキーボードの初期化
BleKeyboard bleKeyboard("ESP32 Keyboard Test", "Espressif", 100);

void setup() {
  // シリアル通信の初期化（デバッグ用）
  Serial.begin(115200);
  delay(1000);  // シリアルモニタの起動を待つ
  
  Serial.println("\n========================================");
  Serial.println("ESP32 BLE Keyboard - 動作確認モード");
  Serial.println("========================================");
  
  // LEDピンの設定
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // ボタンピンの設定（内部プルアップ抵抗を有効化）
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.println("[OK] ボタンピン設定完了 (GPIO4)");
  
  // 起動確認用LED点滅
  Serial.println("[INFO] 起動確認のためLEDを3回点滅します");
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
  
  // BLEキーボードの開始
  Serial.println("[INFO] Bluetooth初期化中...");
  bleKeyboard.begin();
  Serial.println("[OK] Bluetooth初期化完了");
  Serial.println("");
  Serial.println("PCのBluetooth設定から");
  Serial.println("「ESP32 Keyboard Test」に接続してください");
  Serial.println("========================================");
}

void loop() {
  // BLE接続状態の確認と通知
  if(bleKeyboard.isConnected()) {
    // 接続された瞬間の処理
    if (!wasConnected) {
      wasConnected = true;
      Serial.println("\n★★★ Bluetooth接続成功！★★★");
      Serial.println("ボタンを押してENTERキーをテストしてください");
      Serial.println("========================================\n");
      
      // LED点灯で接続を示す
      digitalWrite(LED_PIN, HIGH);
    }
    
    // ボタンの現在の状態を読み取り
    int reading = digitalRead(BUTTON_PIN);
    
    // ボタンの状態が変化した場合、デバウンスタイマーをリセット
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }
    
    // デバウンス時間が経過したら、ボタンの状態を更新
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
      // ボタンの状態が実際に変化した場合
      if (reading != buttonState) {
        buttonState = reading;
        
        // ボタンが押された場合（LOWになった場合）
        if (buttonState == LOW) {
          Serial.println(">>> ボタン押下検出！ENTERキー送信");
          
          // ENTERキーを送信
          bleKeyboard.write(KEY_RETURN);
          
          // LED点滅でフィードバック
          digitalWrite(LED_PIN, LOW);
          delay(100);
          digitalWrite(LED_PIN, HIGH);
          
          Serial.println("    [送信完了] PCで改行が入力されているか確認してください");
        }
      }
    }
    
    // 前回の状態を保存
    lastButtonState = reading;
    
  } else {
    // 切断された瞬間の処理
    if (wasConnected) {
      wasConnected = false;
      Serial.println("\n[警告] Bluetooth接続が切断されました");
      Serial.println("再接続を待機中...\n");
      digitalWrite(LED_PIN, LOW);
    }
    
    // 接続待ち状態（LED点滅）
    static unsigned long lastBlinkTime = 0;
    static bool ledState = false;
    
    if (millis() - lastBlinkTime > 1000) {  // 1秒ごとに点滅
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      lastBlinkTime = millis();
    }
  }
  
  // CPU負荷を下げるための短い待機時間
  delay(10);
}