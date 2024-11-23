#include "overlay.h"
#include <sstream>
#include "million.h"
#include "../Hotkey/hotkey.h"
#include "IconsFontAwesome6.h"
#include "IconsFontAwesome6Brands.h"
#include <process.h>

// pero ara dale otra vez
int selectedHeal = 200;
int selectedArmor = 100;
i_overlay &i_overlay::here()
{
	static i_overlay ins;
	return ins;
}

bool i_overlay::LoadTextureFromFile(const char *filename, PDIRECT3DTEXTURE9 *out_texture, int *out_width, int *out_height)
{
	// Load texture from disk
	PDIRECT3DTEXTURE9 texture;
	HRESULT hr = D3DXCreateTextureFromFileA(p_Device, filename, &texture);
	if (hr != S_OK)
		return false;

	// Retrieve description of the texture surface so we can access its size
	D3DSURFACE_DESC my_image_desc;
	texture->GetLevelDesc(0, &my_image_desc);
	*out_texture = texture;
	*out_width = (int)my_image_desc.Width;
	*out_height = (int)my_image_desc.Height;
	return true;
}

std::int64_t __stdcall i_overlay::wndproc(HWND hwnd, unsigned int message, WPARAM wparam, LPARAM lparam)
{

	std::int64_t ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	ImGui_ImplWin32_WndProcHandler(hwnd, message, wparam, lparam);
	if (i_overlay::here().showmenu)
		return 1;

	return DefWindowProcA(i_overlay::here().MyWnd, message, wparam, lparam);
}

void styledark()
{
	ImGuiStyle *Style = &ImGui::GetStyle();
	ImVec4 *Colors = Style->Colors;

	Style->Colors[ImGuiCol_WindowBg] = ImColor(17, 17, 17);
	Style->Colors[ImGuiCol_ChildBg] = ImColor(22, 22, 22);
	Style->Colors[ImGuiCol_FrameBg] = ImColor(17, 17, 17);
	Style->Colors[ImGuiCol_CheckMark] = ImColor(237, 143, 243);
	Style->Colors[ImGuiCol_FrameBgActive] = ImColor(17, 17, 17);
	Style->Colors[ImGuiCol_FrameBgHovered] = ImColor(17, 17, 17);
	Style->Colors[ImGuiCol_PopupBg] = ImColor(12, 12, 12);
	Style->Colors[ImGuiCol_TextDisabled] = ImColor(255, 255, 255);
	Style->Colors[ImGuiCol_ButtonActive] = ImColor(100, 150, 255);
	Style->Colors[ImGuiCol_Button] = ImColor(27, 27, 27);
	Style->Colors[ImGuiCol_ButtonActive] = ImColor(237, 143, 243);
	Style->Colors[ImGuiCol_ButtonHovered] = ImColor(237, 143, 243);
	Style->Colors[ImGuiCol_Border] = ImColor(26, 26, 26);
	Style->Colors[ImGuiCol_Separator] = ImColor(237, 143, 243);
	Style->Colors[ImGuiCol_ScrollbarGrab] = ImColor(237, 143, 243);
	Style->ScrollbarSize = 2.0f;
	Style->WindowRounding = 5;
	Style->FrameRounding = 5;
	Style->FrameBorderSize = 0;
	Style->ChildBorderSize = 1;

	static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
	static const ImWchar icons_ranges_brands[] = {ICON_MIN_FAB, ICON_MAX_16_FAB, 0};
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	ImFont *FontAwesome = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(fa6_solid_compressed_data, fa6_solid_compressed_size, 14.f, &icons_config, icons_ranges);
	ImFont *FontAwesomeBrands = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(fa_brands_400_compressed_data, fa_brands_400_compressed_size, 14.f, &icons_config, icons_ranges_brands);
}

HRESULT i_overlay::init_wndparams(HWND hwnd)
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		return E_FAIL;

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hwnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = Width;
	p_Params.BackBufferHeight = Height;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device)))
	{
		p_Object->Release();
		return E_FAIL;
	}

	ImGui::CreateContext();

	// LoadTextureFromFileAsync("unknown2.png", &my_texture, &my_image_width, &my_image_height);
	// Load the texture asynchronously to prevent potential UI freezes

	ImGuiIO &io = ImGui::GetIO();
	io.IniFilename = NULL;

	char windows_directory[MAX_PATH];

	// std::string segoeui_dir = (std::string)windows_directory + "\\Fonts\\segoeui.ttf";

	// global34 = io.Fonts->AddFontFromFileTTF(segoeui_dir.c_str(), 18.0f, &font_config, io.Fonts->GetGlyphRangesCyrillic());
	// ico_combo2 = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 19, NULL, io.Fonts->GetGlyphRangesCyrillic());

	global3 = io.Fonts->AddFontFromMemoryTTF(segoui, sizeof(segoui), 17, NULL, io.Fonts->GetGlyphRangesCyrillic());

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX9_Init(p_Device);

	return S_OK;
}

void i_overlay::cleanup_d3d()
{
	if (p_Device != NULL)
	{
		p_Device->EndScene();
		p_Device->Release();
	}
	if (p_Object != NULL)
	{
		p_Object->Release();
	}
}

void set_window_target()
{
	i_overlay &overlay = i_overlay::here();
	i_memory &memory = i_memory::reeq();

	while (true)
	{
		overlay.GameWnd = memory.get_process_wnd(memory.pid);

		if (overlay.GameWnd)
		{
			ZeroMemory(&overlay.GameRect, sizeof(overlay.GameRect));
			GetWindowRect(overlay.GameWnd, &overlay.GameRect);

			DWORD dwStyle = GetWindowLong(overlay.GameWnd, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				overlay.GameRect.top += 32;
				overlay.Height -= 39;
			}

			overlay.ScreenCenterX = overlay.Width / 2;
			overlay.ScreenCenterY = overlay.Height / 2;

			MoveWindow(overlay.MyWnd, overlay.GameRect.left, overlay.GameRect.top, overlay.Width, overlay.Height, true);
		}
	}
}

