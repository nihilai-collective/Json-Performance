
----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15667 | 1.75513 | 59.1959ms | 9249 | 2560 | 249964 | 563 | 0.859907 | 1(Win) | true |
| Glaze | 2193.84 | 0.343113 | 411.19ms | 9249 | 1280 | 243593 | 4020.6 | 0.882556 | 2(Loss) | true |
| simdjson (reflection) | 290.884 | 1.15445 | 2995.77ms | 9249 | 80 | 9.80369e+06 | 30323.2 | 1.78275 | 3(Loss) | true |
