
----
### CitmCatalog Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 710.369 | 0.0542571 | 1409.47ms | 5092 | 1280 | 17608.9 | 6836.04 | 0.261156 | 7.23815 | 31.6599 | 6.48429 | 0.00597153 | 0.000165701 | 7.28778e-05 | 1(Win) | true |
| simdjson (ondemand) | 441.983 | 0.0334146 | 1831.2ms | 5092 | 1280 | 17252.3 | 10987.1 | 0.00209759 | 11.6895 | 56.1084 | 10.9411 | 0.0137701 | 4.06581e-05 | 7.82477e-06 | 2(Loss) | true |
