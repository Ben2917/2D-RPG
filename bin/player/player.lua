

-- Currently the equivalent of a static class.
-- This probably isn't the optimum way to do this.


Player =
{

    x = 0,

    y = 0,

    vel = 320,

    inventory = {},

    moving = false, -- false idle, true moving

    direction = 1, -- directions - 0 up, 1 down, 2 left, 3 right.

}


function Player.MoveRight(frame_time)

    Player.x += Player.vel * frame_time
    Player.direction = 3
    Player.moving = true

end


function Player.MoveLeft(frame_time)

    Player.x -= Player.vel * frame_time
    Player.direction = 2
    Player.moving = true

end


function Player.MoveUp(frame_time)

    Player.y -= Player.vel * frame_time;
    Player.direction = 0
    Player.moving = true

end


function Player.MoveDown(frame_time)

    Player.y += Player.vel * frame_time;
    Player.direction = 1
    Player.moving = true

end


function Player.SearchInventory(item)

    -- See if item appears in inventory.
    
end


function Player.SetIdle()

    Player.moving = false
    
end
