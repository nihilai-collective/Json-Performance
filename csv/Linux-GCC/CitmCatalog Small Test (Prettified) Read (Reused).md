
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2960.66 | 0.13614 | 226.395ms | 5839 | 30 | 196.695 | 1880.83 | 0.425299 | 0.823463 | 1(Win) | true |
| Jsonifier | 2781.84 | 0.098086 | 215.422ms | 5839 | 30 | 115.651 | 2001.73 | 0.42779 | 0.87749 | 2(Loss) | true |
| simdjson (ondemand) | 2535.86 | 0.0816198 | 236.914ms | 5839 | 30 | 96.369 | 2195.9 | 0.0621985 | 0.964029 | 3(Loss) | true |
| simdjson (reflection) | 2433.63 | 0.109162 | 258.99ms | 5839 | 80 | 499.116 | 2288.15 | 0.176216 | 1.00538 | 4(Loss) | true |
| Glaze | 2020.75 | 0.228436 | 297.67ms | 5839 | 4890 | 193771 | 2755.66 | 1.10769 | 1.21314 | 5(Loss) | true |
