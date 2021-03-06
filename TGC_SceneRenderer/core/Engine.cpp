#include "Engine.h"

#include "../collections/SceneObjectsCollection.h"
#include "../collections/stored/StoredShaders.h"
#include "../scene/Camera.h"
#include "../scene/Mesh.h"
#include "../scene/Light.h"
#include "../types/ShaderProgram.h"
#include "../utils/FrameRate.h"
#include "../utils/Time.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "Data.h"
#include "../collections/MeshesCollection.h"
#include "../types/TextureRenderer.h"
#include "../utils/ShadowMapping.h"

using namespace core;

Engine::Engine(void) : initialized(false)
{
    // Get Tools / Collections Instances
    this->framerate     = utils::FrameRate::Instance();
    this->time          = utils::Time::Instance();
    this->lights        = collections::LightsCollection::Instance();
    this->meshes		= collections::MeshesCollection::Instance();
    this->cameras		= collections::CamerasCollection::Instance();
    this->sceneObjects  = collections::SceneObjectsCollection::Instance();
    this->textures		= collections::TexturesCollection::Instance();
}

Engine *core::Engine::Instance()
{
    if (!instance) {
        instance = new Engine();
    }

    return instance;
}

int core::Engine::load()
{
    return ogl_LoadFunctions();
}

void core::Engine::setup()
{
    if (this->initialized) { return; }

    // Initialize Engine Data
    core::Data::Initialize();
    // Setup OpenGL Flags
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_BACK);
    types::Texture::setAnisotropicFilteringLevel(core::EngineData::MaxAnisotropicFilteringAvaible());
    // Load member classes
    this->matrices = new Matrices();
    // Get a default stored shader
    types::ShaderProgram *shProgram = collections::stored::StoredShaders::getStoredShader(core::StoredShaders::Diffuse);
    // Initial camera setup
    this->activeCamera = this->sceneObjects->addCamera();
    this->activeCamera->base->transform.position.z += 5;
    collections::CamerasCollection::Instance()->setActiveCamera(0);
    // set elemental  matrices data info ubo
    this->matrices->setShaderProgram(shProgram);
    this->matrices->setUniformBlockInfo();
    // Initial Light UBO setup
    this->lights->setShaderProgram(shProgram);
    this->lights->setUniformBlockInfo();
    // Add lights to scene objects
    this->sceneObjects->addLight(scene::Light::Spot);
    this->lights->getLight(0)->base->transform.setPosition(0.0, 0.0, 3.0);
    this->lights->getLight(0)->enableShadowProjection(true, utils::ShadowMapping::ShadowQualityPreset::VeryHigh);
    // Add test objects
    this->sceneObjects->addMesh(StoredMeshes::Sphere);
    // set renderer is ready
    this->initialized = true;
}

void core::Engine::loop()
{
    // from cameras collection get the current active camera
    this->activeCamera = this->cameras->getActiveCamera();

    if (!this->activeCamera) { return; }

    // render from this camera position and parameters
    this->activeCamera->render(this);
}

void core::Engine::viewport(const unsigned int width, const unsigned int height)
{
    if (!initialized) { return; }

    this->cameras->getActiveCamera()->viewport(width, height);
}

void core::Engine::polygonModel(Modes mode)
{
    if (!initialized) { return; }

    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void core::Engine::unload()
{
    if (!initialized) { return; }

    core::Data::Clear();
    delete this->matrices;
}

core::Engine::~Engine()
{
    if (!initialized) { return; }

    unload();
}

Engine *core::Engine::instance = nullptr;
