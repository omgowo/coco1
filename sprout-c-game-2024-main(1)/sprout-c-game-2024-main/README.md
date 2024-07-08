# 資訊之芽 2024 大作業二

## How to Start

### WebGL 遊戲安裝

1. 先去右上角點擊 Code -> Download ZIP
2. 解壓縮後，用 VSCode 開啟該資料夾
3. 在 VSCode 的 Terminal 輸入 docker compose up

或是如果會用 git 的話，可以簡單的用以下指令可以把 遊戲跟 C++ server 架起來 

```bash
git clone https://github.com/iceylemon157/sprout-c-game-2024
cd sprout-c-game-2024
docker compose up
```

此時在瀏覽器中打開 `localhost:12345/app` 即可看到遊戲畫面。

### C++ server

接著開一個新的 terminal，先進到 `sprout-c-game-2024` 資料夾 (你剛剛下載完的程式碼檔案的資料夾) 裡面，然後執行以下指令就可以把 C++ server 跑起來

```bash
docker compose exec cpp_server /bin/bash
(在 docker 裡面) make && ./server
```

## Reference

Game Assets are mostly from the tutorial of [Code Monkey](https://www.youtube.com/watch?v=AmGSEH7QcDg). Also, many of the C# code follows the tutorial (for the WebGL build), while the code has been modified by me to be able to connect to C++ Server.
