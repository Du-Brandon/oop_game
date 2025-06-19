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
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2 (-470.36f, 44.0f) , glm::vec2(-305.836f , 200.584f));
        wall->setwall(glm::vec2 (-470.03f, -191.562f) , glm::vec2(-305.101f , -38.670f));
        wall->setwall(glm::vec2 (-134.625f,60.9083f) , glm::vec2(-90.1393f , 162.386f));
        wall->setwall(glm::vec2 (-134.625f,-163.9083f) , glm::vec2(-90.1393f , -64.2383f));                   

        InitializeEnemy_2(glm::vec2(144, 116),50);

        InitializeEnemy_2(glm::vec2(144, -116),50);

        InitializeEnemy_2(glm::vec2(250, 0),50);

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
        m_Ground_Spikes->clear();

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
        m_Ground_Spikes->clear();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2 (-398.86f, 73.006f) , glm::vec2(-152.0f , 125.7f));
        wall->setwall(glm::vec2 (-398.523f, -131.287f) , glm::vec2(-364.459f , 124.414f));
        wall->setwall(glm::vec2 (-398.883f,-124.099f) , glm::vec2(-146.449f , -52.8387f));
        
        wall->setwall(glm::vec2 (-35.7017f,72.0359f) , glm::vec2(210.873f , 123.596f));                
        wall->setwall(glm::vec2 (166.669f,-122.415f) , glm::vec2(211.375f , 123.596f));                
        wall->setwall(glm::vec2 (-40.2019f,-123.842f) , glm::vec2(210.154f , -63.2669f));                

        InitializeEnemy_3(glm::vec2(237, 157));
        InitializeEnemy_3(glm::vec2(237, -162));
        InitializeEnemy_1(glm::vec2(59.96f, 5.513f));
        
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
        m_Ground_Spikes->clear();

        wall->clear();
        wall->Start(192.0f, -192.0f, -465.0f, 267.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2 (-460.86f, 83.006f) , glm::vec2(267.116f , 125.659f));
        wall->setwall(glm::vec2 (-462.523f, -119.287f) , glm::vec2(267.459f , -85.414f));
        
        std::shared_ptr<Angel> m_Angel = std::make_shared<Angel>();
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
        m_Ground_Spikes->clear();

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
        
        wall->setwall(glm::vec2(-465.447,86.7026) , glm::vec2(-378.354, 121.696));
        wall->setwall(glm::vec2(-465.084,-134.085) , glm::vec2(-381.412, -92.4253));
        wall->setwall(glm::vec2(-378.354,86.7026) , glm::vec2(234.131, 122.405),"lake");
        wall->setwall(glm::vec2(-381.412,-132.446) , glm::vec2(234.358, -90.0606),"lake");
        
        
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
        wall->setwall(glm::vec2(202.875,26.502) , glm::vec2(237.063,192.0));
        wall->setwall(glm::vec2(195.252,-192.736) , glm::vec2(245.433,-53.9041));
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
    case player_level::twelfth_level:{
        LOG_DEBUG("twelfth_level");
        levelstatus = levelstatus::normal_level;
        now_level = 12;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(235.0f, -240.0f, -470.0f, 202.0f, 24.0f, -26.0f);
        wall->setwall(glm::vec2(-432.511230, 160.448608), glm::vec2(-357.666656, 203.746307));
        wall->setwall(glm::vec2(-441.663910, -201.050659), glm::vec2(-360.018341, -158.928146));
        // wall->setwall(glm::vec2(-470.624908, -235.643326), glm::vec2(-399.687744, -202.771912));
        wall->setwall(glm::vec2(-292.665344, -60.857697), glm::vec2(-216.186417, 64.015060), "lake");
        wall->setwall(glm::vec2(-70.850838, 28.361452), glm::vec2(15.405961, 147.361252), "lake");
        wall->setwall(glm::vec2(-68.163490, -148.589462), glm::vec2(6.261861, -29.998169), "lake");
        // wall->setwall(glm::vec2(-465.217957,-470.0), glm::vec2(235.0, 229.750458));
        wall->setwall(glm::vec2(104.461571, 159.070633), glm::vec2(187.809036, 192.035782));
        wall->setwall(glm::vec2(153.421, 200.583), glm::vec2(235.0, 202.0));
        wall->setwall(glm::vec2(111.272736, -200.624954), glm::vec2(186.615784, -158.558167));
        // wall->setwall(glm::vec2(-152.809479,202.0), glm::vec2(-240.0, 202.0));

        InitializeEnemy_4(glm::vec2 (-136.875320, -2.482892));
        InitializeEnemy_2(glm::vec2 (-136.875320, 180.155029));
        InitializeEnemy_2(glm::vec2 (-136.875320, -178.583099));
        InitializeEnemy_4(glm::vec2 (-278.955658, -138.826889));    
        InitializeEnemy_4(glm::vec2 (-279.859314, 127.078918)); 
        InitializeEnemy_3(glm::vec2 (56.404697, 184.312897));
        InitializeEnemy_3(glm::vec2 (56.404697, -208.170944));

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::thirteenth_level:{
        LOG_DEBUG("thirteenth_level");
        levelstatus = levelstatus::normal_level;
        now_level = 13;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(250.0f, -250.0f, -490.0f, 195.0f, 30.0f, -30.0f);
        wall->setwall(glm::vec2(-355.221863, 74.320007), glm::vec2(-269.014252, 252.169403));
        wall->setwall(glm::vec2(156.562256, -249.213287), glm::vec2(197.296082, -76.307938));
        wall->setwall(glm::vec2(-29.686546, 66.783104), glm::vec2(53.478371, 244.742615));
        wall->setwall(glm::vec2(-165.320816, -248.419937), glm::vec2(-88.286804, -72.124863));
        wall->setwall(glm::vec2(-162.399368, 76.539131), glm::vec2(-54.109024, 244.185028), "lake");
        wall->setwall(glm::vec2(-297.598572, -248.793655), glm::vec2(-188.474152, -82.476753), "lake");
        wall->setwall(glm::vec2(-496.496490, 74.320007), glm::vec2(-368.915863, 248.594299), "lake");
        wall->setwall(glm::vec2(22.488598, -249.213287), glm::vec2(139.354797, -73.107224), "lake");
        wall->setwall(glm::vec2(-441.235046, -195.966568), glm::vec2(-407.038239, -171.633972), "lake");
        wall->setwall(glm::vec2(110.519859, 170.852798), glm::vec2(144.349182, 198.310333), "lake");

        InitializeEnemy_3(glm::vec2 (-61.373837, -234.151886));
        InitializeEnemy_3(glm::vec2 (-2.339086, -116.024536));
        InitializeEnemy_3(glm::vec2 (82.152374, 112.215309));
        InitializeEnemy_3(glm::vec2 (174.663712, 211.750885));
        InitializeEnemy_3(glm::vec2 (-192.897034, 211.883133));
        InitializeEnemy_3(glm::vec2 (-242.217270, 102.930458));
        InitializeEnemy_3(glm::vec2 (-353.082031, -206.749420));

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::fourteenth_level:{
        LOG_DEBUG("fourteenth_level");
        levelstatus = levelstatus::normal_level;
        now_level = 14;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(187.0f, -187.0f, -495.0f, 270.0f, 32.0f, -32.0f);
        wall->setwall(glm::vec2(103.939682, -57.249733), glm::vec2(152.413391, 51.176914));
        wall->setwall(glm::vec2(-432.777649, 84.844513), glm::vec2(-359.802490, 126.635872));
        wall->setwall(glm::vec2(-392.873322, 126.635872), glm::vec2(-318.606445, 160.135086));
        wall->setwall(glm::vec2(-351.786499, 160.135086), glm::vec2(-283.449829, 188.867691));
        wall->setwall(glm::vec2(-428.615723, -126.041801), glm::vec2(-362.434906, -92.007607));
        wall->setwall(glm::vec2(-387.833679, -164.946701), glm::vec2(-321.407867, -132.022949));
        wall->setwall(glm::vec2(-354.390350, -187.869858), glm::vec2(-286.185333, -166.741302));
        wall->setwall(glm::vec2(97.544060, 162.253815), glm::vec2(173.703491, 188.082458));
        wall->setwall(glm::vec2(140.226791, 128.797531), glm::vec2(208.080704, 162.348495));
        wall->setwall(glm::vec2(174.038254, 86.704666), glm::vec2(240.858536, 126.957870));
        wall->setwall(glm::vec2(98.103294, -187.700089), glm::vec2(164.507706, -161.904434));
        wall->setwall(glm::vec2(138.867188, -161.904434), glm::vec2(206.193008, -127.752701));
        wall->setwall(glm::vec2(173.814484, -127.752701), glm::vec2(240.977325, -93.527504));

        InitializeEnemy_3(glm::vec2 (241.686584, 161.792847),200);
        InitializeEnemy_3(glm::vec2 (241.686584, -162.413361),200);
        InitializeEnemy_7(glm::vec2 (22.833094, 126.660637));
        InitializeEnemy_7(glm::vec2 (22.833094, -126.497574));
        InitializeEnemy_1(glm::vec2 (-155.868454, 17.994854));
        InitializeEnemy_1(glm::vec2 (-155.868454, -17.994854));
        InitializeEnemy_1(glm::vec2 (-155.868454, 45.994854));
        InitializeEnemy_1(glm::vec2 (-155.868454, 45.994854));


        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }
    
    case player_level::fifteenth_level:{
        LOG_DEBUG("fifteenth_level");
        now_level = 15;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(215.0f, -215.0f, -415.0f, 160.0f, 32.0f, -19.0f);
        wall->setwall(glm::vec2(-94.883209, 97.148018), glm::vec2(-3.927504, 138.088272));
        wall->setwall(glm::vec2(13.333346, 64.112724), glm::vec2(105.482346, 181.107330));
        wall->setwall(glm::vec2(-94.883209, -142.886627), glm::vec2(-1.942665, -109.691673));
        wall->setwall(glm::vec2(14.567785, -184.639801), glm::vec2(104.600082, -59.154007));

        std::shared_ptr<Angel> m_Angel = std::make_shared<Angel>();
        m_Angel->Start(glm::vec2(140, 0)); // 初始化敵人的位置
        m_Angel->setWall(wall);
        m_Enemies.push_back(m_Angel);
        m_Root.AddChild(m_Angel);

        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        giraffe_exp = 0;
        is_enemy_empty = false;
        break;
    }

    case player_level::sixteenth_level:{
        LOG_DEBUG("sixteenth_level");
        now_level = 16;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(250.0f, -250.0f, -490.0f, 200.0f, 48.0f, -48.0f);
        wall->setwall(glm::vec2(21.355843, 210.090897), glm::vec2(200.0, 250.0)); // Clear previous walls
        wall->setwall(glm::vec2(165.260757, 67.213509), glm::vec2(200.0, 250.0));
        wall->setwall(glm::vec2(-490.0, -250.0), glm::vec2(-408.825867, -67.646584));
        wall->setwall(glm::vec2(-490.0, -250.0), glm::vec2(-267.868835, -212.427826));
        

        InitializeEnemy_4(glm::vec2 (42.266777, -181.814926),200);
        InitializeEnemy_4(glm::vec2 (42.266777, -5.069035),200);
        InitializeEnemy_4(glm::vec2 (42.266777, 137.183334),200);
        InitializeEnemy_4(glm::vec2 (-143.983749, -47.296814));

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;        
    }

    case player_level::seventeenth_level:{
        LOG_DEBUG("seventeenth_level");
        now_level = 17;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->clear();

        wall->clear();
        wall->Start(230.0f, -230.0f, -450.0f, 200.0f, 48.0f, -48.0f);

        wall->setwall(glm::vec2(-405.184021, 65.842751), glm::vec2(-279.784210, 190.880890), "lake");
        wall->setwall(glm::vec2(-399.094208, -198.630371), glm::vec2(-281.727722, -64.894569), "lake");
        wall->setwall(glm::vec2(36.507782, -191.739227), glm::vec2(162.806686, -66.918549), "lake");
        wall->setwall(glm::vec2(37.065868, 66.971001), glm::vec2(162.387970, 192.457214), "lake");

        m_Ground_Spikes->Add_Spikes(glm::vec2 (-301.488098, -32.151245));
        m_Ground_Spikes->Add_Spikes(glm::vec2 (-301.488098, 26.887753));
        m_Ground_Spikes->Add_Spikes(glm::vec2 (56.874550, 220.768829));
        m_Ground_Spikes->Add_Spikes(glm::vec2 (56.915398, -218.970078));

        InitializeEnemy_3(glm::vec2 (102.435760, 133.164871),300,20);
        InitializeEnemy_3(glm::vec2 (101.490761, -127.940994), 300, 20);
        InitializeEnemy_3(glm::vec2 (-340.558655, -127.940994));
        InitializeEnemy_3(glm::vec2 (-340.558655, 133.353104));

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::eighteenth_level:{
        LOG_DEBUG("eighteenth_level");
        now_level = 18;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(230.0f, -230.0f, -475.0f, 180.0f, 48.0f, -48.0f);
        wall->setwall(glm::vec2(-390.495453, -59.882023), glm::vec2(-345.509277, 59.222626), "lake");
        wall->setwall(glm::vec2(-303.594177, 109.434303), glm::vec2(5.466681, 151.446411), "lake");
        wall->setwall(glm::vec2(-295.030243, -155.815262), glm::vec2(-0.398125, -110.415459), "lake");
        wall->setwall(glm::vec2(58.704426, -59.142815), glm::vec2(95.822876, 58.691250), "lake");

        InitializeEnemy_1(glm::vec2 (132.233276, 192.515762), 200);
        InitializeEnemy_1(glm::vec2 (132.233276, -191.878372), 200);
        InitializeEnemy_1(glm::vec2 (-118.634865, -191.878372), 200);
        InitializeEnemy_1(glm::vec2 (-126.444153, 193.411774), 200);
        InitializeEnemy_1(glm::vec2 (-142.797424, 58.775059), 200);
        InitializeEnemy_1(glm::vec2 (-142.797424, -68.996490), 200);
        InitializeEnemy_2(glm::vec2 (65.689125, 115.513664));
        InitializeEnemy_2(glm::vec2 (50.659519, -110.812569));
        InitializeEnemy_4(glm::vec2 (-16.902779, -1.473674));

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;        
    }

    case player_level::nineteenth_level:{
        LOG_DEBUG("nineteenth_level");
        levelstatus = levelstatus::normal_level;
        now_level = 19;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(240.0f, -245.0f, -480.0f, 215.0f, 48.0f, -48.0f);
        wall->setwall(glm::vec2(117.188400, 59.815006), glm::vec2(201.494614, 240.0));
        wall->setwall(glm::vec2(117.556183, -245.0), glm::vec2(200.147156, -70.890221));

        m_Ground_Spikes->Add_Spikes(glm::vec2 (-109.142021, 109.209435));
        m_Ground_Spikes->Add_Spikes(glm::vec2 (-251.673508, -160.032745));
        m_Ground_Spikes->Add_Spikes(glm::vec2 (-15.573839, -51.453835));
        m_Ground_Spikes->Add_Spikes(glm::vec2 (-319.533142, 162.161377));
        m_Ground_Spikes->Add_Spikes(glm::vec2 (-447.633026, -215.958908));

        InitializeEnemy_5(glm::vec2 (180.945419, 2.086255));
        InitializeEnemy_6(glm::vec2 (28.786255, 165.881821));
        InitializeEnemy_6(glm::vec2 (28.786255, -191.203476));
        InitializeEnemy_6(glm::vec2 (-102.967834, -93.196838)); 
        InitializeEnemy_6(glm::vec2 (-220.167511, 67.141014));
        InitializeEnemy_6(glm::vec2 (-336.893829, 48.410835));
        InitializeEnemy_6(glm::vec2 (-336.893829, -125.477570));
        InitializeEnemy_6(glm::vec2 (-188.031860, -167.115677));

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);
        is_enemy_empty = false;
        break;
    }

    case player_level::twenty_level:{
        LOG_DEBUG("twenty_level");
        levelstatus = levelstatus::boss_level;
         
        now_level = 20;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->clear();

        
        wall->clear();
        wall->Start(250.0f, -250.0f, -460.0f, 210.0f, 48.0f, -48.0f);
        wall->setwall(glm::vec2(-460.052026, 204.963989), glm::vec2(-327.605133, 246.656647));
        wall->setwall(glm::vec2(-460.052026, 154.159546), glm::vec2(-369.046539, 203.041977));
        wall->setwall(glm::vec2(-451.458832, -250.891464), glm::vec2(-375.013794, -160.957672));
        wall->setwall(glm::vec2(-375.013794, -250.494827), glm::vec2(-325.598450, -203.411026));
        wall->setwall(glm::vec2(126.792557, -250.796036), glm::vec2(210.352661, -199.882370));
        wall->setwall(glm::vec2(177.901947, -199.882370), glm::vec2(210.106796, -166.517120));
        wall->setwall(glm::vec2(178.024857, 158.600372), glm::vec2(210.374710, 250.962524));
        wall->setwall(glm::vec2(129.000977, 201.114243), glm::vec2(210.437668, 250.315247));

        std::shared_ptr<Boss_2> m_Boss_2 = std::make_shared<Boss_2>();
        m_Boss_2->Start(glm::vec2(100, 0)); // 初始化敵人的位置
        m_Boss_2->setWall(wall);
        m_Enemies.push_back(m_Boss_2);
        m_Root.AddChild(m_Boss_2);

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;       

    }

    case player_level::twenty_first_level:{
        LOG_DEBUG("twenty_first_level");
        levelstatus = levelstatus::normal_level;
        now_level = 21;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(235.0f, -240.0f, -450.0f, 215.0f, 48.0f, -48.0f);
        wall->setwall(glm::vec2(-366.887848, -186.954880), glm::vec2(-303.774506, 235.0));
        wall->setwall(glm::vec2(-138.331192, -240.0), glm::vec2(-80.999413, 187.920807));
        wall->setwall(glm::vec2(86.839645, -188.079285), glm::vec2(138.339249, 235.0));

        InitializeEnemy_1(glm::vec2 (15.477321, 198.745087),400);
        InitializeEnemy_3(glm::vec2 (181.306564, 199.091248));
        InitializeEnemy_6(glm::vec2 (181.306564, -2.618350));
        InitializeEnemy_6(glm::vec2 (181.306564, -211.763260));
        InitializeEnemy_6(glm::vec2 (-3.174521, -211.763260), 100);

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;        
    }

    case player_level::twenty_second_level:{
        LOG_DEBUG("twenty_second_level");
        levelstatus = levelstatus::normal_level;
        now_level = 22;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(235.0f, -240.0f, -450.0f, 215.0f, 48.0f, -48.0f);

        InitializeEnemy_6(glm::vec2 (153.146423, 175.476807),250);
        InitializeEnemy_6(glm::vec2 (153.146423, -0.254951),250);
        InitializeEnemy_6(glm::vec2 (153.146423, -184.290619),250);
        InitializeEnemy_6(glm::vec2 (-199.249924, -184.290619),250);
        InitializeEnemy_6(glm::vec2 (-199.249924, 182.493637),250);
        InitializeEnemy_6(glm::vec2 (-23.299168, -1.273765),250 );

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::twenty_third_level:{
        LOG_DEBUG("twenty_third_level");
        levelstatus = levelstatus::normal_level;
        now_level = 23;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(235.0f, -240.0f, -450.0f, 215.0f, 48.0f, -48.0f);
        wall->setwall(glm::vec2(-182.620544, 116.973503), glm::vec2(-134.713150,235.0), "lake");
        wall->setwall(glm::vec2(-182.620544, 116.973503), glm::vec2(-0.205011, 156.017517)  , "lake");
        wall->setwall(glm::vec2(-42.285759, 116.973503), glm::vec2(-0.381256, 231.127579), "lake");
        wall->setwall(glm::vec2(-4.143783, -63.975700), glm::vec2(54.412170, 70.450104));
        wall->setwall(glm::vec2(-188.913315,-240.0), glm::vec2(-140.054001, -106.056313), "lake");
        wall->setwall(glm::vec2(-188.913315, -164.376907), glm::vec2(3.388461, -105.519012), "lake");
        wall->setwall(glm::vec2(-38.928951, -240.0), glm::vec2(3.388461, -105.519012), "lake");

        InitializeEnemy_2(glm::vec2 (-92.024170, 0.0f),500);
        InitializeEnemy_7(glm::vec2 (-92.024170, 170.065842),200);
        InitializeEnemy_7(glm::vec2 (-92.024170, -170.065842),200);
        InitializeEnemy_4(glm::vec2 (-88.305328, 14.892389));
        InitializeEnemy_5(glm::vec2 (208.483414, 7.385991));

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::twenty_fourth_level:{
        LOG_DEBUG("twenty_fourth_level");
        levelstatus = levelstatus::normal_level;
        now_level = 24;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();
        wall->Start(250.0f, -250.0f, -470.0f, 200.0f, 48.0f, -48.0f);
        wall->setwall(glm::vec2(-481.154449, -148.749207), glm::vec2(216.047638, -115.339531));
        wall->setwall(glm::vec2(-481.154449, 120.486084), glm::vec2(197.545319, 154.800262));
        
        std::shared_ptr<Angel> m_Angel = std::make_shared<Angel>();
        m_Angel->Start(glm::vec2(140, 0)); // 初始化敵人的位置
        m_Angel->setWall(wall);
        m_Enemies.push_back(m_Angel);
        m_Root.AddChild(m_Angel);

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;

        break;
    }

    case player_level::twenty_fifth_level:{
        LOG_DEBUG("twenty_fifth_level");
        levelstatus = levelstatus::boss_level;
        now_level = 25;
        m_Background->nextbackground(now_level);
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->clear();

        wall->clear();
        wall->Start(235.0f, -240.0f, -450.0f, 215.0f, 48.0f, -48.0f);

        std::shared_ptr<Boss_3> m_Boss_3 = std::make_shared<Boss_3>();
        m_Boss_3->Start(glm::vec2(100, 0)); // 初始化敵人的位置
        m_Boss_3->setWall(wall);
        m_Enemies.push_back(m_Boss_3);
        m_Root.AddChild(m_Boss_3);

        giraffe_exp = 0;
        m_Giraffe -> setpos(glm::vec2(-420, 0));
        m_Giraffe -> Setwall(wall);

        is_enemy_empty = false;
        break;
    }

    case player_level::win_end:
        levelstatus = levelstatus::win;
        m_Background->win_background();
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();

        giraffe_exp = 0;
        m_Giraffe -> End();

        is_enemy_empty = false;

        Logger::info("You win the game!");
        break;

    
    case player_level::loss_end:
        levelstatus = levelstatus::loss;
        m_Background->loss_background();
        this->removeEnemy();
        m_Giraffe->cleararrow();
        m_Enemies.clear();
        m_Ground_Spikes->Start();

        wall->clear();

        giraffe_exp = 0;
        m_Giraffe -> End();

        is_enemy_empty = false;

        Logger::info("You loss the game!");
        break;

    case player_level::end:
        this->End();
        m_CurrentState = State::END;
        break;
    }
}

void App::InitializeEnemy_1(glm::vec2 coordinate , int hp ) {
    std::shared_ptr<Enemy_1> m_Enemy20 = std::make_shared<Enemy_1>();
    m_Enemy20->Start(coordinate); // 初始化敵人的位置
    if (hp > 0) {
        m_Enemy20->setHP(hp);
    }
    m_Enemy20->setWall(wall);
    m_Enemies.push_back(m_Enemy20);
    m_Root.AddChild(m_Enemy20);
}

void App::InitializeEnemy_2(glm::vec2 coordinate , int hp ) {
    std::shared_ptr<Enemy_2> m_Enemy22 = std::make_shared<Enemy_2>();
    m_Enemy22->Start(coordinate); // 初始化敵人的位置
    if (hp > 0) {
        m_Enemy22->setHP(hp);
    }
    m_Enemy22->setWall(wall);
    m_Enemies.push_back(m_Enemy22);
    m_Root.AddChild(m_Enemy22);
}

void App::InitializeEnemy_3(glm::vec2 coordinate, int hp , int exp) {
    std::shared_ptr<Enemy_3> m_Enemy18 = std::make_shared<Enemy_3>();
    m_Enemy18->Start(coordinate); // 初始化敵人的位置
    if (hp > 0) {
        m_Enemy18->setHP(hp);
    }
    m_Enemy18->setWall(wall);
    m_Enemy18->setExp_supply(exp);
    m_Enemies.push_back(m_Enemy18);
    m_Root.AddChild(m_Enemy18);
}

void App::InitializeEnemy_4(glm::vec2 coordinate , int hp) {
    std::shared_ptr<Enemy_4> m_Enemy16 = std::make_shared<Enemy_4>();
    m_Enemy16->Start(coordinate); // 初始化敵人的位置
    if (hp > 0) {
        m_Enemy16->setHP(hp);
    }
    m_Enemy16->setWall(wall);
    m_Enemies.push_back(m_Enemy16);
    m_Root.AddChild(m_Enemy16);
}

void App::InitializeEnemy_5(glm::vec2 coordinate , int hp) {
    std::shared_ptr<Enemy_5> m_Enemy18 = std::make_shared<Enemy_5>();
    m_Enemy18->Start(coordinate); // 初始化敵人的位置
    if (hp > 0) {
        m_Enemy18->setHP(hp);
    }
    m_Enemy18->setWall(wall);
    m_Enemies.push_back(m_Enemy18);
    m_Root.AddChild(m_Enemy18);
}

void App::InitializeEnemy_6(glm::vec2 coordinate , int hp) {
    std::shared_ptr<Enemy_6> m_Enemy18 = std::make_shared<Enemy_6>();
    m_Enemy18->Start(coordinate); // 初始化敵人的位置
    if (hp > 0) {
        m_Enemy18->setHP(hp);
    }
    m_Enemy18->setWall(wall);
    m_Enemies.push_back(m_Enemy18);
    m_Root.AddChild(m_Enemy18);
}

void App::InitializeEnemy_7(glm::vec2 coordinate , int hp) {
    std::shared_ptr<Enemy_7> m_Enemy18 = std::make_shared<Enemy_7>();
    m_Enemy18->setGiraffe(m_Giraffe);
    m_Enemy18->Start(coordinate); // 初始化敵人的位置
    if (hp > 0) {
        m_Enemy18->setHP(hp);
    }
    m_Enemy18->setWall(wall);
    m_Enemies.push_back(m_Enemy18);
    m_Root.AddChild(m_Enemy18);
}


