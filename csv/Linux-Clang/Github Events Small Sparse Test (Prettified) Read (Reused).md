
----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5596.18 | 0.0989187 | 750.624ms | 2158 | 640 | 84.6948 | 367.756 | 0.0722808 | 1.02125 | 3.71038 | 0.531047 | 0.00046484 | 3.98228e-05 | 5.7924e-06 | 1(Win) | true |
| simdjson (ondemand) | 5347.42 | 0.0653825 | 754.957ms | 2158 | 640 | 40.5245 | 384.864 | 0.0450849 | 1.06397 | 3.97776 | 0.512975 | 0.000480045 | 2.67899e-05 | 0 | 2(Loss) | true |
