
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2928.35 | 0.32414 | 210.527ms | 5839 | 2560 | 97260.8 | 1901.59 | 0.523106 | 0.832901 | 1(Win) | true |
| Jsonifier | 2102.7 | 0.137619 | 287.204ms | 5839 | 30 | 398.478 | 2648.27 | 0.377769 | 1.16529 | 2(Loss) | true |
| simdjson (ondemand) | 1983.68 | 0.0933218 | 315.351ms | 5839 | 80 | 549.024 | 2807.16 | 0.202124 | 1.23477 | 3(Loss) | true |
| Glaze | 1928.61 | 0.175746 | 312.16ms | 5839 | 2560 | 65917.5 | 2887.32 | 0.146197 | 1.27129 | 4(Loss) | true |
