# switch-break-in-counter-and-control

An Arduino/Blynk project that controls the speed of the machine's motors, calculates the speed (Beats per minute) of the motor(s), calculates the remaining hours depending on the input Counter Target.

## Blynk Preview
![alt text][snapshot]

[snapshot]: /img/break-in-counter.gif "Blynk Main tab"

## Bill of materials (BOM) 📜
The following is the number of quantities required.

Parts required:
| Part                                                 | Qty        | Comment    |
| ---------------------------------------------------- | ---------- | --------   |
| ESP8266                                              | 1          | Required   |
| Hot Swap Socket                                      | 1-3        | Required   |
| 9v Supply                                            | 1          | Required   |
| Jumper Wires                                         | -          | Required   |
| NodeMCU base/socket                                  | 1          | Optional A |
| L298N Motor Driver                                   | 1          | Optional A |
| NodeMCU L293D Motor Shield                           | 1          | Optional B |

## Blynk PIN and Template 📝
- You guys have to download the exact BLYNK LEGACY one to make the project works completely. Here are the links for [Android](https://play.google.com/store/apps/details?id=cc.blynk) and [iOS](https://apps.apple.com/vn/app/blynk/id808760481).

Blynk Virtual PIN:
| Description                                          | vPIN       | Comment          |
| ---------------------------------------------------- | ---------- | ---------------- |
| Switch Break-in Machine 1 Target Counter             | 0          | Value x 1000     |
| Switch Break-in Machine 1 Current Counter            | 1          | -                |
| Switch Break-in Machine 1 Speed Set                  | 2          | 0 - 100%         |
| Switch Break-in Machine 1 Current Speed              | 3          | Beats per minute |
| Switch Break-in Machine 1 Remaining Hours            | 4          | -                |
| Switch Break-in Machine 1 CLEAR Counter              | 5          | -                |
|                                                      |            |                  |
| Switch Break-in Machine 2 Target Counter             | 10         | Value x 1000     |
| Switch Break-in Machine 2 Current Counter            | 11         | -                |
| Switch Break-in Machine 2 Speed Set                  | 12         | 0 - 100%         |
| Switch Break-in Machine 2 Current Speed              | 13         | Beats per minute |
| Switch Break-in Machine 2 Remaining Hours            | 14         | -                |
| Switch Break-in Machine 2 CLEAR Counter              | 15         | -                |
|                                                      |            |                  |
| Switch Break-in Machine 3 Target Counter             | 20         | Value x 1000     |
| Switch Break-in Machine 3 Current Counter            | 21         | -                |
| Switch Break-in Machine 3 Speed Set                  | 22         | 0 - 100%         |
| Switch Break-in Machine 3 Current Speed              | 23         | Beats per minute |
| Switch Break-in Machine 3 Remaining Hours            | 24         | -                |
| Switch Break-in Machine 3 CLEAR Counter              | 25         | -                |

## To-Do 📝
- Initial README document.

## Changelog 📒
- `May 11, 2022:` Initial commit
