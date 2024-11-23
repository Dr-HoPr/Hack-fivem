#include "esp.h"
#include <thread>
#include <chrono>
static std::string get_weapon_name(DWORD hash)
	{
static auto dagger = std::string("dagger");
static auto bat = std::string("bat");
static auto bottle = std::string("bottle");
static auto crowbar = std::string("crowbar");
static auto unarmed = std::string("unarmed");
static auto flashlight = std::string("flashlight");
static auto golfclub = std::string("golfclub");
static auto hammer = std::string("hammer");
static auto hatchet = std::string("hatchet");
static auto knuckle = std::string("knuckle");
static auto knife = std::string("knife");
static auto machete = std::string("machete");
static auto switchblade = std::string("switchblade");
static auto nightstick = std::string("nightstick");
static auto wrench = std::string("wrench");
static auto battleaxe = std::string("battleaxe");
static auto poolcue = std::string("poolcue");
static auto pistol = std::string("pistol");
static auto pistolmk2 = std::string("pistol_mk2");
static auto combatpistol = std::string("combatpistol");
static auto appistol = std::string("appistol");
static auto stungun = std::string("stungun");
static auto pistol50 = std::string("pistol50");
static auto snspistol = std::string("snspistol");
static auto snspistolmk2 = std::string("snspistol_mk2");
static auto heavypistol = std::string("heavypistol");
static auto vintagepistol = std::string("vintagepistol");
static auto flaregun = std::string("flaregun");
static auto marksmanpistol = std::string("marksmanpistol");
static auto revolver = std::string("revolver");
static auto revolvermk2 = std::string("revolver_mk2");
static auto doubleaction = std::string("doubleaction");
static auto microsmg = std::string("microsmg");
static auto smg = std::string("smg");
static auto smgmk2 = std::string("smg_mk2");
static auto assaultsmg = std::string("assaultsmg");
static auto combatpdw = std::string("combatpdw");
static auto machinepistol = std::string("machinepistol");
static auto minismg = std::string("minismg");
static auto pumpshotgun = std::string("pumpshotgun");
static auto pumpshotgun_mk2 = std::string("pumpshotgun_mk2");
static auto sawnoffshotgun = std::string("sawnoffshotgun");
static auto assaultshotgun = std::string("assaultshotgun");
static auto bullpupshotgun = std::string("bullpupshotgun");
static auto musket = std::string("musket");
static auto heavyshotgun = std::string("heavyshotgun");
static auto dbshotgun = std::string("dbshotgun");
static auto autoshotgun = std::string("autoshotgun");
static auto assaultrifle = std::string("assaultrifle");
static auto assaultrifle_mk2 = std::string("assaultrifle_mk2");
static auto carbinerifle = std::string("carbinerifle");
static auto carbinerifle_mk2 = std::string("carbinerifle_mk2");
static auto advancedrifle = std::string("advancedrifle");
static auto specialcarbine = std::string("specialcarbine");
static auto specialcarbine_mk2 = std::string("specialcarbine_mk2");
static auto bullpuprifle = std::string("bullpuprifle");
static auto bullpuprifle_mk2 = std::string("bullpuprifle_mk2");
static auto compactrifle = std::string("compactrifle");
static auto machine_gun = std::string("machine_gun");
static auto combatmg = std::string("combatmg");
static auto combatmg_mk2 = std::string("combatmg_mk2");
static auto gusenberg = std::string("gusenberg");
static auto sniperrifle = std::string("sniperrifle");
static auto heavysniper = std::string("heavysniper");
static auto heavysniper_mk2 = std::string("heavysniper_mk2");
static auto marksmanrifle = std::string("marksmanrifle");
static auto marksmanrifle_mk2 = std::string("marksmanrifle_mk2");
static auto rpg = std::string("rpg");
static auto grenadelauncher = std::string("grenadelauncher");
static auto grenadelauncher_smoke = std::string("grenadelauncher_smoke");
static auto minigun = std::string("minigun");
static auto firework = std::string("firework");
static auto railgun = std::string("railgun");
static auto hominglauncher = std::string("hominglauncher");
static auto compactlauncher = std::string("compactlauncher");
static auto grenade = std::string("grenade");
static auto bzgas = std::string("bzgas");
static auto smokegrenade = std::string("smokegrenade");
static auto flare = std::string("flare");
static auto molotov = std::string("molotov");
static auto stickybomb = std::string("stickybomb");
static auto proxmine = std::string("proxmine");
static auto snowball = std::string("snowball");
static auto pipebomb = std::string("pipebomb");
static auto ball = std::string("ball");
static auto petrolcan = std::string("petrolcan");
static auto fireextinguisher = std::string("fireextinguisher");
static auto parachute = std::string("parachute");
		switch (hash)
		{
		case 0x92A27487:
			return dagger; break;
		case 0x958A4A8F:
			return bat; break;
		case 0xF9E6AA4B:
			return bottle; break;
		case 0x84BD7BFD:
			return crowbar; break;
		case 0xA2719263:
			return unarmed; break;
		case 0x8BB05FD7:
			return flashlight; break;
		case 0x440E4788:
			return golfclub; break;
		case 0x4E875F73:
			return hammer; break;
		case 0xF9DCBF2D:
			return hatchet; break;
		case 0xD8DF3C3C:
			return knuckle; break;
		case 0x99B507EA:
			return knife; break;
		case 0xDD5DF8D9:
			return machete; break;
		case 0xDFE37640:
			return switchblade; break;
		case 0x678B81B1:
			return nightstick; break;
		case 0x19044EE0:
			return wrench; break;
		case 0xCD274149:
			return battleaxe; break;
		case 0x94117305:
			return poolcue; break;
		case 0x1B06D571:
			return pistol; break;
		case 0xBFE256D4:
			return pistolmk2; break;
		case 0x5EF9FEC4:
			return combatpistol; break;
		case 0x22D8FE39:
			return appistol; break;
		case 0x3656C8C1:
			return stungun; break;
		case 0x99AEEB3B:
			return pistol50; break;
		case 0xBFD21232:
			return snspistol; break;
		case 0x88374054:
			return snspistolmk2; break;
		case 0xD205520E:
			return heavypistol; break;
		case 0x83839C4:
			return vintagepistol; break;
		case 0x47757124:
			return flaregun; break;
		case 0xDC4DB296:
			return marksmanpistol; break;
		case 0xC1B3C3D1:
			return revolver; break;
		case 0xCB96392F:
			return revolvermk2; break;
		case 0x97EA20B8:
			return doubleaction; break;
		case 0x13532244:
			return microsmg; break;
		case 0x2BE6766B:
			return smg; break;
		case 0x78A97CD0:
			return smgmk2; break;
		case 0xEFE7E2DF:
			return assaultsmg; break;
		case 0xA3D4D34:
			return combatpdw; break;
		case 0xDB1AA450:
			return machinepistol; break;
		case 0xBD248B55:
			return minismg; break;
		case 0x1D073A89:
			return pumpshotgun; break;
		case 0x555AF99A:
			return pumpshotgun_mk2; break;
		case 0x7846A318:
			return sawnoffshotgun; break;
		case 0xE284C527:
			return assaultshotgun; break;
		case 0x9D61E50F:
			return bullpupshotgun; break;
		case 0xA89CB99E:
			return musket; break;
		case 0x3AABBBAA:
			return heavyshotgun; break;
		case 0xEF951FBB:
			return dbshotgun; break;
		case 0x12E82D3D:
			return autoshotgun; break;
		case 0xBFEFFF6D:
			return assaultrifle; break;
		case 0x394F415C:
			return assaultrifle_mk2; break;
		case 0x83BF0278:
			return carbinerifle; break;
		case 0xFAD1F1C9:
			return carbinerifle_mk2; break;
		case 0xAF113F99:
			return advancedrifle; break;
		case 0xC0A3098D:
			return specialcarbine; break;
		case 0x969C3D67:
			return specialcarbine_mk2; break;
		case 0x7F229F94:
			return bullpuprifle; break;
		case 0x84D6FAFD:
			return bullpuprifle_mk2; break;
		case 0x624FE830:
			return compactrifle; break;
		case 0x9D07F764:
			return machine_gun; break;
		case 0x7FD62962:
			return combatmg; break;
		case 0xDBBD7280:
			return combatmg_mk2; break;
		case 0x61012683:
			return gusenberg; break;
		case 0x5FC3C11:
			return sniperrifle; break;
		case 0xC472FE2:
			return heavysniper; break;
		case 0xA914799:
			return heavysniper_mk2; break;
		case 0xC734385A:
			return marksmanrifle; break;
		case 0x6A6C02E0:
			return marksmanrifle_mk2; break;
		case 0xB1CA77B1:
			return rpg; break;
		case 0xA284510B:
			return grenadelauncher; break;
		case 0x4DD2DC56:
			return grenadelauncher_smoke; break;
		case 0x42BF8A85:
			return minigun; break;
		case 0x7F7497E5:
			return firework; break;
		case 0x6D544C99:
			return railgun; break;
		case 0x63AB0442:
			return hominglauncher; break;
		case 0x781FE4A:
			return compactlauncher; break;
		case 0x93E220BD:
			return grenade; break;
		case 0xA0973D5E:
			return bzgas; break;
		case 0xFDBC8A50:
			return smokegrenade; break;
		case 0x497FACC3:
			return flare; break;
		case 0x24B17070:
			return molotov; break;
		case 0x2C3731D9:
			return stickybomb; break;
		case 0xAB564B93:
			return proxmine; break;
		case 0x787F0BB:
			return snowball; break;
		case 0xBA45E8B8:
			return pipebomb; break;
		case 0x23C9F95C:
			return ball; break;
		case 0x34A67B97:
			return petrolcan; break;
		case 0x60EC506:
			return fireextinguisher; break;
		case 0xFBAB5776:
			return parachute; break;
		default:
			return unarmed; break;
		}
}

