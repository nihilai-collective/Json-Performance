
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1377.51 | 0.105589 | 1122.64ms | 5092 | 80 | 1108.46 | 3525.29 | 0.128168 | 3.78426 | 15.7903 | 2.89827 | 0.00248429 | 0.000186567 | 5.40063e-05 | 1(Win) | true |
| simdjson (ondemand) | 1342.39 | 0.11159 | 1132.38ms | 5092 | 80 | 1303.65 | 3617.5 | 0.0883807 | 3.95524 | 16.262 | 2.69104 | 0.00323547 | 8.59191e-05 | 4.17321e-05 | 2(Loss) | true |
