
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2173.06 | 0.144276 | 365.67ms | 5839 | 160 | 2186.94 | 2562.51 | 2.67292 | 1(Win) | true |
| Jsonifier (two-stage) | 2093.55 | 0.249399 | 344.935ms | 5839 | 30 | 1320.14 | 2659.83 | 0.00125323 | 2(Loss) | true |
| Glaze | 1476.32 | 0.295226 | 441.708ms | 5839 | 1280 | 158721 | 3771.88 | 0.00161555 | 3(Loss) | true |
| simdjson (ondemand) | 1459 | 0.220471 | 457.308ms | 5839 | 40 | 2832.23 | 3816.65 | 0.037977 | 4(Loss) | true |
