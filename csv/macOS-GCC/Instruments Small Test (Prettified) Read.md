
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2685.32 | 0.534768 | 289.136ms | 7932 | 1280 | 290479 | 2817 | 0.564044 | 1(Win) | true |
| Jsonifier (two-stage) | 2332.43 | 1.09486 | 330.358ms | 7932 | 160 | 201737 | 3243.2 | 0.637255 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1846.81 | 0.333452 | 411.784ms | 7932 | 1280 | 238779 | 4096 | 0.311526 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1826.83 | 0.918675 | 429.238ms | 7932 | 80 | 115766 | 4140.8 | 0.936037 | 3(Tie) | true |
| simdjson (ondemand) | 1613.32 | 0.381152 | 482.122ms | 7932 | 1280 | 408818 | 4688.8 | 0.246788 | 5(Loss) | true |
