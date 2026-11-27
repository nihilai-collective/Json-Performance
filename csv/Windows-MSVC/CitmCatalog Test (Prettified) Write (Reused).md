
----
### CitmCatalog Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12218.3 | 0.464329 | 5787.18ms | 1439562 | 80 | 2.17763e+07 | 112362 | 0.630113 | 0.202573 | 1(Win) | true |
| Glaze | 5919.7 | 0.10731 | 6013.97ms | 1439584 | 640 | 3.96402e+07 | 231920 | 0.140476 | 0.418173 | 2(Loss) | true |
