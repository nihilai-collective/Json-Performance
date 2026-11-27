
----
### Twitter Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5935.29 | 0.0625579 | 6597.64ms | 360584 | 1280 | 1.68153e+06 | 57938.2 | 0.157453 | 0.86064 | 4.3277 | 0.670188 | 0.00136649 | 3.24842e-05 | 2.93101e-05 | 1(Win) | true |
| simdjson (ondemand) | 4927.24 | 0.0650178 | 7701.8ms | 360584 | 640 | 1.3178e+06 | 69791.5 | 0.161953 | 1.03167 | 5.0322 | 0.703856 | 0.00136889 | 3.00121e-05 | 2.27669e-05 | 2(Loss) | true |
