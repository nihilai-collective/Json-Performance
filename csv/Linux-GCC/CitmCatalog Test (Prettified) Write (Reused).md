
----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 27082.7 | 0.200592 | 5068.37ms | 1439562 | 320 | 3.30869e+06 | 50692 | 0.173101 | 0.0913554 | 1(Win) | true |
| Glaze | 6215.18 | 0.182633 | 5683.25ms | 1439584 | 160 | 2.60402e+07 | 220894 | 0.107755 | 0.398299 | 2(Loss) | true |
| simdjson (reflection) | 568.896 | 0.287638 | 7427.41ms | 1439562 | 30 | 1.44547e+09 | 2.41322e+06 | 0.182398 | 4.35192 | 3(Loss) | true |
