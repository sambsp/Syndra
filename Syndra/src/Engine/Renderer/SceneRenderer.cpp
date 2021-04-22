#include "lpch.h"
#include "Engine/Renderer/SceneRenderer.h"
#include <glad/glad.h>
#include "Engine/Scene/Entity.h"

namespace Syndra {

	SceneRenderer::SceneData* SceneRenderer::s_Data = new SceneRenderer::SceneData;

	void SceneRenderer::Initialize()
	{
		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8 , FramebufferTextureFormat::DEPTH24STENCIL8 };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		fbSpec.Samples = 4;
		s_Data->mainFB = FrameBuffer::Create(fbSpec);
		fbSpec.Samples = 1;
		s_Data->postProcFB = FrameBuffer::Create(fbSpec);
		fbSpec.Attachments = { FramebufferTextureFormat::RED_INTEGER , FramebufferTextureFormat::DEPTH24STENCIL8 };
		s_Data->mouseFB = FrameBuffer::Create(fbSpec);

		if (!s_Data->aa) {
			s_Data->shaders.Load("assets/shaders/aa.glsl");
			s_Data->shaders.Load("assets/shaders/diffuse.glsl");
			s_Data->shaders.Load("assets/shaders/mouse.glsl");
			s_Data->shaders.Load("assets/shaders/outline.glsl");
		}
		s_Data->aa = s_Data->shaders.Get("aa");
		s_Data->diffuse = s_Data->shaders.Get("diffuse");
		s_Data->mouseShader = s_Data->shaders.Get("mouse");
		s_Data->outline = s_Data->shaders.Get("outline");

		s_Data->clearColor = glm::vec3(0.196f, 0.196f, 0.196f);

		s_Data->screenVao = VertexArray::Create();
		float quad[] = {
			 1.0f,  1.0f, 0.0f,    1.0f, 1.0f,   // top right
			 1.0f, -1.0f, 0.0f,    1.0f, 0.0f,   // bottom right
			-1.0f, -1.0f, 0.0f,    0.0f, 0.0f,   // bottom left
			-1.0f,  1.0f, 0.0f,    0.0f, 1.0f    // top left 
		};
		auto quadVB = VertexBuffer::Create(quad, sizeof(quad));
		s_Data->screenVao->AddVertexBuffer(quadVB);
		BufferLayout quadLayout = {
			{ShaderDataType::Float3,"a_pos"},
			{ShaderDataType::Float2,"a_uv"},
		};
		quadVB->SetLayout(quadLayout);
		s_Data->screenVao->AddVertexBuffer(quadVB);
		unsigned int quadIndices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
		auto indexBuffer = IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
		s_Data->screenVao->SetIndexBuffer(indexBuffer);
	}

	void SceneRenderer::BeginScene(const PerspectiveCamera& camera)
	{
		s_Data->camera = CreateRef<PerspectiveCamera>(camera);
		s_Data->mainFB->Bind();

		RenderCommand::SetClearColor(glm::vec4(s_Data->clearColor, 1.0f));
		RenderCommand::Clear();
		//glEnable(GL_DEPTH_TEST);
		Renderer::BeginScene(camera);

	}

	void SceneRenderer::RenderEntity(const Entity& entity, TransformComponent& tc, MeshComponent& mc)
	{
		//--------------------------------------------------color and outline pass------------------------------------------------//
		s_Data->diffuse->Bind();
		//TODO material system
		//m_Texture->Bind(0);
		s_Data->diffuse->SetMat4("u_trans", tc.GetTransform());
		s_Data->diffuse->SetFloat3("cameraPos", s_Data->camera->GetPosition());
		s_Data->diffuse->SetFloat3("lightPos", s_Data->camera->GetPosition());
		//difShader->SetFloat3("cubeCol", m_CubeColor);
		glEnable(GL_DEPTH_TEST);
		if (entity.IsSelected())
		{
			s_Data->outline->Bind();
			auto transform = tc;
			transform.Scale += glm::vec3(.05f);
			s_Data->outline->SetMat4("u_trans", transform.GetTransform());
			Renderer::Submit(s_Data->outline, mc.model);
			RenderCommand::SetState(GL_DEPTH_TEST, false);
		}
		//TODO
		Renderer::Submit(s_Data->diffuse, mc.model);

		//-------------------------------------------------entity id pass--------------------------------------------------------//
		s_Data->mouseFB->Bind();
		RenderCommand::SetClearColor(glm::vec4(s_Data->clearColor, 1.0f));
		RenderCommand::Clear();
		s_Data->mouseFB->ClearAttachment(0, -1);
		RenderCommand::SetState(GL_DEPTH_TEST, true);

		s_Data->mouseShader->Bind();
		s_Data->mouseShader->SetMat4("u_trans", tc.GetTransform());
		s_Data->mouseShader->SetInt("u_ID", (uint32_t)entity);
		Renderer::Submit(s_Data->mouseShader, mc.model);
	}

	void SceneRenderer::EndScene()
	{
		//-------------------------------------------------post-processing pass---------------------------------------------------//

		s_Data->postProcFB->Bind();
		RenderCommand::Clear();
		s_Data->screenVao->Bind();
		RenderCommand::SetState(GL_DEPTH_TEST, false);
		s_Data->aa->Bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, s_Data->mainFB->GetColorAttachmentRendererID());
		Renderer::Submit(s_Data->aa, s_Data->screenVao);

		s_Data->postProcFB->Unbind();
		Renderer::EndScene();
	}

	void SceneRenderer::OnViewPortResize(uint32_t width, uint32_t height)
	{
		s_Data->mainFB->Resize(width, height);
		s_Data->postProcFB->Resize(width, height);
		s_Data->mouseFB->Resize(width, height);
	}

}