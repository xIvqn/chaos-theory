# Lorenz Attractor

## Explanation

The Lorenz Attractor is a mathematical model that exhibits chaotic behavior and is named after Edward Lorenz, an American mathematician and meteorologist. It was first described by Lorenz in 1963 while he was studying the behavior of a simplified model of atmospheric convection.

This model is defined by a set of three coupled ordinary differential equations that represent the evolution of a system in three-dimensional space. These equations describe how the system's variables change over time, determining the trajectory of the system in what is known as phase space.

## Mathematical model

### Equations

The equations that govern the Lorenz Attractor are as follows:

$\frac{dx}{dt} = \sigma(y - x)$

$\frac{dy}{dt} = x(\rho - z) - y$

$\frac{dz}{dt} = xy - \beta z$

The equations define how the variables change over time, determining the trajectory of the system in phase space. Here, $x$, $y$, and $z$ represent the system's variables, and $t$ represents time. 

### Parameters

The parameters $\sigma$, $\rho$, and $\beta$ are positive constants and control the dynamics of the system and can lead to various phenomena. 

* Sigma (σ): This parameter represents the Prandtl number, which measures the ratio of momentum diffusivity to thermal diffusivity. Increasing or decreasing sigma affects the rate at which heat is transferred in the system.

  * When sigma is small, the system tends to be less chaotic, and the attractor may have a simpler shape with narrower lobes and fewer details.
  * As sigma increases, the attractor becomes more complex, with wider lobes, more intricate structures, and a greater range of trajectories.
  * At very high values of sigma, the system can exhibit multiple smaller attractors or even lose its chaotic behavior altogether, converging to a stable equilibrium point.

* Rho (ρ): This parameter represents the Rayleigh number, which measures the intensity of thermal convection in the system. Changing rho alters the convection and heat exchange processes.

  * At low values of rho, the system is relatively stable and may exhibit periodic or quasi-periodic behavior, with the attractor forming closed loops or torus-like structures.
  * As rho increases beyond a certain critical value, the attractor transitions into chaotic behavior, characterized by sensitive dependence on initial conditions and the formation of the well-known butterfly-shaped attractor.
  * Further increasing rho causes the attractor to undergo stretching and folding, resulting in more intricate patterns and a wider range of trajectories.

* Beta (β): This parameter represents the ratio of the width of the convection cell to its height. Changing beta influences the aspect ratio of the system.

  * For low values of beta, the attractor remains similar to the standard Lorenz attractor, with the characteristic butterfly shape.
  * Increasing beta leads to a change in the attractor's structure. The lobes become elongated and stretched along a specific direction, distorting the butterfly shape.
  * Very high values of beta can cause the attractor to become more symmetric, with the lobes expanding and appearing more rounded.

## Characteristics

The Lorenz Attractor exhibits several key properties of chaotic systems. One of the most notable properties is its sensitive dependence on initial conditions. Even tiny variations in the initial values of x, y, and z can lead to vastly different trajectories and outcomes over time. This sensitivity is a hallmark of chaos and reflects the exponential amplification of small differences.

Another important characteristic of the Lorenz Attractor is the presence of a strange attractor. The trajectory of the system never repeats itself, and it settles into a complex, non-repeating pattern. The attractor has a fractal nature, meaning that it exhibits self-similarity at different scales. When visualized, the Lorenz Attractor reveals intricate details and fine structures that repeat at different levels of magnification.

## Experiments

### Experiment 1

Parameters: $\sigma = 10$, $\rho = 28$, $\beta = 8/3$:

![image](https://github.com/xIvqn/chaos-theory/assets/72264031/ae554e44-8eab-4d71-a924-6d6468444cdb)


### Experiment 2

Parameters: $\sigma = 10$, $\rho = 50$, $\beta = 4$:

![image](https://github.com/xIvqn/chaos-theory/assets/72264031/8a330866-05b5-42da-96f0-b8943c55aad8)


### Experiment 3

Parameters: $\sigma = 10$, $\rho = 45$, $\beta = 10$:

![image](https://github.com/xIvqn/chaos-theory/assets/72264031/0aae8652-a32f-49d8-a416-c6e33542a37e)


### Experiment 4

Parameters: $\sigma = 25$, $\rho = 40$, $\beta = 7$:

![image](https://github.com/xIvqn/chaos-theory/assets/72264031/ec174e1c-9a9f-4e1c-bda4-9827c16cadf7)


### Experiment 5

Parameters: $\sigma = 5$, $\rho = 15$, $\beta = 2$:

![image](https://github.com/xIvqn/chaos-theory/assets/72264031/2efae893-4115-407f-8201-8b0f4d56f309)



Through the implementation of the Lorenz Attractor in computational models and visualizations, researchers and enthusiasts can explore the fascinating world of chaos theory and gain a deeper understanding of the complex and beautiful dynamics inherent in chaotic systems.
