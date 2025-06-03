#include "App.hpp"

#include "log_my.hpp"
#include "Angel.hpp"
#include "Enemy_2.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include <iostream>
#include <memory>
#include <ostream>

void App::ValidTask() {
    LOG_TRACE("ValidTask");
    switch (m_player_level) {
    case player_level::lobby:
        m_Background->SetBackground("background");
        LOG_DEBUG("lobby");
        break;

    case player_level::first_level:
        LOG_DEBUG("first_level");
        break;
    
    case player_level::second_level:{
        LOG_DEBUG("second_level");
        now_level = 2;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();

        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2 (-470.36f, 44.0f) , glm::vec2(-305.836f , 200.584f));
        wall->setwall(glm::vec2 (-470.03f, -191.562f) , glm::vec2(-305.101f , -38.670f));
        wall->setwall(glm::vec2 (-134.625f,60.9083f) , glm::vec2(-90.1393f , 162.386f));
        wall->setwall(glm::vec2 (-134.625f,-163.9083f) , glm::vec2(-90.1393f , -64.2383f));                   

        InitializeEnemy_2(glm::vec2(144, 116));

        InitializeEnemy_2(glm::vec2(144, -116));

        InitializeEnemy_2(glm::vec2(250, 0));
        
        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }
    case player_level ::third_level:{
        LOG_DEBUG("third_level");
        now_level = 3;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2 (-389.86f, 91.006f) , glm::vec2(-153.184f , 118.659f));
        wall->setwall(glm::vec2 (-74.8f, 93.42f) , glm::vec2(167.101f , 118.670f));
        wall->setwall(glm::vec2 (-399.625f,-122.9083f) , glm::vec2(-143.606f , -88.7307f));
        wall->setwall(glm::vec2 (-74.625f,-122.9083f) , glm::vec2(169.1393f , -88.7307f));                   

        std::shared_ptr<Enemy_3> m_Enemy6 = std::make_shared<Enemy_3>();
        m_Enemy6->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy6->SetZIndex(5);
        m_Enemy6->Start(glm::vec2(226, 145)); // 初始化敵人的位置
        m_Enemy6->setWall(wall);
        m_Enemies.push_back(m_Enemy6);
        m_Root.AddChild(m_Enemy6);
        
        std::shared_ptr<Enemy_3> m_Enemy7 = std::make_shared<Enemy_3>();
        m_Enemy7->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy7->SetZIndex(5);
        m_Enemy7->Start(glm::vec2(226, -140)); // 初始化敵人的位置
        m_Enemy7->setWall(wall);
        m_Enemies.push_back(m_Enemy7);
        m_Root.AddChild(m_Enemy7);
        
        std::shared_ptr<Enemy_3> m_Enemy8 = std::make_shared<Enemy_3>();
        m_Enemy8->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy8->SetZIndex(5);
        m_Enemy8->Start(glm::vec2(-289, -156)); // 初始化敵人的位置
        m_Enemy8->setWall(wall);
        m_Enemies.push_back(m_Enemy8);
        m_Root.AddChild(m_Enemy8);

        std::shared_ptr<Enemy_3> m_Enemy9 = std::make_shared<Enemy_3>();
        m_Enemy9->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy9->SetZIndex(5);
        m_Enemy9->Start(glm::vec2(-289, 156)); // 初始化敵人的位置
        m_Enemy9->setWall(wall);
        m_Enemies.push_back(m_Enemy9);
        m_Root.AddChild(m_Enemy9);


        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::fourth_level:{
        LOG_DEBUG("fourth_level");
        now_level = 4;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2 (-398.86f, 73.006f) , glm::vec2(-149.116f , 121.659f));
        wall->setwall(glm::vec2 (-398.523f, -131.287f) , glm::vec2(-364.459f , 124.414f));
        wall->setwall(glm::vec2 (-398.883f,-124.099f) , glm::vec2(-146.449f , -52.8387f));
        
        wall->setwall(glm::vec2 (-35.7017f,72.0359f) , glm::vec2(210.873f , 123.596f));                
        wall->setwall(glm::vec2 (166.669f,-122.415f) , glm::vec2(211.375f , 123.596f));                
        wall->setwall(glm::vec2 (-40.2019f,-123.842f) , glm::vec2(210.154f , -63.2669f));                

        std::shared_ptr<Enemy_3> m_Enemy10 = std::make_shared<Enemy_3>();
        m_Enemy10->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy10->SetZIndex(5);
        m_Enemy10->Start(glm::vec2(237, 157)); // 初始化敵人的位置
        m_Enemy10->setWall(wall);
        m_Enemies.push_back(m_Enemy10);
        m_Root.AddChild(m_Enemy10);
        
        std::shared_ptr<Enemy_3> m_Enemy11 = std::make_shared<Enemy_3>();
        m_Enemy11->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy11->SetZIndex(5);
        m_Enemy11->Start(glm::vec2(237, -162)); // 初始化敵人的位置
        m_Enemy11->setWall(wall);
        m_Enemies.push_back(m_Enemy11);
        m_Root.AddChild(m_Enemy11);

        std::shared_ptr<Enemy_2> m_Enemy12 = std::make_shared<Enemy_2>();
        m_Enemy12->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));  
        m_Enemy12->SetZIndex(5);
        m_Enemy12->Start(glm::vec2(59.96f, 5.513f)); // 初始化敵人的位置
        m_Enemy12->setWall(wall);
        m_Enemies.push_back(m_Enemy12);
        m_Root.AddChild(m_Enemy12);
        
        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-500, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::fifth_level:{
        LOG_DEBUG("fifth_level");
        now_level = 5;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2 (-460.86f, 83.006f) , glm::vec2(267.116f , 125.659f));
        wall->setwall(glm::vec2 (-462.523f, -119.287f) , glm::vec2(267.459f , -85.414f));
        
        std::shared_ptr<Angel> m_Angel = std::make_shared<Angel>();
        m_Angel->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/angel.png"));
        m_Angel->SetZIndex(10);
        m_Angel->Start(glm::vec2(200, 0)); // 初始化敵人的位置
        m_Angel->setWall(wall);
        m_Enemies.push_back(m_Angel);
        m_Root.AddChild(m_Angel);

        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        giraffe_exp = 0;
        is_enemy_empty = false;
        break;
    }

    case player_level::sixth_level:{
        LOG_DEBUG("sixth_level");
        now_level = 6;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        
        std::shared_ptr<Enemy_2> m_Enemy13 = std::make_shared<Enemy_2>();
        m_Enemy13->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy13->SetZIndex(5);
        m_Enemy13->Start(glm::vec2(200, 0)); // 初始化敵人的位置
        m_Enemy13->setWall(wall);
        m_Enemy13->setHP(200);
        m_Enemies.push_back(m_Enemy13);
        m_Root.AddChild(m_Enemy13);

        std::shared_ptr<Enemy_3> m_Enemy10 = std::make_shared<Enemy_3>();
        m_Enemy10->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/enemy.png"));
        m_Enemy10->SetZIndex(5);
        m_Enemy10->Start(glm::vec2(237, 157)); // 初始化敵人的位置
        m_Enemy10->setWall(wall);
        m_Enemies.push_back(m_Enemy10);
        m_Root.AddChild(m_Enemy10);
        
        std::shared_ptr<Enemy_3> m_Enemy11 = std::make_shared<Enemy_3>();
        m_Enemy11->Start(glm::vec2(237, -162)); // 初始化敵人的位置
        m_Enemy11->setWall(wall);
        m_Enemies.push_back(m_Enemy11);
        m_Root.AddChild(m_Enemy11);

        m_Ground_Spikes -> Add_Spikes(glm::vec2(55, -160));
        m_Ground_Spikes -> Add_Spikes(glm::vec2(55, -105));
        m_Ground_Spikes -> Add_Spikes(glm::vec2(55, -50));
        m_Ground_Spikes -> Add_Spikes(glm::vec2(0, -160));
        m_Ground_Spikes -> Add_Spikes(glm::vec2(-55, -160));

        m_Ground_Spikes -> Add_Spikes(glm::vec2(55, 50));
        m_Ground_Spikes -> Add_Spikes(glm::vec2(55, 105));
        m_Ground_Spikes -> Add_Spikes(glm::vec2(55, 160));
        m_Ground_Spikes -> Add_Spikes(glm::vec2(0, 160));
        m_Ground_Spikes -> Add_Spikes(glm::vec2(-55, 160));

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::seventh_level:{
        LOG_DEBUG("seventh_level");
        now_level = 7;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->clear();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2(-327.061f, 48.5351f), glm::vec2(-185.372f, 116.312f));
        wall->setwall(glm::vec2(-327.383f, -126.515f), glm::vec2(-185.092f, -59.2642f));
        wall->setwall(glm::vec2(-111.49f, 56.3841f), glm::vec2(-60.9309f, 156.414f));
        wall->setwall(glm::vec2(-120.458f, -153.443f), glm::vec2(-53.4003f, -60.0543f));
        wall->setwall(glm::vec2(66.9633f, 16.8441f), glm::vec2(175.582f, 125.904f),"lake");
        wall->setwall(glm::vec2(64.9195f, -119.798f), glm::vec2(174.31f, -17.4799f),"lake");

        std::shared_ptr<Enemy_3> m_Enemy14 = std::make_shared<Enemy_3>();
        m_Enemy14->Start(glm::vec2(123.611,70.2924)); // 初始化敵人的位置
        m_Enemy14->setWall(wall);
        m_Enemies.push_back(m_Enemy14);
        m_Root.AddChild(m_Enemy14);

        std::shared_ptr<Enemy_3> m_Enemy15 = std::make_shared<Enemy_3>();
        m_Enemy15->Start(glm::vec2(123.611,-72.401)); // 初始化敵人的位置
        m_Enemy15->setWall(wall);
        m_Enemies.push_back(m_Enemy15);
        m_Root.AddChild(m_Enemy15);

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::eighth_level:{
        LOG_DEBUG("eighth_level");
        now_level = 8;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->clear();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2(-378.354,79.6777) , glm::vec2(234.131, 122.405),"lake");
        wall->setwall(glm::vec2(-463.447,86.7026) , glm::vec2(-378.354, 121.696),"");
        wall->setwall(glm::vec2(-381.412,-132.446) , glm::vec2(234.358, -90.0606),"lake");
        wall->setwall(glm::vec2(-458.084,-134.085) , glm::vec2(-381.412, -92.4253),"");
        
        std::shared_ptr<Enemy_4> m_Enemy16 = std::make_shared<Enemy_4>();
        m_Enemy16->Start(glm::vec2(123.611,-70)); // 初始化敵人的位置
        m_Enemy16->setWall(wall);
        m_Enemies.push_back(m_Enemy16);
        m_Root.AddChild(m_Enemy16);

        std::shared_ptr<Enemy_4> m_Enemy17 = std::make_shared<Enemy_4>();
        m_Enemy17->Start(glm::vec2(123.611,70)); // 初始化敵人的位置
        m_Enemy17->setWall(wall);
        m_Enemies.push_back(m_Enemy17);
        m_Root.AddChild(m_Enemy17);

        std::shared_ptr<Enemy_3> m_Enemy18 = std::make_shared<Enemy_3>();
        m_Enemy18->Start(glm::vec2(-423.512,157.997)); // 初始化敵人的位置
        m_Enemy18->setWall(wall);
        m_Enemies.push_back(m_Enemy18);
        m_Root.AddChild(m_Enemy18);

        std::shared_ptr<Enemy_3> m_Enemy19 = std::make_shared<Enemy_3>();
        m_Enemy19->Start(glm::vec2(-431.604,-160.49)); // 初始化敵人的位置
        m_Enemy19->setWall(wall);
        m_Enemies.push_back(m_Enemy19);
        m_Root.AddChild(m_Enemy19);

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::ninth_level:{
        LOG_DEBUG("ninth_level");
        now_level = 9;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->clear();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2(202.875,26.502) , glm::vec2(237.063,184.1));
        wall->setwall(glm::vec2(195.252,-188.736) , glm::vec2(245.433,-53.9041));
        wall->setwall(glm::vec2(70.5935,-60.51) , glm::vec2(112.325,48.3685));
        wall->setwall(glm::vec2(-355.065,23.7796) , glm::vec2(-255.647,118.883),"lake");
        wall->setwall(glm::vec2(-351.156,-126.621) , glm::vec2(-257.874,-25.9397),"lake");
        
        std::shared_ptr<Enemy_1> m_Enemy20 = std::make_shared<Enemy_1>();
        m_Enemy20->Start(glm::vec2(-123.611,70)); // 初始化敵人的位置
        m_Enemy20->setWall(wall);
        m_Enemies.push_back(m_Enemy20);
        m_Root.AddChild(m_Enemy20);

        std::shared_ptr<Enemy_1> m_Enemy21 = std::make_shared<Enemy_1>();
        m_Enemy21->Start(glm::vec2(-123.611,-70)); // 初始化敵人的位置
        m_Enemy21->setWall(wall);
        m_Enemies.push_back(m_Enemy21);
        m_Root.AddChild(m_Enemy21);

        std::shared_ptr<Enemy_3> m_Enemy22 = std::make_shared<Enemy_3>();
        m_Enemy22->Start(glm::vec2(172.329, 166.244)); // 初始化敵人的位置
        m_Enemy22->setWall(wall);
        m_Enemies.push_back(m_Enemy22);
        m_Root.AddChild(m_Enemy22);

        std::shared_ptr<Enemy_3> m_Enemy23 = std::make_shared<Enemy_3>();
        m_Enemy23->Start(glm::vec2(172.329, -166.244)); // 初始化敵人的位置
        m_Enemy23->setWall(wall);
        m_Enemies.push_back(m_Enemy23);
        m_Root.AddChild(m_Enemy23);

        std::shared_ptr<Enemy_5> m_Enemy18 = std::make_shared<Enemy_5>();
        m_Enemy18->Start(glm::vec2(247.056,-13.8528)); // 初始化敵人的位置
        m_Enemy18->setWall(wall);
        m_Enemies.push_back(m_Enemy18);
        m_Root.AddChild(m_Enemy18);

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }
        

    case player_level::tenth_level:{
        LOG_DEBUG("tenth_level");
        
        levelstatus = levelstatus::boss_level;
        now_level = 10;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        
        std::shared_ptr<Boss_1_1> m_Boss_1_1 = std::make_shared<Boss_1_1>();
        // std::shared_ptr<Boss_2> m_Boss_1_1 = std::make_shared<Boss_2>();
        m_Boss_1_1->Start(glm::vec2(0, 0)); // 初始化敵人的位置
        m_Boss_1_1->setWall(wall);
        m_Enemies.push_back(m_Boss_1_1);
        m_Root.AddChild(m_Boss_1_1);    

        giraffe_exp = 0;
        // std::cout << "m_Boss_1_1 finish" << std::endl;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        // std::cout << "m_Giraffe set finish" << std::endl;
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }
    case player_level::eleventh_level:{
        LOG_DEBUG("eleventh_level");
        levelstatus = levelstatus::normal_level;
        now_level = 11;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(220.0f, -220.0f, -455.0f, 194.0f, 24.0f, -26.0f);
        wall->setwall(glm::vec2(-325.162933 , 151.094772), glm::vec2(75 , 200),"lake");
        wall->setwall(glm::vec2(-325.162933 , 76.490715), glm::vec2(-276.849213 , 151.094772),"lake");
        wall->setwall(glm::vec2(22.515726, -201.125214), glm::vec2(75 , 200),"lake");
        wall->setwall(glm::vec2(-317.187531 , -196.484528), glm::vec2(73.025383 , -146.556702),"lake");
        wall->setwall(glm::vec2(-317.187531 , -196.484528), glm::vec2(-282.300720 , -71.500229),"lake");
        

        InitializeEnemy_7(glm::vec2 (100, -100), 100);
        InitializeEnemy_7(glm::vec2 (100, 100), 100);
        InitializeEnemy_7(glm::vec2 (100, -150), 100);
        InitializeEnemy_7(glm::vec2 (100, 150), 100);
        
        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::end:
        this->End();
        m_CurrentState = State::END;
        break;

    }
}

