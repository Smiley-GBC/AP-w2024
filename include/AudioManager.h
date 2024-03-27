#pragma once
#include <raylib.h>
#include <Singleton.h>
#include <unordered_map>

// Singleton are NOT always good.
// If we do this this makes our program harder to read without any benefit.
struct AudioManager// : public Singleton<AudioManager>
{
	Sound& LoadSound(const char* path)
	{
		// Return the sound if its key is present (meaning its already been loaded)
		if (sounds.find(path) != sounds.end())
			return sounds[path];

		// Otherwise, load and return the sound!
		sounds[path] = ::LoadSound(path);
		return sounds[path];

		// *** Since raylib's LoudSound function signature is *identical* to ours,
		// we must tell c++ that we want raylib's sound function with :: otherwise we enter an infinite loop!
		//sounds[path] = LoadSound(path); <-- what NOT to do!
	}

	// Worry about unloading later
	std::unordered_map<const char*, Sound> sounds;
};