i_esp& i_esp::esp()
{
	static i_esp ins;
	return ins;
}

bool i_esp::IsOnScreen(D3DXVECTOR2 coords)
{
	const float displayWidth = ImGui::GetIO().DisplaySize.x;
	const float displayHeight = ImGui::GetIO().DisplaySize.y;

	return !(coords.x < 0.1f || coords.y < 0.1f || coords.x > displayWidth || coords.y > displayHeight);
}



void i_esp::draw_skeleton(uintptr_t ped_base) {
	int bone_positions[][2] = {
		{ 0, 7 },
		{ 7, 6 },
		{ 7, 5 },
		{ 7, 8 },
		{ 8, 3 },
		{ 8, 4 }
	};
	for (int i = 0; i < 6; ++i) {
		D3DXVECTOR2 screen_1, screen_2;
		auto bone_1 = i_sdk::sdk().get_bone_position(ped_base, bone_positions[i][0]),
			bone_2 = i_sdk::sdk().get_bone_position(ped_base, bone_positions[i][1]);
		if (bone_1 != D3DXVECTOR3(0, 0, 0) && bone_2 != D3DXVECTOR3(0, 0, 0) && ((screen_1 = i_sdk::sdk().world_to_screen(bone_1)) != D3DXVECTOR2(0, 0)) && ((screen_2 = i_sdk::sdk().world_to_screen(bone_2)) != D3DXVECTOR2(0, 0))) {
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(screen_1.x, screen_1.y), ImVec2(screen_2.x, screen_2.y), colorespon, 1);
		}
	}
}


