# Project6-1_Enigma_machine

## 執行方式
1. 修改Enigma.cpp中第185行，決定plate的編號。
2. 編譯並執行Enigma.cpp開始進行暴力破解
3. 如果該plate組合有找到解答，則會印出相對應的rotor、starting及plug board

## 介紹
185行為轉盤設定需先初始化：int plate[3] = {第一個轉盤，第二個轉盤，第三個轉盤}

1. get_group()設定plug board的組合存在group
2. Combi()找出C26取12的所有組合然後去執行test()
3. test()執行解密的過程(185行為轉盤初始設定)
4. test()中的input進入encrypt()後產生output
