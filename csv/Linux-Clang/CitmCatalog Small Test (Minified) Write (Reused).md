
----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8751.91 | 0.406836 | 768.943ms | 3223 | 1280 | 2613.15 | 351.202 | 0.0731326 | 0.646466 | 2.2628 | 0.282035 | 0.000310512 | 2.7391e-05 | 7.51435e-06 | 1(Win) | true |
| Glaze | 3129.93 | 0.177185 | 833.305ms | 3223 | 4890 | 14805.2 | 982.032 | 1.03254 | 1.67747 | 4.65095 | 0.652498 | 0.000317503 | 3.62299e-05 | 6.97949e-06 | 2(Loss) | true |
