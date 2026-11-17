
----
### CitmCatalog Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 762.23 | 0.0280133 | 1409.55ms | 5092 | 2560 | 8154.06 | 6370.93 | 0.118131 | 6.79459 | 30.7901 | 6.19917 | 0.0058461 | 5.7842e-05 | 1.23509e-05 | 1(Win) | true |
| simdjson (ondemand) | 458.818 | 0.0218087 | 1832.15ms | 5092 | 2560 | 13639.4 | 10583.9 | 0.00358014 | 11.2664 | 54.4747 | 10.5479 | 0.0138815 | 6.80448e-05 | 2.19401e-05 | 2(Loss) | true |
