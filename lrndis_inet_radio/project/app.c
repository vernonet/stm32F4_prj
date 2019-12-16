#include <stdlib.h>
#include <stdio.h>
#include "usbd_rndis_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usb_conf.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lis302dl.h"
#include "lwip/init.h"
#include "lwip/tcp.h"
#include "netif/ethernet.h"
#include "lwip/memp.h"
#include "lwip/netif.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "netif/etharp.h"
#include "time.h"
#include "lwip/priv/tcp_priv.h"
#include "lwip/dns.h"

#include "usb_bsp.h"
#include "mp3dec.h"
#include "Audio.h"
#include "mp3common.h"

__ALIGN_BEGIN
USB_OTG_CORE_HANDLE USB_OTG_dev
__ALIGN_END;

static uint8_t hwaddr[6]  = {0x20,0x89,0x84,0x6A,0x96,00};
static uint8_t ipaddr[4]  = {192, 168, 137, 10};  // {192, 168, 7, 1};
static uint8_t netmask[4] = {255, 255, 255, 0};  
static uint8_t gateway[4] = {192, 168, 137, 1};  //{0, 0, 0, 0};

#define LED_ORANGE LED3
#define LED_GREEN  LED4
#define LED_RED    LED5
#define LED_BLUE   LED6
#define LINK_LED   LED_BLUE

#define MP3DECODE_IS_START  GPIOD->BSRRL  = GPIO_BSRR_BS_0  //
#define MP3DECODE_IS_COMPL  GPIOD->BSRRH  = GPIO_BSRR_BS_0

#define OTHER_WORK_IS_START  GPIOD->BSRRL  = GPIO_BSRR_BS_2
#define OTHER_WORK_IS_COMPL  GPIOD->BSRRH  = GPIO_BSRR_BS_2

#define NUMELEMENTS(x)           (sizeof(x) / sizeof((x)[0]))         //wrong

#define RCC_DMA2_CLK_ENABLE()     do { \
                                        __IO uint32_t tmpreg = 0x00U; \
                                        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN);\
                                        /* Delay after an RCC peripheral clock enabling */ \
                                        tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN);\
                                          } while(0U)




typedef struct {                 //internet  radio stations
	 char     *name;
   uint16_t frame_sze;
	 bool     constant_frame_sze; 
   uint8_t  ipaddr[4];
	 uint16_t port;
	 char     *host;
	 char     *get;
}station;


 const station radio_st[] = {
	  {
	   .name       =  "<SomaFM - The Trip>",         //slow speed from server
     .frame_sze =  0x1a1,
	   .constant_frame_sze = true,
     .ipaddr     =  {173,239,76,149},
		 .port       =  80,
		 .host       =  "ice2.somafm.com",
		 .get        =  "GET /thetrip-128-mp3 HTTP/1.1\r\nHost: ice2.somafm.com\r\nCache-Control: no-cache\r\n\r\n",

		},
 
    {
	   .name       =  "<KissFM>",
     .frame_sze =  0x1a2,      //or 0x1a1
	   .constant_frame_sze = false,
     .ipaddr     =  {195,95,206,14},
		 .port       =  80,
		 .host       =  "online-kissfm2.tavrmedia.ua",
     .get        =  "GET /KissFM_Digital HTTP/1.1\r\nhost: online-kissfm2.tavrmedia.ua\r\nCache-Control: no-cache\r\n\r\n ",
		},
 
    {  
	   .name       =  "<Costa Del Mar - Chillout>",
     .frame_sze =  0x13a,//or 0x139
	   .constant_frame_sze = false,
     .ipaddr     =  {178,32,111,41},
		 .port       =  8020,
		 .host       =  "ip41.ip-178-32-111.eu",
     .get        =  "GET /stream-mp3-Chill_autodj HTTP/1.1\r\nUser-Agent: Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.6) Gecko/20040413 Epiphany/1.2.1\\r\nhost: radio.cdm-radio.com\r\nCache-Control: no-cache\r\n\r\n ",
		},
 
	  {
	   .name       =  "<Rockantenne>",
     .frame_sze =  0x1a2,   //or 0x1a1
		 .constant_frame_sze = false,
     .ipaddr     =  {194,97,151,129},
		 .port       =  80,
		 .host       =  "mp3channels.webradio.de",
     .get        =  "GET /rockantenne HTTP/1.0\r\nHost: mp3channels.webradio.de\r\nUser-Agent: VLC/3.0.8 LibVLC/3.0.8\r\nIcy-MetaData: 0\r\nCache-Control: no-cache\r\n\r\n ",
		},	
	
	  {                           //128kbit  Classic
	   .name       =  "<Venice Classic Radio Italia>",
     .frame_sze =  0x1a1,
		 .constant_frame_sze = true, 
     .ipaddr     =  {174,36,206,197},
		 .port       =  8000,
		 //.host       =  "",
     .get        =  "GET /stream HTTP/1.1\r\nhost: 174.36.206.197\r\nCache-Control: no-cache\r\n\r\n ",
		},
	
		{                        //192kbit  DNB
	   .name       =  "<Different Drumz DnB Radio>",
     .frame_sze =  0x240,
		 .constant_frame_sze = true,
     .ipaddr     =  {37,187,79,93},
		 .port       =  8031,
		 .host       =  "andromeda.shoutca.st",
     .get        =  "GET /stream HTTP/1.1\r\nhost: 37.187.79.93\r\nCache-Control: no-cache\r\n\r\n ",
		},
		
		{                        //128kbit  DNB
	   .name       =  "<www.innersenceradio.com>",
     .frame_sze =  0x1a1,
		 .constant_frame_sze = true,
     .ipaddr     =  {50,7,71,219},
		 .port       =  7201,
		 //.host       =  "ice2.somafm.com",
     .get        =  "GET /stream HTTP/1.1\r\nhost: 50.7.71.219\r\nCache-Control: no-cache\r\n\r\n ",
		},
		{                        //128kbit  
	   .name       =  "<OFFRadio>",
     .frame_sze =  0x1a2,
		 .constant_frame_sze = false,
     .ipaddr     =  {46,28,53,118},
		 .port       =  7062,
//		 .host       =  "",
     .get        =  "GET /stream HTTP/1.1\r\nhost: 46.28.53.118\r\nCache-Control: no-cache\r\n\r\n ",
		},
		{                        //192kbit  
	   .name       =  "<Ambiesphere>",
     .frame_sze =  0x273,
		 .constant_frame_sze = false,
     .ipaddr     =  {139,162,245,57},
		 .port       =  8347,
		 .host       =  "uk5.internet-radio.com",
     .get        =  "GET /stream HTTP/1.1\r\nhost: 139.162.245.57\r\nCache-Control: no-cache\r\n\r\n ",
		}
	};	 
 
 const station * cur_st, *next_st;
 ip_addr_t      station_ip = {0}; 

	
