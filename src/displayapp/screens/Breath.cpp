#include "displayapp/screens/Breath.h"
#include "displayapp/DisplayApp.h"

using namespace Pinetime::Applications::Screens;

Breath::Breath(DisplayApp* app,
               Controllers::MotorController& motorController,
               System::SystemTask& systemTask,
               Controllers::BrightnessController& brightnessController)
  : Screen(app), motorController {motorController}, systemTask {systemTask}, brightnessController {brightnessController} {
  lv_obj_t* title = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(title, "Slow Breathing App");
  lv_label_set_align(title, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(title, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);

  systemTask.PushMessage(System::Messages::DisableSleeping);
  brightnessController.Set(Controllers::BrightnessController::Levels::Off);
  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
  startTime = xTaskGetTickCount();
  motorController.RunForDuration(duration);
}

Breath::~Breath() {
  lv_task_del(taskRefresh);
  systemTask.PushMessage(System::Messages::EnableSleeping);
  lv_obj_clean(lv_scr_act());
}

void Breath::Refresh() {
  if (xTaskGetTickCount() - startTime > 60u * configTICK_RATE_HZ / static_cast<uint16_t>(bpm)) {
    startTime += 60 * configTICK_RATE_HZ / bpm;
    motorController.RunForDuration(duration);
  }
}