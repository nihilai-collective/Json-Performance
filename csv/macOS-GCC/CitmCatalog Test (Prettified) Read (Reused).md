
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3138.53 | 0.266948 | 5107.21ms | 1151920 | 320 | 2.79381e+08 | 350022 | 0.22357 | 1(Win) | true |
| Jsonifier (two-stage) | 2727.97 | 0.343385 | 5863.95ms | 1151920 | 320 | 6.11898e+08 | 402702 | 3.53214 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 2152.83 | 0.395598 | 7520.65ms | 1151920 | 160 | 6.52009e+08 | 510285 | 0.535793 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2137.41 | 0.434397 | 7207.77ms | 1151920 | 160 | 7.97559e+08 | 513966 | 1.03765 | 3(Tie) | true |
| Glaze | 1943.93 | 0.114055 | 7905.28ms | 1151920 | 640 | 2.65883e+08 | 565121 | 0.0398657 | 5(Loss) | true |
