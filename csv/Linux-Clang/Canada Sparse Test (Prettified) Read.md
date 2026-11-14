
----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10851.5 | 0.0349425 | 5933.98ms | 5212421 | 640 | 1.63978e+07 | 458088 | 0.031344 | 0.468048 | 1.95585 | 0.18325 | 0.00198073 | 0.0394006 | 5.33042e-06 | 1(Win) | true |
| simdjson (ondemand) | 9893.29 | 0.0769887 | 6499.05ms | 5212421 | 30 | 4.48924e+06 | 502457 | 0.287343 | 0.520055 | 2.19705 | 0.202784 | 0.00230684 | 0.039483 | 2.34056e-06 | 2(Loss) | true |
