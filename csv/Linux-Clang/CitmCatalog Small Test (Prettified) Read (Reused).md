
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3245.81 | 0.0881381 | 192.169ms | 5839 | 30 | 68.5931 | 1715.6 | 0.0952955 | 0.751618 | 1(Win) | true |
| Jsonifier | 2280.29 | 0.075023 | 266.658ms | 5839 | 80 | 268.519 | 2442.01 | 0.0220057 | 1.07344 | 2(Loss) | true |
| Glaze | 2095.19 | 0.103208 | 287.029ms | 5839 | 40 | 300.962 | 2657.75 | 0.321915 | 1.1706 | 3(Loss) | true |
| simdjson (ondemand) | 2080.94 | 0.0681267 | 282.48ms | 5839 | 160 | 531.76 | 2675.96 | 0.0729241 | 1.17734 | 4(Loss) | true |