//***********************************************************************		
//                          SETTINGS		
//***********************************************************************			
//#define STATION                innersen_st	
//#define NUM_OF_FRAMES          100  
//#define FRAME_SZE              0x1a2 		//station.frame_sze
#define LOW_TRES               70       //treshold             60
#define HIGH_TRES		           85       //treshold            80
#define NUMSTATIONS            9	
#define AUDIO_VOL              0x8d	
//***********************************************************************		
//                          SETTINGS		
//***********************************************************************			
		
		

//int32_t p_XYZ[3];
unsigned char AudioVol = 0x8b, AudioVol_old = 0x8b;		
bool first=true, buf_full=false, two = false, busy = false, frame_ready = false;
bool stop_recv = false, decode_err = false, dns_found_flag = false; 		
uint32_t num_packet=0;

struct pbuf *temp_p;
struct tcp_pcb *temp_tpcb;		
		
// MP3 Variables            
#define FILE_READ_BUFFER_SIZE (0x7A*0x240)//(0x5B4*40)     //0x80
#define PERCENT               (FILE_READ_BUFFER_SIZE/100)
MP3FrameInfo			mp3FrameInfo;
HMP3Decoder				hMP3Decoder;
unsigned char syncbyte[2];   //3 byte
char					file_read_buffer[FILE_READ_BUFFER_SIZE] __attribute__((section ("BUFF"))) __attribute__ ((aligned (4)));  //main buff
char					temp_read_buffer[0x1200]                __attribute__((section ("BUFF"))) __attribute__ ((aligned (4)));  //temp buff
int32_t      file_read_buffer_poz =0, file_write_buffer_poz =0;
volatile int			bytes_left, temp_bytes_left_old, bytes_left_, temp_bytes_left;
char					*read_ptr, *temp_read_ptr_old, *temp_read_ptr;

uint8_t tgl=0, sigma=0;
char temp[0x2da] __attribute__ ((aligned (4)));
DMA_InitTypeDef dma_buf, dma_buf1, dma_buf2, dma_buf3;
struct pbuf *frame;
uint16_t bytes=0;

bool button_pres = false;

// Private function prototypes
static int AudioCallback(void *context,int buffer);

struct netif netif_data;

struct tcp_pcb *testpcb;

void tcp_setup(void);
err_t tcpRecvCallback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
void dns_found(const char *name, const ip_addr_t *ipaddr, void *arg);
err_t get_station_ip(void);

static uint8_t received[RNDIS_MTU + 14];
static int recvSize = 0;




void on_packet(const char *data, int size)
{
	  DMA2 ->LIFCR |= DMA_LIFCR_CTCIF2; // Clear interrupt flag.
		DMA2_Stream2 ->CR &= ~DMA_SxCR_EN; // Disable DMA stream.
		while (DMA2_Stream2 ->CR & DMA_SxCR_EN ) {}; // Wait for DMA stream to stop.
		DMA2_Stream2->M0AR = (uint32_t)received;     //dst
		DMA2_Stream2->PAR  = (uint32_t)data;         //src
		DMA2_Stream2->NDTR = size;	
    DMA2 ->LIFCR |= DMA_LIFCR_CTCIF2; // clear any pending (old) DMA2 Stream 2 interrupts	
    DMA2_Stream2 ->CR |= DMA_SxCR_TCIE;			
		DMA2_Stream2 ->CR |= DMA_SxCR_EN;
		//while (DMA2_Stream2->NDTR != 0) {}	
    recvSize = size;
	  if (buf_full) STM_EVAL_LEDOff(LINK_LED);
			 else STM_EVAL_LEDToggle(LINK_LED);
}


