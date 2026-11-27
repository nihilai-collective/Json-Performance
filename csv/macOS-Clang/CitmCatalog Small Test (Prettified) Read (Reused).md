
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2491.08 | 0.170638 | 279.18ms | 5839 | 40 | 581.984 | 2235.38 | 0.0964604 | 1(Win) | true |
| Jsonifier (two-stage) | 2233.2 | 0.0998997 | 303.723ms | 5839 | 4890 | 30343 | 2493.51 | 0.128349 | 2(Loss) | true |
| Glaze | 1628.72 | 0.0838445 | 397.172ms | 5839 | 160 | 1314.78 | 3418.94 | 0.0955155 | 3(Loss) | true |
| simdjson (ondemand) | 1473.44 | 0.170745 | 427.294ms | 5839 | 2560 | 106598 | 3779.25 | 0.0682127 | 4(Loss) | true |
