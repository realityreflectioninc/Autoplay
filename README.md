<h1 align="center"> Autoplay </h1>

In game development, Testing is very hard. sometimes, it even looks as if impossible. why testing in game is difficult? because, making test case of complex, stateful features is very hard. and almost game features are very complex & stateful. we want to test this complex, stateful game features more easily. so, we make **AUTO PLAY**! with Autoplay, you can make some kind of these test cases more easily.

## Concept

Autoplay uses 'Record - Playing' model. you can **record** your inputs in test scene. after that, you can **play** your inputs and check that works correctly by using some functions provided by autoplay.

you can make this process automatic by using command line script. moreover, you can integrate this automatic test into your build process.

if you want how autoplay works, See Example project. it contains various autoplay test cases.

## Install

1. Copy Autoplay plugin into your project's Plugins folder.

## How to use

1. after install the autoplay plugin, open Project Setting - General - change Game Viewport Client Class to **AutoplayGameViewportClient**
2. make your test scene.
3. test scene must have one Autoplay manager. add Autoplay manager Actor into the scene.
4. if you play that test scene in PIE mode, it automatically record your all inputs into Tests/(sceneName).json file.
5. play that level with **-autoplay** commandline argument, it playing your recorded input.
6. when play ended, testing results saved in Tests/Result/result.json file.

but manual test is not recommended. use script file(autoplay.py) to check test case.

### Check Test Case

you can use these functions.

- AutoplayManager::Assert
- AutoplayManager::ShouldExecute
- AutoplayManager::Routine

## How to use Autoplay script

## TO DO
- [ ] record VR HMD & motion controller input
- [ ] network test
- [ ] check unreal engine log & game crash
- [ ] integrate unreal engine automation test framework