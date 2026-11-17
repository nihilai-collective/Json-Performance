
----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10241.3 | 0.0416136 | 821.653ms | 11579 | 4890 | 984.498 | 1078.25 | 0.0395354 | 0.521589 | 2.71137 | 0.345367 | 0.000259425 | 8.56568e-06 | 1.30693e-06 | 1(Win) | true |
| simdjson (ondemand) | 8491.68 | 0.0592805 | 845.916ms | 11579 | 2560 | 1521.31 | 1300.4 | 0.0184773 | 0.625172 | 2.962 | 0.362294 | 0.000295221 | 9.58092e-06 | 3.13741e-06 | 2(Loss) | true |
