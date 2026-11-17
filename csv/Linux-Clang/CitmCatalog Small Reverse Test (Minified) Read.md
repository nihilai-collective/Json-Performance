
----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 697.674 | 0.0327405 | 1423.36ms | 5092 | 2560 | 13294.9 | 6960.43 | 0.0319542 | 7.4187 | 32.7159 | 6.65278 | 0.00582884 | 4.27294e-05 | 1.21207e-05 | 1(Win) | true |
| simdjson (ondemand) | 438.032 | 0.02228 | 1860.01ms | 5092 | 2560 | 15618.3 | 11086.2 | 0.0384833 | 11.7938 | 56.1612 | 10.9546 | 0.0138356 | 5.50803e-05 | 1.98688e-05 | 2(Loss) | true |
