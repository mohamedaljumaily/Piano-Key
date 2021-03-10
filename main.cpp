#include "mbed.h"
#include "TextLCD.h"
 
// Protoypes
void twinkle();
void jingle();
 
// Digital Input Pins used for buttons
DigitalIn b0(D10);
DigitalIn b1(D8);
DigitalIn b2(D2);
DigitalIn b3(D3);
DigitalIn b4(D4);
DigitalIn b5(D5);
DigitalIn b6(D6);
DigitalIn b7(D7);
 
// Threads used for running buttons concurrently
Thread thread_b0;
Thread thread_b1;
Thread thread_b2;
Thread thread_b3;
Thread thread_b4;
Thread thread_b5;
Thread thread_b6;
Thread thread_b7;
 
// Speaker Output
PwmOut speaker1(D9);
PwmOut speaker2(D11);
 
// count for song selection
int songCount = 0;
 
void PlayNote(float frequency, float duration, float volume)
{
    speaker1.period(1.0/frequency);
    speaker1 = volume;
    wait_ms(duration);
}
 
// Speaker Flags: used for speaker availability
bool speaker1_used = false;
bool speaker2_used = false;
 
// Backlight Potentionmeter for LCD: adjusts contrast
DigitalOut backlight(LED1);
 
// LCD Display
TextLCD display(PA_0,PA_1,PA_4,PB_0,PC_1,PC_0);
 
// Plays Note through Speaker #1
void speaker1_Note(float frequency, char note, DigitalIn buttonUsed)
{
    speaker1_used = true; // sets flag to true indicating speaker is in use
    display.locate(0,1); // place cursor on display on second row, 1st character
    display.printf("%c", note); // print corresponding note being played
    speaker1.period(1.0/frequency);
    speaker1 = 0.5;
    
    // continue to play the frequency until button is not pressed anymore
    while(!buttonUsed)
    {wait(0.2);};
    wait(0.25);
    speaker1 = 0;
    speaker1_used = false; // reset flag
}
 
// Plays Note through Speaker #2
void speaker2_Note(float frequency, char note, DigitalIn buttonUsed)
{
    speaker2_used = true; // sets flag to true indicating speaker is in use
    display.locate(0,1); // place cursor on display on second row, 1st character
    display.printf("%c", note); // print corresponding note being played
    speaker2.period(1.0/frequency);
    speaker2 = 0.5;
    
    // continue to play the frequency until button is not pressed anymore
    while(!buttonUsed)
    {wait(0.2);};
    
    //wait(0.25);
    speaker2 = 0;
    speaker2_used = false; // reset flag
}
 
// Plays Note: A
void thread_button0()
{
    while(1) {
        // if button pressed
        if(!b0) {
            if(!speaker1_used) // speaker #1 available if flag false
                speaker1_Note(440.0, 'A', b0); // play note through speaker #1
            else if(!speaker2_used) // speaker #2 available if flag false
                speaker2_Note(440.0, 'A', b0); // play note through speaker #2
            else // none of the speakers are available
                break;
        }
    }
}
 
// Plays Note: B
void thread_button1()
{
    while(1) {
        if(!b1) {
            if(!speaker1_used) // speaker #1 available if flag false
                speaker1_Note(493.0, 'B', b1); // play note through speaker #1
            else if(!speaker2_used) // speaker #2 available if flag false
                speaker2_Note(493.0, 'B', b1); // play note through speaker #2
            else // none of the speakers are available
                break;
        }
    }
}
 
// Plays Note: C
void thread_button2()
{
    while(1) {
        if(!b2) {
            if(!speaker1_used) // speaker #1 available if flag false
                speaker1_Note(261.0, 'C', b2); // play note through speaker #1
            else if(!speaker2_used) // speaker #2 available if flag false
                speaker2_Note(261.0, 'C', b2); // play note through speaker #2
            else // none of the speakers are available
                break;
        }
    }
}
 
// Plays Note: D
void thread_button3()
{
    while(1) {
        if(!b3) {
            if(!speaker1_used) // speaker #1 available if flag false
                speaker1_Note(294.0, 'D', b3); // play note through speaker #1
            else if(!speaker2_used) // speaker #2 available if flag false
                speaker2_Note(294.0, 'D', b3); // play note through speaker #2
            else // none of the speakers are available
                break;
        }
    }
}
 
// Plays Note: E
void thread_button4()
{
    while(1) {
        if(!b4) {
            //DigitalIn buttonUsed = b4;
            if(!speaker1_used) // speaker #1 available if flag false
                speaker1_Note(329.0, 'E', b4); // play note through speaker #1
            else if(!speaker2_used) // speaker #2 available if flag false
                speaker2_Note(329.0, 'E', b4); // play note through speaker #2
            else // none of the speakers are available
                break;
        }
    }
}
 
// Plays Note: F
void thread_button5()
{
    while(1) {
        if(!b5) {
            if(!speaker1_used) // speaker #1 available if flag false
                speaker1_Note(349.0, 'F', b5); // play note through speaker #1
            else if(!speaker2_used) // speaker #2 available if flag false
                speaker2_Note(349.0, 'F', b5); // play note through speaker #2
            else // none of the speakers are available
                break;
        }
    }
}
 
