#pragma once
#include <Engine.h>
#include "UI/ScenePanel.h"

namespace Syndra {

	class EditorLayer : public Layer
	{

	public:
		EditorLayer();
		~EditorLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;


	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void ShowMenuBars();
		void ShowIcons();
		void ShowGizmos();
		void ShowCameraSettings();
		void ShowRendererInfo();

		void OnLoadEditor();
		void ResetLayout();

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	private:

		Ref<Scene> m_ActiveScene;
		Ref<ScenePanel> m_ScenePanel;

		int m_GizmoType = 7;
		int m_GizmoMode = 0;
		bool m_GizmosChanged = true;
		Ref<Texture2D> m_GizmosIcon;

		bool altIsDown=false;
		bool m_FullScreen = false;
		Ref<Texture2D> m_FullScreenIcon;

		Ref<Texture2D> m_TransformIcon;
		Ref<Texture2D> m_RotationIcon;
		Ref<Texture2D> m_ScaleIcon;

		std::string m_Info;

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		//Showing and controlling tabs
		bool m_InfoOpen = true;
		bool m_ViewportOpen = true;
		bool m_CameraSettingOpen = false;
		bool m_SceneHierarchyOpen = true;
		bool m_PropertiesOpen = true;
		bool m_RendererOpen = true;
		bool m_EnvironmentOpen = true;

		glm::vec2 m_ViewportBounds[2];
		glm::vec2 m_ViewportSize = { 200.0f,200.0f};
		glm::vec3 m_CubeColor = { 1.0f,1.0f,1.0f };
		glm::vec3 m_Scale = { 1.0f,1.0f,1.0f };
		glm::vec3 m_ClearColor = { 0.196f, 0.196f, 0.196f };

	};
}