void usb_polling()
{
	  if (frame_ready)       //send last frame transmited over DMA
    {
			  ethernet_input(frame, &netif_data);
        pbuf_free(frame);
		    frame_ready = false;
        return;
    }
	
    if (recvSize == 0) 
    {
        return;
    }
    frame = pbuf_alloc(PBUF_RAW, recvSize, PBUF_POOL);
    if (frame == NULL) 
    {
        return;
    }
		while (DMA2_Stream2->NDTR != 0) {}	  // wait while on_packet exec
//		DMA2 ->LIFCR |= DMA_LIFCR_CTCIF1; // Clear interrupt flag.
//		NVIC_ClearPendingIRQ (DMA2_Stream1_IRQn); 			
		DMA2_Stream1 ->CR &= ~DMA_SxCR_EN; // Disable DMA stream.
		while (DMA2_Stream1 ->CR & DMA_SxCR_EN ) {}
		; // Wait for DMA stream to stop.
		DMA2_Stream1->M0AR = (uint32_t)frame->payload;     //dst
		DMA2_Stream1->PAR  = (uint32_t)received; //src
		DMA2_Stream1->NDTR = recvSize;	
    DMA2_Stream1 ->CR |= DMA_SxCR_TCIE;	 			
		DMA2_Stream1 ->CR |= DMA_SxCR_EN;
//		while (DMA2_Stream1->NDTR != 0) {}	  // wait while data transfer		
    frame->len = recvSize;
    recvSize = 0;
}

void frame_polling() {
	
	if (frame_ready) {
//		frame->len = recvSize;
//    recvSize = 0;
    ethernet_input(frame, &netif_data);
    pbuf_free(frame);
		frame_ready = false;
	}  
}

static int outputs = 0;

err_t output_fn(struct netif *netif, struct pbuf *p, const ip_addr_t *ipaddr)
{
    return etharp_output(netif, p, ipaddr);
}

err_t linkoutput_fn(struct netif *netif, struct pbuf *p)
{
    int i;
    struct pbuf *q;
    static char data[RNDIS_MTU + 14 + 4];
	  volatile uint32_t time;
    int size = 0;
    for (i = 0; i < 200; i++)
    {
        if (rndis_can_send()) break;
//        msleep(1);
			  time=0xffff;
			  while(time-->1) {}// {__asm("nop");}			  
    }
    for(q = p; q != NULL; q = q->next)
    {
        if (size + q->len > RNDIS_MTU + 14)
            return ERR_ARG;
        memcpy(data + size, (char *)q->payload, q->len);
        size += q->len;
    }
    if (!rndis_can_send())
        return ERR_USE;
    rndis_send(data, size);
    outputs++;
    return ERR_OK;
}

err_t netif_init_cb(struct netif *netif)
{
    LWIP_ASSERT("netif != NULL", (netif != NULL));
    netif->mtu = RNDIS_MTU;
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP | NETIF_FLAG_UP;
    netif->state = NULL;
    netif->name[0] = 'E';
    netif->name[1] = 'X';
    netif->linkoutput = linkoutput_fn;
    netif->output = output_fn;
    return ERR_OK;
}

#define PADDR(ptr) ((ip_addr_t *)ptr)

void init_lwip()
{
    struct netif  *netif = &netif_data;

    lwip_init();
    netif->hwaddr_len = 6;
    memcpy(netif->hwaddr, hwaddr, 6);

    netif = netif_add(netif, PADDR(ipaddr), PADDR(netmask), PADDR(gateway), NULL, netif_init_cb, ip_input);
    netif_set_default(netif);
}

void init_periph(void)
{
	  GPIO_InitTypeDef  GPIO_InitStructure;
	
    static LIS302DL_InitTypeDef accInit =
    {
        LIS302DL_LOWPOWERMODE_ACTIVE,
        LIS302DL_DATARATE_100,
        LIS302DL_XYZ_ENABLE,
        LIS302DL_FULLSCALE_2_3,
        LIS302DL_SELFTEST_NORMAL
    };

    time_init();
		
		//NVIC_SetPriority (SysTick_IRQn, 0);   //////////////////////////////////
		
    USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &usbd_rndis_cb, &USR_cb);
    rndis_rxproc = on_packet;
    STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
    STM_EVAL_LEDInit(LED_ORANGE);
    STM_EVAL_LEDInit(LED_GREEN);
    STM_EVAL_LEDInit(LED_RED);
    STM_EVAL_LEDInit(LED_BLUE);
    LIS302DL_Init(&accInit);
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

		/* Configure the oscil pin */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
}




