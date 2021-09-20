#include "Aplicacion.h"

void SysTick_Handler (void)
{
	DriverTeclado();
	BarridoDisplay();
}
