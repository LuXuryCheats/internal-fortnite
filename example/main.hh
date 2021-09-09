#include "structs.hh"
HWND hwnd;
bool enabled = true;

void menu()
{
	/* menu example and style */
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.44f, 0.44f, 0.44f, 0.60f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.57f, 0.57f, 0.57f, 0.70f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.80f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.60f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.13f, 0.75f, 0.75f, 0.80f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
	colors[ImGuiCol_Button] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
	colors[ImGuiCol_Header] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
	colors[ImGuiCol_Separator] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);

	/* if insert is pressed it will open/close the menu! */
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		enabled = !enabled;
	}

	/* set the size to 300 x 300 (width + height) */
	ImGui::SetNextWindowSize({ 300, 300 });

	/* if enabled is true it will open the menu */
	if (enabled)
	{
		/* ImGui::Begin will create a simple menu, use checkboxes/sliders to customize/enabled your pastes option. */
		ImGui::Begin("Fortnite Internal Example");
		ImGui::Checkbox("aimbot", &settings::aimbot);
		ImGui::Checkbox("aimbot fov", &settings::draw_circle);
		ImGui::Checkbox("box esp", &settings::esp);
		ImGui::Checkbox("text esp", &settings::text);
		ImGui::Checkbox("lines esp", &settings::lines);
		ImGui::SliderFloat("fov size", &settings::fov_size, 1, 40);
		ImGui::SliderFloat("smoothing", &settings::smooth, 1, 20);
		ImGui::End();
	}
}

bool actor_loop()
{
	/* get the middle of the screen */
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	float closest_pawn_dist  = FLT_MAX;
	PVOID closest_pawn = NULL;
	bool op = false;

	auto gworld = *(uintptr_t*)(utils::uworld);
	auto game_instance = *(uint64_t*)(gworld + offsets::game_instance);
	auto local_players = *(uint64_t*)(game_instance + offsets::local_players);
	auto local_player = *(uint64_t*)(local_players);
	utils::player_controller = *(uint64_t*)(local_player + offsets::player_controller);
	utils::local_pawn = *(uint64_t*)(utils::player_controller + offsets::acknowledged_pawn);
	auto levels = *(uintptr_t*)(gworld + offsets::persistent_level);
	auto actors_array = *(uintptr_t*)(levels + offsets::aactors);
	int actors_count = *(int*)(levels + offsets::actor_count);	
	auto camera_manager = *(uint64_t*)(utils::player_controller + offsets::cam_manager);
	structs::fov_angle = structs::get_fov_angle(camera_manager);
	
	/* checks if something went wrong in our main offsets */
	if (!gworld || !game_instance || !local_players)
	{
		printf("something went wrong");
		return false;
	}

	/* create a for loop to loop actors */
	for (int i = 0; i < actors_count; i++)
	{
		auto current_pawn = *(uintptr_t*)(actors_array + i * sizeof(uintptr_t));
		auto object_name = structs::getobjectname(current_pawn);

		if (strstr(object_name, ("PlayerPawn")))
		{
			structs::vector3 head, root, head1, root1;
			structs::vector3 view_point;

			/* here we get the bones location by using the bones index */
			structs::get_bone_loc(current_pawn, 66, &head); /* this is the top left of the players head*/
			structs::get_bone_loc(current_pawn, 0, &root); /* this is the bottom of the player */

			/* now we will project the bones to the screen, so anything using these vectors will be set to the screen! */
			structs::world_to_screen(structs::vector3(head.x, head.y, head.z), &head);
			structs::world_to_screen(structs::vector3(root.x, root.y, root.z), &root);

			if (current_pawn == utils::local_pawn) continue; // so you dont have self aimbot/self esp.

			float Height = head.y - root.y;
			if (Height < 0) { Height = Height * (-1.f); }
			float Width = Height * 0.55;

			auto is_visible = structs::line_of_sight((PVOID)utils::player_controller, (PVOID)current_pawn, &view_point);
			ImColor box_color;

			if (settings::vis_check)
			{
				/* if the player is visible the box is white */
				if (is_visible) { box_color = { color::white }; }
				/* if the player is invisible the box is red */
				else { box_color = { color::red }; }
			}

			if (settings::esp)
			{
				/* draws a outlined box around a pawn */
				structs::vector3 head_base = head;
				head_base.x = head_base.x - (Width / 2);

				structs::vector3 head_ = head_base;
				head_.x = head_.x + (Width);

				ImGui::GetOverlayDrawList()->AddRect(ImVec2(head_base.x, head_base.y), ImVec2(head_.x, root.y), ImColor(0, 0, 0, 255), 0, 0, 3); // outline
				ImGui::GetOverlayDrawList()->AddRect(ImVec2(head_base.x, head_base.y), ImVec2(head_.x, root.y), ImColor(box_color)); // main box
			}

			structs::vector3 aim_;

			if (f_::aim_key())
			{
				if (settings::aimbot && is_visible) /* if is_visible will check if the player is visible and will only aim on visible players. */
				{
					f_::mousemove(head.x, head.y, width, height, settings::smooth);
				}
				/* you can do an else (!is_visible) and it will not check if the player is in the players line of sight */
			}

			if (settings::text)
			{
				/* draws a text under the player */
				f_::draw_outlined_text(root.x - 15, root.y, "player", ImColor(color::white));
			}

			if (settings::lines)
			{
				/* draw a line to the middle bottom of the players box.*/
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(960, 1100), ImVec2(root.x, root.y), color::white, 1);
			}
		}
	}
}

