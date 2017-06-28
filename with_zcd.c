/* This Is A Simple Program To get trigger Pulses From digital Interface Of UTLP Kit & It also
 Provides Option to control Some other appliances via same interface. Remove Experimental
 Section If its Not working
 AUTHORS:
 PRASAD T
 NAVANEETH INDAMATH
 CHINMAYEE L M
 MEGHA KADOLE
 */
#include "macros.h"
#include <ulk.h>
int main(void) PROGRAM_ENTRY;

int main()
{
      unsigned long a = 0;               //Variable To Hold Delay Value
      unsigned long a1,i;
      unsigned long appliance;         //Choice of Appliance
      unsigned int app_status[2]={};  //Variable to Hold Status of Appliance
      char option, cont_opt;
      int zcd=1;

      cont_opt='y';

      //Initialize All Required Modules
      //Initialize GPIO
      ulk_proc_gpio_init();
      //Initialize 7 Segment Display
      ulk_fpga_7seg_led_enable ();

      //=================================================================================================
      //EXPERIMENTAL SECTION BEGINS

      //GPIO INPUT >> PIN NO 10==GPIO>>159
      //Configure Pin 10 as input
      ulk_proc_gpio_set_dir(159,1);
      //EXPRIMENTAL SECTION ENDS
      //=================================================================================================

      //Set Directions of GPIOs as Output
      //PULSES
      ulk_proc_gpio_set_dir(140,0);
      ulk_proc_gpio_set_dir(141,0);

      //Control Signals
      ulk_proc_gpio_set_dir(142,0);
      ulk_proc_gpio_set_dir(143,0);
      ulk_proc_gpio_set_dir(158,0);

      //Set Initial Conditionsfor Trigger signals
      ulk_proc_gpio_set_data_out(140,0);
      ulk_proc_gpio_set_data_out(141,0);

      //Control Signals Set To Zero Initially (OFF All APlliances)
      ulk_proc_gpio_set_data_out(142,0);
      ulk_proc_gpio_set_data_out(143,0);
      ulk_proc_gpio_set_data_out(158,0);


      while(cont_opt=='y')
      {
       ulk_cpanel_printf ("Would you like control Ilumination?");
       ulk_scanf_string(&option);

       //============================================SPEED CONTROL SECTION=================================================================
       if(option=='y')
       {
    	  //speed Control Unit
          ulk_cpanel_printf ("Initialising\n");
	  ulk_cpanel_printf ("Enter Delay in msc\n");
	  ulk_scanf_hex (&a);
	  ulk_cpanel_printf ("Value entered is %lx\n", a);

	  //Display Delay in  7 Seg Display
	  ulk_fpga_7seg_led_write(a);

	  //GPIO Config
	  gpio_init();

	  //ULK GPIO DIRECTION;
	  ulk_proc_gpio_set_dir(140,0);
    ulk_proc_gpio_set_dir(141,0);

	  //LED CONFIG (REMOVED FOR MEMORY SAVING)
	  ulk_proc_led_config(led1-1);
	  ulk_proc_led_config(led2-1);

	  // EXPERIMENTAL SECTION
	  //======================================================================
	  //syntax: int ulk_proc_gpio_get_data_in (uint8 pin, uint8 *datain)
	  //Get Data From pin
	  ulk_proc_gpio_get_data_in (159, *zcd);
	  //Debug message
	  ulk_cpanel_printf ("Waiting For ZCD Roll over\n");
	  while(zcd=='1')
	  {
	    //Wait till Zcd=0
	  ulk_proc_gpio_get_data_in (159, *zcd);
	  if(zcd==0)
	  {
	    break;

	  }
	  }
	  //Debug Message
	  ulk_cpanel_printf ("Loop Exit Notification\n");

          //When zcd = 0 Start Delay Routine
	  //EXPERIMENTAL SECTION ENDS
	  //========================================================================

	  //Loop to Generate Signal

	  for(i=0;i<=1000;i++)
	  {
	  //Set Signal to Zero
	  ulk_proc_gpio_set_data_out(140,0);
	  //ulk_proc_led_drive(led1-1,0);

	  //delay 1
	  ulk_proc_delay (ULK_MSEC(a));
	  //ulk_proc_led_drive(led1-1,1); //on 1st
	  ulk_proc_gpio_set_data_out(140,1);
	  a1=10-a;

	  //10-a ms delay
	  ulk_proc_delay (ULK_MSEC(a1));
	  //ulk_proc_led_drive(led1-1,0); //turn off first led
	  ulk_proc_gpio_set_data_out(140,0);

	  ulk_proc_delay (ULK_MSEC(a));
	  //ulk_proc_led_drive(led2-1,1); //turn on second led
	  ulk_proc_gpio_set_data_out(141,1);

	  ulk_proc_delay (ULK_MSEC(a1));
	  //ulk_proc_led_drive(led2-1,0); //turn off second led
	  ulk_proc_gpio_set_data_out(141,0);
	  }

	  //Signals Disable & Turn Off 7 Segment Display
	  ulk_proc_gpio_set_data_out(141,0);
	  ulk_proc_gpio_set_data_out(140,0);
	  ulk_fpga_7seg_led_disable ();
         }
      //==================================================== APLLIANCE SECTION ==============================================================
        else if (option=='n')
       {
    	  ulk_cpanel_printf ("Other Options\n");
    	  ulk_cpanel_printf ("1 : Turn On Appliance 1\n");
    	  ulk_cpanel_printf ("2 : Turn On Appliance 2\n");
    	  ulk_cpanel_printf ("3 : Turn On Appliance 3\n");
    	  ulk_cpanel_printf ("4 : Read Status of Appliance 1\n");
    	  ulk_cpanel_printf ("5 : Read Status of Appliance 2\n");
    	  ulk_cpanel_printf ("6 : Read Status of Appliance 3\n");
    	  ulk_cpanel_printf ("7 : Turn Off All Appliances\n");
    	  ulk_cpanel_printf ("Enter Appropriate Value\n");

	  //Read Data From ULK Control Panel
    	  ulk_scanf_hex (&appliance);

         //Take Deciscion Based On Input Value
    	  switch(appliance)
    	  {

    	  //TURN ON APPLIANCES
    	  //1
    	  case 1:
          if(app_status[0]==0)
          {

    	  ulk_proc_gpio_set_data_out(142,1);
    	  app_status[0]=1;
    	  ulk_cpanel_printf ("Appliance 1 is has been turned on\n");
          }
          else
          {
          ulk_cpanel_printf ("Appliance 1 is already turned on\n");
          }
          break;

	  //2
    	  case 2:
    	  if(app_status[1]==0)
    	  {

    		  ulk_proc_gpio_set_data_out(143,1);
    		  app_status[1]=1;
    		  ulk_cpanel_printf ("Appliance 2 is has been turned on\n");
    	  }
    	  else
    	  {
    	      ulk_cpanel_printf ("Appliance 2 is already turned on\n");
    	  }
          break;

	  //3
          case 3:
          if(app_status[2]==0)
          {

             ulk_proc_gpio_set_data_out(158,1);
             app_status[2]=1;
             ulk_cpanel_printf ("Appliance 3 is has been turned on\n");
          }
             else
          {
            ulk_cpanel_printf ("Appliance 3 is already turned on\n");
          }
           break;

        //READ STATUS OF APPLIANCES
          case 4:
        	  if(app_status[0]==0)
        	  {
        	   ulk_cpanel_printf ("Appliance 1 status: OFF\n");
        	  }
        	  else
        	  {
        		  ulk_cpanel_printf ("Appliance 1 status: ON\n");
        	  }
        	  break;

          case 5:
              if(app_status[1]==0)
             {
               ulk_cpanel_printf ("Appliance 2 status: OFF\n");
             }
              else
             {
                ulk_cpanel_printf ("Appliance 2 status: ON\n");
             }
              break;

          case 6:
            if(app_status[2]==0)
           {
            ulk_cpanel_printf ("Appliance 3 status: OFF\n");
           }
            else
           {
            ulk_cpanel_printf ("Appliance 3 status: ON\n");
           }
            break;
          case 7:
	    //Turn Off All
        	  //ulk_proc_gpio_set_dir(142,0);
        	  ulk_proc_gpio_set_data_out(142,0);
        	  app_status[0]=0;
        	  //ulk_proc_gpio_set_dir(143,0);
        	  ulk_proc_gpio_set_data_out(143,0);
        	  app_status[1]=0;
        	  //ulk_proc_gpio_set_dir(158,0);
        	  ulk_proc_gpio_set_data_out(158,0);
        	  app_status[2]=0;
        	  ulk_cpanel_printf ("ALL APPLIANCES TURNED OFF\n");
        	  break;
		  //Data Validation
           default:
        	  ulk_cpanel_printf ("ERROR: INVALID ENTRY!!\n");
        	  break;
    	  }
    	  //End Of Switch Statement
       }//End of Else if Section

    	  else
    	  {
    		  ulk_cpanel_printf ("INVALID ENTRY\n");
    	  }
      ulk_cpanel_printf ("Would You Like To Continue?\n");
      ulk_scanf_string(&cont_opt);
      }

      return 0;
}
