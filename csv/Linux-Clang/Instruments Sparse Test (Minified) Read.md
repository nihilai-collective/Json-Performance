
----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4998.32 | 0.0303992 | 2805.38ms | 108313 | 2560 | 101036 | 20666 | 0.0890614 | 1.02245 | 5.53887 | 0.852871 | 0.0010264 | 8.79973e-06 | 4.68477e-06 | 1(Win) | true |
| simdjson (ondemand) | 4252.77 | 0.0245566 | 3167.67ms | 108313 | 4890 | 173965 | 24289 | 0.000476951 | 1.19846 | 6.10412 | 0.772659 | 0.00126631 | 1.11715e-05 | 7.4181e-06 | 2(Loss) | true |
