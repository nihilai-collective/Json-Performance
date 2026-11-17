
----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5892.68 | 0.0663722 | 6566.21ms | 360584 | 4890 | 7.33615e+06 | 58357.1 | 0.244246 | 0.86103 | 4.37902 | 0.664142 | 0.00136016 | 7.47367e-06 | 4.77526e-06 | 1(Win) | true |
| simdjson (ondemand) | 4941.17 | 0.0989772 | 7661.83ms | 360584 | 320 | 1.51836e+06 | 69594.8 | 0.0447705 | 1.02845 | 5.03403 | 0.704717 | 0.00195629 | 8.31984e-07 | 1.38664e-07 | 2(Loss) | true |
