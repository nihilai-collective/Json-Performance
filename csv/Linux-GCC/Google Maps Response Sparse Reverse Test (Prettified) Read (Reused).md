
----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3448.37 | 0.0454406 | 1436.09ms | 25388 | 4890 | 49776.8 | 7021.26 | 0.0549471 | 1.4915 | 7.09918 | 1.24941 | 0.00345087 | 8.94099e-06 | 1.00687e-06 | 1(Win) | true |
| simdjson (ondemand) | 3305.95 | 0.0256225 | 1465.52ms | 25388 | 4890 | 17219.4 | 7323.74 | 0.0926815 | 1.56587 | 7.11517 | 1.14022 | 0.00323248 | 1.19455e-05 | 4.60743e-06 | 2(Loss) | true |
