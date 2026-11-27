
----
### Discord Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5166.95 | 0.0668535 | 842.993ms | 6701 | 4890 | 3343.24 | 1236.82 | 0.0279921 | 1.02972 | 4.40695 | 0.658111 | 0.00020395 | 2.80152e-05 | 1.05896e-05 | 1(Win) | true |
| simdjson (ondemand) | 4759.33 | 0.0815094 | 857.797ms | 6701 | 1280 | 1533.25 | 1342.75 | 0.202763 | 1.11516 | 4.73123 | 0.617072 | 0.000250312 | 1.469e-05 | 2.6815e-06 | 2(Loss) | true |