// Plays Note: G
void thread_button6()
{
    while(1) {
        if(!b6) {
            if(!speaker1_used) // speaker #1 available if flag false
                speaker1_Note(392.0, 'G', b6); // play note through speaker #1
            else if(!speaker2_used) // speaker #2 available if flag false
                speaker2_Note(392.0, 'G', b6); // play note through speaker #2
            else // none of the speakers are available
                break;
        }
    }
}
 
// Plays Song: Twinkle Twinkle Little Star
void thread_button7()
{
    while(1) {
        if(!b7) {
            display.cls(); // clears screen
            display.locate(0,0);
            if(songCount == 0)
            {
                display.printf("Twinkle Twinkle\nLittle Star");
                twinkle(); // play song
                songCount = 1;
            }
            else
            {
                display.printf("Jingle Bells");
                jingle();
                songCount = 0;
            }
        }
    }
}
 
// MAIN FUNCTION
int main()
{
    thread_b0.start(thread_button0);
    thread_b1.start(thread_button1);
    thread_b2.start(thread_button2);
    thread_b3.start(thread_button3);
    thread_b4.start(thread_button4);
    thread_b5.start(thread_button5);
    thread_b6.start(thread_button6);
    thread_b7.start(thread_button7);
    display.cls(); // clears screen
    display.locate(0,0);
    display.printf("Playing Note...");
}
 
 
// Function plays beginning of song, "Twinkle Twinkle Little Star"
void twinkle()
{
    PlayNote(261.0, 250, 0.5); // C
    speaker1 = 0.0;
    wait(0.25);
 
    PlayNote(261.0, 250, 0.5); // C
    speaker1 = 0.0;
    wait(0.25);
 
    PlayNote(392.0, 250, 0.5); // G
    speaker1 = 0.0;
    wait(0.25);
 
    PlayNote(392.0, 250, 0.5); // G
    speaker1 = 0.0;
    wait(0.25);
 
    PlayNote(440.0, 250, 0.5); // A
    speaker1 = 0.0;
    wait(0.25);
 
    PlayNote(440.0, 250, 0.5); // A
    speaker1 = 0.0;
    wait(0.25);
 
    PlayNote(392.0, 500, 0.5); // G
    speaker1 = 0.0;
    wait(0.25);
 
    PlayNote(349.0, 250, 0.5);  // F
    speaker1 = 0.0;
    wait(0.25);
 
    PlayNote(349.0, 250, 0.5);  // F
    speaker1 = 0.0;
    wait(0.25);
 
    PlayNote(329.0, 250, 0.5); // E
    speaker1 = 0.0;
    wait(0.25);
 
    PlayNote(329.0, 250, 0.5); // E
    speaker1 = 0.0;
    wait(0.25);
 
    PlayNote(294.0, 250, 0.5);  // D
    speaker1 = 0.0;
    wait(0.25);
 
    PlayNote(294.0, 250, 0.5);  // D
    speaker1 = 0.0;
    wait(0.25);
 
    PlayNote(261.0, 1000, 0.5); // C
    wait(0.5);
    speaker1 = 0.0;
    display.cls(); // clears screen
    display.locate(0,0);
    display.printf("Playing Note...");
}
 
// Function plays beginning of song, "Jingle Bells"
void jingle()
{
    PlayNote(330.0, 520, 0.5); // e - 2
 
    PlayNote(330.0, 520, 0.5); // e - 2
    
    PlayNote(330.0, 780, 0.5); // e - 3
    
    PlayNote(330.0, 260, 0.0); // rest - 1
    
    PlayNote(330.0, 520, 0.5); // e - 2
    
    PlayNote(330.0, 520, 0.5); // e - 2
    
    PlayNote(330.0, 780, 0.5); // e - 3
    
    PlayNote(330.0, 260, 0.0); // rest - 1
    
    PlayNote(330.0, 520, 0.5); // e - 2
    
    PlayNote(392.0, 520, 0.5); // g - 2
    
    PlayNote(262.0, 780, 0.5); // c - 3
    
    PlayNote(294.0, 260, 0.5); // d - 1
    
    PlayNote(330.0, 1040, 0.5); // e - 4
    
    PlayNote(330.0, 1040, 0.0); // rest - 4
    
    PlayNote(349.0, 520, 0.5); // f - 2
    
    PlayNote(349.0, 520, 0.5); // f - 2
    
    PlayNote(349.0, 780, 0.5); // f - 3
    
    PlayNote(330.0, 0, 0.0); // rest - 0
    
    PlayNote(349.0, 260, 0.5); // f - 1
    
    PlayNote(349.0, 520, 0.5); // f - 2
    
    PlayNote(330.0, 520, 0.5); // e - 2
    
    PlayNote(330.0, 520, 0.5); // e - 2
    
    PlayNote(330.0, 0, 0.0); // rest - 0
    
    PlayNote(330.0, 260, 0.5); // e - 1
    
    PlayNote(330.0, 260, 0.5); // e - 1
    
    PlayNote(392.0, 520, 0.5); // g - 2
    
    PlayNote(392.0, 520, 0.5); // g - 2
    
    PlayNote(349.0, 520, 0.5); // f - 2
    
    PlayNote(294.0, 520, 0.5); // d - 2
    
    PlayNote(262.0, 1040, 0.5); // c - 4
    
    PlayNote(262.0, 1040, 0.0); // c - 4
    
    display.cls(); // clears screen
    display.locate(0,0);
    display.printf("Playing Note...");
}