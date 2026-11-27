
----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2462.96 | 0.200292 | 962.37ms | 5839 | 2560 | 52496.3 | 2260.9 | 0.169381 | 2.08936 | 8.37164 | 1.65525 | 0.000605974 | 2.42844e-05 | 2.74287e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2312.22 | 0.150132 | 980.248ms | 5839 | 2560 | 33466.1 | 2408.29 | 0.0460922 | 2.22344 | 9.10396 | 1.5167 | 0.000640159 | 8.24199e-05 | 4.74316e-05 | 2(Loss) | true |
| Glaze | 1786.78 | 0.0819407 | 1048.95ms | 5839 | 4890 | 31889.2 | 3116.5 | 0.223276 | 2.86369 | 11.3055 | 2.18359 | 0.00183142 | 4.48644e-05 | 1.39391e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1715.18 | 0.158467 | 1062.99ms | 5839 | 640 | 16940.1 | 3246.61 | 0.054931 | 2.98175 | 11.3173 | 1.75116 | 0.0013329 | 4.121e-05 | 9.6335e-06 | 4(Loss) | true |
