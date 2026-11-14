
----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2518.15 | 0.0638627 | 3903.85ms | 83958 | 1280 | 527797 | 31796.6 | 0.0306076 | 2.02747 | 9.37298 | 1.71673 | 0.00355944 | 1.04405e-05 | 3.98265e-06 | 1(Win) | true |
| simdjson (ondemand) | 1935.15 | 0.08817 | 4849.37ms | 83958 | 160 | 212940 | 41375.9 | 0.0151984 | 2.65205 | 11.5053 | 1.99393 | 0.00747338 | 8.78415e-06 | 5.06205e-06 | 2(Loss) | true |
