
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1531.21 | 0.279159 | 437.136ms | 5839 | 30 | 3091.95 | 3636.67 | 0.456204 | 1.60168 | 1(Win) | true |
| Jsonifier | 1343.72 | 0.20171 | 483.375ms | 5839 | 4890 | 341684 | 4144.11 | 0.218431 | 1.8296 | 2(Loss) | true |
| Glaze | 841.482 | 0.161305 | 735.363ms | 5839 | 40 | 4557.69 | 6617.5 | 0.238693 | 2.9295 | 3(Loss) | true |
| simdjson (ondemand) | 800.149 | 0.259788 | 821.396ms | 5839 | 2560 | 836787 | 6959.34 | 0.232397 | 3.08034 | 4(Loss) | true |
