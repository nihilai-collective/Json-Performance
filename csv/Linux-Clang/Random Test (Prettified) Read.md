
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1806.59 | 0.0758687 | 9147.31ms | 676745 | 1280 | 9.40301e+07 | 357245 | 0.681727 | 1.37027 | 1(Win) | true |
| simdjson (ondemand) | 1563.99 | 0.177241 | 5323.01ms | 676745 | 640 | 3.42365e+08 | 412659 | 0.501626 | 1.58284 | 2(Loss) | true |
