/* 
 * Sample Ripdraw program on how to put up simple images
 *
 * sampleloader.c
 *
 * Demo program for Ripdraw Display
 * This program will, 
 *   - enable a layer
 *   - load a image (from Ripdraw flash to graphic memory, images must already be loaded int he Ripdraw flash)
 *   - write the image to a layer 
 *   - compose all the layers, which display it on the Ripdraw Display
 *
 * The program will look at the image_list structure for the
 *    - image name
 *    - layer to write it to
 *    - x position
 *    - y positon
 *    - imageid is for storage of imageid from Rd_ImageLoad()
 *    - imagewrite_id is for storage of imagewrite_id from Rd_ImageWrite()
 * 
 */


#include <stdio.h>
#include "../include/ripdraw.h"
#include "../include/sampleloader.h"

#define ENDLIST 0xff	/* End of list flag in layer field */

int main(int argc, char **argv)
{
	int i;
	int ret;
	/* load the image_list with the image name, layer, x position, y positon, imageid and imagewrite id, last two are uninitialzied */
	struct image_object image_list[] =
	{
		{"blue-off",		1,		0,0,		0,0},\
		{"blue-on",		2,		0,150,		0,0},\
		{"gold-button",		3,		0,300,		0,0},\
		{"gray-off",		4,		0,450,		0,0},\
		{"green-off",		5,		150,0,		0,0},\
		{"pink-off",		6,		150,150,	0,0},\
		{"red-off",		7,		150,300,	0,0},\
		{"red-on",		7,		150,450,	0,0},\
		{"button-lrb-blue",	7,		300,0,		0,0},\
		{"button-lrb-green",	7,		300,150,	0,0},\
		{"button-lrb-orange",	7,		300,300,	0,0},\
		{"button-lrb-yellow",	7,		300,450,	0,0},\
		{"blue-off",		1,		450,0,		0,0},\
		{"blue-on",		2,		450,150,	0,0},\
		{"gold-button",		3,		450,300,	0,0},\
		{"gray-off",		4,		450,450,	0,0},\
		{"green-off",		5,		600,0,		0,0},\
		{"pink-off",		6,		600,150,	0,0},\
		{"red-off",		7,		600,300,	0,0},\
		{"red-on",		7,		600,450,	0,0},\
		{"button-lrb-blue",	7,		750,0,		0,0},\
		{"button-lrb-green",	7,		750,150,	0,0},\
		{"button-lrb-orange",	7,		750,300,	0,0},\
		{"button-lrb-yellow",	7,		750,450,	0,0},\
		{"button-lrb-blue",	7,		900,0,		0,0},\
		{"button-lrb-green",	7,		900,150,	0,0},\
		{"button-lrb-orange",	7,		900,300,	0,0},\
		{"button-lrb-yellow",	7,		900,450,	0,0},\
		{"button-lrb-yellow",	7,		900,450,	0,0},\
		{"STOP",ENDLIST,0,0,	0,0}     /* Setting layer = ENDLIST, denotes end of list this must be last entry in list */
	};


	/* RdInterfaceInit()
	 *    Open port on host computer to Ripdraw display
	 *    initialize Ripdraw library by creating a rd_interface handle
	 */
	RD_INTERFACE* rd_interface = RdInterfaceInit("/dev/ttyACM0");

	/* check if verbose is set from command line */
	if (argc > 1)
	{
		rd_interface->verbose = atoi(argv[1]);
		if (rd_interface->verbose < 0)
		{
			rd_interface->verbose = 0;
		}
	}

	/* Issue reset to Ripdraw display */
	ret = Rd_Reset(rd_interface);
	if (ret != STATUS_OK) return ret;

	/* enable layer, load image and write it 
	do this for every element of the list
	stop when element has image_layer = ENDLIST
	*/
	for (i=0; image_list[i].image_layer != ENDLIST; i++)
	{
		ret =enableloadwrite(rd_interface, image_list[i]);
		if (ret != STATUS_OK) return ret;
	}
	
	/* compose all layers to page 1 */
	ret = Rd_ComposeLayersToPage(rd_interface, 1);
	if (ret != STATUS_OK) return ret;

	/* close off the interface */
	ret = RdInterfaceClose(rd_interface);

	printf("\nRet: %d\n", ret);
	printf("Done!\n");
	return 0;
}
