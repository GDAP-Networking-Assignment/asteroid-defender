# NetworkGameEngine

## Networking

### Time Sync

- Added velocity to transform
- Server send MSG_SYNC every sync
  - Contains snapshot of all transforms in the scene
  - Contains totalTime of server
- Client receives MSG_SYNC
  - records server time as well as time from previous MSG_SYNC 
  - predicts position of server using transform velocity and server time delta
  - interpolates over 0.2 seconds from current transform to new transform

### Entity Creation

- Client sends RPC to create a bullet
  - Serializes bullet position and velocity and reads them on invoke
  - Also serialize bullet Uid
- Server creates bullet and propogates creation to clients
  - Also sends out server Uid so clients entities have the same Uid
  - RPC caller will receive back it's old Uid and stop creation of new entity