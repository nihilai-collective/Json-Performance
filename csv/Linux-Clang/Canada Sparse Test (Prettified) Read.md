
----
### Canada Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10606.5 | 0.262904 | 6057.52ms | 5212421 | 640 | 9.71653e+08 | 468672 | 0.134024 | 0.478087 | 1.94446 | 0.198823 | 0.00213746 | 0.0394054 | 6.51748e-06 | 1(Win) | true |
| simdjson (ondemand) | 9938.37 | 0.371136 | 6476.65ms | 5212421 | 40 | 1.3784e+08 | 500178 | 0.233858 | 0.507557 | 2.19705 | 0.202784 | 0.00190664 | 0.0394776 | 8.31188e-06 | 2(Loss) | true |
