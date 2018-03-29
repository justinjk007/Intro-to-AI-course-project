# AI-Course-Project

First thoughts, implement an **Environment**, **Agent** and **Target** class.

**Environment** is considered to be a 10mx10m square. Right now all I
can think is the 4 corner points of the square as the properties.

**Agent**, the project does not mention the shape of the agent but the
reach of the agent, which is a 10cm radius cirlce. So I think agents
can be a dot, with a 10cm radius cirlce draw anround them. Agents can
move 1cm in up,down,left and right directions only.

**Target**s, can just be a small dot. Since they don't move around or
anything, the properties they should have is there posistion and to
what agent it belongs to.

# Design

  * Create the Environment, which will setup its boundaries.
  * It also create 5 agents with random locations within the boundaries.
  * Then create 5 targets for each of the agents, total 25.
  * Sent this to the frontend so it can render

# Setup

Read [SETUP.org](./docs/SETUP.org) to setup `SDL2` and `SDL2_image`
