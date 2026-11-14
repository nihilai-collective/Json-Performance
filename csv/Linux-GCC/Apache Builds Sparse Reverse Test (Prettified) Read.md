
----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2363.39 | 0.0961223 | 5777.79ms | 124597 | 40 | 93422.7 | 50277.3 | 0.0835332 | 2.18078 | 10.0945 | 1.9305 | 0.00590383 | 3.61164e-06 | 8.02588e-07 | 1(Win) | true |
| simdjson (ondemand) | 2120.67 | 0.0367188 | 6336.18ms | 124597 | 1280 | 541823 | 56031.9 | 0.226605 | 2.41621 | 10.097 | 1.86025 | 0.00685063 | 3.79975e-06 | 8.33939e-07 | 2(Loss) | true |