float x, y;
HRESULT hook_present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!device)
	{
		ID3D11Texture2D* renderTarget = 0;
		ID3D11Texture2D* backBuffer = 0;
		D3D11_TEXTURE2D_DESC backBufferDesc = { 0 };
		pSwapChain->GetDevice(__uuidof(device), (PVOID*)&device);
		device->GetImmediateContext(&context);

		pSwapChain->GetBuffer(0, __uuidof(renderTarget), (PVOID*)&renderTarget);
		device->CreateRenderTargetView(renderTarget, nullptr, &render_target_view);
		renderTarget->Release();
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (PVOID*)&backBuffer);
		backBuffer->GetDesc(&backBufferDesc);
		is_inital_release = true;

		backBuffer->Release();

		x = (float)backBufferDesc.Width;
		y = (float)backBufferDesc.Height;

		if (!hwnd)
		{
			hwnd = FindWindowW(L"UnrealWindow", L"Fortnite  ");
			if (!hwnd)
			{
				hwnd = GetForegroundWindow();
			}
		}

		ImGui_ImplDX11_Init(hwnd, device, context);
		ImGui_ImplDX11_CreateDeviceObjects();
	}

	context->OMSetRenderTargets(1, &render_target_view, nullptr);
	auto& present_scene = utils::begin_scene();
	
	/* draw everything here */
	actor_loop();
	menu();
	if (settings::draw_circle)
	{
		// here we will draw a circle, this circle will check if there is any players inside of it and aim to the closest. | does nothing currently
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x / 2, y / 2), (settings::fov_size * structs::fov_angle) / 2, color::white, 50, 1);
		// settings::fov_size * structs::fov_angle / 2 will use the players camera angle and set the size to make a cool dynamic fov circle!
	}

	utils::end_scene(present_scene);
	return present_og(pSwapChain, SyncInterval, Flags);
}

ImGuiWindow& utils::begin_scene()
{
	ImGui_ImplDX11_NewFrame();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	ImGui::Begin(("##sus"), 0, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);

	auto& io = ImGui::GetIO();
	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

	return *ImGui::GetCurrentWindow();
}

void utils::end_scene(ImGuiWindow& window)
{
	window.DrawList->PushClipRectFullScreen();
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
	ImGui::Render();
}

void main()
{
	/* initalize the patterns */
	utils::uworld = Scanners::PatternScan("48 8B 05 ? ? ? ? 4D 8B C2");
	utils::uworld = rva(utils::uworld, 7);

	structs::_getobjectname = Scanners::PatternScan("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 33 F6 48 8B F2 44 39 71 04 0F 85 ? ? ? ? 8B 19 0F B7 FB E8 ? ? ? ? 8B CB 48 8D 54 24");
	structs::free_name = Scanners::PatternScan("48 85 C9 0F 84 ? ? ? ? 53 48 83 EC 20 48 89 7C 24 30 48 8B D9 48 8B 3D ? ? ? ? 48 85 FF 0F 84 ? ? ? ? 48 8B 07 4C 8B 40 30 48 8D 05 ? ? ? ? 4C 3B C0");
	
	structs::bone_matrix = Scanners::PatternScan("E8 ? ? ? ? 48 8B 47 30 F3 0F 10 45");
	structs::bone_matrix = rva(structs::bone_matrix, 5);

	utils::worldtoscreen = Scanners::PatternScan("E8 ? ? ? ? 41 88 07 48 83 C4 30");
	utils::worldtoscreen = rva(utils::worldtoscreen, 5);

	structs::los = Scanners::PatternScan("E8 ? ? ? ? 48 8B 0D ? ? ? ? 33 D2 40 8A F8");
	structs::los = rva(structs::los, 5);
}
