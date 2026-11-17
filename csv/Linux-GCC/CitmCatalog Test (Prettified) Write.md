
----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 27253.5 | 0.849846 | 5034.24ms | 1439562 | 40 | 7.33089e+06 | 50374.2 | 0.63674 | 0.0907956 | 1(Win) | true |
| Glaze | 5334.02 | 0.309624 | 6829.93ms | 1439584 | 30 | 1.90526e+07 | 257384 | 0.177641 | 0.464096 | 2(Loss) | true |
| simdjson (reflection) | 554.428 | 0.0912545 | 7724.54ms | 1439562 | 80 | 4.08478e+08 | 2.4762e+06 | 0.275755 | 4.46551 | 3(Loss) | true |
