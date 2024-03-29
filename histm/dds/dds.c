#include "dds.h"

/*  HiSTM Driverlib for AD9850 */


void AD9850_Delay(uint32_t z)
{
    for(;z>0;z--)
    {;}
}

#ifdef DDS_MODE_PARALLEL

/********************************************
AD9850_Reset_Parallel
*********************************************/
void AD9850_Reset_Parallel(void)
{
    AD9850_WCLK_CLR ;
    AD9850_FQUD_CLR ;
    //RST
    AD9850_RST_CLR ;
    AD9850_RST_SET ;
    AD9850_Delay(0xFFFF) ;
    AD9850_RST_CLR ;
}
/********************************************
AD9850_Write_Parallel
*********************************************/
void AD9850_Write_Parallel(uint8_t W0, unsigned long freq)
{
    uint8_t wdata ;
    unsigned long  y=(unsigned long)(4294967295/AD9850_SYSTEM_COLCK) ;
    y *= freq ;
    wdata=W0 ;  //?w0
    GPIO_Write(AD9850_DATA_PORT ,wdata) ;
    AD9850_WCLK_SET ;
    AD9850_WCLK_CLR ;

    wdata=y>>24 ;  //?w1
    GPIO_Write(AD9850_DATA_PORT ,wdata) ;
    AD9850_WCLK_SET ;
    AD9850_WCLK_CLR ;

    wdata=y>>16 ;  //?w2
    GPIO_Write(AD9850_DATA_PORT ,wdata) ;
    AD9850_WCLK_SET ;
    AD9850_WCLK_CLR ;

    wdata=y>>8 ;  //?w3
    GPIO_Write(AD9850_DATA_PORT ,wdata) ;
    AD9850_WCLK_SET ;
    AD9850_WCLK_CLR ;

    wdata=y>>0 ;  //?w4
    GPIO_Write(AD9850_DATA_PORT ,wdata) ;
    AD9850_WCLK_SET ;
    AD9850_WCLK_CLR ;

    AD9850_FQUD_SET ;  //????
    AD9850_Delay(0xFFFF) ;
    AD9850_FQUD_CLR ;
}
#endif /* MODE_PARALLEL */
/*------------------------????-------------------------*/
/*---------------------------------------------------------*/
/*------------------------????-------------------------*/
#ifdef DDS_MODE_SERIAL
/********************************************
????:AD9850_Reset_Sreial
?    ?:????????AD9850
?    ?:?
???  :?
*********************************************/
void AD9850_Reset_Sreial(void)
{
    AD9850_WCLK_CLR ;
    AD9850_FQUD_CLR ;
    //RST??
    AD9850_RST_CLR ;
    AD9850_RST_SET ;
    AD9850_Delay(0xFFFF) ;
    AD9850_RST_CLR ;
    //WCLK??
    AD9850_WCLK_CLR ;
    AD9850_WCLK_SET ;
    AD9850_Delay(0xFFFF) ;
    AD9850_WCLK_CLR ;
    //FQUD??
    AD9850_FQUD_CLR ;
    AD9850_FQUD_SET ;
    AD9850_Delay(0xFFFF) ;
    AD9850_FQUD_CLR ;
}
/********************************************
????:AD9850_Write_Serial
?    ?:???????AD9850???
?    ?:W0 - W0?????
          freq - ???
???  :?
*********************************************/
void AD9850_Write_Serial(uint8_t W0,unsigned long freq)
{
    uint8_t i,wdata ;
    unsigned long  y ;
    y = (unsigned long)268435456.0/AD9850_SYSTEM_COLCK*freq ;
    //y = (unsigned long )AD9850_SYSTEM_COLCK*freq ;
    wdata = y>>0 ;   //?w4
    for(i=0 ;i<8 ;i++)
    {
        if(wdata & 0x01)
          AD9850_DATA_Write_1 ;
        else
          AD9850_DATA_Write_0 ;
        AD9850_WCLK_SET ;
        wdata >>= 1 ;
        AD9850_WCLK_CLR ;
    }
    wdata = y>>8 ;  //?w3
     for(i=0 ;i<8 ;i++)
    {
        if(wdata & 0x01)
          AD9850_DATA_Write_1 ;
        else
          AD9850_DATA_Write_0 ;
        AD9850_WCLK_SET ;
        wdata >>= 1 ;
        AD9850_WCLK_CLR ;
    }
    wdata = y>>16 ;  //?w2
     for(i=0 ;i<8 ;i++)
    {
        if(wdata & 0x01)
          AD9850_DATA_Write_1 ;
        else
          AD9850_DATA_Write_0 ;
        AD9850_WCLK_SET ;
        wdata >>= 1 ;
        AD9850_WCLK_CLR ;
    }
    wdata = y>>24 ;  //?w1
     for(i=0 ;i<8 ;i++)
    {
        if(wdata & 0x01)
          AD9850_DATA_Write_1 ;
        else
          AD9850_DATA_Write_0 ;
        AD9850_WCLK_SET ;
        wdata >>= 1 ;
        AD9850_WCLK_CLR ;
    }
    wdata = W0 ;  //?w0
     for(i=0 ;i<8 ;i++)
    {
        if(wdata & 0x01)
          AD9850_DATA_Write_1 ;
        else
          AD9850_DATA_Write_0 ;
        AD9850_WCLK_SET ;
        wdata >>= 1 ;
        AD9850_WCLK_CLR ;
    }

    AD9850_FQUD_SET ;  //????
    AD9850_Delay(0xFFFF) ;
    AD9850_FQUD_CLR ;
}
#endif /* MODE_SERIAL */
/*------------------------????-------------------------*/
/*---------------------------------------------------------*/
/********************************************
????:Init_AD9834
?    ?:???AD9834
?    ?:?
???  :?
*********************************************/
void Init_AD9850(void)
{
#ifdef DDS_MODE_SERIAL
    GPIO_InitTypeDef GPIO_InitStructure ;
    GPIO_InitStructure.GPIO_Pin = AD9850_WCLK | AD9850_FQUD | AD9850_RST | AD9850_DATA ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(AD9850_CONTROL_PORT ,&GPIO_InitStructure) ;

    AD9850_Reset_Sreial() ;
#endif

#ifdef DDS_MODE_PARALLEL //????
    GPIO_InitTypeDef GPIO_InitStructure ;
    GPIO_InitStructure.GPIO_Pin = AD9850_WCLK | AD9850_FQUD | AD9850_RST ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(AD9850_CONTROL_PORT ,&GPIO_InitStructure) ;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(AD9850_DATA_PORT ,&GPIO_InitStructure) ;

    AD9850_Reset_Parallel() ;
#endif

}

