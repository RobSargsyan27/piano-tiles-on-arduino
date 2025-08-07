#include <util/delay.h>
#include <usart.h>
#include <display.h>

int main()
{
    initUSART();
    initDisplay();
    while ( 1 )
    {
        for ( int i = 0; i < 4; i++ )
        {
            writeNumberToSegment( i, i );
            _delay_ms( 1000 );
        }

        writeNumber( "0027" );
        _delay_ms( 1000 );
        for ( int i = 0; i < 10000; i ++ )
        {
            writeNumber( "0027" );
        }
        writeNumberAndWait( 2002, 10000 );
    }
}