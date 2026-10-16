# Immersive Audio 1.1 — Android source project

A local music player for Android with a device-dependent headphone effects chain.

## Implemented in this source project
- Pick a local audio file through Android's system file picker.
- Play, pause, seek, and show playback position.
- Four presets: Balanced, Wide, Bass, and Cinema.
- Live controls for Android's Virtualizer, BassBoost, Equalizer, and auxiliary PresetReverb where supported by the device.
- Effects are attached to the selected player's audio session; individual unsupported effects are handled without disabling the others.
- No broad storage permission and no network permission.

## Build
1. Open this project in Android Studio (JDK 17; Android SDK Platform 35).
2. Let Gradle sync, then choose **Build > Build APK(s)**.
3. Install the generated debug APK on the phone. The project has not been compiled or device-tested in this environment.

## Important limitations
- The app plays audio selected inside its own player. Android does not allow an ordinary third-party app to replace audio processing globally for YouTube, Spotify, games, calls, and every other app.
- The app uses audio effects provided by Android/device firmware. Availability and audible behavior vary by phone, firmware, and connected output.
- This version does not implement a custom HRTF/binaural convolution engine. The Virtualizer is device-provided, and the other effects are EQ, bass enhancement, and reverberation. It is not Dolby-certified and does not create literal 11.2 physical channels.
- Playback is activity-owned in this build; closing the activity may stop playback. A persistent background playback service is not included.
