
----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6835.81 | 0.0281896 | 4420.15ms | 264040 | 4890 | 527285 | 36836.6 | 0.191569 | 0.742528 | 3.61408 | 0.46821 | 0.00134443 | 1.92231e-06 | 6.95501e-07 | 1(Win) | true |
| simdjson (ondemand) | 6054.28 | 0.0684974 | 4891.94ms | 264040 | 160 | 129862 | 41591.7 | 0.0401533 | 0.837042 | 3.99731 | 0.439348 | 0.000975018 | 2.08302e-06 | 1.11252e-06 | 2(Loss) | true |