char Licence[50] = "";
void i_overlay::setup_window()
{
	(HANDLE) _beginthreadex(nullptr, 0, reinterpret_cast<_beginthreadex_proc_type>(&set_window_target), 0, 0, 0);
	WNDCLASSEXA wcex = {
		sizeof(WNDCLASSEXA),
		0,
		wndproc,
		0,
		0,
		nullptr,
		LoadIcon(nullptr, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		nullptr,
		nullptr,
		("Chrome"),
		LoadIcon(nullptr, IDI_APPLICATION)};

	RECT Rect;
	GetWindowRect(GetDesktopWindow(), &Rect);

	RegisterClassExA(&wcex);

	MyWnd = CreateWindowA(("Chrome"), ("Chrome"), WS_POPUP, Rect.left, Rect.top, Rect.right, Rect.bottom, NULL, NULL, wcex.hInstance, NULL);
	SetWindowLong(MyWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);
	SetLayeredWindowAttributes(MyWnd, RGB(0, 0, 0), 255, LWA_ALPHA);

	MARGINS margin = {-1};
	DwmExtendFrameIntoClientArea(MyWnd, &margin);

	ShowWindow(MyWnd, SW_SHOW);
}

void i_overlay::style()
{
	ImGuiStyle *Style = &ImGui::GetStyle();
	ImVec4 *Colors = Style->Colors;

	ImGui::StyleColorsDark();
	Style->WindowRounding = 4.f;
	Style->WindowBorderSize = 0;
	Style->ChildRounding = 3.0f;
	Style->Colors[ImGuiCol_WindowBg] = ImColor(17, 17, 17);
	Style->Colors[ImGuiCol_Border] = ImColor(23, 23, 23);
	Style->Colors[ImGuiCol_Button] = ImColor(20, 24, 28);
	Style->Colors[ImGuiCol_ButtonActive] = ImColor(237, 143, 243);
	Style->Colors[ImGuiCol_ButtonHovered] = ImColor(237, 143, 243);

	static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
	static const ImWchar icons_ranges_brands[] = {ICON_MIN_FAB, ICON_MAX_16_FAB, 0};
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	ImFont *FontAwesome = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(fa6_solid_compressed_data, fa6_solid_compressed_size, 14.f, &icons_config, icons_ranges);
	ImFont *FontAwesomeBrands = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(fa_brands_400_compressed_data, fa_brands_400_compressed_size, 14.f, &icons_config, icons_ranges_brands);
}

void i_overlay::CustomStyleColor()
{
	ImGuiStyle &s = ImGui::GetStyle();

	s.WindowBorderSize = 0;

	s.PopupBorderSize = 0;
	s.FrameBorderSize = 1.0f;
	s.FrameRounding = 4.f;
}
int slider_int = 0;
int slider_int2 = 0;
int slider_int3s = 0;
bool test = false;
bool test2 = false;
bool test3 = false;
bool test4 = false;
const char *items[3] = {"head", "chest", "legs"};

const char *const KeyNames[] = {
	"Right Click",
	"ALT",
	"Control",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"Left Click",
};

bool aimbot = false;
bool esp = false;
bool autotarget = false;
bool autoshot = false;
bool drawfov = false;

ImFont *LexendRegular;

int fov = 0;
int smooth = 0;

int Hotkey = 2;

bool active = true;
bool active2 = false;
int subtab2 = 0;

uint64_t selectedped = 0;

void i_overlay::menu()
{
	styledark();
	ImDrawList *draw;
	ImGui::SetNextWindowSize(ImVec2({600, 365}));

	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(skCrypt("FiveM"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse);
	{
		ImVec2 pos;
		auto p = ImGui::GetWindowPos();
		pos = ImGui::GetWindowPos();
		draw = ImGui::GetWindowDrawList();
		ImGui::SetCursorPos(ImVec2(10, 5));
		ImGui::BeginChild("a", ImVec2(583, 25));
		{
			ImGui::SetCursorPos(ImVec2(10, 3));
			ImVec4 color = ImVec4(231.0f / 255.0f, 97.0f / 255.0f, 223.0f / 255.0f, 1.0f);
			ImGui::TextColored(color, "FiveM");
		}
		ImGui::EndChild();
		ImGui::PushFont(global3);

		ImGui::SetCursorPos(ImVec2(10, 35));
		ImGui::BeginChild(("main1"), ImVec2(80, 320));
		{

			ImGui::PushFont(global3);

			ImGui::SetCursorPos({5, 5});

			ImGui::SetCursorPos(ImVec2(20, 17));
			if (ImGui::Button(ICON_FA_SKULL, ImVec2(40, 40)))
			{
				subtab2 = 0;
			}
			ImGui::SetCursorPos(ImVec2(20, 65));
			if (ImGui::Button(ICON_FA_EYE, ImVec2(40, 40)))
			{
				subtab2 = 1;
			}
			ImGui::SetCursorPos(ImVec2(20, 113));
			if (ImGui::Button(ICON_FA_USER, ImVec2(40, 40)))
			{
				subtab2 = 2;
			}
			ImGui::SetCursorPos(ImVec2(20, 161));
			if (ImGui::Button(ICON_FA_CAR, ImVec2(40, 40)))
			{
				subtab2 = 6;
			}
			ImGui::SetCursorPos(ImVec2(20, 209));
			if (ImGui::Button(ICON_FA_FOLDER, ImVec2(40, 40)))
			{
				subtab2 = 4;
			}
			ImGui::SetCursorPos(ImVec2(20, 257));
			if (ImGui::Button(ICON_FA_GEAR, ImVec2(40, 40)))
			{
				subtab2 = 3;
			}

			ImGui::PopFont();
		}
		ImGui::EndChild();

		if (subtab2 == 6)
		{
			ImGui::SetCursorPos({100, 35});
			ImGui::BeginChild(skCrypt(("Vehicle")));
			{

				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(20 / 255.0f, 20 / 255.0f, 20 / 255.0f, 1.0f)); // Cambiar el color de la sombra del borde
				ImGui::PushFont(global3);
				ImGui::BeginChild(skCrypt(("Vehicle")), ImVec2(220, 220));
				{
					ImGui::SetWindowFontScale(1.0f);
					ImGui::SetCursorPos({85, 5});
					ImGui::Text("Options");
					ImGui::Separator();
					ImGui::SetWindowFontScale(1.0f);
					ImGui::SetCursorPos({15, 50});
					ImGui::Checkbox(skCrypt("Boost vehicle"), &i_exploits::exp().boostvehicle);

					ImGui::SetCursorPos({3, 95});
					ImGui::PushItemWidth(195);
					ImGui::SliderFloat(skCrypt(("Boost Value")), &i_exploits::exp().boostvalue, 0.0f, 100);

					ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);

					ImGui::SetCursorPos(ImVec2(20, 135));
					if (ImGui::Button(skCrypt("Repair Engine")))
					{
						uintptr_t localplayer = i_dupa::skid().i_localplayer;
						uintptr_t actualcar = i_memory::reeq().Read<uintptr_t>(localplayer + i_dupa::skid().i_veh);
						i_memory::reeq().Write<float>(actualcar + i_dupa::skid().i_enginehealth, 1000.f);
					}
					ImGui::SameLine();
					if (ImGui::Button(skCrypt("Break Engine")))
					{
						uintptr_t localplayer = i_dupa::skid().i_localplayer;
						uintptr_t actualcar = i_memory::reeq().Read<uintptr_t>(localplayer + i_dupa::skid().i_veh);
						i_memory::reeq().Write<float>(actualcar + i_dupa::skid().i_enginehealth, 0.f); //  nice , do it wait
					}

					ImGui::SetCursorPos({120, 165});
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
					ImGui::SetCursorPos({25, 165}); // Adjust the position as needed
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
					ImGui::SetCursorPos({75, 195}); // Adjust the position as needed
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
				}
				ImGui::EndChild();
				ImGui::PopFont();
			}
			ImGui::PopStyleColor();
			ImGui::EndChild();
		}
		if (subtab2 == 4)
		{
			static char searchQuery[256];

			ImGui::PushFont(global3);
			ImGui::SetCursorPos({100, 35});
			ImGui::BeginChild(skCrypt(("players")));

			{
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(20 / 255.0f, 20 / 255.0f, 20 / 255.0f, 1.0f)); // Cambiar el color de la sombra del borde
				ImGui::BeginChild(skCrypt(("Player-List")), ImVec2(200, 300));
				{
					ImGui::SetCursorPos({73, 5});
					ImGui::Text("Player list");
					ImGui::Separator();
					ImGui::SetCursorPos({10, 40});
					ImGui::InputTextWithHint("##Search", "Search the id", searchQuery, sizeof(searchQuery));

					uintptr_t ClosestPlayer = 0;
					uintptr_t ReplayInterface = i_dupa::skid().i_replay;
					uintptr_t localplayer = i_dupa::skid().i_localplayer;
					if (ReplayInterface)
					{
						uintptr_t PedReplayInterface = i_memory::reeq().Read<DWORD64>(ReplayInterface + 0x18);
						uintptr_t PedList = i_memory::reeq().Read<DWORD64>(PedReplayInterface + 0x100);
						int entitylist = i_memory::reeq().Read<int>(PedReplayInterface + 0x108);

						bool firstSeparator = true;

						for (int i = 0U; i < entitylist; i++)
						{
							if (!PedList)
								continue;

							uintptr_t Ped = i_memory::reeq().Read<uintptr_t>(PedList + (i * 0x10));
							if (!Ped)
								continue;

							if (!i_memory::reeq().Read<uintptr_t>(Ped + i_dupa::skid().playerinfo))
								continue;

							uint64_t playerinfos = i_memory::reeq().Read<uint64_t>(Ped + i_dupa::skid().playerinfo);
							int playeridaddr = i_memory::reeq().Read<int>(playerinfos + 0x88);
							std::string playeridstr = std::to_string(playeridaddr);

							if (!searchQuery[0] || playeridstr.find(searchQuery) != std::string::npos)
							{
								if (!firstSeparator)
								{
									ImGui::Separator();
								}
								firstSeparator = false;

								ImGui::Text(playeridstr.c_str());
								if (ImGui::IsItemClicked())
								{
									selectedped = Ped;
								}
							}
						}
					}
				}
				ImGui::EndChild();
				ImGui::PopFont();

				ImGui::PushFont(global3);
				ImGui::SetCursorPos({220, 8});
				ImGui::BeginChild(skCrypt(("Selected player")), ImVec2(200, 200));
				{

					ImGui::Text("ID:");
					ImGui::SameLine();
					uint64_t playerinfos = i_memory::reeq().Read<uint64_t>(selectedped + i_dupa::skid().playerinfo);
					int playeridaddr = i_memory::reeq().Read<int>(playerinfos + 0x88);
					std::string playeridstr = std::to_string(playeridaddr);

					ImGui::Text(playeridstr.c_str());
					auto it = std::find(i_esp::esp().friends.begin(), i_esp::esp().friends.end(), playeridstr);

					if (it != i_esp::esp().friends.end())
						ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Friend: True");
					else
						ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Friend: False");

					if (ImGui::Button(skCrypt("Teleport to player")))
					{
						D3DXVECTOR3 pos = i_memory::reeq().Read<D3DXVECTOR3>(selectedped + 0x90);
						uintptr_t localplayer = i_dupa::skid().i_localplayer;
						uintptr_t navig = i_memory::reeq().Read<uintptr_t>(localplayer + 0x30);
						i_memory::reeq().Write<D3DXVECTOR3>(navig + 0x30, pos);
						i_memory::reeq().Write<D3DXVECTOR3>(localplayer + 0x90, pos);
					}

					if (it != i_esp::esp().friends.end())
					{
						if (ImGui::Button(skCrypt("Remove Friend")))
						{

							int index = (it - i_esp::esp().friends.begin());
							i_esp::esp().friends.erase(i_esp::esp().friends.begin() + index);
						}
					}
					else
					{
						if (ImGui::Button(skCrypt("Add Friend")))
						{
							i_esp::esp().friends.push_back(playeridstr);
						}
					}
				}
				ImGui::EndChild();
				ImGui::PopFont();
			}
			ImGui::EndChild();
		}
		if (subtab2 == 0)
		{
			ImGui::SetCursorPos({100, 35});
			ImGui::BeginChild(skCrypt(("Aimbot-cheat")));
			{
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(20 / 255.0f, 20 / 255.0f, 20 / 255.0f, 1.0f)); // Cambiar el color de la sombra del borde
				ImGui::PushFont(global3);
				ImGui::BeginChild((("Aimbot")), ImVec2(200, 220));
				{
					ImGui::SetCursorPos({75, 5});
					ImGui::Text("Aimbot");
					ImGui::Separator();
					ImGui::SetCursorPos({15, 45});
					{
						ImGui::Checkbox(skCrypt("Enable"), &i_aim::aim().aimenable);
						ImGui::SetCursorPosX(15);
						ImGui::Checkbox(skCrypt("AntiCheat Bypass"), &i_aim::aim().smooth4);
						ImGui::SetCursorPosX(15);
						ImGui::Checkbox(skCrypt("Draw Fov"), &i_aim::aim().showfov);
						ImGui::SetCursorPosX(15);
						ImGui::Checkbox(skCrypt("Ignore Ped"), &i_aim::aim().ignoreped);
						ImGui::SetCursorPosX(15);
						ImGui::Checkbox(skCrypt("Ignore Dead"), &i_aim::aim().ignoredeath);
					}
				}
				ImGui::EndChild();
				ImGui::PopFont();

				ImGui::PushFont(global3);
				ImGui::SetCursorPos({220, 8});
				ImGui::BeginChild(skCrypt(("Options")), ImVec2(200, 300));
				{
					ImGui::SetCursorPos({85, 5});
					ImGui::Text("Setting");
					ImGui::Separator();

					ImGui::SetCursorPos({5, 45});
					ImGui::PushItemWidth(175);
					ImGui::SliderInt(skCrypt(("Fov")), &i_aim::aim().fov, 2.0f, 300);
					// maricon
					ImGui::SetCursorPos({5, 75});
					ImGui::PushItemWidth(175);
					ImGui::SliderInt(skCrypt(("Smooth")), &i_aim::aim().smooth, 2, 100);

					ImGui::SetCursorPos({5, 105});
					ImGui::PushItemWidth(175);
					ImGui::SliderInt(skCrypt(("Distance")), &i_aim::aim().distance, 0.0f, 1000);

					const char *AimType[]{"Mouse"};
					ImGui::SetCursorPos({17, 155});
					ImGui::PushItemWidth(175);
					ImGui::Combo(skCrypt(((("Aim Type")))), &i_aim::aim().aimbottype, AimType, IM_ARRAYSIZE(AimType), ImGuiComboFlags_NoArrowButton);
					ImGui::Spacing();
					ImGui::SetCursorPos({17, 205});
					const char *Boness[]{"Head", "Feet", "Chest"};
					ImGui::Combo(skCrypt((("Bone"))), &i_aim::aim().boneid, Boness, IM_ARRAYSIZE(Boness), ImGuiComboFlags_NoArrowButton);
				}
				ImGui::EndChild();
				ImGui::PopFont();
			}
			ImGui::EndChild();
		}

		if (subtab2 == 1)
		{
			ImGui::PushFont(global3);
			ImGui::SetCursorPos({100, 35});
			ImGui::BeginChild(skCrypt(("ESPINFO")));
			{
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(20 / 255.0f, 20 / 255.0f, 20 / 255.0f, 1.0f)); // Cambiar el color de la sombra del borde
				ImGui::PushFont(global3);
				ImGui::BeginChild(skCrypt(("ESP")), ImVec2(200, 320));
				{
					// preview
					ImGui::SetNextWindowSize(ImVec2(200, 300));
					ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 250, 150));
					ImGui::Begin(skCrypt("preview"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
					{

						float windowWidth = ImGui::GetWindowWidth();

						float textWidth = ImGui::CalcTextSize("Visuals Preview").x;

						float centerX = (windowWidth - textWidth) / 2.0f;

						ImGui::SetCursorPosX(centerX);

						ImGui::Text("Visuals Preview");
						ImGui::PushFont(global3);

						// crosshair preview
						if (i_esp::esp().crosshair)
						{

							ImVec2 previewWindowPos = ImGui::GetWindowPos();
							ImVec2 previewWindowSize = ImGui::GetWindowSize();
							float center_x = previewWindowPos.x + (previewWindowSize.x / 2.f);
							float center_y = previewWindowPos.y + (previewWindowSize.y / 2.f);

							ImVec2 lineStart(center_x - 6, center_y);
							ImVec2 lineEnd(center_x + 7, center_y);
							ImVec2 lineStartVertical(center_x, center_y - 6);
							ImVec2 lineEndVertical(center_x, center_y + 7);
							ImU32 lineColor = IM_COL32(255, 255, 255, 255);

							ImGui::GetForegroundDrawList()->AddLine(lineStart, lineEnd, lineColor);
							ImGui::GetForegroundDrawList()->AddLine(lineStartVertical, lineEndVertical, lineColor);
						}

						// Corner Box preview
						if (i_esp::esp().box)
						{
							// Calcular el centro de la ventana de preview
							ImVec2 previewWindowPos = ImGui::GetWindowPos();
							ImVec2 previewWindowSize = ImGui::GetWindowSize();
							float center_x = previewWindowPos.x + (previewWindowSize.x / 2.f);
							float center_y = previewWindowPos.y + (previewWindowSize.y / 2.f);

							float Width = 100.0f;
							float Height = 100.0f;

							float boxMargin = 5.0f;

							ImVec2 topLeft(center_x - Width / 2 + boxMargin, center_y - Height / 2 + boxMargin);
							ImVec2 bottomRight(center_x + Width / 2 - boxMargin, center_y + Height / 2 - boxMargin);

							float cornerSize = 10.0f;

							ImGui::GetForegroundDrawList()->AddLine(ImVec2(topLeft.x, topLeft.y), ImVec2(topLeft.x + cornerSize, topLeft.y), i_esp::esp().colorespon, 1.0f);
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(topLeft.x, topLeft.y), ImVec2(topLeft.x, topLeft.y + cornerSize), i_esp::esp().colorespon, 1.0f);
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottomRight.x - cornerSize, topLeft.y), ImVec2(bottomRight.x, topLeft.y), i_esp::esp().colorespon, 1.0f);
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottomRight.x, topLeft.y), ImVec2(bottomRight.x, topLeft.y + cornerSize), i_esp::esp().colorespon, 1.0f);
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(topLeft.x, bottomRight.y - cornerSize), ImVec2(topLeft.x, bottomRight.y), i_esp::esp().colorespon, 1.0f);
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(topLeft.x, bottomRight.y), ImVec2(topLeft.x + cornerSize, bottomRight.y), i_esp::esp().colorespon, 1.0f);
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottomRight.x - cornerSize, bottomRight.y), ImVec2(bottomRight.x, bottomRight.y), i_esp::esp().colorespon, 1.0f);
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(bottomRight.x, bottomRight.y - cornerSize), ImVec2(bottomRight.x, bottomRight.y), i_esp::esp().colorespon, 1.0f);

							ImGui::GetForegroundDrawList()->AddRectFilled(topLeft, bottomRight, IM_COL32(70, 70, 70, 70));
						}
						// Normal Box preview
						if (i_esp::esp().boxnormal)
						{
							ImVec2 previewWindowPos = ImGui::GetWindowPos();
							ImVec2 previewWindowSize = ImGui::GetWindowSize();
							float center_x = previewWindowPos.x + (previewWindowSize.x / 2.f);
							float center_y = previewWindowPos.y + (previewWindowSize.y / 2.f);

							float Width = 100.0f;
							float Height = 100.0f;

							float boxMargin = 5.0f;

							ImVec2 topLeft(center_x - Width / 2 + boxMargin, center_y - Height / 2 + boxMargin);
							ImVec2 bottomRight(center_x + Width / 2 - boxMargin, center_y + Height / 2 - boxMargin);

							ImU32 lineColor = i_esp::esp().colorespon;
							ImU32 fillColor = IM_COL32(70, 70, 70, 50);

							ImGui::GetForegroundDrawList()->AddRect(topLeft, bottomRight, lineColor, 0);

							ImGui::GetForegroundDrawList()->AddRectFilled(topLeft, bottomRight, fillColor);
						}
						// Health Bar Preview
						if (i_esp::esp().heathbar)
						{
							ImVec2 previewWindowPos = ImGui::GetWindowPos();
							ImVec2 previewWindowSize = ImGui::GetWindowSize();
							float center_x = previewWindowPos.x + (previewWindowSize.x / 2.f);
							float center_y = previewWindowPos.y + (previewWindowSize.y / 2.f);

							float Width = 92.0f;
							float Height = 5.0f;

							float HealthPed = 200;
							float HealthDistance = 0;

							float HealthPercentage = (HealthPed - 100) / 100.0f; // Ajusta esta lógica según tus necesidades

							ImColor healthColor = ImColor(14, 110, 17, 255);
							ImColor backgroundColor = ImColor(0, 0, 0, 255);

							float barX = center_x + (Width / 2) + HealthDistance + 5; // Ajusta la posición X aquí
							float barY = center_y + Height / 2 - 2;					  // Ajusta la posición Y aquí, por ejemplo, agregamos 10 píxeles hacia abajo

							i_overlay::here().DrawHealthBarhorizontal(ImVec2(barX, barY), ImVec2(barX, barY), ImVec2(Width, Height), backgroundColor);
							i_overlay::here().DrawHealthBarhorizontal(ImVec2(barX, barY), ImVec2(barX, barY), ImVec2(Width * HealthPercentage, Height), healthColor);
						}

						// Armor Bar Preview
						if (i_esp::esp().armorbar)
						{
							ImVec2 previewWindowPos = ImGui::GetWindowPos();
							ImVec2 previewWindowSize = ImGui::GetWindowSize();
							float center_x = previewWindowPos.x + (previewWindowSize.x / 2.f);
							float center_y = previewWindowPos.y + (previewWindowSize.y / 2.f);

							float Width = 92.0f;
							float Height = 5.0f;

							float ArmorPed = 200;
							float ArmorDistance = 0;

							float ArmorPercentage = (ArmorPed - 100) / 100.0f; // Ajusta esta lógica según tus necesidades

							ImColor armorColor = ImColor(10, 145, 255, 255);
							ImColor backgroundColor = ImColor(0, 0, 0, 255);

							float barX = center_x + (Width / 2) + ArmorDistance - 102; // Ajusta la posición X aquí
							float barY = center_y + Height / 2 - 2;					   // Ajusta la posición Y aquí, por ejemplo, agregamos 10 píxeles hacia abajo

							i_overlay::here().DrawHealthBarhorizontal(ImVec2(barX, barY), ImVec2(barX, barY), ImVec2(Width, Height), backgroundColor);
							i_overlay::here().DrawHealthBarhorizontal(ImVec2(barX, barY), ImVec2(barX, barY), ImVec2(Width * ArmorPercentage, Height), armorColor);
						}

						ImVec2 cursorPos = ImGui::GetCursorPos();

						if (i_esp::esp().distance)
						{
							float offsetX = 55.0f;

							float offsetY = 190.0f;

							ImGui::SetCursorPos(ImVec2(cursorPos.x + offsetX, cursorPos.y + offsetY));

							ImGui::Text("ID: 1 - [ 33m ]");

							ImGui::SetCursorPos(cursorPos);
						}

						if (i_esp::esp().weapons)
						{
							float offsetX = 77.0f;

							float offsetY = 170.0f;

							ImGui::SetCursorPos(ImVec2(cursorPos.x + offsetX, cursorPos.y + offsetY));

							ImGui::Text("pistol");

							ImGui::SetCursorPos(cursorPos);
						}
					}
					ImGui::End();
					// preview

					ImGui::SetCursorPos({88, 5});
					ImGui::Text("ESP");
					ImGui::Separator();

					ImGui::SetCursorPos({15, 45});
					{
						ImGui::Checkbox(skCrypt("Crosshair"), &i_esp::esp().crosshair);
						ImGui::SetCursorPosX(15);
						ImGui::Checkbox(skCrypt("Corner Box"), &i_esp::esp().box);
						ImGui::SetCursorPosX(15);
						ImGui::Checkbox(skCrypt("Box"), &i_esp::esp().boxnormal);
						ImGui::SetCursorPosX(15);
						ImGui::Checkbox(skCrypt("Skeleton"), &i_esp::esp().skeleton);
						ImGui::SetCursorPosX(15);
						ImGui::Checkbox(skCrypt("Health Bar"), &i_esp::esp().heathbar);
						ImGui::SetCursorPosX(15);
						ImGui::Checkbox(skCrypt("Armor Bar"), &i_esp::esp().armorbar);
						ImGui::SetCursorPosX(15);
						ImGui::Checkbox(skCrypt("ID + Distance"), &i_esp::esp().distance);
						ImGui::SetCursorPosX(15);
						ImGui::Checkbox(skCrypt("Weapon"), &i_esp::esp().weapons);
						ImGui::SetCursorPosX(15);
						ImGui::Checkbox(skCrypt("Lines"), &i_esp::esp().lines);
						ImGui::SetCursorPosX(15);
					}
				}
				ImGui::EndChild();
				ImGui::PopFont();

				ImGui::PushFont(global3);
				ImGui::SetCursorPos({220, 8});
				ImGui::BeginChild(skCrypt(("Other1")), ImVec2(200, 150));
				{
					{
						ImGui::SetCursorPos({80, 5});
						ImGui::Text("Setting");
						ImGui::Separator();

						ImGui::SetCursorPos({5, 40});
						ImGui::PushItemWidth(175);
						ImGui::SliderInt(skCrypt(("Distance")), &i_esp::esp().distanceint, 0.0f, 500);
						ImGui::SetCursorPosX(20);
						ImGui::Checkbox(skCrypt("Ignore Ped"), &i_esp::esp().ignoreped);
						ImGui::SetCursorPosX(20);
						ImGui::Checkbox(skCrypt("Ignore Dead"), &i_esp::esp().ignoredead);
						ImGui::SetCursorPosX(15);
					}
				}
				ImGui::EndChild();
				ImGui::PopFont();

				ImGui::SetCursorPos({220, 170});
				ImGui::BeginChild(skCrypt(("Other2")), ImVec2(200, 180));
				{
					ImGui::SetCursorPos({80, 5});
					ImGui::Text("Custom");
					ImGui::Separator();

					ImGui::SetCursorPos({10, 50});
					const char *HealthbarStyle[]{"Right", "Left", "Up"};
					const char *ArmorbarStyle[]{"Right", "Left", "Up"};
					ImGui::SetCursorPos({10, 50});
					ImGui::Combo(skCrypt(((("Health Bar Pos")))), &i_esp::esp().HealthBar_type, HealthbarStyle, IM_ARRAYSIZE(HealthbarStyle), ImGuiComboFlags_NoArrowButton);
					ImGui::SetCursorPos({10, 105});
					ImGui::Combo(skCrypt(((("Armor Bar Pos")))), &i_esp::esp().ArmorBar_type, ArmorbarStyle, IM_ARRAYSIZE(ArmorbarStyle), ImGuiComboFlags_NoArrowButton);
				}
				ImGui::EndChild();
				ImGui::PopFont();

				ImGui::SetCursorPos({8, 335});

				ImGui::BeginChild(skCrypt(("Other23")), ImVec2(200, 100));
				{
					ImGui::SetCursorPos({70, 5});
					ImGui::Text("ESP Color");
					ImGui::Separator();

					ImGui::SetCursorPosX(15);
					ImGui::SetCursorPos({10, 40});
					ImGui::Text("Move mouse to modify colors");
					ImGui::SetCursorPos({10, 60});

					// Ajusta el tamaño de la paleta de colores
					ImGui::PushItemWidth(120);
					ImGui::ColorEdit3(skCrypt(""), (float *)&i_esp::esp().colorespon, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHex | ImGuiColorEditFlags_DisplayRGB);

					ImGui::PopItemWidth(); // Restablece el ancho predeterminado
				}
				ImGui::EndChild();
				ImGui::PopFont();
			}
		}

		if (subtab2 == 2)
		{
			ImGui::SetCursorPos({100, 35});
			ImGui::BeginChild(skCrypt(("PLAYERSSELF")));
			{
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(20 / 255.0f, 20 / 255.0f, 20 / 255.0f, 1.0f)); // Cambiar el color de la sombra del borde
				ImGui::BeginChild(skCrypt("Self"), ImVec2(200, 245));
				{
					ImGui::SetCursorPos({88, 5});
					ImGui::Text("Self");
					ImGui::Separator();
					ImGui::SetCursorPos({15, 40});
					ImGui::Checkbox(skCrypt("Noclip"), &i_exploits::exp().noclip);

					ImGui::SetCursorPosX(15);
					ImGui::Checkbox(skCrypt("Semi GodMode"), &i_exploits::exp().godmodee);
					ImGui::SetCursorPosX(15);
					ImGui::Checkbox(skCrypt("Custom Speed"), &i_exploits::exp().customspeed);

					ImGui::SetCursorPosX(15);
					ImGui::Checkbox(skCrypt("Infinite Stamina"), &i_exploits::exp().infinitestamina);
					ImGui::SetCursorPosX(15);
					ImGui::Checkbox(skCrypt("Fov Changer"), &i_exploits::exp().customfov);

					ImGui::SetCursorPos({10, 180});
					if (ImGui::Button("Heal", ImVec2(180, 22)))
					{
						i_memory::reeq().Write<float>(i_dupa::skid().i_localplayer + 0x280, static_cast<float>(selectedHeal));
					}
					ImGui::SetCursorPos({10, 210});
					if (ImGui::Button("Armor", ImVec2(180, 22)))
					{
						uintptr_t armadura = i_dupa::skid().armoroffset;
						i_memory::reeq().Write<float>(i_dupa::skid().i_localplayer + armadura, static_cast<float>(selectedArmor));
					}
				}
				ImGui::EndChild();

				ImGui::BeginChild(skCrypt("settings"), ImVec2(200, 320));
				{
					ImGui::SetCursorPos({80, 5});
					ImGui::Text("Setting");
					ImGui::Separator();
					ImGui::SetCursorPos({9, 50});
					{
						ImGui::SetCursorPosX(5);
						ImGui::PushItemWidth(175);
						ImGui::SliderInt(("Heal Amount"), &selectedHeal, 1, 200);
						ImGui::SetCursorPosX(5);
						ImGui::SliderInt(("Armor Amount"), &selectedArmor, 1, 100);
						ImGui::SetCursorPosX(5);
						ImGui::SliderInt(skCrypt(("Fov")), &i_exploits::exp().fovvalue, 50.0f, 150);
						ImGui::SetCursorPosX(5);
						ImGui::PushItemWidth(175);
						ImGui::SliderInt(skCrypt(("Run Speed")), &i_exploits::exp().playerspeed, 1.0f, 100);
						ImGui::SetCursorPosX(5);
						ImGui::PushItemWidth(175);
						ImGui::SliderInt(skCrypt(("Swim Speed")), &i_exploits::exp().swimspeed2, 1.0f, 100);
						ImGui::SetCursorPosX(5);
						ImGui::SliderInt(skCrypt(("Noclip Speed")), &i_exploits::exp().noclipspeed, 1.0f, 100);
						ImGui::SliderInt(skCrypt("Damage Amount"), &i_exploits::exp().damageamount, 1.0f, 100);
					}
				}
				ImGui::EndChild();

				ImGui::SetCursorPos({220, 235});
				ImGui::BeginChild(skCrypt("teleport"), ImVec2(200, 220));
				{
					ImGui::SetCursorPos({75, 5});
					ImGui::Text("Teleport");
					ImGui::Separator();
					ImGui::SetCursorPos({10, 40});
					{
						ImGui::SetCursorPos({9, 40});
						if (ImGui::Button("TP Legion Square", ImVec2(180, 22)))
						{
							D3DXVECTOR3 pos = i_memory::reeq().Read<D3DXVECTOR3>(i_dupa::skid().i_localplayer + 0x90);
							uintptr_t navig = i_memory::reeq().Read<uintptr_t>(i_dupa::skid().i_localplayer + 0x30);
							float xcoord = 190.52f;
							float ycoord = -873.23f;
							float zcoord = 31.5f;

							i_memory::reeq().Write<D3DXVECTOR3>(navig + 0x30, D3DXVECTOR3(0, 0, 0));

							i_memory::reeq().Write<D3DXVECTOR3>(i_dupa::skid().i_localplayer + 0x90, D3DXVECTOR3(xcoord, ycoord, zcoord));

							i_memory::reeq().Write<D3DXVECTOR3>(navig + 0x50, D3DXVECTOR3(xcoord, ycoord, zcoord));
						}
						if (ImGui::Button("TP Humane", ImVec2(180, 22)))
						{
							D3DXVECTOR3 pos = i_memory::reeq().Read<D3DXVECTOR3>(i_dupa::skid().i_localplayer + 0x90);
							uintptr_t navig = i_memory::reeq().Read<uintptr_t>(i_dupa::skid().i_localplayer + 0x30);
							float xcoord = 3641.22f;
							float ycoord = 3743.51f;
							float zcoord = 28.52f;

							i_memory::reeq().Write<D3DXVECTOR3>(navig + 0x30, D3DXVECTOR3(0, 0, 0));

							i_memory::reeq().Write<D3DXVECTOR3>(i_dupa::skid().i_localplayer + 0x90, D3DXVECTOR3(xcoord, ycoord, zcoord));

							i_memory::reeq().Write<D3DXVECTOR3>(navig + 0x50, D3DXVECTOR3(xcoord, ycoord, zcoord));
						}
						if (ImGui::Button("TP Paleto Bay", ImVec2(180, 22)))
						{
							D3DXVECTOR3 pos = i_memory::reeq().Read<D3DXVECTOR3>(i_dupa::skid().i_localplayer + 0x90);
							uintptr_t navig = i_memory::reeq().Read<uintptr_t>(i_dupa::skid().i_localplayer + 0x30);
							float xcoord = -138.52f;
							float ycoord = 6356.99f;
							float zcoord = 31.49f;

							i_memory::reeq().Write<D3DXVECTOR3>(navig + 0x30, D3DXVECTOR3(0, 0, 0));

							i_memory::reeq().Write<D3DXVECTOR3>(i_dupa::skid().i_localplayer + 0x90, D3DXVECTOR3(xcoord, ycoord, zcoord));

							i_memory::reeq().Write<D3DXVECTOR3>(navig + 0x50, D3DXVECTOR3(xcoord, ycoord, zcoord));
						}
						if (ImGui::Button("TP Sandy Shores", ImVec2(180, 22)))
						{
							D3DXVECTOR3 pos = i_memory::reeq().Read<D3DXVECTOR3>(i_dupa::skid().i_localplayer + 0x90);
							uintptr_t navig = i_memory::reeq().Read<uintptr_t>(i_dupa::skid().i_localplayer + 0x30);
							float xcoord = 1837.16f;
							float ycoord = 3695.66f;
							float zcoord = 34.27f;

							i_memory::reeq().Write<D3DXVECTOR3>(navig + 0x30, D3DXVECTOR3(0, 0, 0));

							i_memory::reeq().Write<D3DXVECTOR3>(i_dupa::skid().i_localplayer + 0x90, D3DXVECTOR3(xcoord, ycoord, zcoord));

							i_memory::reeq().Write<D3DXVECTOR3>(navig + 0x50, D3DXVECTOR3(xcoord, ycoord, zcoord));
						}
						if (ImGui::Button("TP Los Santos Airport", ImVec2(180, 22)))
						{
							D3DXVECTOR3 pos = i_memory::reeq().Read<D3DXVECTOR3>(i_dupa::skid().i_localplayer + 0x90);
							uintptr_t navig = i_memory::reeq().Read<uintptr_t>(i_dupa::skid().i_localplayer + 0x30);
							float xcoord = -1037.52f;
							float ycoord = -2737.02f;
							float zcoord = 13.77f;

							i_memory::reeq().Write<D3DXVECTOR3>(navig + 0x30, D3DXVECTOR3(0, 0, 0));

							i_memory::reeq().Write<D3DXVECTOR3>(i_dupa::skid().i_localplayer + 0x90, D3DXVECTOR3(xcoord, ycoord, zcoord));

							i_memory::reeq().Write<D3DXVECTOR3>(navig + 0x50, D3DXVECTOR3(xcoord, ycoord, zcoord));
						}
					}
				}
				ImGui::EndChild();

				ImGui::SetCursorPos({220, 8});
				ImGui::BeginChild(skCrypt("Weapon6"), ImVec2(200, 220));
				{
					ImGui::SetCursorPos({60, 5});
					ImGui::Text("Weapon Setting");
					ImGui::Separator();

					ImGui::SetCursorPos({15, 40});
					ImGui::Checkbox(skCrypt("No Recoil"), &i_exploits::exp().norecoil);
					ImGui::SetCursorPosX(15);
					ImGui::Checkbox(skCrypt("No Spread"), &i_exploits::exp().nospread);
					ImGui::SetCursorPosX(15);
					ImGui::Checkbox(skCrypt("No Reload"), &i_exploits::exp().noreload);
					ImGui::SetCursorPosX(15);
					ImGui::Checkbox(skCrypt("Infinite Ammo"), &i_exploits::exp().infiniteammo);
					ImGui::SetCursorPosX(15);
					ImGui::Checkbox(skCrypt("Damage Multiplier"), &i_exploits::exp().damageboos);

					ImGui::SetCursorPos({10, 180});
					if (ImGui::Button("Refill Ammo", ImVec2(180, 22)))
					{
						uintptr_t WeaponManager = i_memory::reeq().Read<uintptr_t>(i_dupa::skid().i_localplayer + i_dupa::skid().weaponmanager);
						uintptr_t weaponinfo = i_memory::reeq().Read<uintptr_t>(WeaponManager + 0x20);
						uintptr_t AmmoInfo = i_memory::reeq().Read<uintptr_t>(weaponinfo + 0x60);

						uintptr_t AmmoCount = i_memory::reeq().Read<uintptr_t>(AmmoInfo + 0x8);

						uintptr_t AmmoCount2 = i_memory::reeq().Read<uintptr_t>(AmmoCount + 0x0);
						int actualammo = i_memory::reeq().Read<uintptr_t>(AmmoCount2 + 0x18);

						i_memory::reeq().Write<float>(AmmoCount2 + 0x18, 30);
					}
				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
		if (subtab2 == 3)
		{

			ImGui::SetCursorPos({120, 35});
			ImGui::BeginChild(skCrypt(("Config")), ImVec2(200, 320));
			{
				ImGui::SetCursorPos({5, 10});
				ImGui::PushItemWidth(190);
				ImGui::InputTextWithHint("##cfgname", "Config Name", Licence, 155);
				ImGui::Text("                          ");
				ImGui::SetCursorPosX(5);

				if (ImGui::Button(skCrypt(("Save Config")), ImVec2(190, 25)))
				{
					// Define la ubicación de la carpeta donde se guardarán los archivos.
					const char *saveFolder = "C:/FiveMLabs/";

					// Intenta crear la carpeta si no existe.
					if (!CreateDirectoryA(saveFolder, NULL))
					{
						// Si la carpeta ya existe o hubo un error al crearla, no pasa nada.
						if (GetLastError() != ERROR_ALREADY_EXISTS)
						{
							const char *errorCreateFolder = "Failed to create the folder.";

							MessageBoxA(NULL, errorCreateFolder, "Error", MB_ICONERROR | MB_OK);
							return;
						}
					}

					// Combina la ubicación de la carpeta con el nombre de la configuración.
					char savePath[MAX_PATH];
					snprintf(savePath, sizeof(savePath), "%s%s", saveFolder, Licence);

					FILE *p_stream4;

					// Abre el archivo para escritura extendida.
					fopen_s(&p_stream4, savePath, "w+");

					// Verifica si el archivo se abrió correctamente.
					if (p_stream4)
					{
						// Aimbot
						fwrite(&i_aim::aim().aimenable, sizeof(bool), 1, p_stream4);
						fwrite(&i_aim::aim().ignoredeath, sizeof(bool), 1, p_stream4);
						fwrite(&i_aim::aim().ignoreped, sizeof(bool), 1, p_stream4);
						fwrite(&i_aim::aim().showfov, sizeof(bool), 1, p_stream4);
						fwrite(&i_aim::aim().aimbottype, sizeof(bool), 1, p_stream4);
						fwrite(&i_aim::aim().distance, sizeof(bool), 1, p_stream4);
						fwrite(&i_aim::aim().fov, sizeof(bool), 1, p_stream4);
						fwrite(&i_aim::aim().smooth, sizeof(bool), 1, p_stream4);

						// ESP
						fwrite(&i_esp::esp().box, sizeof(bool), 1, p_stream4);
						fwrite(&i_esp::esp().distance, sizeof(bool), 1, p_stream4);
						fwrite(&i_esp::esp().distanceint, sizeof(bool), 1, p_stream4);
						fwrite(&i_esp::esp().HealthBar_type, sizeof(bool), 1, p_stream4);
						fwrite(&i_esp::esp().heathbar, sizeof(bool), 1, p_stream4);
						fwrite(&i_esp::esp().skeleton, sizeof(bool), 1, p_stream4);
						fwrite(&i_esp::esp().ignoreped, sizeof(bool), 1, p_stream4);
						fwrite(&i_esp::esp().ignoredead, sizeof(bool), 1, p_stream4);
						fwrite(&i_esp::esp().ArmorBar_type, sizeof(bool), 1, p_stream4);
						fwrite(&i_esp::esp().armorbar, sizeof(bool), 1, p_stream4);
						fwrite(&i_esp::esp().crosshair, sizeof(bool), 1, p_stream4);
						fwrite(&i_esp::esp().boxnormal, sizeof(bool), 1, p_stream4);
						fwrite(&i_esp::esp().lines, sizeof(bool), 1, p_stream4);
						fwrite(&i_esp::esp().weapons, sizeof(bool), 1, p_stream4);

						// Exploits
						fwrite(&i_exploits::exp().boostvehicle, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().brakeforce, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().brakevalue, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().customfov, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().customspeed, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().damageamount, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().damageboos, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().infiniteammo, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().fovvalue, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().godmodee, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().noclip, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().infinitestamina, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().norecoil, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().noreload, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().nospread, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().swimspeed2, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().testbool, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().rapidfire, sizeof(bool), 1, p_stream4);
						fwrite(&i_exploits::exp().playerspeed, sizeof(bool), 1, p_stream4);

						// Config
						fwrite(&Hotkey::hot().key, sizeof(bool), 1, p_stream4);

						// Cierra el archivo después de escribir.
						fclose(p_stream4);
					}
					else
					{
						const char *errorSave = "Failed to save the config.";

						MessageBoxA(NULL, errorSave, "Error", MB_ICONERROR | MB_OK);
					}
				}
				ImGui::Text("                          ");

				ImGui::SetCursorPosX(5);

				if (ImGui::Button(skCrypt("Load Config"), ImVec2(190, 25)))
				{
					// Construye la ruta completa al archivo de configuración
					std::string configPath = "C:/FiveMLabs/" + std::string(Licence);

					FILE *p_stream4;

					// Abre el archivo para lectura
					fopen_s(&p_stream4, configPath.c_str(), "r+");

					if (p_stream4 != nullptr)
					{
						// Aimbot
						fread_s(&i_aim::aim().aimenable, sizeof(bool), sizeof(bool), 1, p_stream4);

						fread_s(&i_aim::aim().ignoredeath, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_aim::aim().ignoreped, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_aim::aim().showfov, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_aim::aim().aimbottype, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_aim::aim().distance, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_aim::aim().fov, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_aim::aim().smooth, sizeof(bool), sizeof(bool), 1, p_stream4);

						// ESP
						fread_s(&i_esp::esp().box, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_esp::esp().distance, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_esp::esp().distanceint, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_esp::esp().HealthBar_type, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_esp::esp().heathbar, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_esp::esp().skeleton, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_esp::esp().ignoreped, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_esp::esp().ignoredead, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_esp::esp().ArmorBar_type, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_esp::esp().armorbar, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_esp::esp().crosshair, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_esp::esp().boxnormal, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_esp::esp().lines, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_esp::esp().weapons, sizeof(bool), sizeof(bool), 1, p_stream4);

						// Exploits
						fread_s(&i_exploits::exp().boostvehicle, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().brakeforce, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().brakevalue, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().customfov, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().customspeed, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().damageamount, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().damageboos, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().infiniteammo, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().fovvalue, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().godmodee, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().noclip, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().infinitestamina, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().norecoil, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().noreload, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().nospread, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().swimspeed2, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().testbool, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().rapidfire, sizeof(bool), sizeof(bool), 1, p_stream4);
						fread_s(&i_exploits::exp().playerspeed, sizeof(bool), sizeof(bool), 1, p_stream4);

						// Config
						fread_s(&Hotkey::hot().key, sizeof(bool), sizeof(bool), 1, p_stream4);

						fclose(p_stream4);
					}
					else
					{
						const char *errorLoad = "Failed to load the config.";

						MessageBoxA(NULL, errorLoad, "Error", MB_ICONERROR | MB_OK);
					}
				}
				ImGui::Dummy(ImVec2(0, 90));

				ImGui::SetCursorPosX(5);
				// Guarda el color original del texto
				ImVec4 originalTextColor = ImGui::GetStyle().Colors[ImGuiCol_Text];

				// Establece el color del texto a rojo
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));

				if (ImGui::Button(skCrypt(("Unload Cheat")), ImVec2(190, 25)))
				{
					exit(0);
				}

				// Restaura el color original del texto
				ImGui::PopStyleColor();
			}
			ImGui::EndChild();

			ImGui::SetCursorPos({340, 35});
			ImGui::BeginChild((("Binds")), ImVec2(200, 320));
			{
				ImGui::SetCursorPos({15, 10});
				ImGui::Combo((((("Aimbot Hotkey")))), &Hotkey::hot().key, KeyNames, IM_ARRAYSIZE(KeyNames), ImGuiComboFlags_NoArrowButton);
			}
			ImGui::EndChild();
		}
	}
	ImGui::End();
}

