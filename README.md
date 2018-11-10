# Frangitron Midibox

MIOS32 part of Frangitron

Compile and upload to a Midibox using [MIOS Studio](http://www.ucapps.de/mios_studio.html)

5 pushable infinite rotary encoders on J10 & J5

## Midi implementation

| Midi | Role | Values |
| --- | --- | --- |
| CC 20 | Encoder 1 pushed state | 0 or 127 |
| CC 21 | Encoder 2 pushed state | 0 or 127 |
| CC 22 | Encoder 3 pushed state | 0 or 127 |
| CC 23 | Encoder 4 pushed state | 0 or 127 |
| CC 24 | Encoder 5 pushed state | 0 or 127 |
| NRPN 0 | Encoder 1 INC/DEC | NRPN INC or NRPN DEC |
| NRPN 1 | Encoder 2 INC/DEC | NRPN INC or NRPN DEC |
| NRPN 2 | Encoder 3 INC/DEC | NRPN INC or NRPN DEC |
| NRPN 3 | Encoder 4 INC/DEC | NRPN INC or NRPN DEC |
| NRPN 4 | Encoder 5 INC/DEC | NRPN INC or NRPN DEC |

## Notes

- https://www.elektronauts.com/t/push-rotary-encoders-for-machinedrum-replacement-part/49408/6

