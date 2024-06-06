# Screen Layout Plugin
The screen layout plugin tries to approach the behavior of widget trees. By comparing a widget to a tree node, depending on its attribute as either a leaf or a root, we have the capabilities of handling cases such as back actions, behavior of a parent when a leaf node is shown and so on. It uses the **CommonUI plugin** and the **GameplayTags**, so in order for the plugin to work as expected both of them are necessary. This is based on Epic's Lyra approach.

<!-- TOC -->

## Core Overview
Since versatility and on the fly application are a must have for me, most of the functionality is exposed in blueprints. 

### Screen Layout
The `ScreenLayout.h` is the base widget of the plugin and kind of the main powerhouse &mdash; hence the name being the same as the plugin's &mdash; since it acts as the base on which the widget tree is built. The functionality is pretty straightforward as the widget contains `CommonActivatableWidgetQueue` s which act as layers. The order of those queues are also tied with the priority of the widgets shown on screen &mdash; an example could be a layer for the player's HUD would be lower in hierarchy than the layer system messages.

**Important** to note that the gameplay tags will be under the UI.Layer category.

### Screen Layout Manager System
`ScreenLayoutManagerSystem.h` is the heart of the screen layout plugin. It is created on the client as it manages the proper function of the screen layout async. It also provides a means of setting states which refer to game concepts such as game menu, game HUD etc (the layers mentioned previously). These states have to have a correlation with a gameplay tag. Based on that, it has the ability to display the proper first (primary) widget that should be shown in said state.

### Modular Player Controller
`ModularPlayerController.h` was created as a way to provide the ability of notifying when the screen layout was added on screen. The main problem that I tried to solve with this is the asynchronous setting up of the screen layout widget could create race conflicts.

### Modular Game Mode [DEPRECATED]
With `ModularGameMode` I tried to move the process of notifying about the UI setup from the controller to the game mode. That was mainly because in a server-client scenario it seemed like a better idea for the server to know about the players' UI state if any need for notifications, game/match progression arose. Alas I kind of dumped that idea and maybe come back to it in the future. 🤥

**NOTE** that the system works without the controller being necessarily derived from the `ModularPlayerController.h` and thus not limiting any application of it.
