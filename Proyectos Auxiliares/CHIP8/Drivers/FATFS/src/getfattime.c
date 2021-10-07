#include "main.h"

uint32_t get_fattime(void)
{

  RTC_DateTypeDef sDate;
  HAL_RTC_GetDate(&hrtc,&sDate, RTC_FORMAT_BIN);
	uint32_t dia = sDate.Date;
	uint32_t mes = sDate.Month;
	uint32_t anio = sDate.Year;

	return ((anio - 1980) << 25) | (mes << 21) | (dia << 16);
}
