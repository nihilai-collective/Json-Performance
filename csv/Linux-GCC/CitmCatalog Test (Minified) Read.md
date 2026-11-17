
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1402.15 | 0.202441 | 8982.08ms | 500299 | 40 | 1.89813e+07 | 340278 | 0.00540273 | 3.62736 | 16.7806 | 3.13038 | 0.0145345 | 0.0100136 | 8.66482e-05 | 1(Win) | true |
| simdjson (ondemand) | 1164.64 | 0.249283 | 5308.11ms | 500299 | 160 | 1.66872e+08 | 409675 | 0.158192 | 4.33663 | 17.745 | 2.9652 | 0.0238359 | 0.0171811 | 4.63473e-05 | 2(Loss) | true |
