
----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24759 | 0.985082 | 5647.75ms | 1439562 | 30 | 8.95079e+06 | 55449.5 | 0.123146 | 0.0999413 | 1(Win) | true |
| Glaze | 5082.6 | 0.16805 | 6866.95ms | 1439584 | 160 | 3.29685e+07 | 270117 | 0.428132 | 0.487044 | 2(Loss) | true |
| simdjson (reflection) | 565.336 | 0.26181 | 7494.73ms | 1439562 | 80 | 3.23376e+09 | 2.42842e+06 | 0.427389 | 4.37907 | 3(Loss) | true |
