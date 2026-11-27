
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 10466.4 | 0.0373374 | 5294.88ms | 500299 | 640 | 185408 | 45585.9 | 0.0425937 | 0.492328 | 2.53185 | 0.173932 | 1.66151e-05 | 1.57406e-06 | 5.43425e-07 | 1(Win) | true |
| simdjson (stage-1) | 9879.96 | 0.11143 | 5525.89ms | 500299 | 30 | 86871.1 | 48291.9 | 0.0667223 | 0.521245 | 2.80238 | 0.112561 | 0.000290426 | 2.33194e-05 | 2.13872e-05 | 2(Loss) | true |
