<h1 align="center"> Autoplay </h1>
<p align="center">:warning: this project is work in progress!</p>

In game development, Testing is very hard. sometimes, it even looks as if impossible. why testing in game is difficult? because, making test case of complex, stateful features is very hard. and almost game features are very complex & stateful. we want to test this complex, stateful game features more easily. so, we make **AUTO PLAY**! with Autoplay, you can make some kind of these test cases more easily.

## Concept

Autoplay uses **Record - Playing** model. you can *record* your inputs in test level. after that, you can *play* your inputs and check that works correctly.

you can make this process automatically by using command line script. moreover, you can integrate this automatic test into your build process.

if you want to see how Autoplay works, See Example project. it contains various Autoplay test cases.

## Install

Copy Autoplay plugin into your project's Plugins folder. after install the Autoplay plugin, open your Project Setting - General - change Game Viewport Client Class to **AutoplayGameViewportClient**

## How to use

in auto play, one level is one test case. record your input and play that inputs, that level's game state must satisfy assertions you descripted. Autoplay checks all assertions and save result.

1. make your test level.
2. test level must have one Autoplay manager. add Autoplay manager Actor into the level.
3. make some assert & check for your test level. see **Check Test Case** section.
3. if you play that test level in PIE mode, it automatically record your all inputs into Tests/(levelName).json file.
4. play that level with **-autoplay** commandline argument, it playing your recorded input.
5. when play ended, testing results saved in Tests/Result/result.json file.

but manual test is not recommended. use script file(autoplay.py) to check test case.

### Check Test Case

you can use these functions to check your input works correctly.

- AutoplayManager::Assert
- AutoplayManager::ShouldExecute
- AutoplayManager::Routine

## How to use Autoplay script

### Config fields

- Use Editor : if true, use UE4Editor.exe to play test case. if false, it considered Project field value as executable file(build binary file).
- Editor Path : path that UE4Editor.exe exists. if Use Editor field set false, this field ignored.
- Project : test project name. you can use absolute path or relative path.
- Autoplay : test case list. for example, if you set this field to [ "MoveTest", "ShootTest", "DeadTest" ], Autoplay will test these three case step by step(MoveTest.umap & MoveTest.json, ShootTest.umap & ShootTest.json, DeadTest.umap & DeadTest.json) and print all test results.

## TO DO
- [ ] record VR HMD & motion controller input
- [ ] network test
- [ ] check unreal engine log & game crash
- [ ] integrate unreal engine automation test framework