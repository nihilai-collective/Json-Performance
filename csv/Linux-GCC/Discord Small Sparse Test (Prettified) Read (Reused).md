
----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5562.22 | 0.110216 | 838.959ms | 6701 | 160 | 256.56 | 1148.92 | 0.0587851 | 0.958253 | 4.08894 | 0.550216 | 0.000465416 | 1.77212e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5234.42 | 0.124411 | 847.003ms | 6701 | 80 | 184.566 | 1220.88 | 0.051219 | 1.01662 | 4.36412 | 0.536636 | 0.000520445 | 1.49231e-05 | 0 | 2(Loss) | true |
