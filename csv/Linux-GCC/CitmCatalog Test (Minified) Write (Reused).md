
----
### CitmCatalog Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 12537.1 | 0.0646204 | 4571.79ms | 500299 | 320 | 193533 | 38056.8 | 0.0915753 | 0.411001 | 1.90708 | 0.192453 | 0.00106934 | 0.000658025 | 7.35185e-06 | 1(Win) | true |
| Jsonifier | 11833.6 | 0.0673988 | 4827.73ms | 500299 | 640 | 472617 | 40319.2 | 0.0169865 | 0.434852 | 1.83144 | 0.215147 | 0.00157264 | 0.0044868 | 1.6968e-05 | 2(Loss) | true |
| Glaze | 7261.99 | 0.0246532 | 7324.69ms | 500299 | 4890 | 1.28294e+06 | 65701.4 | 0.00155346 | 0.70138 | 3.75128 | 0.547385 | 0.00156064 | 0.000691088 | 2.44688e-05 | 3(Loss) | true |
