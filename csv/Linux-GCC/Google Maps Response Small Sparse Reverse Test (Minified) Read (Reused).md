
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1766.89 | 0.0777748 | 954.85ms | 4390 | 320 | 1086.78 | 2369.5 | 0.0433712 | 2.96525 | 13.508 | 2.52118 | 0.0032695 | 3.34567e-05 | 7.11845e-06 | 1(Win) | true |
| simdjson (ondemand) | 1657.5 | 0.0201092 | 972.276ms | 4390 | 2560 | 660.471 | 2525.88 | 0.109897 | 3.15547 | 13.7843 | 2.37312 | 0.00442278 | 2.11774e-05 | 3.38126e-06 | 2(Loss) | true |
