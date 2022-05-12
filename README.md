# switch-break-in-counter-and-control

An Arduino/Blynk project that controls the speed of the machine's motors, calculates the speed (Beats per minute) of the motor(s), calculates the remaining hours depending on the bpm speed and input Counter Target.

## Blynk Preview
![alt text][snapshot]

[snapshot]: /img/break-in-counter.gif "Blynk Main tab"

## Bill of materials (BOM) 📜
The following is the number of quantities required.

Parts required:
| Part                                                 | Qty        | Comment    |
| ---------------------------------------------------- | ---------- | --------   |
| ESP8266                                              | 1          | Required   |
| Hot Swap Socket                                      | 1-4        | Required   |
| 9v Supply                                            | 1          | Required   |
| Jumper Wires                                         | -          | Required   |
| NodeMCU base/socket                                  | 1          | Optional A |
| L298N Motor Driver                                   | 1          | Optional A |
| NodeMCU L293D Motor Shield                           | 1          | Optional B |

## Hardware Schematic 📝
Option A: L298N using D5(GPIO14) D6(GPIO12) for motor A and D7(GPIO13) D8(GPIO15) for motor B
![](/img/Switch-Break-in-Machine-Counter-and-Control-L298N.png "L298N")

Option B: L293D using D1(GPIO05) D3(GPIO00) for motor A and D2(GPIO04) D4(GPIO02) for motor B
![](/img/Switch-Break-in-Machine-Counter-and-Control-L293D.png "L293D")

## Blynk PIN and Template 📝
- You guys have to download the exact BLYNK LEGACY one to make the project works completely. Here are the links for [Android](https://play.google.com/store/apps/details?id=cc.blynk) and [iOS](https://apps.apple.com/vn/app/blynk/id808760481).

Download the app, login to your account then scan this QR to clone my template.
![](/img/Blynk-QR-Break-in-Machin-Counter-Clone.png "Blynk Clone QR")


Blynk Virtual PIN:
| Description                                          | vPIN       | Comment          |
| ---------------------------------------------------- | ---------- | ---------------- |
| Switch Break-in Machine 1 Target Counter             | 0          | Value x 1000     |
| Switch Break-in Machine 1 Current Counter            | 1          | -                |
| Switch Break-in Machine 1 Speed Set                  | 2          | 0 - 100%         |
| Switch Break-in Machine 1 Current Speed              | 3          | Beats per minute |
| Switch Break-in Machine 1 Remaining Hours            | 4          | -                |
| Switch Break-in Machine 1 CLEAR Counter              | 9          | -                |
|                                                      |            |                  |
| Switch Break-in Machine 2 Target Counter             | 10         | Value x 1000     |
| Switch Break-in Machine 2 Current Counter            | 11         | -                |
| Switch Break-in Machine 2 Speed Set                  | 12         | 0 - 100%         |
| Switch Break-in Machine 2 Current Speed              | 13         | Beats per minute |
| Switch Break-in Machine 2 Remaining Hours            | 14         | -                |
| Switch Break-in Machine 2 CLEAR Counter              | 19         | -                |
|                                                      |            |                  |
| Switch Break-in Machine 3 Target Counter             | 20         | Value x 1000     |
| Switch Break-in Machine 3 Current Counter            | 21         | -                |
| Switch Break-in Machine 3 Speed Set                  | 22         | 0 - 100%         |
| Switch Break-in Machine 3 Current Speed              | 23         | Beats per minute |
| Switch Break-in Machine 3 Remaining Hours            | 24         | -                |
| Switch Break-in Machine 3 CLEAR Counter              | 29         | -                |
|                                                      |            |                  |
| Switch Break-in Machine 4 Target Counter             | 30         | Value x 1000     |
| Switch Break-in Machine 4 Current Counter            | 31         | -                |
| Switch Break-in Machine 4 Speed Set                  | 32         | 0 - 100%         |
| Switch Break-in Machine 4 Current Speed              | 33         | Beats per minute |
| Switch Break-in Machine 4 Remaining Hours            | 34         | -                |
| Switch Break-in Machine 4 CLEAR Counter              | 39         | -                |

## To-Do 📝
- Re-wire the L298N input to D1 D3 (A) and D2 D4 (B)

## Changelog 📒
- `May 11, 2022:` Initial commit
