LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/utils/AnimationUtil.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/domain/character/CharacterBase.cpp \
../../Classes/domain/character/Hero.cpp \
../../Classes/domain/character/Monstor.cpp \
../../Classes/domain/character/Boss.cpp \
../../Classes/domain/goods/GoodsBase.cpp \
../../Classes/domain/goods/Medicine.cpp \
../../Classes/domain/goods/Prop.cpp \
../../Classes/domain/goods/Weapon.cpp \
../../Classes/gameui/dialog/Resuleui.cpp \
../../Classes/gameui/Ingameui.cpp \
../../Classes/gameui/Optionui.cpp \
../../Classes/gameui/Welcomeui.cpp \
../../Classes/gameui/Storeui.cpp \
../../Classes/gameui/Levelui.cpp \
../../Classes/module/MonstorManager.cpp \
../../Classes/module/AnimManager.cpp \
../../Classes/module/GameController.cpp \
../../Classes/module/LevelManager.cpp \
../../Classes/tui/TuiBase.cpp \
../../Classes/tui/TuiManager.cpp \
../../../CocosWidget/Button.cpp \
../../../CocosWidget/CheckBox.cpp \
../../../CocosWidget/ColorView.cpp \
../../../CocosWidget/ControlView.cpp \
../../../CocosWidget/ExpandableListView.cpp \
../../../CocosWidget/GradientView.cpp \
../../../CocosWidget/GridPageView.cpp \
../../../CocosWidget/GridView.cpp \
../../../CocosWidget/ImageView.cpp \
../../../CocosWidget/ImageViewScale9.cpp \
../../../CocosWidget/Label.cpp \
../../../CocosWidget/LabelAtlas.cpp \
../../../CocosWidget/LabelBMFont.cpp \
../../../CocosWidget/Layout.cpp \
../../../CocosWidget/ListView.cpp \
../../../CocosWidget/Lua_cocos2dx_widget.cpp \
../../../CocosWidget/PageView.cpp \
../../../CocosWidget/ProgressBar.cpp \
../../../CocosWidget/Scale9Sprite.cpp \
../../../CocosWidget/ScrollView.cpp \
../../../CocosWidget/Slider.cpp \
../../../CocosWidget/TableView.cpp \
../../../CocosWidget/TextArea.cpp \
../../../CocosWidget/TextRich.cpp \
../../../CocosWidget/ToggleView.cpp \
../../../CocosWidget/Widget.cpp \
../../../CocosWidget/WidgetProtocol.cpp \
../../../CocosWidget/WidgetWindow.cpp \
../../../CocosWidget/WitlsMacros.cpp \
../../../CocosBase/CCBundle.cpp \
../../../CocosBase/CCMsgDelegate.cpp \
../../../CocosBase/CCMsgManager.cpp \
../../../CocosBase/CCSceneExtension.cpp \
../../../CocosBase/CCSceneExTransition.cpp \
../../../CocosBase/CCSceneManager.cpp \
../../../tinyxml/tinystr.cpp \
../../../tinyxml/tinyxml.cpp \
../../../tinyxml/tinyxmlerror.cpp \
../../../tinyxml/tinyxmlparser.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
