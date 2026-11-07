
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3190.75 | 0.106559 | 199.737ms | 5839 | 30 | 103.752 | 1745.2 | 0.112817 | 0.764098 | 1(Win) | true |
| Jsonifier | 2303.05 | 0.0665015 | 269.054ms | 5839 | 80 | 206.835 | 2417.89 | 0.342896 | 1.06402 | 2(Loss) | true |
| simdjson (ondemand) | 2144.57 | 0.0760432 | 279.001ms | 5839 | 80 | 311.895 | 2596.56 | 0.0746736 | 1.14198 | 3(Loss) | true |
| Glaze | 2095.68 | 0.0584799 | 286.775ms | 5839 | 160 | 386.333 | 2657.14 | 0.0574255 | 1.16971 | 4(Loss) | true |
