
----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7182.18 | 0.100111 | 773.373ms | 4630 | 160 | 60.6086 | 614.788 | 0.134013 | 0.762589 | 3.56566 | 0.463715 | 0.000431965 | 2.29482e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6504.02 | 0.0244529 | 777.014ms | 4630 | 2560 | 70.5506 | 678.89 | 0.0546917 | 0.838457 | 4.1149 | 0.492441 | 0.000431965 | 1.73799e-05 | 1.8561e-06 | 2(Loss) | true |
