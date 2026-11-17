
----
### Github Events Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6016.28 | 0.0186478 | 1760.37ms | 65103 | 4890 | 18109.7 | 10319.8 | 0.0440432 | 0.856907 | 3.96635 | 0.608544 | 0.0015572 | 3.55265e-06 | 1.02402e-06 | 1(Win) | true |
| simdjson (ondemand) | 4805.66 | 0.0671316 | 2046.67ms | 65103 | 320 | 24071.3 | 12919.6 | 0.314902 | 1.06209 | 5.07588 | 0.78809 | 0.00171747 | 8.97616e-06 | 5.4721e-06 | 2(Loss) | true |
