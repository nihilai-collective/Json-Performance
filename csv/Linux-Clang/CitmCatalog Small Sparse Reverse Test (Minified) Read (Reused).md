
----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3309.3 | 0.0501174 | 865.574ms | 5092 | 2560 | 1384.59 | 1467.41 | 0.291404 | 1.60438 | 7.74686 | 1.37824 | 0.00303026 | 1.66468e-05 | 5.29323e-06 | 1(Win) | true |
| simdjson (ondemand) | 3041.17 | 0.0891613 | 881.452ms | 5092 | 1280 | 2594.52 | 1596.79 | 0.0289238 | 1.74 | 8.20974 | 1.28024 | 0.00249871 | 1.08933e-05 | 3.83567e-06 | 2(Loss) | true |
