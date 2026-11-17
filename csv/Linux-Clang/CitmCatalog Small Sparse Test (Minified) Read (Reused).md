
----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4917.13 | 0.066393 | 810.592ms | 5092 | 320 | 137.578 | 987.591 | 0.0611077 | 1.0903 | 4.8533 | 0.664768 | 0.00143546 | 1.35016e-05 | 6.13708e-07 | 1(Win) | true |
| simdjson (ondemand) | 4748.64 | 0.0695175 | 830.497ms | 5092 | 1280 | 646.899 | 1022.63 | 0.0324024 | 1.12619 | 5.17262 | 0.638256 | 0.00107322 | 9.35904e-06 | 0 | 2(Loss) | true |
