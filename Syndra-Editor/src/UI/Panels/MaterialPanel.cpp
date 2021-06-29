#include "lpch.h"
#include "MaterialPanel.h"
#include "Engine/Utils/PlatformUtils.h"


namespace Syndra {

	MaterialPanel::MaterialPanel()
	{
		m_EmptyTexture = Texture2D::Create("assets/Models/cube/default.png");
		m_TextureId = reinterpret_cast<void*>(m_EmptyTexture->GetRendererID());
	}

	void MaterialPanel::DrawMaterial(Entity& entity)
	{
		static bool MaterialRemoved = false;
		ImGui::Separator();
		if (UI::DrawComponent<MaterialComponent>("Material", entity, true, &MaterialRemoved))
		{
			auto& component = entity.GetComponent<MaterialComponent>();

			ImGui::Separator();
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 80);
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
			ImGui::Text("Shader\0");

			ImGui::PopStyleVar();
			ImGui::NextColumn();
			ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());
			ImGui::Text("PBR shader\0");
			ImGui::PopItemWidth();
			ImGui::Columns(1);

			ImGui::Separator();

			ImGuiIO& io = ImGui::GetIO();
			std::vector<Sampler>& samplers = component.m_Material.GetSamplers();
			auto& materialTextures = component.m_Material.GetTextures();
			const auto& buffer = component.m_Material.GetCBuffer();

			float tiling = buffer.tiling;
			if (UI::DragFloat("Tiling", &tiling, 0.05f, 0.001f, 100)) {
				component.m_Material.Set("tiling", tiling);
			}

			for (auto& sampler : samplers)
			{
				ImGui::PushID(sampler.name.c_str());
				ImGui::Separator();
				int frame_padding = -1 + 0;                              // -1 == uses default padding (style.FramePadding)
				ImVec2 size = ImVec2(64.0f, 64.0f);                      // Size of the image we want to make visible
				ImGui::Checkbox("Use", &sampler.isUsed);
				ImGui::SameLine();
				ImGui::Text(sampler.name.c_str());

				m_TextureId = reinterpret_cast<void*>(m_EmptyTexture->GetRendererID());
				auto& texture = component.m_Material.GetTexture(sampler);
				if (texture)
				{
					m_TextureId = reinterpret_cast<void*>(texture->GetRendererID());
				}

				if (ImGui::ImageButton(m_TextureId, size, ImVec2{ 0, 1 }, ImVec2{ 1, 0 })) {

					auto path = FileDialogs::OpenFile("Syndra Texture (*.*)\0*.*\0");
					if (path) {
						//Add texture as sRGB color space if it is binded to 0 (diffuse texture binding)
						materialTextures[sampler.binding] = Texture2D::Create(*path);
					}
				}

				//Albedo color
				if (sampler.binding == 0) {
					glm::vec4 color = buffer.material.color;
					if (ImGui::ColorEdit4("Albedo", glm::value_ptr(color), ImGuiColorEditFlags_NoInputs)) {
						component.m_Material.Set("push.material.color", color);
					}
				}
				//metal factor
				if (sampler.binding == 1) {
					float metal = buffer.material.MetallicFactor;
					if (UI::SliderFloat("Metallic", &metal, 0.0f, 1.0f)) {
						component.m_Material.Set("push.material.MetallicFactor", metal);
					}
				}
				//Roughness factor
				if (sampler.binding == 3) {
					float roughness = buffer.material.RoughnessFactor;
					if (UI::SliderFloat("Roughness", &roughness, 0.0f, 1.0f)) {
						component.m_Material.Set("push.material.RoughnessFactor", roughness);
					}
				}
				//Ambient Occlusion factor
				if (sampler.binding == 4) {
					float AO = buffer.material.AO;
					if (UI::SliderFloat("Ambient Occlusion", &AO, 0.0f, 1.0f)) {
						component.m_Material.Set("push.material.AO", AO);
					}
				}
				ImGui::PopID();
			}
			ImGui::TreePop();
			ImGui::Separator();
		}

		if (MaterialRemoved) {
			entity.RemoveComponent<MaterialComponent>();
			MaterialRemoved = false;
		}
	}

}

