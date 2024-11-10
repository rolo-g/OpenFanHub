/*
 * app.h
 *
 *  Created on: Aug 25, 2024
 *      Author: rolo
 */

#ifndef INC_APP_H_
#define INC_APP_H_

/*
 * app.c
 *
 *  Created on: Aug 25, 2024
 *      Author: rolo
 */

/* Includes *******************************************************************/

/* Functions ******************************************************************/

void initOpenFanHub(void);
void fanDriverLoop(void);
void tUsbLoop(void);
void cdcLoop(void);
void ledLoop();

#endif /* INC_APP_H_ */