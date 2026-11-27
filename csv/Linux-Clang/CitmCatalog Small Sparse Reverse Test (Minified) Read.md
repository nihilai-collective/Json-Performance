
----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3240.92 | 0.0956362 | 880.455ms | 5092 | 4890 | 10041.4 | 1498.37 | 0.262683 | 1.62968 | 7.87196 | 1.40475 | 0.00275503 | 1.90764e-05 | 4.17673e-06 | 1(Win) | true |
| simdjson (ondemand) | 2985.14 | 0.0746271 | 878.317ms | 5092 | 80 | 117.905 | 1626.76 | 0.00537849 | 1.77018 | 8.33189 | 1.30577 | 0.00197614 | 4.90966e-06 | 0 | 2(Loss) | true |
