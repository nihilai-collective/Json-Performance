
----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 689.706 | 0.0419321 | 1430.36ms | 5092 | 2560 | 22314.2 | 7040.84 | 0.0424463 | 7.51466 | 32.5171 | 6.61361 | 0.00700893 | 0.000123739 | 6.49763e-05 | 1(Win) | true |
| simdjson (ondemand) | 449.415 | 0.0629382 | 1804.05ms | 5092 | 160 | 7399.96 | 10805.4 | 0.0251095 | 11.5046 | 56.1387 | 10.9487 | 0.0138133 | 3.06854e-05 | 2.45483e-06 | 2(Loss) | true |
