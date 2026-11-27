
----
### Google Maps Response Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4686.79 | 0.0734655 | 1264.08ms | 25388 | 1280 | 18436.7 | 5165.99 | 0.268197 | 1.09334 | 5.36013 | 0.865527 | 0.00133712 | 1.73249e-05 | 9.8164e-06 | 1(Win) | true |
| simdjson (ondemand) | 3902.23 | 0.131901 | 1360.74ms | 25388 | 2560 | 171463 | 6204.63 | 0.269925 | 1.31217 | 5.86175 | 0.89952 | 0.00199858 | 1.58324e-05 | 7.80081e-06 | 2(Loss) | true |
