
----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3836.45 | 0.0614912 | 887.306ms | 6701 | 4890 | 5130.44 | 1665.75 | 0.126315 | 1.37317 | 5.8157 | 0.984331 | 0.000674685 | 2.19727e-05 | 7.53787e-06 | 1(Win) | true |
| simdjson (ondemand) | 2880.36 | 0.0889618 | 941.293ms | 6701 | 1280 | 4986.56 | 2218.67 | 0.0622593 | 1.82073 | 8.0191 | 1.19654 | 0.00145186 | 4.59353e-05 | 2.83307e-05 | 2(Loss) | true |
