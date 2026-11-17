
----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3254.18 | 0.03432 | 1471.66ms | 25388 | 2560 | 16692 | 7440.23 | 0.0240558 | 1.57997 | 7.29057 | 1.30168 | 0.00323249 | 7.72388e-06 | 1.32321e-06 | 1(Win) | true |
| simdjson (ondemand) | 3134.96 | 0.0663488 | 1503ms | 25388 | 640 | 16805.1 | 7723.2 | 0.0163293 | 1.6504 | 7.43611 | 1.15535 | 0.00322507 | 6.09294e-06 | 0 | 2(Loss) | true |
