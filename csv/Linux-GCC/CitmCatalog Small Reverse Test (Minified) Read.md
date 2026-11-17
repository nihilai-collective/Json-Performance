
----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 687.041 | 0.0629614 | 1434.71ms | 5092 | 160 | 3168.7 | 7068.16 | 0.07431 | 7.54165 | 32.0024 | 6.55818 | 0.00722457 | 3.06854e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 451.605 | 0.0352826 | 1795.75ms | 5092 | 2560 | 36848.5 | 10753 | 0.0666319 | 11.4338 | 53.6991 | 10.9242 | 0.0183536 | 0.000151279 | 8.66095e-05 | 2(Loss) | true |
