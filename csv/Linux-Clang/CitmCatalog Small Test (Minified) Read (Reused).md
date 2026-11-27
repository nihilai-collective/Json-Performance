
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2462.31 | 0.0304923 | 143.506ms | 3223 | 640 | 92.7242 | 1248.29 | 0.226546 | 0.984801 | 1(Win) | true |
| Jsonifier (two-stage) | 1926.53 | 0.0508543 | 180.144ms | 3223 | 320 | 210.656 | 1595.45 | 0.101367 | 1.26451 | 2(Loss) | true |
| Glaze | 1591.21 | 0.21843 | 212.932ms | 3223 | 40 | 712.122 | 1931.67 | 0.00388279 | 1.53512 | 3(Loss) | true |
| simdjson (ondemand) | 1234.9 | 0.0855997 | 268.273ms | 3223 | 80 | 363.152 | 2489.01 | 0.015566 | 1.98105 | 4(Loss) | true |
