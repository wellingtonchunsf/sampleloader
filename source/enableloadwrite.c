/* 
 * enableloadwrite()
 * 
 * 
 * 
 */
#include "../include/ripdraw.h"
#include "../include/sampleloader.h"

int layerstatus[8] = 
{
	OFF, \
	OFF, \
	OFF, \
	OFF, \
	OFF, \
	OFF, \
	OFF, \
	OFF \
};

int enableloadwrite(RD_INTERFACE* rd_interface, struct image_object local)
{
	extern int layerstatus[];
	int ret;
	int id_image;
	int id_imagewrite;

	/* Enable layer based on incoming image object, check if layer is already enabled, if so don't enable */
	if (layerstatus[local.image_layer] == OFF )
	{
		printf("\nEnable Layer %d", local.image_layer);
	        layerstatus[local.image_layer] = ON;		/* set status to layer on */ 
		ret = Rd_SetLayerEnable(rd_interface, local.image_layer, RD_TRUE); /* enable layer only once for each layer */
		if (ret != STATUS_OK) return ret;
	}

	/* Load image based on incoming image object  */
	printf("\nLoading image %s", local.image_name);
	ret = Rd_ImageLoad(rd_interface, local.image_name, &id_image);
	if (ret != STATUS_OK) return ret;
	local.image_id = id_image;   /* store image_id from Rd_ImageLoad backinto object*/


	/* Write the image based on the incoming image object */
	printf("\nImagewrite");
	ret = Rd_ImageWrite(rd_interface,local.image_layer,id_image, Rd_Position(local.image_x, local.image_y), &id_imagewrite);
	if (ret != STATUS_OK) return ret;
	local.image_write_id = id_imagewrite;   /* store image_id from Rd_ImageLoad backinto object*/

	return ret;
};
