/**
 * Robot Sumo Champion - 360° Attack & Defense Firmware
 * Developed by Nekena Herinirina
 * 
 * Hardware Setup:
 * - 2 IR Line Sensors (Front & Back to detect border color)
 * - 4 Ultrasonic Sensors (Front, Left, Right, Back for 360° situational awareness)
 * - 2 DC Motors with H-Bridge driver
 */

// --- PINS CAPTEURS ULTRASONS ---
#define TRIG_FRONT 2
#define ECHO_FRONT 3
#define TRIG_LEFT  4
#define ECHO_LEFT  5
#define TRIG_RIGHT 6
#define ECHO_RIGHT 7
#define TRIG_BACK  8
#define ECHO_BACK  9

// --- PINS CAPTEURS INFRAROUGES (Ligne du Dohyo) ---
#define IR_FRONT_LINE 10
#define IR_BACK_LINE  11

// --- PINS MOTEURS ---
#define MOTOR_LEFT_A  12
#define MOTOR_LEFT_B  13
#define MOTOR_RIGHT_A A0
#define MOTOR_RIGHT_B A1

// --- PARAMÈTRES ---
#define SENSOR_TIMEOUT 20000 // 20ms timeout pour les ultrasons
#define MAX_ENEMY_DISTANCE 50 // Distance de détection en cm
#define BORDER_COLOR LOW      // Ajuster selon le capteur (Ligne blanche détectée)

void setup() {
  // Configuration des Ultrasons
  pinMode(TRIG_FRONT, OUTPUT); pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT); pinMode(ECHO_RIGHT, INPUT);
  pinMode(TRIG_BACK, OUTPUT);  pinMode(ECHO_BACK, INPUT);

  // Configuration des IR
  pinMode(IR_FRONT_LINE, INPUT);
  pinMode(IR_BACK_LINE, INPUT);

  // Configuration des Moteurs
  pinMode(MOTOR_LEFT_A, OUTPUT);  pinMode(MOTOR_LEFT_B, OUTPUT);
  pinMode(MOTOR_RIGHT_A, OUTPUT); pinMode(MOTOR_RIGHT_B, OUTPUT);

  // Délai réglementaire de sécurité de 5 secondes avant le combat
  delay(5000);
}

void loop() {
  // ==========================================
  // SÉCURITÉ ANTI-CHUTE (Priorité Absolue)
  // ==========================================
  if (digitalRead(IR_FRONT_LINE) == BORDER_COLOR) {
    moveBackward();
    delay(600);
    spinRight();
    delay(400);
    return;
  }
  
  if (digitalRead(IR_BACK_LINE) == BORDER_COLOR) {
    moveForward();
    delay(600);
    return;
  }

  // ==========================================
  // ACQUISITION DES RADARS (360° Scan)
  // ==========================================
  int distFront = readDistance(TRIG_FRONT, ECHO_FRONT);
  int distLeft  = readDistance(TRIG_LEFT, ECHO_LEFT);
  int distRight = readDistance(TRIG_RIGHT, ECHO_RIGHT);
  int distBack  = readDistance(TRIG_BACK, ECHO_BACK);

  // ==========================================
  // STRATÉGIE DE COMBAT AUTONOME
  // ==========================================
  
  // 1. L'ennemi est devant -> On charge à pleine puissance !
  if (distFront > 0 && distFront <= MAX_ENEMY_DISTANCE) {
    attack();
  } 
  // 2. L'ennemi essaie de nous contourner par la gauche -> On pivote rapidement à gauche
  else if (distLeft > 0 && distLeft <= MAX_ENEMY_DISTANCE) {
    spinLeft();
    delay(150); // Petit ajustement pour se réaligner face à lui
  } 
  // 3. L'ennemi essaie de nous contourner par la droite -> On pivote rapidement à droite
  else if (distRight > 0 && distRight <= MAX_ENEMY_DISTANCE) {
    spinRight();
    delay(150);
  } 
  // 4. L'ennemi est derrière nous -> Manœuvre de contre-attaque rapide !
  else if (distBack > 0 && distBack <= MAX_ENEMY_DISTANCE) {
    spinRight();
    delay(350); // Demi-tour complet pour faire face à l'adversaire
  } 
  // 5. Aucun ennemi en vue -> Rotation lente pour balayer l'arène
  else {
    searchPattern();
  }
}

// --- FONCTIONS DE PILOTAGE DES MOTEURS ---

void moveForward() {
  digitalWrite(MOTOR_LEFT_A, HIGH);  digitalWrite(MOTOR_LEFT_B, LOW);
  digitalWrite(MOTOR_RIGHT_A, HIGH); digitalWrite(MOTOR_RIGHT_B, LOW);
}

void attack() {
  moveForward(); // Foncer à vitesse maximale
}

void moveBackward() {
  digitalWrite(MOTOR_LEFT_A, LOW);  digitalWrite(MOTOR_LEFT_B, HIGH);
  digitalWrite(MOTOR_RIGHT_A, LOW); digitalWrite(MOTOR_RIGHT_B, HIGH);
}

void spinLeft() {
  digitalWrite(MOTOR_LEFT_A, LOW);   digitalWrite(MOTOR_LEFT_B, HIGH);
  digitalWrite(MOTOR_RIGHT_A, HIGH); digitalWrite(MOTOR_RIGHT_B, LOW);
}

void spinRight() {
  digitalWrite(MOTOR_LEFT_A, HIGH);  digitalWrite(MOTOR_LEFT_B, LOW);
  digitalWrite(MOTOR_RIGHT_A, LOW);   digitalWrite(MOTOR_RIGHT_B, HIGH);
}

void searchPattern() {
  // Rotation lente sur un seul moteur pour économiser l'énergie et scanner
  digitalWrite(MOTOR_LEFT_A, HIGH);  digitalWrite(MOTOR_LEFT_B, LOW);
  digitalWrite(MOTOR_RIGHT_A, LOW);   digitalWrite(MOTOR_RIGHT_B, LOW);
}

// --- FONCTION DE LECTURE ULTRASON ---
int readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, SENSOR_TIMEOUT);
  if (duration == 0) return 999; // Pas d'obstacle détecté dans la limite du timeout
  
  return duration * 0.034 / 2;
}