void _InitializeAudio(unsigned int frek){
	switch(frek)
			{
			case 8000: InitializeAudio(Audio8000HzSettings);
					break;
			case 16000: InitializeAudio(Audio16000HzSettings);
					break;
			case 22050: InitializeAudio(Audio22050HzSettings);
					break;
			case 44100: InitializeAudio(Audio44100HzSettings);
					break;
			case 48000: InitializeAudio(Audio48000HzSettings);
					break;
			default:    InitializeAudio(Audio44100HzSettings);
			}   
}			

/*
 * Called by the audio driver when it is time to provide data to
 * one of the audio buffers (while the other buffer is sent to the
 * CODEC using DMA). One mp3 frame is decoded at a time and
 * provided to the audio driver.
 */
static int  AudioCallback(void *context, int buffer) {
	static int16_t audio_buffer0[0x1000];  // __attribute__((section ("BUFF")));
	static int16_t audio_buffer1[0x1000];  // __attribute__((section ("BUFF")));

	int offset, err;
	int outOfData = 0;

	int16_t *samples;
	
	if (tgl++>3) {
	    STM_EVAL_LEDOn(LED3);
	    tgl=0; 
	}
	if (buffer) {
		samples = audio_buffer0;
	} else {
		samples = audio_buffer1;
	}
	
	offset = MP3FindSyncWord((unsigned char*)temp_read_ptr, temp_bytes_left);
	temp_bytes_left -= offset;
	temp_read_ptr += offset;
	
  temp_bytes_left_old = temp_bytes_left;
	temp_read_ptr_old   = temp_read_ptr;
	
	
	UsrLog("\n\r   AudClb: wr_poz %04x rd_poz %04x bytes_left %04x ", file_write_buffer_poz, file_read_buffer_poz, bytes_left);
	
	if (stop_recv) {
	volatile int32_t delta = file_write_buffer_poz-file_read_buffer_poz;
	if (delta<0) {delta = FILE_READ_BUFFER_SIZE+delta;}
	UsrLog(" delta %d", delta/PERCENT);
		 if (delta/PERCENT<LOW_TRES)   {
				stop_recv=false;
				tcp_recved(testpcb, 0xB68);//0xB68
				UsrLog("\n\r TCP Window Update");
		 }			
	}
	
	UsrLog(" MP3Dec ERR ");

	err = MP3Decode(hMP3Decoder, (unsigned char**)&temp_read_ptr, (int*)&temp_bytes_left, samples, 0);
	STM_EVAL_LEDOff(LED3);
	if (!syncbyte[0] && !err && (temp_bytes_left_old-temp_bytes_left) == cur_st->frame_sze) {  //find the third byte in the header of frame
		syncbyte[0] = *(temp_read_ptr_old+2);
		if (!cur_st->constant_frame_sze) syncbyte[1] = syncbyte[0] - 2;
	}
	

	if (!err) UsrLog("%d ", err);


	if (0) {  //if (err) 
		/* error occurred */
		

		switch (err) {
		case ERR_MP3_INDATA_UNDERFLOW:
			outOfData = 1;
			break;
		case ERR_MP3_MAINDATA_UNDERFLOW:
			/* do nothing - next call to decode will provide more mainData */
			break;
		case ERR_MP3_FREE_BITRATE_SYNC:
		default:
			outOfData = 1;
			break;
		}
	} else {
		// no error
		MP3GetLastFrameInfo(hMP3Decoder, &mp3FrameInfo);

		// Duplicate data in case of mono to maintain playback speed
		if (mp3FrameInfo.nChans == 1) {
			for(int i = mp3FrameInfo.outputSamps;i >= 0;i--) 	{
				samples[2 * i]=samples[i];
				samples[2 * i + 1]=samples[i];
			}
			mp3FrameInfo.outputSamps *= 2;
		}
	}

	if (!outOfData) {
		ProvideAudioBuffer(samples, mp3FrameInfo.outputSamps);
	}


	if (temp_bytes_left < cur_st->frame_sze-1)  { 
		  uint16_t len, tmp_sze = sizeof temp_read_buffer - temp_bytes_left;
		  uint32_t dst, src;
		  memmove(temp_read_buffer, &temp_read_buffer[tmp_sze], temp_bytes_left); 
		  if (tmp_sze <= FILE_READ_BUFFER_SIZE-file_read_buffer_poz) {
		      //memcpy(&temp_read_buffer[temp_bytes_left], read_ptr, tmp_sze);
				  dst = (uint32_t)&temp_read_buffer[temp_bytes_left];
				  src = (uint32_t)read_ptr;
				  len = tmp_sze;
				  file_read_buffer_poz += tmp_sze; 
			}
			 else {
				  memcpy(&temp_read_buffer[temp_bytes_left], read_ptr, FILE_READ_BUFFER_SIZE-file_read_buffer_poz);
				  //memcpy(&temp_read_buffer[temp_bytes_left+(FILE_READ_BUFFER_SIZE-file_read_buffer_poz)], file_read_buffer, tmp_sze-(FILE_READ_BUFFER_SIZE-file_read_buffer_poz));
				  dst = (uint32_t)&temp_read_buffer[temp_bytes_left+(FILE_READ_BUFFER_SIZE-file_read_buffer_poz)];
				  src = (uint32_t)&file_read_buffer[0];
				  len = tmp_sze-(FILE_READ_BUFFER_SIZE-file_read_buffer_poz);
				  file_read_buffer_poz = tmp_sze-(FILE_READ_BUFFER_SIZE-file_read_buffer_poz);
			 }
		  
      //memcpy replace
      DMA2 ->LIFCR |= DMA_LIFCR_CTCIF3; // Clear interrupt flag.
			DMA2_Stream3 ->CR &= ~DMA_SxCR_EN; // Disable DMA stream.
			while (DMA2_Stream3 ->CR & DMA_SxCR_EN ) {}
			; // Wait for DMA stream to stop.
			DMA2_Stream3->M0AR = dst;     //dst
			DMA2_Stream3->PAR  = src;                       //src  
			DMA2_Stream3->NDTR = len;	
			DMA2_Stream3 ->CR |= DMA_SxCR_TCIE;	
			DMA2_Stream3 ->CR |= DMA_SxCR_EN;			

      read_ptr = &file_read_buffer[0] + file_read_buffer_poz ;
			temp_read_ptr = temp_read_buffer;					
			temp_bytes_left = sizeof temp_read_buffer;				
	}
	
		if (err && err != ERR_MP3_MAINDATA_UNDERFLOW) {
		 UsrLog("%d ", err);
	   temp_read_ptr+= (cur_st->frame_sze-1); temp_bytes_left-=(cur_st->frame_sze-1);
		 if  (temp_read_ptr >= &temp_read_buffer[0] + sizeof temp_read_buffer) {
			 temp_read_ptr = &temp_read_buffer[0];
			 temp_bytes_left = sizeof temp_read_buffer;
		 }
	}
	
	return outOfData;
	
}

