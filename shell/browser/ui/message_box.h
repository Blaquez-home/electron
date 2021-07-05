// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SHELL_BROWSER_UI_MESSAGE_BOX_H_
#define SHELL_BROWSER_UI_MESSAGE_BOX_H_

#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "third_party/abseil-cpp/absl/types/optional.h"
#include "ui/gfx/image/image_skia.h"

namespace electron {

class NativeWindow;

enum class MessageBoxType {
  kNone = 0,
  kInformation,
  kWarning,
  kError,
  kQuestion,
};

struct MessageBoxSettings {
  electron::NativeWindow* parent_window = nullptr;
  MessageBoxType type = electron::MessageBoxType::kNone;
  std::vector<std::string> buttons;
  absl::optional<int> id;
  int default_id;
  int cancel_id;
  bool no_link = false;
  std::string title;
  std::string message;
  std::string detail;
  std::string checkbox_label;
  bool checkbox_checked = false;
  gfx::ImageSkia icon;

  MessageBoxSettings();
  MessageBoxSettings(const MessageBoxSettings&);
  ~MessageBoxSettings();
};

int ShowMessageBoxSync(const MessageBoxSettings& settings);

using MessageBoxCallback = base::OnceCallback<
    void(const std::string& error, int code, bool checkbox_checked)>;

void ShowMessageBox(const MessageBoxSettings& settings,
                    MessageBoxCallback callback);

bool CloseMessageBox(int id, std::string* error);

// Like ShowMessageBox with simplest settings, but safe to call at very early
// stage of application.
void ShowErrorBox(const std::u16string& title, const std::u16string& content);

}  // namespace electron

#endif  // SHELL_BROWSER_UI_MESSAGE_BOX_H_