void App::InitializeEnemy_1(glm::vec2 coordinate , int hp ) {
    std::shared_ptr<Enemy_1> m_Enemy20 = std::make_shared<Enemy_1>();
    m_Enemy20->Start(coordinate); // 初始化敵人的位置
    m_Enemy20->setWall(wall);
    m_Enemies.push_back(m_Enemy20);
    m_Root.AddChild(m_Enemy20);
}

void App::InitializeEnemy_2(glm::vec2 coordinate , int hp ) {
    std::shared_ptr<Enemy_2> m_Enemy22 = std::make_shared<Enemy_2>();
    m_Enemy22->Start(coordinate); // 初始化敵人的位置
    m_Enemy22->setWall(wall);
    m_Enemies.push_back(m_Enemy22);
    m_Root.AddChild(m_Enemy22);
}

void App::InitializeEnemy_3(glm::vec2 coordinate, int hp , int exp) {
    std::shared_ptr<Enemy_3> m_Enemy18 = std::make_shared<Enemy_3>();
    m_Enemy18->Start(coordinate); // 初始化敵人的位置
    m_Enemy18->setWall(wall);
    m_Enemy18->setExp_supply(exp);
    m_Enemies.push_back(m_Enemy18);
    m_Root.AddChild(m_Enemy18);
}

