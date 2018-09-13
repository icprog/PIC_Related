#include "../lib/include/pic24_all.h"
#include "t6963c.h"
    

int main()
{
    int row,col,i,j;
    UCHAR ch = 0x40;
    row = col = 0;
    configClock();
    configHeartbeat();
    configDefaultUART(DEFAULT_BAUDRATE);
    outString("testing...\n");
    t6963c_init();
    outString("\n");

    for(i = 0x40;i < 0x46;i++)
    {
    DELAY_MS(20);
    j = 0;
    do
    {
        ch = t6963c_StatusRead();
        outUint8NoLeader(ch);
        outChar(0x20);
        j++;
    }while(((ch & 0x03) != 0x03) && j < 20);
    outUint8NoLeader(ch);
    outString("\n");

    j = 0;
    t6963c_set_address(0,i);
    do
    {
        ch = t6963c_StatusRead();
        outUint8NoLeader(ch);
        outChar(0x20);
        j++;
    }while(((ch & 0x03) != 0x03) && j < 20);
    outUint8NoLeader(ch);
    outString("\n");


    j = 0;
    t6963c_writeByte(0,i);
    do
    {
        ch = t6963c_StatusRead();
        outUint8NoLeader(ch);
        outChar(0x20);
        j++;
    }while(((ch & 0x03) != 0x03) && j < 20);
    outUint8NoLeader(ch);
    outString("\n");


#if 0
    DELAY_MS(20);
    t6963c_writeByte(0,0x42);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);

    DELAY_MS(20);
    t6963c_set_address(0,1);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);

    DELAY_MS(20);
    t6963c_writeByte(0,0x43);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);

    DELAY_MS(20);
    t6963c_set_address(0,2);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);

    DELAY_MS(20);
    t6963c_writeByte(0,0x44);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);

    DELAY_MS(20);
    t6963c_set_address(0,3);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);

    DELAY_MS(20);
    t6963c_writeByte(0,0x45);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);

    DELAY_MS(20);
    t6963c_set_address(0,4);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);

    DELAY_MS(20);
    t6963c_writeByte(0,0x46);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);

    DELAY_MS(20);
    t6963c_set_address(0,5);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);

    DELAY_MS(20);
    t6963c_writeByte(0,0x47);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);

    DELAY_MS(20);
    t6963c_set_address(0,6);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);

    DELAY_MS(20);
    t6963c_writeByte(0,0x48);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);

    DELAY_MS(20);
    t6963c_set_address(0,7);
    ch = t6963c_StatusRead();
    outUint8NoLeader(ch);
    outChar(0x20);
#endif
    outString("\n");
    }
    return 0;
//    t6963c_writeString("Hello Wolrd!");
    DELAY_MS(2);
    t6963c_set_address(1,2);
    outChar(0x43);
//    DELAY_MS(2);
//    t6963c_writeByte(0,0x43);
//    t6963c_writeString("This is the 2nd row.");
    DELAY_MS(2);
    outChar(0x44);
    outString("done");
    return 0;   
    for(row = 0;row < 16;row++)
        for(col = 0;col < 40;col++)
        {
//            t6963c_writeString(&ch);
            t6963c_startAutoWrite();
            t6963c_autoWriteChar(ch);
            t6963c_stopAutoWrite();
            t6963c_set_address(row,col);
            if(++ch > 0x7e)
                ch = 0x20;
            DELAY_MS(200);
         }
   return 0;
}
