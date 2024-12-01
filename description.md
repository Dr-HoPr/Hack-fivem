# Code Description

## Car Managament

The code creates a vehicle control interface that appears when a specific tab (`subtab2`) is selected. It uses ImGui for rendering the UI elements, and custom memory manipulation functions to read and write to the vehicle's properties in memory.

### Car Repair && Break

```cpp
if (ImGui::Button(skCrypt("Repair Engine")))
{
    uintptr_t localplayer = i_dupa::skid().i_localplayer;
    uintptr_t actualcar = i_memory::reeq().Read<uintptr_t>(localplayer + i_dupa::skid().i_veh);
    i_memory::reeq().Write<float>(actualcar + i_dupa::skid().i_enginehealth, 1000.f);
}

if (ImGui::Button(skCrypt("Break Engine")))
{
	uintptr_t localplayer = i_dupa::skid().i_localplayer;
	uintptr_t actualcar = i_memory::reeq().Read<uintptr_t>(localplayer + i_dupa::skid().i_veh);
	i_memory::reeq().Write<float>(actualcar + i_dupa::skid().i_enginehealth, 0.f);
}
```
### Car Color Options

```cpp

if (ImGui::Button(skCrypt("Red Color")))
{
	uintptr_t localplayer = i_dupa::skid().i_localplayer;
	uintptr_t cur_vehicle = i_memory::reeq().Read<uintptr_t>(localplayer + i_dupa::skid().i_veh);
	auto vehicle_mods_ptr = i_memory::reeq().Read<uintptr_t>(cur_vehicle + 0x48);
	if (vehicle_mods_ptr)
	{
		auto model_info = i_memory::reeq().Read<uintptr_t>(vehicle_mods_ptr + 0x0020);
		if (model_info)
		{
			float red = 1.0f;
			i_memory::reeq().Write<float>(model_info + 0xA4, red);
			i_memory::reeq().Write<float>(model_info + 0xA8, red);
		}
	}
}
if (ImGui::Button(skCrypt("Green Color")))
{
	uintptr_t localplayer = i_dupa::skid().i_localplayer;
	uintptr_t cur_vehicle = i_memory::reeq().Read<uintptr_t>(localplayer + i_dupa::skid().i_veh);
	auto vehicle_mods_ptr = i_memory::reeq().Read<uintptr_t>(cur_vehicle + 0x48);

	if (vehicle_mods_ptr)
	{
		auto model_info = i_memory::reeq().Read<uintptr_t>(vehicle_mods_ptr + 0x0020);

		if (model_info)
		{
			float green = 1.0f;										 // Set the green color value
			i_memory::reeq().Write<float>(model_info + 0xA0, green); // Change A4 to A0 for green channel
			i_memory::reeq().Write<float>(model_info + 0xA4, green); // Change A8 to A4 for green channel
		}
	}
}
if (ImGui::Button(skCrypt("Blue Color")))
{
	uintptr_t localplayer = i_dupa::skid().i_localplayer;
	uintptr_t cur_vehicle = i_memory::reeq().Read<uintptr_t>(localplayer + i_dupa::skid().i_veh);
	auto vehicle_mods_ptr = i_memory::reeq().Read<uintptr_t>(cur_vehicle + 0x48);

	if (vehicle_mods_ptr)
	{
		auto model_info = i_memory::reeq().Read<uintptr_t>(vehicle_mods_ptr + 0x0020);

		if (model_info)
		{
			float blue = 1.0f;										// Set the blue color value
			i_memory::reeq().Write<float>(model_info + 0xA8, blue); // Change A0 to A8 for blue channel
			i_memory::reeq().Write<float>(model_info + 0xAC, blue); // Change A4 to AC for blue channel
		}
	}
}
```