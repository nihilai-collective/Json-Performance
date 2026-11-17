
----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3182.3 | 0.0703763 | 1007.93ms | 9378 | 1280 | 5007.27 | 2810.41 | 0.141073 | 1.6365 | 7.2813 | 1.28247 | 0.00232642 | 1.38289e-05 | 6.66453e-07 | 1(Win) | true |
| simdjson (ondemand) | 3151.08 | 0.0325333 | 999.863ms | 9378 | 4890 | 4169.33 | 2838.25 | 0.147937 | 1.65643 | 7.28396 | 1.17061 | 0.00210241 | 1.84917e-05 | 5.12447e-06 | 2(Loss) | true |