void i_esp::esp_init()
{

	uintptr_t ClosestPlayer = 0;
	uintptr_t ReplayInterface = i_dupa::skid().i_replay;
	uintptr_t localplayer = i_dupa::skid().i_localplayer;
		if (crosshair)
		{
		float center_x = ImGui::GetIO().DisplaySize.x / 2.f;
		float center_y = ImGui::GetIO().DisplaySize.y / 2.f;
		ImVec2 lineStart(center_x - 6, center_y);
		ImVec2 lineEnd(center_x + 7, center_y);
		ImVec2 lineStartVertical(center_x, center_y - 6);
		ImVec2 lineEndVertical(center_x, center_y + 7);
		ImU32 lineColor = IM_COL32(255, 255, 255, 255);

		ImGui::GetForegroundDrawList()->AddLine(lineStart, lineEnd, lineColor);
		ImGui::GetForegroundDrawList()->AddLine(lineStartVertical, lineEndVertical, lineColor);
		}
	if (ReplayInterface)
	{
		uintptr_t PedReplayInterface = i_memory::reeq().Read<DWORD64>(ReplayInterface + 0x18);
		uintptr_t PedList = i_memory::reeq().Read<DWORD64>(PedReplayInterface + 0x100);
		int entitylist = i_memory::reeq().Read<int>(PedReplayInterface + 0x108);

		for (int i = 0U; i < entitylist; i++)
		{
			if (!PedList) continue;

			uintptr_t Ped = i_memory::reeq().Read<uintptr_t>(PedList + (i * 0x10));
			if (!Ped) continue;

			if (Ped == localplayer) continue;

			if (ignoreped)
			{
				if (!i_memory::reeq().Read<uintptr_t>(Ped + i_dupa::skid().playerinfo))
					continue;
			}


			float HealthPed = i_memory::reeq().Read<float>(Ped + 0x280);
			float ArmorPed = i_memory::reeq().Read<float>(Ped + i_dupa::skid().armoroffset);

			if (ignoredead)
			{
				if (HealthPed == 0)
					continue;
			}





			D3DXVECTOR3 GetCordLocal = i_memory::reeq().Read<D3DXVECTOR3>(localplayer + 0x90);
			D3DXVECTOR3 GetCordPed = i_memory::reeq().Read<D3DXVECTOR3>(Ped + 0x90);
			D3DXVECTOR3 DistanceCalculation = (GetCordLocal - GetCordPed);

			auto bone_pos = i_sdk::sdk().get_bone_position(Ped, 0);
			auto RightFoot = i_sdk::sdk().get_bone_position(Ped, 4);
			auto LeftFoot = i_sdk::sdk().get_bone_position(Ped, 3);
			auto Pelvis_ = i_sdk::sdk().get_bone_position(Ped, 5);
			auto bone_pos3 = i_sdk::sdk().get_bone_position(Ped, 7);
			D3DXVECTOR2 screen = i_sdk::sdk().world_to_screen(bone_pos);
			if (!IsOnScreen(screen)) continue;
			D3DXVECTOR2 screen2 = i_sdk::sdk().world_to_screen(RightFoot);
			if (!IsOnScreen(screen2)) continue;
			D3DXVECTOR2 screen4 = i_sdk::sdk().world_to_screen(LeftFoot);
			if (!IsOnScreen(screen4)) continue;
			D3DXVECTOR2 screen3 = i_sdk::sdk().world_to_screen(bone_pos3);
			if (!IsOnScreen(screen3)) continue;
			D3DXVECTOR2 Pelvis = i_sdk::sdk().world_to_screen(Pelvis_);
			if (!IsOnScreen(Pelvis)) continue;


			float Foot_Middle = (screen4.y + screen2.y) / 2.f;
			float Height = abs(screen.y - Foot_Middle) * 1.35f;
			float Width = (Height / 1.75f);
			float HealthDistance = Width / 16;


			uint64_t PedModelInfo = i_memory::reeq().Read<uint64_t>(Ped + 0x20);
			D3DXVECTOR3 mins = i_memory::reeq().Read<D3DXVECTOR3>(PedModelInfo + 0x30);
			D3DXVECTOR3 maxs = i_memory::reeq().Read<D3DXVECTOR3>(PedModelInfo + 0x40);
			D3DXVECTOR2 Ped_Location = i_sdk::sdk().world_to_screen(GetCordPed);
			double Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);

			if (fixedesp)
			{


				D3DXVECTOR3 min = (GetCordPed + mins);
				D3DXVECTOR3 max = (GetCordPed + maxs);
				D3DXVECTOR3 points[] = {
						D3DXVECTOR3(min.x, min.y, min.z),
						D3DXVECTOR3(min.x, max.y, min.z),
						D3DXVECTOR3(max.x, max.y, min.z),
						D3DXVECTOR3(max.x, min.y, min.z),
						D3DXVECTOR3(max.x, max.y, max.z),
						D3DXVECTOR3(min.x, max.y, max.z),
						D3DXVECTOR3(min.x, min.y, max.z),
						D3DXVECTOR3(max.x, min.y, max.z)
				};

				D3DXVECTOR2 w2s_points[8];
				auto index = 0;
				for (D3DXVECTOR3 point : points) {
					w2s_points[index] = i_sdk::sdk().world_to_screen(point);
					if (w2s_points[index].x == 0.f && w2s_points[index].y == 0.f)
						continue;
					index++;
				}

				float x = w2s_points[0].x;
				float y = w2s_points[0].y;
				float width = w2s_points[0].x;
				float height = w2s_points[0].y;
				for (auto point : w2s_points) {
					if (x > point.x)
						x = point.x;
					if (width < point.x)
						width = point.x;
					if (y > point.y)
						y = point.y;
					if (height < point.y)
						height = point.y;
				}

				int out_x = x;
				int out_y = y;
				int out_w = width - x;
				int out_h = height - y;
				Height = out_h;
				Width = out_w;

				Width = (Height / 1.75f);
				if (((Ped_Location.x + Width / 2) - (Ped_Location.x - Width / 2)) > 600)
					continue;
			}
			if (Distance <= distanceint)
			{
				auto color = ImColor(255, 255, 255);
				uint64_t playerinfos = i_memory::reeq().Read<uint64_t>(Ped + i_dupa::skid().playerinfo);
				int playeridaddr = i_memory::reeq().Read<int>(playerinfos + 0x88);
				std::string playeridstr = std::to_string(playeridaddr);
				auto it = std::find(i_esp::esp().friends.begin(), i_esp::esp().friends.end(), playeridstr);
				if (it != i_esp::esp().friends.end())
					color = ImColor(0, 255, 0);
				else
					color = ImColor(255, 255, 255);

				std::string str = "";

				if (it != i_esp::esp().friends.end())
				{
					i_overlay::here().DrawOutlinedText(ImGui::GetFont(), "Friend", ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 18), 15.0f, ImColor(0, 0, 0), true);
					i_overlay::here().DrawOutlinedText(ImGui::GetFont(), "Friend", ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 19), 15.0f, ImColor(0, 255, 0), true);
					i_overlay::here().DrawOutlinedText(ImGui::GetFont(), "Friend", ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 18), 15.0f, ImColor(0, 0, 0), true);
					i_overlay::here().DrawOutlinedText(ImGui::GetFont(), "Friend", ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 19), 15.0f, ImColor(0, 255, 0), true);

				}




				if (distance) {

					int Ddistance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);

					std::string strr = " | " + std::to_string(Ddistance) + " m";
						strr = "[ " + std::to_string(Ddistance) + " m " + " ]";
					str.append(strr);

					uint64_t playerinfos = i_memory::reeq().Read<uint64_t>(Ped + i_dupa::skid().playerinfo);
					int playeridaddr = i_memory::reeq().Read<int>(playerinfos + 0x88);
					std::string playeridstr = "ID: " + std::to_string(playeridaddr);

				}
				if (distance)
				{

					//i_overlay::here().DrawOutlinedText(ImGui::GetFont(), str, ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 5), 15.0f, ImColor(255, 255, 255), true);
					std::string combinedStr = "ID: " + playeridstr + " - " + str;
					float yOffset = -4.0f; // Ajusta este valor según sea necesario para mover el texto más arriba

					i_overlay::here().DrawOutlinedText(ImGui::GetFont(), combinedStr.c_str(), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 11 + yOffset), 15.0f, ImColor(0, 0, 0), true);
					i_overlay::here().DrawOutlinedText(ImGui::GetFont(), combinedStr.c_str(), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 12 + yOffset), 15.0f, ImColor(255, 255, 255), true);
					i_overlay::here().DrawOutlinedText(ImGui::GetFont(), combinedStr.c_str(), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 11 + yOffset), 15.0f, ImColor(0, 0, 0), true);
					i_overlay::here().DrawOutlinedText(ImGui::GetFont(), combinedStr.c_str(), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 12 + yOffset), 15.0f, ImColor(255, 255, 255), true);
				}
				if (box)
				{
					// Ajusta el margen de la caja con respecto al personaje
					float boxMargin = 5.0f;

					ImVec2 topLeft(Ped_Location.x - Width / 2 + boxMargin, Ped_Location.y - Height / 2 + boxMargin);
					ImVec2 bottomRight(Ped_Location.x + Width / 2 - boxMargin, Ped_Location.y + Height / 2 - boxMargin);

					// Dibuja las líneas del contorno de la caja
					float cornerSize = 10.0f; // Tamaño de la esquina de la caja

					ImGui::GetForegroundDrawList()->AddLine(ImVec2(topLeft.x, topLeft.y), ImVec2(topLeft.x + cornerSize, topLeft.y), colorespon, 1.0f); // Esquina superior izquierda
					ImGui::GetForegroundDrawList()->AddLine(ImVec2(topLeft.x, topLeft.y), ImVec2(topLeft.x, topLeft.y + cornerSize), colorespon, 1.0f);

					ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottomRight.x - cornerSize, topLeft.y), ImVec2(bottomRight.x, topLeft.y), colorespon, 1.0f); // Esquina superior derecha
					ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottomRight.x, topLeft.y), ImVec2(bottomRight.x, topLeft.y + cornerSize), colorespon, 1.0f);

					ImGui::GetForegroundDrawList()->AddLine(ImVec2(topLeft.x, bottomRight.y - cornerSize), ImVec2(topLeft.x, bottomRight.y), colorespon, 1.0f); // Esquina inferior izquierda
					ImGui::GetForegroundDrawList()->AddLine(ImVec2(topLeft.x, bottomRight.y), ImVec2(topLeft.x + cornerSize, bottomRight.y), colorespon, 1.0f);

					ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottomRight.x - cornerSize, bottomRight.y), ImVec2(bottomRight.x, bottomRight.y), colorespon, 1.0f); // Esquina inferior derecha
					ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottomRight.x, bottomRight.y - cornerSize), ImVec2(bottomRight.x, bottomRight.y), colorespon, 1.0f);

					// Rellena el interior de la caja con el color en formato RGBA
					ImGui::GetForegroundDrawList()->AddRectFilled(topLeft, bottomRight, IM_COL32(70, 70, 70, 70));
				}





				if (boxnormal)
				{
					ImVec2 topLeft(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2);
					ImVec2 bottomRight(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2);

					// Dibuja la caja con borde
					ImGui::GetForegroundDrawList()->AddRect(topLeft, bottomRight, colorespon, 0);

					// Rellenar el interior de la caja con el mismo color
					ImGui::GetForegroundDrawList()->AddRectFilled(topLeft, bottomRight, IM_COL32(70, 70, 70, 50));
				}

				if (lines)
				{
					 // aslo when user in friend change snapline color to green okok
					ImGui::GetForegroundDrawList()->AddLine(ImVec2(i_sdk::sdk().WindowSize.x / 2, i_sdk::sdk().WindowSize.y / 2), ImVec2(Ped_Location.x, Ped_Location.y), colorespon, 1);
					// WindowSize
				}


				if (heathbar)
				{
					float HealthPercentage = Height / 100 * (HealthPed - 100);
					float HealthPercentagee = Height / 100 * 100;

					float fixedhealth = HealthPed / 2;
					float fixedhealthh = 100;

					ImColor	col = ImColor(14, 110, 17, 255);
					ImColor coll = ImColor(0, 0, 0, 255);

					float  caca = (Width) / 8.f;
					if (Distance < 20)
					{
						caca = (Width) / 12.f;
					}
					float HealthPercentageeee = Width / 100 * (HealthPed - 100);
					float HealthPercentageee = Width / 100 * 100;
					if (fixedhealth != 0)


						if (HealthBar_type == 0)
						{
							i_overlay::here().DrawHealthBar(ImVec2((Ped_Location.x + Width / 1.70), Ped_Location.y + Height / 2), ImVec2(3, HealthPercentagee), coll);

							i_overlay::here().DrawHealthBar(ImVec2((Ped_Location.x + Width / 1.70), Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);
						}
						else if (HealthBar_type == 1)
						{
							if (fixedhealth != 0)
							i_overlay::here().DrawHealthBar(ImVec2((Ped_Location.x - Width / 1.70) - HealthDistance, Ped_Location.y + Height / 2), ImVec2(3, HealthPercentagee), coll);
							i_overlay::here().DrawHealthBar(ImVec2((Ped_Location.x - Width / 1.70) - HealthDistance, Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);

						}

						else if (HealthBar_type == 2)
						{

							i_overlay::here().DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y - Height / 2) - 10), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) - 10), ImVec2(3, HealthPercentageee), coll);
							i_overlay::here().DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y - Height / 2) - 10), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) - 10), ImVec2(3, HealthPercentageeee), col);

						}

				}


				if (weapons)
				{
					auto weapon_mgr = i_memory::reeq().Read<uintptr_t>(Ped + i_dupa::skid().weaponmanager);
					if (weapon_mgr) {
						auto weapon_current = i_memory::reeq().Read<uintptr_t>(weapon_mgr + 0x20);
						if (weapon_current) {
							auto weapon_hash = i_memory::reeq().Read<uintptr_t>(weapon_current + 0x10);
							ImFont* font = ImGui::GetFont();
							float yOffset = -5.0f;

							i_overlay::here().DrawOutlinedText(font, get_weapon_name(weapon_hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + yOffset), 15.0f, ImColor(0, 0, 0), true);
							i_overlay::here().DrawOutlinedText(font, get_weapon_name(weapon_hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 1 + yOffset), 15.0f, ImColor(255, 255, 255), true);
							i_overlay::here().DrawOutlinedText(font, get_weapon_name(weapon_hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + yOffset), 15.0f, ImColor(0, 0, 0), true);
							i_overlay::here().DrawOutlinedText(font, get_weapon_name(weapon_hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2 + 1 + yOffset), 15.0f, ImColor(255, 255, 255), true);
						}
					}
				}



				//armor bar
				if (armorbar)
				{
					float HealthPercentage = Height / 100 * (ArmorPed);
					float HealthPercentagee = Height / 100 * 100;

					float fixedhealth = ArmorPed;
					float fixedhealthh = 100;

					ImColor col = ImColor(10, 145, 255, 255);
					ImColor coll = ImColor(0, 0, 0, 255);

					float  caca = (Width) / 8.f;
					if (Distance < 20)
					{
						caca = (Width) / 12.f;
					}
					float HealthPercentageeee = Width / 100 * (ArmorPed);
					float HealthPercentageee = Width / 100 * 100;
					if (fixedhealth != 0)


						if (ArmorBar_type == 0)
						{
							i_overlay::here().DrawHealthBar(ImVec2((Ped_Location.x + Width / 1.70), Ped_Location.y + Height / 2), ImVec2(3, HealthPercentagee), coll);

							i_overlay::here().DrawHealthBar(ImVec2((Ped_Location.x + Width / 1.70), Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);
						}
						else if (ArmorBar_type == 1)
						{
							if (fixedhealth != 0)
							i_overlay::here().DrawHealthBar(ImVec2((Ped_Location.x - Width / 1.70) - HealthDistance, Ped_Location.y + Height / 2), ImVec2(3, HealthPercentagee), coll);
							i_overlay::here().DrawHealthBar(ImVec2((Ped_Location.x - Width / 1.70) - HealthDistance, Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);

						}

						else if (ArmorBar_type == 2)
						{

							i_overlay::here().DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y - Height / 2) - 10), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) - 10), ImVec2(3, HealthPercentageee), coll);
							i_overlay::here().DrawHealthBarhorizontal(ImVec2((Ped_Location.x - Width / 2), (Ped_Location.y - Height / 2) - 10), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) - 10), ImVec2(3, HealthPercentageeee), col);

						}

				}
				if (skeleton)
				{
					draw_skeleton(Ped);
				}
			}

		}
	
	}
}

void i_esp::vehicleesp()
{

	uintptr_t ReplayInterface = i_dupa::skid().i_replay;

	if (ReplayInterface)
	{
		uintptr_t VehicleInterface = i_memory::reeq().Read<DWORD64>(ReplayInterface + 0x10);
		uintptr_t  VehucleList = i_memory::reeq().Read<DWORD64>(VehicleInterface + 0x180);
		int vehiclelist = i_memory::reeq().Read<int>(VehicleInterface + 0x188);

		for (int i = 0U; i < vehiclelist; i++)
		{

			uintptr_t Vehicle = i_memory::reeq().Read<uintptr_t>(VehucleList + (i * 0x10));
			if (!Vehicle) continue;

			D3DXVECTOR3 GetCorrdinateVehicle = i_memory::reeq().Read<D3DXVECTOR3>(Vehicle + 0x90);

			D3DXVECTOR2 VehicleLocation = i_sdk::sdk().world_to_screen(GetCorrdinateVehicle);




		}

	}


}

void i_esp::start()
{
	// some stuff

	if (i_dupa::skid().i_localplayer)
	{
		esp_init();
		vehicleesp();

	}
}