void App::InitializeEnemy_4(glm::vec2 coordinate , int hp) {
    std::shared_ptr<Enemy_4> m_Enemy16 = std::make_shared<Enemy_4>();
    m_Enemy16->Start(coordinate); // 初始化敵人的位置
    m_Enemy16->setWall(wall);
    m_Enemies.push_back(m_Enemy16);
    m_Root.AddChild(m_Enemy16);
}

void App::InitializeEnemy_5(glm::vec2 coordinate , int hp) {
    std::shared_ptr<Enemy_5> m_Enemy18 = std::make_shared<Enemy_5>();
    m_Enemy18->Start(coordinate); // 初始化敵人的位置
    m_Enemy18->setWall(wall);
    m_Enemies.push_back(m_Enemy18);
    m_Root.AddChild(m_Enemy18);
}

void App::InitializeEnemy_6(glm::vec2 coordinate , int hp) {
    std::shared_ptr<Enemy_6> m_Enemy18 = std::make_shared<Enemy_6>();
    m_Enemy18->Start(glm::vec2(247.056,-13.8528)); // 初始化敵人的位置
    m_Enemy18->setWall(wall);
    m_Enemies.push_back(m_Enemy18);
    m_Root.AddChild(m_Enemy18);
}

void App::InitializeEnemy_7(glm::vec2 coordinate , int hp) {
    std::shared_ptr<Enemy_7> m_Enemy18 = std::make_shared<Enemy_7>();
    m_Enemy18->setGiraffe(m_Giraffe);
    m_Enemy18->Start(coordinate); // 初始化敵人的位置
    m_Enemy18->setWall(wall);
    m_Enemies.push_back(m_Enemy18);
    m_Root.AddChild(m_Enemy18);
}


