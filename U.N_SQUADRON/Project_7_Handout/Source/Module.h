#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

struct Collider;

class Module
{
private:
	bool enabled = true;
public:

	//Called at the beginning of the application execution
	virtual bool Init();

	//Called when the module is activated
	//By now we will consider all modules to be permanently active
	virtual bool Start();

	//Called at the beginning of each application loop
	virtual update_status PreUpdate();

	//Called at the middle of each application loop
	virtual update_status Update();

	//Called at the end of each application loop
	virtual update_status PostUpdate();

	//Called at the end of the application
	virtual bool CleanUp();

	//Called when two colliders are intersecting
	//and the module is registered as the listener

	virtual void OnCollision(Collider* c1, Collider* c2);

	// Switches isEnabled and calls Start() method
	void Enable();

	// Switches isEnabled and calls CleanUp() method
	void Disable();

	inline bool IsEnabled() const { return enabled; }
};

#endif // __MODULE_H__