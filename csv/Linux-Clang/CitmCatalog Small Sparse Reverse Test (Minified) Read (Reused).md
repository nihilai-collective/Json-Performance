
----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3138.59 | 0.0166905 | 869.764ms | 5092 | 2560 | 170.721 | 1547.23 | 0.0691284 | 1.68396 | 7.80538 | 1.35055 | 0.00224932 | 1.90249e-05 | 2.3014e-07 | 1(Win) | true |
| simdjson (ondemand) | 3131.82 | 0.0297592 | 870.619ms | 5092 | 1280 | 272.542 | 1550.57 | 0.0119901 | 1.68814 | 8.20719 | 1.28044 | 0.00213202 | 1.59564e-05 | 1.6877e-06 | 2(Loss) | true |