//-----------------------------------debug------------------------------------

volatile int ITM_RxBuffer = ITM_RXBUFFER_EMPTY;       /* used for Debug Input */
struct __FILE {int handle;/* Add whatever you need here */};

FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f)
{
  ITM_SendChar(ch);
  return(ch);
}

int fgetc( FILE *f) {                /* blocking */
  while (ITM_CheckChar() != 1);
  return (ITM_ReceiveChar());
}
//-----------------------------------debug------------------------------------

uint32_t tcp_send_packet(void)
{
	  err_t error;
	  uint32_t len = strlen(cur_st->get);

    /* push to buffer */
        error = tcp_write(testpcb, cur_st->get, len, TCP_WRITE_FLAG_COPY);

    if (error) {
        UsrLog("ERROR: Code: %d (tcp_send_packet :: tcp_write)\n", error);
        return 1;
    }

    /* now send */
    error = tcp_output(testpcb);
    if (error) {
        UsrLog("ERROR: Code: %d (tcp_send_packet :: tcp_output)\n", error);
        return 1;
    }
    return 0;
}


err_t tcpRecvCallback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
//	  uint16_t bytes=0;
	  uint16_t sigma=0;
	  bytes=0; 
	  //int offset;
	
    UsrLog("\n\rData recieved,  ERR -> %d\n", err);
    if (p == NULL) {
			  if (tpcb->flags & TF_FIN)  UsrLog("\n\rFinal packet!\n");
			  UsrLog(" ---------------------------------------\n");
        UsrLog("| The remote host closed the connection.|\n");
			  UsrLog(" ---------------------------------------");
        return ERR_ABRT;
    } else {
        UsrLog("Number of pbufs %d", pbuf_clen(p));
			  UsrLog("  len %04d  tot_len %04d num_pack %04d", p->len, p->tot_len, num_packet);
        if (num_packet<1) {  
					 UsrLog("Contents of pbuf %s\n", (char *)p->payload);
					 bytes = p->len; 
				}
				  else {
						//bytes=0;
						temp_p = p;
						temp_tpcb = tpcb;
						UsrLog(" write_poz %04x ", file_write_buffer_poz);
						if (1) {//if (!(buf_full))
							  if (stop_recv) {
									 UsrLog("\n\r TCP ZeroWindow  delta %x ", file_read_buffer_poz-file_write_buffer_poz);
								}
                while (DMA2_Stream0->NDTR != 0) {}	  // wait while  last transfer												 							
								if (file_write_buffer_poz + p->len > FILE_READ_BUFFER_SIZE) {  // last packet in buffer 								
									  uint32_t temp_bytes = FILE_READ_BUFFER_SIZE - file_write_buffer_poz ;								
										memcpy(&file_read_buffer[0]+file_write_buffer_poz, (char *)p->payload, temp_bytes);  //+5
										bytes = 	p->len - temp_bytes;
									  sigma = p->len - bytes;	
										file_write_buffer_poz = 0;
									 }				  									
									 else {
                         bytes = p->len;
                         //printf("\n\r bytes %03x ", bytes); 										 
									 }
									  
								    if (buf_full)  { //if (cur_st != &radio_st[0] && buf_full)
											volatile int32_t delta = file_write_buffer_poz-file_read_buffer_poz;
											if (delta<0) delta=FILE_READ_BUFFER_SIZE+delta;
											if (!stop_recv ) {  //(!stop_recv && cur_st != &radio_st[0]) {
												 if (delta/PERCENT>HIGH_TRES)  stop_recv=true;  
											}								
			             }			
								
								//memcpy(&file_read_buffer[0]+file_write_buffer_poz, (char *)p->payload, bytes);	 
								STM_EVAL_LEDOn(LED4);	 	 
								if (1) {   //if (!buf_full) {
									
											//memcpy(&file_read_buffer[0]+file_write_buffer_poz, (char *)p->payload, bytes);
											DMA2 ->LIFCR |= DMA_LIFCR_CTCIF0; // Clear interrupt flag.
											DMA2_Stream0 ->CR &= ~DMA_SxCR_EN; // Disable DMA stream.
											while (DMA2_Stream0 ->CR & DMA_SxCR_EN ) {}
											; // Wait for DMA stream to stop.
											DMA2_Stream0->M0AR = (uint32_t)&file_read_buffer[0]+file_write_buffer_poz;     //dst
											DMA2_Stream0->PAR  = (uint32_t)(char *)p->payload+sigma;                       //src  (char *)p->payload+sigma;
											DMA2_Stream0->NDTR = bytes;	
											//DMA_Cmd(DMA2_Stream0, ENABLE);
											DMA2_Stream0 ->CR |= DMA_SxCR_TCIE;	
											DMA2_Stream0 ->CR |= DMA_SxCR_EN;										
								}

								uint16_t temp_cnt;
                if (cur_st == &radio_st[0]) temp_cnt = 0x2200;  //1200
								    else temp_cnt = 30*cur_st->frame_sze;
								if (file_write_buffer_poz > FILE_READ_BUFFER_SIZE-temp_cnt)  { //0x1200  0x6000
									 buf_full=true;  //0x600
								}							
					}
				}
				
				if (tpcb->flags & TF_ACK_NOW)  {
					UsrLog("\n\rFinal packet!\n");
				}

				if (!stop_recv) tcp_recved(tpcb, p->tot_len);   //send ack   bytes   p->len
				   else tcp_recved(tpcb, 0);
				num_packet++;
				//pbuf_free(p);


				
    }

    return 0;
}

