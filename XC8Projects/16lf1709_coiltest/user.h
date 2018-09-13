/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void LCDWrite(unsigned char data_or_command, unsigned char data);
void gotoXY(int x, int y);
void LCDBitmap(char my_array[]);
void LCDCharacter(char character);
void LCDString(char *characters);
void LCDClear(void);
void LCDInit(void) ;

void InitApp(void);         /* I/O and Peripheral Initialization */
