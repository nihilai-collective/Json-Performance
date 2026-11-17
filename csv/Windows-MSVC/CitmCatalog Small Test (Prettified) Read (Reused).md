
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1499.11 | 0.130264 | 438.939ms | 5839 | 1280 | 29968.5 | 3714.53 | 0.0210278 | 2.01568 | 1(Win) | true |
| Jsonifier | 1362.3 | 0.0897077 | 475.562ms | 5839 | 4890 | 65751 | 4087.59 | 0.0997005 | 2.21708 | 2(Loss) | true |
| Glaze | 1130.09 | 0.13496 | 560.126ms | 5839 | 80 | 3537.97 | 4927.5 | 0 | 2.6797 | 3(Loss) | true |
| simdjson (ondemand) | 1053.74 | 0.0828272 | 589.914ms | 5839 | 2560 | 49045.5 | 5284.53 | 0.303987 | 2.87393 | 4(Loss) | true |
