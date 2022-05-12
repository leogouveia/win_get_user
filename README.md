# win_get_user

Flutter plugin to get logged user name on windows machines.

## Getting Started

To add the dependency from github, do as on image below:

![Add plugin as flutter dependency from github](./assets/include_git_depency.jpg "Add plugin as flutter dependency from github")

Call the getters as below:

```dart
import 'package:win_get_user/win_get_user.dart';

try {
  // get the windows version
  platformVersion =
      await WinGetUser.platformVersion ?? 'Unknown platform version';

  // get the logged user name
  userName = await WinGetUser.getLoggedUser ?? 'Unknown User';

  // if it's not windows
} on PlatformException {
  platformVersion = 'Failed to get platform version.';
  userName = await WinGetUser.getLoggedUser ?? 'Failed to get User Name';
}
```
