
----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6484.52 | 0.0706135 | 3427.86ms | 183677 | 160 | 58217 | 27013.3 | 0.0217207 | 0.795165 | 3.87686 | 0.535059 | 0.000573153 | 2.79703e-05 | 2.62009e-05 | 1(Win) | true |
| simdjson (ondemand) | 6251.75 | 0.0545777 | 3534.81ms | 183677 | 640 | 149664 | 28019 | 0.0529828 | 0.822578 | 4.11054 | 0.47638 | 0.0011807 | 2.28832e-06 | 1.05484e-06 | 2(Loss) | true |
