
----
### CitmCatalog Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14021.4 | 0.0437865 | 5422.11ms | 1439562 | 2560 | 4.70541e+06 | 97912.5 | 0.0302474 | 0.360119 | 1.39264 | 0.220277 | 0.000675317 | 0.0189471 | 4.44498e-06 | 1(Win) | true |
| Glaze | 7064.37 | 0.137529 | 5168.85ms | 1439584 | 320 | 2.28594e+07 | 194341 | 0.0749971 | 0.715386 | 3.06771 | 0.527269 | 0.000994107 | 0.0188737 | 1.80239e-05 | 2(Loss) | true |
