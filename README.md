# Chaos Theory

This GitHub repository aims to provide a visualization of various models of Chaos Theory, with the Lorenz Attractor being the currently implemented model. The repository contains code and resources to generate interactive visualizations of the Lorenz Attractor using, as for now, C++, OpenGL, GLFW.

By exploring and expanding this GitHub repository, I can delve into the captivating world of Chaos Theory and gain a better understanding of complex and unpredictable systems through interactive visualizations of the different models implemented.

## Table of contents

1. [Background](#Background)
    1. [Chaos Theory](#chaos-theory)
    2. [Lorenz Attractor](#lorenz-attractor)
2. [Key Features](#key-features)

## Background

### Chaos Theory

The Chaos Theory is a branch of mathematics and physics that seeks to understand the behavior of complex and unpredictable systems. It emerged in the late 20th century as a field of study that challenged the traditional belief that complex systems could be fully understood and predicted using deterministic models. The Chaos Theory provides a framework for understanding and analyzing such nonlinear systems. It explores the behavior of dynamical systems, which are systems that evolve over time according to specific rules or equations. These systems may involve a multitude of interacting components, feedback loops, and nonlinearity.

One of the fundamental concepts in Chaos Theory is the notion of sensitive dependence on initial conditions, often referred to as the "butterfly effect." It suggests that even minute changes in the initial state of a system can lead to significantly different outcomes over time. The idea is captured by the famous quote often attributed to Edward Lorenz: "Does the flap of a butterfly's wings in Brazil set off a tornado in Texas?" This sensitivity to initial conditions is a key characteristic of chaotic systems.

Another key concept in Chaos Theory is that of attractors. An attractor is a region or a set of states towards which a system tends to evolve over time. In chaotic systems, attractors can exhibit a complex and intricate geometric structure. These structures are often referred to as "strange attractors" due to their fractal nature. Fractals are self-similar patterns that repeat at different scales, and they can be found in various natural phenomena, such as coastlines, clouds, and tree branches. The study of strange attractors and fractals has revealed the underlying order within chaotic systems.

In summary, the Chaos Theory highlights the sensitive dependence on initial conditions, the existence of strange attractors with intricate geometric structures, and the inherent nonlinearity in such systems. By studying and analyzing chaotic systems, scientists and researchers gain insights into the underlying patterns and dynamics of these systems, enabling a deeper understanding of the world around us.

### Lorenz Attractor

The Lorenz Attractor is a mathematical model that exhibits chaotic behavior and is named after Edward Lorenz, an American mathematician and meteorologist. It was first described by Lorenz in 1963 while he was studying the behavior of a simplified model of atmospheric convection.

The Lorenz Attractor is defined by a set of three coupled ordinary differential equations that represent the evolution of a system in three-dimensional space. These equations describe how the system's variables change over time, determining the trajectory of the system in what is known as phase space.

The equations that govern the Lorenz Attractor are as follows:

$\frac{dx}{dt} = \sigma(y - x)$

$\frac{dy}{dt} = x(\rho - z) - y$

$\frac{dz}{dt} = xy - \beta z$

Here, $x$, $y$, and $z$ represent the system's variables, and $t$ represents time. The parameters $\sigma$, $\rho$, and $\beta$ are positive constants that control the behavior of the system. The equations define how the variables change over time, determining the trajectory of the system in phase space.

The Lorenz Attractor exhibits several key properties of chaotic systems. One of the most notable properties is its sensitive dependence on initial conditions. Even tiny variations in the initial values of x, y, and z can lead to vastly different trajectories and outcomes over time. This sensitivity is a hallmark of chaos and reflects the exponential amplification of small differences.

Another important characteristic of the Lorenz Attractor is the presence of a strange attractor. The trajectory of the system never repeats itself, and it settles into a complex, non-repeating pattern. The attractor has a fractal nature, meaning that it exhibits self-similarity at different scales. When visualized, the Lorenz Attractor reveals intricate details and fine structures that repeat at different levels of magnification.

Through the implementation of the Lorenz Attractor in computational models and visualizations, researchers and enthusiasts can explore the fascinating world of chaos theory and gain a deeper understanding of the complex and beautiful dynamics inherent in chaotic systems.

## Key Features

1. **Interactive Visualization**: The repository integrates with visualization libraries to create interactive visualizations of the Lorenz Attractor. Users can manipulate parameters, view the attractor from different angles, and zoom in/out to examine its intricate structure. The visualization may include features like color mapping, trajectory animations, and user-friendly controls.

2. **Documentation and Examples**: The repository provides clear documentation on how to use the code and replicate the visualizations. It includes examples showcasing various aspects of the Lorenz Attractor, such as the sensitivity to initial conditions, the fractal nature of the attractor, and the effect of parameter variations on the system's behavio

3. **Lorenz Attractor Implementation**: The repository includes the code to numerically solve the Lorenz Attractor's differential equations and generate its trajectory in three-dimensional space. It provides functions to specify initial conditions and parameter values, allowing users to explore different scenarios.

