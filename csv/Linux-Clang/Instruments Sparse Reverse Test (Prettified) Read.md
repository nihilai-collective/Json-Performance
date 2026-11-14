
----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5012.14 | 0.0213931 | 4214.51ms | 183677 | 2560 | 143103 | 34948.7 | 0.0445678 | 1.02481 | 5.5993 | 0.900124 | 0.000901304 | 2.58606e-06 | 6.76289e-07 | 1(Win) | true |
| simdjson (ondemand) | 4046.58 | 0.0416988 | 5048.84ms | 183677 | 1280 | 417054 | 43287.9 | 0.0306736 | 1.26686 | 6.5987 | 0.960719 | 0.00183773 | 2.48823e-06 | 3.78552e-07 | 2(Loss) | true |