void i_overlay::signal()
{
	ZeroMemory(&Message, sizeof(MSG));
	style();
	static RECT old_rc;
	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, MyWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();

		if (hwnd_active == GameWnd)
		{
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		if (showmenu)
		{
		}
		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO &io = ImGui::GetIO();
		io.ImeWindowHandle = GameWnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;
		if (GetAsyncKeyState(0x1))
		{
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{

			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			p_Params.BackBufferWidth = Width;
			p_Params.BackBufferHeight = Height;
			SetWindowPos(MyWnd, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
		i_overlay::here().render();

		Sleep(10);
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	i_overlay::here().cleanup_d3d();
	DestroyWindow(i_overlay::here().MyWnd);
}

std::wstring MBytesToWString(const char *lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t *pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t *)pUnicode;
	delete[] pUnicode;
	return wString;
}

std::string WStringToUTF8(const wchar_t *lpwcszWString)
{
	char *pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void *)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}

void i_overlay::RectFilled(float x, float y, float x1, float y1, ImColor color, float rounding, int rounding_corners_flags)
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x1, y1), color, rounding, rounding_corners_flags);
}

void i_overlay::DrawHealthBarhorizontal(ImVec2 pos, ImVec2 pos2, ImVec2 dim, ImColor col)
{

	ImGui::GetForegroundDrawList()->AddLine(ImVec2(pos.x + dim.y, pos.y), ImVec2(pos2.x, pos.y), col, dim.x);
}

