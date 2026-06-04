bool ShowCollisions = false;


void hShowCollsions() {
	if (Input::pressed(VK_RETURN) and ShowCollisions) {
		ShowCollisions = false;
	}
	else if (Input::pressed(VK_RETURN) and !ShowCollisions) {
		ShowCollisions = true;
	}
}