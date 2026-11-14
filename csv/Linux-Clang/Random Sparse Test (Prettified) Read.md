
----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3459.74 | 0.0382419 | 9907.11ms | 676745 | 320 | 1.62851e+06 | 186544 | 0.187949 | 1.46296 | 6.54911 | 1.15094 | 0.00421664 | 0.00645237 | 6.46015e-06 | 1(Win) | true |
| simdjson (ondemand) | 2978.91 | 0.04224 | 5719.33ms | 676745 | 640 | 5.35998e+06 | 216654 | 0.24642 | 1.71387 | 7.0958 | 1.09716 | 0.00579269 | 0.00631021 | 4.64771e-06 | 2(Loss) | true |
