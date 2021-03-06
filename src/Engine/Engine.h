#ifndef GAMEENGINE_ENGINE_H
#define GAMEENGINE_ENGINE_H

#include <Actors/Quad.h>
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Bullet.h"
#include "Camera.h"

struct Engine {
public:
    static Engine& Editor();
    void Render();
    Engine(Engine&) = delete;
    Engine& operator=(Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    void ConfigPlayerAnim(GameObjects::ACTION act, const std::string & sprite_name, const std::vector<std::vector<float>> & sprite_frames);
    void ConfigPlayerParticles(const std::string & sprite_name);
    inline void SetPlayer(glm::vec2 position, glm::vec2 size, float rotation, float layer){
        player_controller.reset();
        player_controller = std::make_shared<GameObjects::Player>(position, size, rotation, layer);
        player_start_pos = position;
    };
    [[nodiscard]] inline std::shared_ptr<GameObjects::Player> & GetPlayerController() {
        return player_controller;
    }
    void PlayerDeadChecker();

    void SetDeadSign(glm::vec2 size = {1.f, 1.f}, float timer_to_restart = 3.f);
    void ConfigSpriteDeadSign(const std::string & sprite_name);

    void SetPauseSign(glm::vec2 size = {1.f, 1.f});
    void ConfigSpritePauseSign(const std::string & sprite_name);

    bool CheckPauseMode(GLFWwindow *window);

    void SetMap(glm::vec2 position, glm::vec2 size);
    void ConfigSpriteMap(const std::string & sprite_name);

    void SetProp(glm::vec2 position, glm::vec2 size);
    void ConfigSpriteProp(const std::string & sprite_name);

    void SetEnemiesSpawns(std::vector<glm::vec2> spawn_pos);
    void SetEnemies(glm::vec2 size, float layer, size_t numbers);
    void ConfigEnemies(GameObjects::ACTION act, const std::string & sprite_name, glm::vec2 left_bottom,
                       glm::vec2 right_top,
                       float x,
                       float y,
                       size_t vertical,
                       size_t horizontal);

    void SetSprite(const std::string & name,
                   const std::string & texture_name);

    void SetSpritePack(const std::string & name,
                   const std::string & texture_name, size_t max_count);

    void SetTexture(const std::string& name,
                    const std::filesystem::path &,

                    unsigned int type = GL_RGBA,
                    unsigned int format = GL_RGBA,
                    bool flip_vertically = true);

    void SetShader(const std::filesystem::path & vertex_shader, const std::filesystem::path & fragment_shader);

    void SetCameraUpdatePosition();

private:
    Engine() = default;

    std::shared_ptr<Shader> m_shader;

    std::shared_ptr<GameObjects::Player> player_controller = nullptr;
    glm::vec2 player_start_pos;
    std::shared_ptr<GameObjects::Quad> map;
    std::shared_ptr<GameObjects::Quad> DeadSign;
    std::shared_ptr<GameObjects::Quad> PauseSign;
    std::vector<std::shared_ptr<GameObjects::Quad>> props;

    float StartDeathTime = 0.f;
    bool is_Dead = false;
    float deltaTime;
    bool On_Pause = false;

    std::vector<std::shared_ptr<GameObjects::Enemy>> enemies;

    std::map<std::string, std::shared_ptr<Graphic::Sprite>> pool_sprites;
    std::map<std::string, std::vector<std::shared_ptr<Graphic::Sprite>>> pool_pack_sprites;
    std::map<std::string, std::shared_ptr<Graphic::Texture2D>> pool_textures;

    std::shared_ptr<Camera> m_cam;
};


#endif //GAMEENGINE_ENGINE_H
