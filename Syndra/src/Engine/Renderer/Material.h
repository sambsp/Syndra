#pragma once
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Texture.h"

namespace Syndra {


	class Material {

	public:
		struct ShaderMaterial
		{
			glm::vec4 color = glm::vec4(0.3f,0.3f,0.3f,1.0f);
			float RoughnessFactor = 1;
			float MetallicFactor = 0;
			float AO = 1;
		};

		struct CBuffer {
			ShaderMaterial material;
			int id;
			float tiling;
			int HasAlbedoMap;
			int HasNormalMap;
			int HasRoughnessMap;
			int HasMetallicMap;
			int HasAOMap;

			CBuffer() :
				id(-1), HasAOMap(1), HasNormalMap(1), HasRoughnessMap(1), HasAlbedoMap(1), HasMetallicMap(1),tiling(1) {}
		};

		Material() = default;
		Material(const Material& material) { 
			m_Shader = material.m_Shader;
			m_Samplers = m_Shader->GetSamplers();
			m_PushConstants = m_Shader->GetPushConstants();
			m_Textures = material.m_Textures;
			m_Cbuffer = material.m_Cbuffer;
			SetSamplersUsed();
		};
		Material(Ref<Shader>& shader);

		void Bind();

		std::vector<PushConstant>& GetPushConstants() { return m_PushConstants; }
		std::vector<Sampler>& GetSamplers() { return m_Samplers; }
		std::unordered_map<uint32_t, Ref<Texture2D>>& GetTextures() { return m_Textures; }
		
		void AddTexture(const Sampler& sampler, Ref<Texture2D>& texture);

		Ref<Shader> GetShader() const { return m_Shader; }
		Ref<Texture2D> GetTexture(const Sampler& sampler);
		CBuffer GetCBuffer() { return m_Cbuffer; }

		void SetTextures(const std::unordered_map<uint32_t, Ref<Texture2D>>& textures) { m_Textures = textures; }

		void Set(const std::string& name, float value);
		void Set(const std::string& name, int value);
		void Set(const std::string& name, const glm::vec4& value);
		void Set(const std::string& name, const glm::vec3& value);

		static Ref<Material> Create(Ref<Shader>& shader);

	private:
		void SetSamplersUsed();


	private:

		Ref<Shader> m_Shader;
		CBuffer m_Cbuffer;
		std::unordered_map<uint32_t, Ref<Texture2D>> m_Textures;

		std::vector<PushConstant> m_PushConstants;
		std::vector<Sampler> m_Samplers;

	};

}