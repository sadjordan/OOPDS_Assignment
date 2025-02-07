#include "shootingship.h"
using namespace std;

void ShootingShip::kill(int target_x, int target_y) {
    for (int i = 0; i < turn_queue->list_size(); i++) {
        if ((*turn_queue)[i]->get_x() == target_x && (*turn_queue)[i]->get_y() == target_y) {
            // cout << "Pass 1" << endl;
            if ((*turn_queue)[i]->get_lives() == 0) {
                cout << "An enemy ship " << (*turn_queue)[i]->get_type() << ", with the id " << (*turn_queue)[i]->get_id() << " from Team " << (*turn_queue)[i]->get_team() << " was hit!" << endl;
                outputFile << "An enemy ship " << (*turn_queue)[i]->get_type() << ", with the id " << (*turn_queue)[i]->get_id() << " from Team " << (*turn_queue)[i]->get_team() << " was hit!" << endl;
                
                cout << "The enemy ship has no more lives" << endl;
                outputFile << "The enemy ship has no more lives" << endl;
                
                Ship* temp = (*turn_queue)[i];
                // cout << "Pass 1" << endl;
                // cout << temp << endl;
                // cout << (*turn_queue)[i] << endl;
                turn_queue->deleteNode(temp);
                // delete (*turn_queue)[i];
                // cout << "Pass 2" << endl;
                delete temp;
                // cout << "Pass 3" << endl;
                // cin.get();
                game_map[target_x][target_y] = '0';
                symbol_map[target_x][target_y] = NULL;
                break;
            }
            (*turn_queue)[i]->set_status("In Respawn Queue");
            (*turn_queue)[i]->decrement_lives();
            (*turn_queue)[i]->set_x(NULL);
            (*turn_queue)[i]->set_y(NULL);
            // cout << "Pass 2" << endl;
            game_map[target_x][target_y] = '0';
            symbol_map[target_x][target_y] = NULL;
            // cout << "Pass 3" << endl;
            cout << "An enemy ship " << (*turn_queue)[i]->get_type() << ", with the id " << (*turn_queue)[i]->get_id() << " from Team " << (*turn_queue)[i]->get_team() << " was hit!" << endl;
            outputFile << "An enemy ship " << (*turn_queue)[i]->get_type() << ", with the id " << (*turn_queue)[i]->get_id() << " from Team " << (*turn_queue)[i]->get_team() << " was hit!" << endl;
            
            respawn_queue->push_back((*turn_queue)[i]);
            turn_queue->deleteNode((*turn_queue)[i]);
            // cout << "Pass 4" << endl;
            // cout << "Pass 5" << endl;
            // i--;
            break;
        }
    }
}
