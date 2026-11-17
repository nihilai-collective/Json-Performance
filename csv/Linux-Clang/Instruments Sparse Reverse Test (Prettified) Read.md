
----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4674.23 | 0.169018 | 4431.03ms | 183677 | 160 | 641910 | 37475.2 | 0.0452003 | 1.09979 | 5.59955 | 0.900184 | 0.000956707 | 2.31384e-06 | 7.48597e-07 | 1(Win) | true |
| simdjson (ondemand) | 3958.4 | 0.119001 | 5127.37ms | 183677 | 640 | 1.77482e+06 | 44252.2 | 0.0750246 | 1.29463 | 6.6009 | 0.961454 | 0.00196982 | 1.36108e-06 | 1.02081e-07 | 2(Loss) | true |