err_t connectCallback(void *arg, struct tcp_pcb *tpcb, err_t err)
{
	  if(err == ERR_OK) {
    UsrLog("\n\rConnection Established.\n");
    UsrLog("\n\rNow sending a packet\n");
    tcp_send_packet();
    return 0;
		}
		return err;
		
}

void dns_found(const char *name, const ip_addr_t *ipaddr, void *arg)

{
 LWIP_UNUSED_ARG(arg);
 printf("  next_st_host %s: %s\n", name, ipaddr ? ip_ntoa(ipaddr) : "<not found>");
 if ((ipaddr) && (ipaddr->addr)) {	
   station_ip = *ipaddr;	
   dns_found_flag = true;
 }	 
}

err_t get_station_ip(void){
	ip_addr_t ip;
	
	switch(dns_gethostbyname(next_st->host, &ip, dns_found, NULL)){
  case ERR_OK:
    // numeric or cached, returned in resolved
    station_ip = ip;
    dns_found_flag = true;
    return ERR_OK;
  case ERR_INPROGRESS:
    // need to ask, will return data via callback
    dns_found_flag = false;
    return ERR_INPROGRESS;
  default:
    // bad arguments in function call
   return ERR_ARG;
  }
}	


void tcp_setup(void)
{
    uint32_t data = 0xdeadbeef;
	  err_t error;

    /* create an ip */
//    ip_addr_t ip;
	
    if (!dns_found_flag) IP4_ADDR(&station_ip, cur_st->ipaddr[0],cur_st->ipaddr[1],cur_st->ipaddr[2],cur_st->ipaddr[3]);     

    /* create the control block */
    testpcb = tcp_new();    //testpcb is a global struct tcp_pcb
                            // as defined by lwIP

    /* dummy data to pass to callbacks*/

    tcp_arg(testpcb, &data);

    /* register callbacks with the pcb */

    tcp_err(testpcb, NULL);
    tcp_recv(testpcb, tcpRecvCallback);
    tcp_sent(testpcb, NULL);

    /* now connect */
    error = tcp_connect(testpcb, &station_ip, cur_st->port, connectCallback);  //tcp_connect(testpcb, &ip, cur_st->port, connectCallback)
		if (error != ERR_OK)  {UsrLog ("connect ERROR"); while(1){};}
		dns_found_flag = false;	

}

