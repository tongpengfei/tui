#ifndef __CONFIG_H__
#define __CONFIG_H__

static const int HERO_CHASE_DIS = 50;//英雄和敌人 追逐最小距离
static const int HERO_INIT_COIN = 1000000;//初始化金币数

static const int WEAPON_BASE_POWERLENGTH = 110;//武器基础配置
static const int WEAPON_BASE_ATTACTVALUE = 50;
static const int MEDICINE_BASE_RESUMELENGTH = 500;//药水基础配置
static const int PROP_BASE_ATTACTVALUE = 70;//道具基础配置

static const int MSG_HERO_DEAD = 0;//英雄死亡事件

static const int MSG_MONSTOR_DEAD = 10;//怪物死亡事件
static const int MSG_BOSS_DEAD = 16;//boss死亡事件
static const int MSG_ENDGAME = 11;//本局结束 展示结果
static const int MSG_RESPON_RESULE = 13;//本局开始
static const int MSG_EQUIIP = 14;//装备武器
static const int MSG_INTOENTRANCE = 12;//怪物进入入口
static const int MSG_PLACEBOSS = 15;//放置boss

static const int SCENE_INGAME = 6;
static const int SCENE_STORE = 7;
static const int SCENE_WELCOME = 8;
static const int SCENE_OPTION = 9;

static const int TYPE_WEAPON = 15;
static const int TYPE_MEDICINE = 16;
static const int TYPE_PROP = 17;

static const int COST_BASE_WEAPON = 500;//武器基础价格
static const int COST_BASE_MEDICINE = 100;//药水基础价格
static const int COST_BASE_PROP = 300;//道具

static const int TMP_ENTRANCEANIM_TAG = 900;

#endif