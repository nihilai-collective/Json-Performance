
----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3793.3 | 0.0252094 | 886.546ms | 6701 | 4890 | 882.024 | 1684.7 | 0.024606 | 1.39176 | 6.08685 | 1.01224 | 0.000405397 | 1.92872e-05 | 1.06812e-06 | 1(Win) | true |
| simdjson (ondemand) | 2849.47 | 0.0773607 | 938.782ms | 6701 | 1280 | 3853.02 | 2242.72 | 0.0136882 | 1.83945 | 8.02015 | 1.19713 | 0.0012687 | 2.89136e-05 | 7.69475e-06 | 2(Loss) | true |
