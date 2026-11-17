
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2908.87 | 0.305729 | 5398.01ms | 1151920 | 640 | 8.53196e+08 | 377658 | 0.21586 | 1(Win) | true |
| Jsonifier (two-stage) | 2798.15 | 0.328787 | 5562.69ms | 1151920 | 640 | 1.06638e+09 | 392601 | 1.96049 | 2(Loss) | true |
| Glaze | 2005.15 | 1.017 | 7732.43ms | 1151920 | 40 | 1.2418e+09 | 547868 | 1.29894 | 3(Loss) | true |
| simdjson (ondemand) | 1684.84 | 0.541889 | 8940.94ms | 1151920 | 160 | 1.99742e+09 | 652026 | 0.172403 | 4(Loss) | true |
