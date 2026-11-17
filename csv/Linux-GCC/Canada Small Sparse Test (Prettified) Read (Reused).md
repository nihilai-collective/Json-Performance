
----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12274 | 0.0718525 | 806.36ms | 11579 | 4890 | 2043.45 | 899.676 | 0.129738 | 0.437383 | 2.11262 | 0.205631 | 0.000222301 | 1.1886e-05 | 2.27829e-06 | 1(Win) | true |
| simdjson (ondemand) | 10844 | 0.0659193 | 815.127ms | 11579 | 320 | 144.192 | 1018.32 | 0.122907 | 0.492778 | 2.43674 | 0.228517 | 0.000172726 | 7.82667e-06 | 5.3977e-07 | 2(Loss) | true |
