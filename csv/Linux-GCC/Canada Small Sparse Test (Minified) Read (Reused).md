
----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7304.05 | 0.236135 | 772.479ms | 4630 | 640 | 1304.17 | 604.53 | 0.0965006 | 0.74992 | 3.53218 | 0.45594 | 0.00043399 | 9.44924e-06 | 1.01242e-06 | 1(Win) | true |
| simdjson (ondemand) | 6666 | 0.0219876 | 779.276ms | 4630 | 4890 | 103.728 | 662.393 | 0.193249 | 0.819966 | 4.08013 | 0.484233 | 0.00043201 | 1.38688e-05 | 3.18011e-06 | 2(Loss) | true |
