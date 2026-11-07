
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2240.71 | 0.146469 | 158.558ms | 3223 | 40 | 161.474 | 1371.75 | 0.229108 | 1.08439 | 1(Win) | true |
| Jsonifier (two-stage) | 1934.19 | 0.181882 | 178.665ms | 3223 | 4890 | 40851.9 | 1589.14 | 0.0201404 | 1.25921 | 2(Loss) | true |
| Glaze | 1578.06 | 0.543592 | 209.886ms | 3223 | 1280 | 143493 | 1947.77 | 0.32272 | 1.54819 | 3(Loss) | true |
| simdjson (ondemand) | 1235.27 | 0.11828 | 280.48ms | 3223 | 30 | 259.857 | 2488.27 | 0.229885 | 1.98258 | 4(Loss) | true |