void dma_cfg (void) {
	
		RCC_DMA2_CLK_ENABLE();
		 
		dma_buf.DMA_Channel = DMA_Channel_0;
		dma_buf.DMA_Memory0BaseAddr = (uint32_t)received;
		dma_buf.DMA_PeripheralBaseAddr = (uint32_t)(file_read_buffer); //
		dma_buf.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		dma_buf.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
		dma_buf.DMA_DIR = DMA_DIR_MemoryToMemory;
		dma_buf.DMA_Mode = DMA_Mode_Normal;
		dma_buf.DMA_MemoryInc = DMA_MemoryInc_Enable;
		dma_buf.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
		//dma_buf.DMA_BufferSize = sizeof received;
		dma_buf.DMA_Priority = DMA_Priority_Low;
		dma_buf.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		dma_buf.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		dma_buf.DMA_FIFOMode = DMA_FIFOMode_Enable;
		 
		DMA_Init(DMA2_Stream0, &dma_buf);
		//DMA_Cmd(DMA2_Stream0, DISABLE);
	  NVIC_SetPriority(DMA2_Stream0_IRQn, 12);
		NVIC_EnableIRQ (DMA2_Stream0_IRQn); 	
			
		dma_buf1.DMA_Channel = DMA_Channel_0;
		dma_buf1.DMA_Memory0BaseAddr = (uint32_t)received;
		dma_buf1.DMA_PeripheralBaseAddr = (uint32_t)(temp); //
		dma_buf1.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		dma_buf1.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
		dma_buf1.DMA_DIR = DMA_DIR_MemoryToMemory;
		dma_buf1.DMA_Mode = DMA_Mode_Normal;
		dma_buf1.DMA_MemoryInc = DMA_MemoryInc_Enable;
		dma_buf1.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
		//dma_buf1.DMA_BufferSize = sizeof received;
		dma_buf1.DMA_Priority = DMA_Priority_Medium;
		dma_buf1.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		dma_buf1.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		dma_buf1.DMA_FIFOMode = DMA_FIFOMode_Enable;
		 
		DMA_Init(DMA2_Stream1, &dma_buf1);
    NVIC_SetPriority(DMA2_Stream1_IRQn, 11);		
		NVIC_EnableIRQ (DMA2_Stream1_IRQn); 


		dma_buf2.DMA_Channel = DMA_Channel_0;
		dma_buf2.DMA_Memory0BaseAddr = (uint32_t)received;
		dma_buf2.DMA_PeripheralBaseAddr = (uint32_t)(temp); //
		dma_buf2.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		dma_buf2.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
		dma_buf2.DMA_DIR = DMA_DIR_MemoryToMemory;
		dma_buf2.DMA_Mode = DMA_Mode_Normal;
		dma_buf2.DMA_MemoryInc = DMA_MemoryInc_Enable;
		dma_buf2.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
		//dma_buf1.DMA_BufferSize = sizeof received;
		dma_buf2.DMA_Priority = DMA_Priority_High;
		dma_buf2.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		dma_buf2.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		dma_buf2.DMA_FIFOMode = DMA_FIFOMode_Enable;
		 
		DMA_Init(DMA2_Stream2, &dma_buf2);
		NVIC_SetPriority(DMA2_Stream2_IRQn, 10);
		NVIC_EnableIRQ (DMA2_Stream2_IRQn); 
		
		
		dma_buf3.DMA_Channel = DMA_Channel_0;
		dma_buf3.DMA_Memory0BaseAddr = (uint32_t)received;
		dma_buf3.DMA_PeripheralBaseAddr = (uint32_t)(temp); //
		dma_buf3.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		dma_buf3.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
		dma_buf3.DMA_DIR = DMA_DIR_MemoryToMemory;
		dma_buf3.DMA_Mode = DMA_Mode_Normal;
		dma_buf3.DMA_MemoryInc = DMA_MemoryInc_Enable;
		dma_buf3.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
		//dma_buf1.DMA_BufferSize = sizeof received;
		dma_buf3.DMA_Priority = DMA_Priority_High;
		dma_buf3.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		dma_buf3.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		dma_buf3.DMA_FIFOMode = DMA_FIFOMode_Enable;
		 
		DMA_Init(DMA2_Stream3, &dma_buf3);
//		NVIC_SetPriority(DMA2_Stream3_IRQn, 10);
//		NVIC_EnableIRQ (DMA2_Stream3_IRQn); 

}


void DMA2_Stream2_IRQHandler (void)          //end of copy on_packet
{
	  DMA2 ->LIFCR |= DMA_LIFCR_CTCIF2; // Clear interrupt flag.
	  NVIC_ClearPendingIRQ (DMA2_Stream2_IRQn); 		
}

void DMA2_Stream1_IRQHandler (void)
{
	  DMA2 ->LIFCR |= DMA_LIFCR_CTCIF1; // Clear interrupt flag.
	  NVIC_ClearPendingIRQ (DMA2_Stream1_IRQn); 		
	  frame_ready = true;
}


void DMA2_Stream0_IRQHandler (void)              //end of copy on tcpRecvCallback
{

	  DMA2 ->LIFCR |= DMA_LIFCR_CTCIF0; // Clear interrupt flag.
	  NVIC_ClearPendingIRQ (DMA2_Stream0_IRQn); 		
	
	  file_write_buffer_poz += bytes;
	  if (file_write_buffer_poz >= FILE_READ_BUFFER_SIZE)  file_write_buffer_poz = 0;
	  STM_EVAL_LEDOff(LED4);
}


