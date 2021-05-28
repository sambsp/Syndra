#pragma once
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Texture.h"

namespace Syndra {


	class Material {

		struct ShaderMaterial
		{
			glm::vec4 color;
		};

		struct CBuffer{
			ShaderMaterial mat;
			int HasDiffuseMap;
			int HasNormalMap;
		};

	public:

		Material() = default;
		Material(const Material& material) { 
			m_Shader = material.m_Shader;
			m_Samplers = m_Shader->GetSamplers();
			m_PushConstants = m_Shader->GetPushConstants();
		};
		Material(Ref<Shader>& shader);

		void Bind();

		std::vector<PushConstant>& GetPushConstants() { return m_PushConstants; }
		std::vector<Sampler>& GetSamplers() { return m_Samplers; }
		std::unordered_map<uint32_t, Ref<Texture2D>>& GetTextures() { return m_Textures; }
		
		void AddTexture(const Sampler& sampler, Ref<Texture2D>& texture);

		Ref<Texture2D> GetTexture(const Sampler& sampler);

		void Set(const std::string& name, float value);
		void Set(const std::string& name, int value);
		void Set(const std::string& name, const glm::vec4& value);
		void Set(const std::string& name, const glm::vec3& value);

		static Ref<Material> Create(Ref<Shader>& shader);

	private:

		Ref<Shader> m_Shader;
		CBuffer m_Cbuffer;
		std::unordered_map<uint32_t, Ref<Texture2D>> m_Textures;

		std::vector<PushConstant> m_PushConstants;
		std::vector<Sampler> m_Samplers;

	};

}