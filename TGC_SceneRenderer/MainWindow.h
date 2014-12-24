#pragma once
#include "Collections/SceneObjectsCollection.h"
#include "Context/OpenGL.h"
#include "ObjectsWindow.h"
#include "InspectorWindow.h"
#include "Scene/Mesh.h"
#include "core/Data.h"
#include <msclr/marshal_cppstd.h>

namespace SceneRenderer {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace OGLContext;
    using namespace utils;

    /// <summary>
    /// Summary for Form1
    /// </summary>
    public ref class MainWindow : public System::Windows::Forms::Form {
        public:
            MainWindow(void)
            {
                InitializeComponent();
                this->TopLevel = true;
                // Setup OpenGL Render Context Inside a Panel
                System::Windows::Forms::Panel ^oglRenderPanel = this->OpenGLRenderPanel;
                OpenGL = gcnew COpenGL(oglRenderPanel, 0, 0, oglRenderPanel->ClientSize.Width, oglRenderPanel->ClientSize.Height);
                // Add OpenGL Info to Form Title
                this->Text += " (" + OpenGL->OGL_INFO_STRING + ")";
                // Other Components / Forms
                consoleIsActive               = true;
                objectsWindow                 = gcnew ObjectsWindow();
                inspWin                       = gcnew SceneRenderer::InspectorWindow();
                objectsWindow->InstancedBy    = this;
                inspWin->InstancedBy          = this;
                objectsWindow->Height   = this->Height / 2 - 5;
                inspWin->Height   = this->Height / 2 - 5;
                // Enable OGL rendering
                renderingEnabled = true;
            }

            ObjectsWindow ^GetObjectsWindow() { return objectsWindow; }
            InspectorWindow ^GetInspectorWindow() { return inspWin; }

            void EnableRendering(bool value)
            {
                this->renderingEnabled = value;
                // case true redraw
                this->OpenGLRenderPanel->Invalidate();
            }

        protected:
            /// <summary>
            /// Clean up any resources being used.
            /// </summary>
            ~MainWindow()
            {
                objectsWindow->Close();
                inspWin->Close();

                if (components) {
                    delete components;
                }
            }

        private: OGLContext::COpenGL ^OpenGL;
        private: ObjectsWindow ^objectsWindow;
        private: InspectorWindow ^inspWin;
        private: System::Windows::Forms::MenuStrip  ^topMenuBar;
        private: System::Boolean consoleIsActive;
        private: System::Boolean renderingEnabled;
            /// <summary>
            /// Required designer variable.
            /// </summary>
        private: System::Windows::Forms::ToolStripMenuItem  ^fileToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^newSceneToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^openSceneToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^saveSceneToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^exitToolStripMenuItem;
        private: System::Windows::Forms::ToolStripSeparator  ^toolStripSeparator1;
        private: System::Windows::Forms::ToolStripMenuItem  ^saveSceneAsToolStripMenuItem;
        private: System::Windows::Forms::ToolStripSeparator  ^toolStripSeparator2;
        private: System::Windows::Forms::ToolStripMenuItem  ^editToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^modelsToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^sceneObjectToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^windowToolStripMenuItem;
        private: System::Windows::Forms::OpenFileDialog  ^assetImportFileDialog;


        private: System::Windows::Forms::ToolStripMenuItem  ^consoleToolStripMenuItem;
        private: System::Windows::Forms::Panel  ^OpenGLRenderPanel;
        private: System::Windows::Forms::ToolStripMenuItem  ^createOtherToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^cameraToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^objectsToolStripMenuItem;

        private: System::Windows::Forms::ToolStripMenuItem  ^importAssetToolStripMenuItem;
        private: System::Windows::Forms::ToolStripSeparator  ^toolStripSeparator4;
        private: System::Windows::Forms::ToolStripMenuItem  ^directionalLightToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^spotLightToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^pointLightToolStripMenuItem;
        private: System::Windows::Forms::ToolStripSeparator  ^toolStripSeparator5;
        private: System::Windows::Forms::ToolStripMenuItem  ^cubeToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^sphereToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^settingsToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^torusToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^cylinderToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem  ^inspectorToolStripMenuItem;





            System::ComponentModel::Container ^components;

            #pragma region Windows Form Designer generated code
            /// <summary>
            /// Required method for Designer support - do not modify
            /// the contents of this method with the code editor.
            /// </summary>
            void InitializeComponent(void)
            {
                this->topMenuBar = (gcnew System::Windows::Forms::MenuStrip());
                this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->newSceneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->openSceneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
                this->saveSceneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->saveSceneAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
                this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->settingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->modelsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->importAssetToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->sceneObjectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->createOtherToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->cameraToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
                this->directionalLightToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->spotLightToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->pointLightToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
                this->cubeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->sphereToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->torusToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->cylinderToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->windowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->consoleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->objectsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->inspectorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->assetImportFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
                this->OpenGLRenderPanel = (gcnew System::Windows::Forms::Panel());
                this->topMenuBar->SuspendLayout();
                this->SuspendLayout();
                //
                // topMenuBar
                //
                this->topMenuBar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem ^  >(5) {
                    this->fileToolStripMenuItem,
                         this->editToolStripMenuItem, this->modelsToolStripMenuItem, this->sceneObjectToolStripMenuItem, this->windowToolStripMenuItem
                });
                this->topMenuBar->Location = System::Drawing::Point(0, 0);
                this->topMenuBar->Name = L"topMenuBar";
                this->topMenuBar->Size = System::Drawing::Size(1424, 24);
                this->topMenuBar->TabIndex = 1;
                this->topMenuBar->Text = L"topMenu";
                //
                // fileToolStripMenuItem
                //
                this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem ^  >(7) {
                    this->newSceneToolStripMenuItem,
                         this->openSceneToolStripMenuItem, this->toolStripSeparator1, this->saveSceneToolStripMenuItem, this->saveSceneAsToolStripMenuItem,
                         this->toolStripSeparator2, this->exitToolStripMenuItem
                });
                this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
                this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
                this->fileToolStripMenuItem->Text = L"File";
                //
                // newSceneToolStripMenuItem
                //
                this->newSceneToolStripMenuItem->Name = L"newSceneToolStripMenuItem";
                this->newSceneToolStripMenuItem->Size = System::Drawing::Size(157, 22);
                this->newSceneToolStripMenuItem->Text = L"New Scene";
                //
                // openSceneToolStripMenuItem
                //
                this->openSceneToolStripMenuItem->Name = L"openSceneToolStripMenuItem";
                this->openSceneToolStripMenuItem->Size = System::Drawing::Size(157, 22);
                this->openSceneToolStripMenuItem->Text = L"Open Scene";
                //
                // toolStripSeparator1
                //
                this->toolStripSeparator1->Name = L"toolStripSeparator1";
                this->toolStripSeparator1->Size = System::Drawing::Size(154, 6);
                //
                // saveSceneToolStripMenuItem
                //
                this->saveSceneToolStripMenuItem->Name = L"saveSceneToolStripMenuItem";
                this->saveSceneToolStripMenuItem->Size = System::Drawing::Size(157, 22);
                this->saveSceneToolStripMenuItem->Text = L"Save Scene";
                //
                // saveSceneAsToolStripMenuItem
                //
                this->saveSceneAsToolStripMenuItem->Name = L"saveSceneAsToolStripMenuItem";
                this->saveSceneAsToolStripMenuItem->Size = System::Drawing::Size(157, 22);
                this->saveSceneAsToolStripMenuItem->Text = L"Save Scene As...";
                //
                // toolStripSeparator2
                //
                this->toolStripSeparator2->Name = L"toolStripSeparator2";
                this->toolStripSeparator2->Size = System::Drawing::Size(154, 6);
                //
                // exitToolStripMenuItem
                //
                this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
                this->exitToolStripMenuItem->ShowShortcutKeys = false;
                this->exitToolStripMenuItem->Size = System::Drawing::Size(157, 22);
                this->exitToolStripMenuItem->Text = L"Exit";
                //
                // editToolStripMenuItem
                //
                this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem ^  >(1) {this->settingsToolStripMenuItem});
                this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
                this->editToolStripMenuItem->Size = System::Drawing::Size(39, 20);
                this->editToolStripMenuItem->Text = L"Edit";
                //
                // settingsToolStripMenuItem
                //
                this->settingsToolStripMenuItem->Name = L"settingsToolStripMenuItem";
                this->settingsToolStripMenuItem->Size = System::Drawing::Size(116, 22);
                this->settingsToolStripMenuItem->Text = L"Settings";
                //
                // modelsToolStripMenuItem
                //
                this->modelsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem ^  >(1) {this->importAssetToolStripMenuItem});
                this->modelsToolStripMenuItem->Name = L"modelsToolStripMenuItem";
                this->modelsToolStripMenuItem->Size = System::Drawing::Size(53, 20);
                this->modelsToolStripMenuItem->Text = L"Model";
                //
                // importAssetToolStripMenuItem
                //
                this->importAssetToolStripMenuItem->BackColor = System::Drawing::Color::White;
                this->importAssetToolStripMenuItem->Name = L"importAssetToolStripMenuItem";
                this->importAssetToolStripMenuItem->Size = System::Drawing::Size(147, 22);
                this->importAssetToolStripMenuItem->Text = L"Import Model";
                this->importAssetToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::importAssetToolStripMenuItem_Click);
                //
                // sceneObjectToolStripMenuItem
                //
                this->sceneObjectToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem ^  >(1) {this->createOtherToolStripMenuItem});
                this->sceneObjectToolStripMenuItem->Name = L"sceneObjectToolStripMenuItem";
                this->sceneObjectToolStripMenuItem->Size = System::Drawing::Size(88, 20);
                this->sceneObjectToolStripMenuItem->Text = L"Scene Object";
                //
                // createOtherToolStripMenuItem
                //
                this->createOtherToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem ^  >(10) {
                    this->cameraToolStripMenuItem,
                         this->toolStripSeparator4, this->directionalLightToolStripMenuItem, this->spotLightToolStripMenuItem, this->pointLightToolStripMenuItem,
                         this->toolStripSeparator5, this->cubeToolStripMenuItem, this->sphereToolStripMenuItem, this->torusToolStripMenuItem, this->cylinderToolStripMenuItem
                });
                this->createOtherToolStripMenuItem->Name = L"createOtherToolStripMenuItem";
                this->createOtherToolStripMenuItem->Size = System::Drawing::Size(141, 22);
                this->createOtherToolStripMenuItem->Text = L"Create Other";
                //
                // cameraToolStripMenuItem
                //
                this->cameraToolStripMenuItem->Name = L"cameraToolStripMenuItem";
                this->cameraToolStripMenuItem->Size = System::Drawing::Size(161, 22);
                this->cameraToolStripMenuItem->Text = L"Camera";
                //
                // toolStripSeparator4
                //
                this->toolStripSeparator4->Name = L"toolStripSeparator4";
                this->toolStripSeparator4->Size = System::Drawing::Size(158, 6);
                //
                // directionalLightToolStripMenuItem
                //
                this->directionalLightToolStripMenuItem->Name = L"directionalLightToolStripMenuItem";
                this->directionalLightToolStripMenuItem->Size = System::Drawing::Size(161, 22);
                this->directionalLightToolStripMenuItem->Text = L"Directional Light";
                //
                // spotLightToolStripMenuItem
                //
                this->spotLightToolStripMenuItem->Name = L"spotLightToolStripMenuItem";
                this->spotLightToolStripMenuItem->Size = System::Drawing::Size(161, 22);
                this->spotLightToolStripMenuItem->Text = L"Spot Light";
                //
                // pointLightToolStripMenuItem
                //
                this->pointLightToolStripMenuItem->Name = L"pointLightToolStripMenuItem";
                this->pointLightToolStripMenuItem->Size = System::Drawing::Size(161, 22);
                this->pointLightToolStripMenuItem->Text = L"Point Light";
                //
                // toolStripSeparator5
                //
                this->toolStripSeparator5->Name = L"toolStripSeparator5";
                this->toolStripSeparator5->Size = System::Drawing::Size(158, 6);
                //
                // cubeToolStripMenuItem
                //
                this->cubeToolStripMenuItem->Name = L"cubeToolStripMenuItem";
                this->cubeToolStripMenuItem->Size = System::Drawing::Size(161, 22);
                this->cubeToolStripMenuItem->Text = L"Cube";
                this->cubeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::cubeToolStripMenuItem_Click);
                //
                // sphereToolStripMenuItem
                //
                this->sphereToolStripMenuItem->Name = L"sphereToolStripMenuItem";
                this->sphereToolStripMenuItem->Size = System::Drawing::Size(161, 22);
                this->sphereToolStripMenuItem->Text = L"Sphere";
                this->sphereToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::sphereToolStripMenuItem_Click);
                //
                // torusToolStripMenuItem
                //
                this->torusToolStripMenuItem->Name = L"torusToolStripMenuItem";
                this->torusToolStripMenuItem->Size = System::Drawing::Size(161, 22);
                this->torusToolStripMenuItem->Text = L"Torus";
                this->torusToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::torusToolStripMenuItem_Click);
                //
                // cylinderToolStripMenuItem
                //
                this->cylinderToolStripMenuItem->Name = L"cylinderToolStripMenuItem";
                this->cylinderToolStripMenuItem->Size = System::Drawing::Size(161, 22);
                this->cylinderToolStripMenuItem->Text = L"Cylinder";
                this->cylinderToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::cylinderToolStripMenuItem_Click);
                //
                // windowToolStripMenuItem
                //
                this->windowToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem ^  >(3) {
                    this->consoleToolStripMenuItem,
                         this->objectsToolStripMenuItem, this->inspectorToolStripMenuItem
                });
                this->windowToolStripMenuItem->Name = L"windowToolStripMenuItem";
                this->windowToolStripMenuItem->Size = System::Drawing::Size(63, 20);
                this->windowToolStripMenuItem->Text = L"Window";
                //
                // consoleToolStripMenuItem
                //
                this->consoleToolStripMenuItem->Name = L"consoleToolStripMenuItem";
                this->consoleToolStripMenuItem->Size = System::Drawing::Size(123, 22);
                this->consoleToolStripMenuItem->Text = L"Console";
                this->consoleToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::consoleToolStripMenuItem_Click);
                //
                // objectsToolStripMenuItem
                //
                this->objectsToolStripMenuItem->Name = L"objectsToolStripMenuItem";
                this->objectsToolStripMenuItem->Size = System::Drawing::Size(123, 22);
                this->objectsToolStripMenuItem->Text = L"Objects";
                this->objectsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::objectsToolStripMenuItem_Click);
                //
                // inspectorToolStripMenuItem
                //
                this->inspectorToolStripMenuItem->Name = L"inspectorToolStripMenuItem";
                this->inspectorToolStripMenuItem->Size = System::Drawing::Size(123, 22);
                this->inspectorToolStripMenuItem->Text = L"Inspector";
                this->inspectorToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::inspectorToolStripMenuItem_Click);
                //
                // assetImportFileDialog
                //
                this->assetImportFileDialog->FileName = L"assetImportFileDialog";
                //
                // OpenGLRenderPanel
                //
                this->OpenGLRenderPanel->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
                this->OpenGLRenderPanel->Dock = System::Windows::Forms::DockStyle::Fill;
                this->OpenGLRenderPanel->Location = System::Drawing::Point(0, 24);
                this->OpenGLRenderPanel->Margin = System::Windows::Forms::Padding(0);
                this->OpenGLRenderPanel->Name = L"OpenGLRenderPanel";
                this->OpenGLRenderPanel->Size = System::Drawing::Size(1424, 838);
                this->OpenGLRenderPanel->TabIndex = 3;
                this->OpenGLRenderPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainWindow::timer1_Tick);
                this->OpenGLRenderPanel->Resize += gcnew System::EventHandler(this, &MainWindow::OpenGLRenderPanel_Resize);
                //
                // MainWindow
                //
                this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
                this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
                this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
                this->ClientSize = System::Drawing::Size(1424, 862);
                this->Controls->Add(this->OpenGLRenderPanel);
                this->Controls->Add(this->topMenuBar);
                this->MainMenuStrip = this->topMenuBar;
                this->Name = L"MainWindow";
                this->Text = L"TCG - SCENE";
                this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainWindow::MainWindow_FormClosing);
                this->Shown += gcnew System::EventHandler(this, &MainWindow::MainWindow_Shown);
                this->topMenuBar->ResumeLayout(false);
                this->topMenuBar->PerformLayout();
                this->ResumeLayout(false);
                this->PerformLayout();
            }
            #pragma endregion
        private: System::Void timer1_Tick(System::Object  ^sender, System::Windows::Forms::PaintEventArgs  ^e)
            {
                if (!renderingEnabled) { return; }

                OpenGL->restartStopwatch();
                UNREFERENCED_PARAMETER(sender);
                UNREFERENCED_PARAMETER(e);
                OpenGL->render();
                OpenGL->swapOpenGLBuffers();
                // Invalidate To Create a Game Loop
                ((System::Windows::Forms::Panel ^)sender)->Invalidate();
            }

        private: System::Void consoleToolStripMenuItem_Click(System::Object  ^sender, System::EventArgs  ^e)
            {
                consoleIsActive ? ShowWindow(GetConsoleWindow(), SW_HIDE) : ShowWindow(GetConsoleWindow(), SW_SHOW);
                consoleIsActive = !consoleIsActive;
            }
        private: System::Void objectsToolStripMenuItem_Click(System::Object  ^sender, System::EventArgs  ^e)
            {
                if (objectsWindow->Visible) {
                    objectsWindow->Hide();
                } else {
                    objectsWindow->Show();
                }
            }

        private: System::Void importAssetToolStripMenuItem_Click(System::Object  ^sender, System::EventArgs  ^e)
            {
                System::Windows::Forms::DialogResult result = assetImportFileDialog->ShowDialog();

                if (result != System::Windows::Forms::DialogResult::Cancel) {
                    msclr::interop::marshal_context context;
                    std::string standardString = context.marshal_as<std::string>(assetImportFileDialog->FileName);
                    // Load mesh
                    collections::SceneObjectsCollection::Instance()->addMeshFromFile(standardString);
                    // Notify the objects window of the new addition
                    this->objectsWindow->addedObject();
                }
            }
        private: System::Void MainWindow_Shown(System::Object  ^sender, System::EventArgs  ^e)
            {
                // Show Tool Windows At Startup
                objectsWindow->Show();
                inspWin->Show();
                objectsWindow->Refresh();
                inspWin->Refresh();
                // Set Convenient positions
                this->SetDesktopLocation(50, 50);
                this->objectsWindow->SetDesktopLocation(this->DesktopLocation.X + this->Width + 5, this->DesktopLocation.Y);
                this->inspWin->SetDesktopLocation(this->DesktopLocation.X + this->Width + 5, this->DesktopLocation.Y + this->inspWin->Height + 5);
                // Refresh Parent
                this->Refresh();
            }
        private: System::Void MainWindow_FormClosing(System::Object  ^sender, System::Windows::Forms::FormClosingEventArgs  ^e)
            {
                OpenGL->~COpenGL();
            }
        private: System::Void cubeToolStripMenuItem_Click(System::Object  ^sender, System::EventArgs  ^e)
            {
                this->objectsWindow->addCube();
            }
        private: System::Void sphereToolStripMenuItem_Click(System::Object  ^sender, System::EventArgs  ^e)
            {
                this->objectsWindow->addSphere();
            }
        private: System::Void torusToolStripMenuItem_Click(System::Object  ^sender, System::EventArgs  ^e)
            {
                this->objectsWindow->addTorus();
            }
        private: System::Void cylinderToolStripMenuItem_Click(System::Object  ^sender, System::EventArgs  ^e)
            {
                this->objectsWindow->addCylinder();
            }
        private: System::Void inspectorToolStripMenuItem_Click(System::Object  ^sender, System::EventArgs  ^e)
            {
                if (inspWin->Visible) {
                    inspWin->Hide();
                } else {
                    inspWin->Show();
                }
            }
        private: System::Void OpenGLRenderPanel_Resize(System::Object  ^sender, System::EventArgs  ^e)
            {
                this->OpenGL->resizeRenderingViewPort(this->OpenGLRenderPanel->Width, this->OpenGLRenderPanel->Height);
            }
    };
}

