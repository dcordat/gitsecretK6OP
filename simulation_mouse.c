#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BTN_RIGHT 2
#define BTN_LEFT 1
#define MOVE_X 3
#define MOVE_Y 4
#define MOVE_Z 5
#define CLOSE_CONNECTION 6





struct mouse_hid_report
{
  unsigned char btcode; // 0xA1
  unsigned char rep_id; 
  unsigned char button; // click 
  int axis_x; // move left/right
  int axis_y; // move up/down
  int axis_z; // wheel
};

/*Global variables*/


int write_file(char* report)
{
  FILE *f = fopen("tmp.txt", "w");
  if (f == NULL)
  {
      printf("Error opening file!\n");
      return -1;
  }


  fprintf(f, "%s", report);

  fclose(f);

  return 0;
}

int init_msg(struct mouse_hid_report* report)
{

  char hex_report[6];
  hex_report[0] = report->btcode;
  hex_report[1] = report->rep_id;
  hex_report[2] = report->button;
  hex_report[3] = report->axis_x;
  hex_report[4] = report->axis_y;
  hex_report[5] = report->axis_z;


  FILE *f = fopen("tmp.txt", "w");
  if (f == NULL)
  {
      printf("Error opening file!\n");
      return -1;
  }

  //fprintf(f, "%s", report);
  fprintf(f,"%x\n",report->btcode);
  fprintf(f,"%x\n",report->rep_id);
  fprintf(f,"%x\n",report->button);
  report->axis_x >= 0 ? fprintf(f,"%x\n",report->axis_x) : fprintf(f,"-%x\n",abs(report->axis_x));
  report->axis_y >= 0 ? fprintf(f,"%x\n",report->axis_y) : fprintf(f,"-%x\n",abs(report->axis_y));
  report->axis_z >= 0 ? fprintf(f,"%x\n",report->axis_z) : fprintf(f,"-%x\n",abs(report->axis_z));
  fclose(f);

  return 0;

}

int send_command(int commande,int value_x, int value_y)
{
   int j;
   struct mouse_hid_report* report = malloc(sizeof(struct mouse_hid_report));
   switch(commande)
   {
      case BTN_RIGHT: 
      case BTN_LEFT:
          report->btcode = 0xA1;
          report->rep_id = 0x02;
          report->button = (commande == BTN_LEFT ? 0x01 : 0x02);
          report->axis_x = value_x;
          report->axis_y = value_y;
          report->axis_z = 0;
      break;
      case MOVE_X:
      case MOVE_Y:
          report->btcode = 0xA1;
          report->rep_id = 0x02;
          report->button = 0;
          //report->axis_x = (commande == MOVE_X ? value : 0);
          //report->axis_y = (commande == MOVE_Y ? value : 0);
          report->axis_x = value_x;
          report->axis_y = value_y;
          report->axis_z = 0;
          
      break;
   }
   
   
   init_msg(report);

   return 0;
}



void menu()
{
    printf("SIMULATION MENU \n");
    printf("----------------------\n");
    printf("1) Move right\n");
    printf("2) Move left\n");
    printf("3) Move up\n");
    printf("4) Move down\n");
    printf("5) Click\n");
    printf("6) Right Click\n");
    printf("7) Quit\n");

    int commande=0;

    send_command(MOVE_X,0x00,0x00);

    int x_position = 0, y_position = 0;


       printf("Enter your command : ");
       scanf("%d",&commande);
       switch(commande)
       {
          case 1 : x_position += 25; send_command(MOVE_X,x_position, y_position);break;
          case 2 : x_position -= 25; send_command(MOVE_X,x_position, y_position);break;
          case 3 : y_position += 25; send_command(MOVE_Y,x_position, y_position);break;
          case 4 : y_position -= 25; send_command(MOVE_Y,x_position, y_position);break;
          case 5 : send_command(BTN_LEFT,x_position,y_position);break;
          case 6 : send_command(BTN_RIGHT,x_position,y_position);break;
          case 7 : printf("GoodBye!");break;
          default : printf("%d is not recognized !\n" , commande);
       }
    

}


int main()
{
  menu();
  return 0;
}
