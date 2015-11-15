#include "World/World.h"

int main(void)
{
	World w;
	w.build();
	w.camera_ptr->render_scene(w);
	return 0;
}