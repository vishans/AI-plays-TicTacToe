#include "Header.h"
#include <iostream>
int main()
{
    Board myGame;
    Human me(1);
    Machine ai(2);
    myGame.swap_player_characters();
    myGame.switchANSIcolorOutput();
    

    int count = 2;  //controls turn of each player and at the beginning specifies who starts i.e who plays first
                    //in this case, player with symbol 2 goes first i.e the Machine will play first.

    while (true) {
        //
        printf("There are %d empty slots\n\n", myGame.helper_count());

        if (count == 1) {
            myGame.showBoard();

            me.promptMove(myGame);
       
        }
        else {
            std::cout << "AI playing..." << std::endl;
            tuple f = ai.smartMove(myGame,false,-10,10,-1);
            //std::cout << f.move << std::endl;
            myGame.Modify(f.move, 2);
            myGame.showBoard();

        }


        int verdict = myGame.check();

        if (verdict != 0) {
            myGame.showBoard();

            std::cout << myGame.encode(verdict) << " wins!" << std::endl;
            break;
        }

        if (myGame.isGameFull() && verdict == 0) {
            std::cout << "\nIt's a draw" << std::endl;
            break;
        }

        count = count % 2 + 1;

   }



   


}

