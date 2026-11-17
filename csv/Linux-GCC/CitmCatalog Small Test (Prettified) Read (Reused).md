
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2873.94 | 0.241908 | 213.979ms | 5839 | 2560 | 56242.3 | 1937.59 | 0.0227358 | 0.849175 | 1(Win) | true |
| simdjson (ondemand) | 2576.4 | 0.289691 | 235.153ms | 5839 | 2560 | 100360 | 2161.35 | 0.30781 | 0.948878 | 2(Loss) | true |
| simdjson (reflection) | 2468.08 | 0.0796116 | 248.923ms | 5839 | 160 | 516.215 | 2256.21 | 0.0124641 | 0.991234 | 3(Loss) | true |
| Jsonifier | 2117.22 | 0.141929 | 280.676ms | 5839 | 40 | 557.374 | 2630.1 | 0.838371 | 1.15683 | 4(Loss) | true |
| Glaze | 1921.94 | 0.0919642 | 298.044ms | 5839 | 30 | 212.989 | 2897.33 | 0.310812 | 1.27543 | 5(Loss) | true |
