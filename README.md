# AI-Course-Project

We have implemented 3 scenarios of agent based search environment where each agent has to collect 5
of its targets spawned randomly in the environment with a fixed location.

- Scenario 1: **Competition:** Here only public broadcast is allowed. Each agent may lie or
  broadcast the correct information about other agent's targets into a public channel that every
  agent can see. An iteration is over as soon as one agent collect all of its targets.
- Scenario 2: **Collaboration:** Here public and private broadcast is allowed. An agent can
  broadcast information publicly or specificly to an agents channel. Here we may or may not lie in
  the public channel and always tell the truth in private communication. Iteration is over when all
  the agents collects all the targets.
- Scenario 3: **Compassionate:** This is the same as Collaboration except no one will ever lie and
  the game is over when one agent collect all of its targets.

# Setup

Read [SETUP.org](./docs/SETUP.org) to setup `SDL2` and `SDL2_image`
