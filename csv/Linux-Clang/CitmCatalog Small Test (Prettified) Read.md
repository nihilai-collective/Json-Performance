
----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2657.74 | 0.0769518 | 213.726ms | 5839 | 80 | 207.959 | 2095.2 | 0.0214731 | 0.919395 | 1(Win) | true |
| Jsonifier | 2563.37 | 0.10921 | 221.317ms | 5839 | 30 | 168.851 | 2172.33 | 0.0168818 | 0.953925 | 2(Loss) | true |
| simdjson (ondemand) | 1827.79 | 0.0872314 | 315.942ms | 5839 | 40 | 282.507 | 3046.57 | 0.318195 | 1.34251 | 3(Loss) | true |
| Glaze | 1801.17 | 0.0721118 | 309.608ms | 5839 | 40 | 198.81 | 3091.6 | 0.0344902 | 1.363 | 4(Loss) | true |
