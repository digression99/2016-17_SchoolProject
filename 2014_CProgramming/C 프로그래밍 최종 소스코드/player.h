#pragma once

typedef struct _player Player;
typedef struct _map Map;

void Player_Init(struct _player *player);
void Player_Update(struct _player *player, struct _map *map);
void Player_Shoot(struct _player *p);
void Player_Bullet_Update(struct _player *player, struct _map *map);