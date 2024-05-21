#ifndef ARYANA_KEYPAD_H
#define ARYANA_KEYPAD_H

/*
 ArrayCharacters[16] = {'1', '2', '3', 'A',
                                    '4', '5', '6', 'B',
                                    '7', '8', '9', 'C',
                                    '*', '0', '#', 'D'};
*/

class aryana_keyPad
{
public:
    aryana_keyPad(char myport = 'C', int row0 = 0, int row1 = 1, int row2 = 2, int row3 = 3, int col0 = 4, int col1 = 5, int col2 = 6, int col3 = 7);

    char getPressedKey(void);

private:
    int IsPressedFlag; // is Any key pressd ?
    int PressedRow;
    int PressedCol;
    int PortX_Value[16];
    int RowsValue[4]; // value of KeyPad_row1Pin ~ KeyPad_row4Pin
    char  ArrayCharacters[16];

    char port;
    int row0Pin;
    int row1Pin;
    int row2Pin;
    int row3Pin;
    int col0Pin;
    int col1Pin;
    int col2Pin;
    int col3Pin;

    int getIsPressedFlag(void);
    void Initialize(void);
    void ResetPins(void);
    int Listen_toKeyPad(void);
    void rowColFinder(void);
};

#endif