void i_overlay::DrawRectImGui(int x, int y, int w, int h, ImVec4 color, float thickness)
{
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(color), 0, 0, thickness);
}

void i_overlay::DrawLeftProgressBar(int x, int y, int w, int h, int thick, int m_health)
{
	int G = (255 * m_health / 100);
	int R = 255 - G;
	RGBA healthcol = {R, G, 0, 255};

	DrawFilledRect(x - (w / 2) - 3, y, thick, (h)*m_health / 100, &healthcol);
}

void i_overlay::DrawFilledRect(int x, int y, int w, int h, RGBA *color)
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 153.0, color->B / 51.0, color->A / 255.0)), 0, 0);
}
void i_overlay::DrawShieldbar(int x, int y, int w, int h, int thick, int m_health)
{
	int G = (255 * m_health / 100);
	int R = 255 - G;

	DrawFilledRect(x - (w / 2) - 3, y, thick, (h)*m_health / 100, &Col.darkblue);
}

void i_overlay::DrawHealthBar(ImVec2 pos, ImVec2 dim, ImColor col)
{

	ImGui::GetForegroundDrawList()->AddLine(pos, ImVec2(pos.x, pos.y - dim.y), col, dim.x);
}
void i_overlay::DrawLine(const ImVec2 &x, const ImVec2 y, ImU32 color, const FLOAT width)
{
	ImGui::GetForegroundDrawList()->AddLine(x, y, color, width);
}

void i_overlay::DrawOutlinedText(ImFont *pFont, const std::string &text, const ImVec2 &pos, float size, ImU32 color, bool center)
{
	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int index = 0;

	while (std::getline(stream, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

		if (center)
		{

			ImGui::GetForegroundDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}
		else
		{ //

			ImGui::GetForegroundDrawList()->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}

		y = pos.y + textSize.y * (index + 1);
		index++;
	}
}

void i_overlay::DrawString(float fontSize, int x, int y, bool bCenter, bool stroke, const char *pText, ...)
{
	va_list va_alist;
	char buf[1024] = {0};
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImColor(189, 175, 255), text.c_str());
}

static const char *keyNames[] = {
	"",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};

static bool Items_ArrayGetter(void *data, int idx, const char **out_text)
{
	const char *const *items = (const char *const *)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}

void i_overlay::HotkeyButton(int aimkey, void *changekey, int status)
{
	const char *preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = ("Select Key");
	else
		aimkeys = preview_value;

	if (status == 1)
	{
		aimkeys = ("Press key to bind");
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(100, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}

void i_overlay::initialize()
{

	// some stuff xyzus
	setup_window();
	init_wndparams(MyWnd);
	Sleep(2000);
	signal();
}