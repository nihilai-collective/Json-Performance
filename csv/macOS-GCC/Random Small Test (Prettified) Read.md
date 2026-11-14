
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1550.99 | 0.414921 | 536.395ms | 8051 | 160 | 67504.1 | 4950.4 | 0.0646831 | 1(Win) | true |
| Jsonifier (two-stage) | 1184.11 | 0.406841 | 622.805ms | 8051 | 1280 | 890784 | 6484.2 | 0.07717 | 2(Loss) | true |
| simdjson (reflection) | 1128.06 | 0.916566 | 693.476ms | 8051 | 160 | 622705 | 6806.4 | 0.424929 | 3(Loss) | true |
| Glaze | 1041.68 | 0.274502 | 731.521ms | 8051 | 2560 | 1.048e+06 | 7370.8 | 1.07902 | 4(Loss) | true |
| simdjson (ondemand) | 916.627 | 0.521398 | 839.111ms | 8051 | 640 | 1.22077e+06 | 8376.4 | 0.290449 | 5(Loss) | true |
