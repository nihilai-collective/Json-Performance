
----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4973.66 | 0.103309 | 843.656ms | 6701 | 640 | 1127.68 | 1284.88 | 0.0923845 | 1.06782 | 4.51157 | 0.672885 | 0.000160191 | 1.6089e-05 | 2.33174e-07 | 1(Win) | true |
| simdjson (ondemand) | 4635.8 | 0.0799603 | 853.983ms | 6701 | 320 | 388.802 | 1378.53 | 0.00272022 | 1.14388 | 4.73616 | 0.618117 | 0.000283073 | 1.81876e-05 | 0 | 2(Loss) | true |
