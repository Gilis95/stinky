//
// Created by christian on 05/11/2020.
//

#pragma once

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky::hoatzin::Workspace {
    /**
     * This function must be called before rendering all other panels. Once this function is called you can
     * continue panels rendering, they will be ```docked``` to this workspace
     */
    void Begin();

    /**
     * When you finish panels rendering, this function must be called!
     */
    void End();
}
