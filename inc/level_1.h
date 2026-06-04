#pragma once
void level_1() {
    // background layer
    bck.render(backDC);

    lvl.render(backDC);
    // background layer

    for (walkingEnemy &i : walkingEnemyV) {
        if (!i.died) {
            i.update(&lvl, backDC);
            i.render(backDC);
        }
    }
    for (jumpingEnemy &i : jumpingEnemyV) {
        if (!i.died) {
            i.update(&lvl, backDC);
            i.render(backDC);
        }
    }
    for (collictable &i : cV) {
        if (!i.used){
            i.update(backDC);
            i.render(backDC);
        }
    }

    for (jumppad &i : jpV) {
        i.update();
        i.render(backDC);
    }
    for (rocketShooter &i : rsV) {
        i.update(backDC);
        i.render(backDC);
    }

    if (Input::pressed(VK_RETURN)) {
        lvl.del();
        lvl.init(backDC, "tilesets/moon/tile_1.bmp", "tilesets/moon/tile_2.bmp", "tilesets/moon/tile_3.bmp", "levels/level_1.sl");
    }
    UpdatePlayer(&lvl, pv, backDC);
    playerRun();
    UpdatePlayerAnim(backDC);
    playerShoot(backDC);
    updateCamera();

    player.render(backDC);

    //rs.update(backDC);
    //rs.render(backDC);

    hShowCollsions();

    renderUI(backDC);
}