int main(void)
{
	 int16_t temp_buffer[0x3c0];  //to STACK
	 int test, offs;
	 uint8_t station_id;
		
    init_periph();	
	  dma_cfg ();	
	  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);  
    init_lwip();
    while (!netif_is_up(&netif_data)) {__asm("nop");}
		USB_OTG_BSP_mDelay(10);	
    dns_init();		
//	  while(1){
//	  if ((STM_EVAL_PBGetState(BUTTON_USER)) == 1) {break;}
//		USB_OTG_BSP_mDelay(10);
//	  }

		UsrLog("\033[2J");                           //clear screen
    station_id = 0 ;
		cur_st  =  &radio_st[station_id];
		next_st =  &radio_st[station_id+1];
		USB_OTG_BSP_mDelay(6000);
		printf("\n Connect to - ");
		printf("%s",cur_st->name);
		//printf("\n\r");
		temp_bytes_left = sizeof temp_read_buffer;
		file_write_buffer_poz = 0;
		
		//IP4_ADDR(&station_ip, cur_st->ipaddr[0],cur_st->ipaddr[1],cur_st->ipaddr[2],cur_st->ipaddr[3]);
		tcp_setup();

		
    while (1)
    {
        usb_polling();     /* usb device polling */
				if (buf_full && first) { 
					  first = false;				
					  hMP3Decoder = MP3InitDecoder();		
						InitializeAudio(Audio44100HzSettings);
						SetAudioVolume(0);
					  memcpy(temp_read_buffer, file_read_buffer, sizeof temp_read_buffer);
						//read_ptr = file_read_buffer;
					  temp_read_ptr = &temp_read_buffer[0];
					  file_read_buffer_poz = sizeof temp_read_buffer;
					  //read_ptr_old = file_read_buffer;
					  temp_bytes_left = sizeof temp_read_buffer;
					  //bytes_left_old = FILE_READ_BUFFER_SIZE;
						test = sizeof temp_buffer;
						offs = MP3FindSyncWord((unsigned char*)temp_read_ptr, test);
						temp_read_ptr += offs;
						MP3Decode(hMP3Decoder, (unsigned char**)&temp_read_ptr, (int*)&test, &temp_buffer[0], 0); //detect samplerate 
						StopAudio();
					  read_ptr = &file_read_buffer[sizeof temp_read_buffer];
					  file_read_buffer_poz = sizeof temp_read_buffer;
					  temp_read_ptr = &temp_read_buffer[0];
						MP3GetLastFrameInfo(hMP3Decoder, &mp3FrameInfo);
						_InitializeAudio(((MP3DecInfo *)hMP3Decoder)->samprate);  
					  //printf("\n\r");
						printf(" (%iHz", ((MP3DecInfo *)hMP3Decoder)->samprate);  
						printf("  %ikbps)", ((MP3DecInfo *)hMP3Decoder)->bitrate/1000); 										
						printf("\n\r");
						AudioVol = AUDIO_VOL;
						//AudioVol_old = AudioVol;
						SetAudioVolume(AudioVol);  //0xAF  0x8a  0x9c
						//__disable_irq();
						PlayAudioWithCallback(AudioCallback, 0);	
            
            //dns_found_flag = false;
				    if (next_st->host == NULL || get_station_ip() == ERR_ARG)	{
			        IP4_ADDR(&station_ip, next_st->ipaddr[0],next_st->ipaddr[1],next_st->ipaddr[2],next_st->ipaddr[3]); 
					    dns_found_flag = true;
		        }						
				}
				
	      if (button_pres) {                //next station		 
					 StopAudioDMA();
					 // Re-initialize and set volume to avoid noise
					 InitializeAudio(Audio44100HzSettings);
					 SetAudioVolume(0);
					 buf_full = 0;
					 first = 1;
					 stop_recv = false;
					 station_id++;
					 if (station_id>NUMSTATIONS-1) station_id=0;
					 cur_st  =  &radio_st[station_id];	
					 next_st = 	(station_id == NUMSTATIONS-1) ? &radio_st[0] : &radio_st[station_id+1];
					 syncbyte[0] = 0;//
					 syncbyte[1] = 0;
					 printf("\n\r Connect to - ");
					 printf("%s",cur_st->name);
					 temp_bytes_left = sizeof temp_read_buffer;
					 file_write_buffer_poz = 0;		
					 num_packet = 0;	 
					 tcp_setup();			 
					 button_pres = false;			 
		    }
				
				

     
//		if ((sequen & 0x7) == 0x7) {
//		sequen = 0;	
//    BSP_ACCELERO_GetXYZ(&p_XYZ[0]);
//		if ((p_XYZ[0]> 200) && (AudioVol<0xB0)) AudioVol ++;  //sound volume
//		if ((p_XYZ[0]<-200) && (AudioVol>0x50)) AudioVol --;
//    if (AudioVol_old != AudioVol)		SetAudioVolume(AudioVol);
//	  AudioVol_old = AudioVol; 
//		}
//		UsrLog(" p_XYZ[0] %x ",p_XYZ[0] );   
     	
    }
}
