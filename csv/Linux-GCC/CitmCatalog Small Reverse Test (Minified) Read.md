
----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 673.235 | 0.0295061 | 1445.85ms | 5092 | 4890 | 22150.1 | 7213.1 | 0.18553 | 7.64238 | 31.9878 | 6.55596 | 0.00746984 | 5.34942e-05 | 1.32531e-05 | 1(Win) | true |
| simdjson (ondemand) | 455.537 | 0.0202525 | 1791.5ms | 5092 | 4890 | 22792.7 | 10660.2 | 0.107612 | 11.34 | 53.7581 | 10.9344 | 0.0165508 | 7.22895e-05 | 1.97993e-05 | 2(Loss) | true |
