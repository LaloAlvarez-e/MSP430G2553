/*
 * Imagenes.h
 *
 *  Created on: 25/04/2016
 *      Author: Lalo
 */

#ifndef IMAGENES_H_
#define IMAGENES_H_



// *************************** Capture image dimensions out of BMP**********
#define BUNKERW     ((unsigned char)Bunker0[18])
#define BUNKERH     ((unsigned char)Bunker0[22])
#define ENEMY30W    ((unsigned char)SmallEnemy30PointA[18])
#define ENEMY30H    ((unsigned char)SmallEnemy30PointA[22])
#define ENEMY20W    ((unsigned char)SmallEnemy20PointA[18])
#define ENEMY20H    ((unsigned char)SmallEnemy20PointA[22])
#define ENEMY10W    ((unsigned char)SmallEnemy10PointA[18])
#define ENEMY10H    ((unsigned char)SmallEnemy10PointA[22])
#define ENEMYBONUSW ((unsigned char)SmallEnemyBonus0[18])
#define ENEMYBONUSH ((unsigned char)SmallEnemyBonus0[22])
#define LASERW      ((unsigned char)Laser0[18])
#define LASERH      ((unsigned char)Laser0[22])
#define MISSILEW    ((unsigned char)Missile0[18])
#define MISSILEH    ((unsigned char)Missile0[22])
#define PLAYERW     ((unsigned char)PlayerShip0[18])
#define PLAYERH     ((unsigned char)PlayerShip0[22])

extern const unsigned char SmallEnemy30PointA[];
extern const unsigned char SmallEnemy30PointB[];
extern const unsigned char SmallEnemy20PointA[];
extern const unsigned char SmallEnemy20PointB[];
extern const unsigned char SmallEnemy10PointA[];
extern const unsigned char SmallEnemy10PointB[];
extern const unsigned char PlayerShip0[];
extern const unsigned char SmallEnemyBonus0[];
extern const unsigned char Bunker0[];
extern const unsigned char Bunker1[];
extern const unsigned char Bunker2[];
extern const unsigned char Bunker3[];
extern const unsigned char BigExplosion0[];
extern const unsigned char BigExplosion1[];
extern const unsigned char SmallExplosion0[];
extern const unsigned char SmallExplosion1[];
extern const unsigned char Missile0[];
extern const unsigned char Missile1[];
extern const unsigned char Missile2[];
extern const unsigned char Laser0[];
extern const unsigned char Laser1[];


#endif /* IMAGENES_H_ */
