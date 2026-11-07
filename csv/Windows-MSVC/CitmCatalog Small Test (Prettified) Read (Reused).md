
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1491.15 | 0.280174 | 451.185ms | 5839 | 2560 | 280240 | 3734.38 | 0.0376427 | 1.64802 | 1(Win) | true |
| Jsonifier | 1324.78 | 0.369327 | 502.425ms | 5839 | 30 | 7229.89 | 4203.33 | 0.158856 | 1.85487 | 2(Loss) | true |
| Glaze | 924.649 | 0.14841 | 674.487ms | 5839 | 4890 | 390626 | 6022.29 | 0.0367481 | 2.66608 | 3(Loss) | true |
| simdjson (ondemand) | 862.947 | 0.23678 | 727.252ms | 5839 | 1280 | 298819 | 6452.89 | 0.0157366 | 2.85703 | 4(Loss) | true |
