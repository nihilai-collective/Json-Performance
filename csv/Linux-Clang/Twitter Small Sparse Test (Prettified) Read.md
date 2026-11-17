
----
### Twitter Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6730.66 | 0.327 | 769.115ms | 3770 | 40 | 122.046 | 534.175 | 0.0452616 | 0.819854 | 3.25013 | 0.405305 | 0.000285146 | 3.97878e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6334.02 | 0.0533938 | 783.65ms | 3770 | 4890 | 449.174 | 567.626 | 0.332039 | 0.861193 | 3.32122 | 0.353316 | 0.000824451 | 1.291e-05 | 2.98341e-06 | 2(Loss) | true |
