// Workshop 8 - Smart Pointers

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
        for (size_t i = 0; i < allProfiles.size(); ++i) {
            const Profile& currentProfile = allProfiles[i];

            // Check if the current profile is not in bannedProfiles
            bool isBanned = false;
            for (size_t j = 0; j < bannedProfiles.size(); ++j) {
                if (currentProfile.m_name.first_name == bannedProfiles[j].m_name.first_name &&
                    currentProfile.m_name.last_name == bannedProfiles[j].m_name.last_name &&
                    currentProfile.m_age == bannedProfiles[j].m_age) {
                    isBanned = true;
                    break;
                }
            }

            // If the current profile is not banned, add a validated copy to the result
            if (!isBanned) {
                unique_ptr<Profile> validatedProfile = make_unique<Profile>(currentProfile.m_name, currentProfile.m_address, currentProfile.m_age);

                try {
                    validatedProfile->validateAddress();
                    result += validatedProfile.get(); // Add the validated profile to the result
                    validatedProfile.release(); // Release ownership of the pointer after adding it
                }
                catch (const std::exception& e) {
                    // Handle validation error
                    cerr << "Validation error for profile: " << currentProfile << ". Error: " << e.what() << endl;
                }
            }
        }
		return result;
	}
}
