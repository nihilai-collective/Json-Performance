
----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10126.2 | 0.0584754 | 8898.38ms | 7351818 | 640 | 1.04912e+08 | 692387 | 0.157829 | 0.505731 | 2.37653 | 0.241967 | 0.00102663 | 0.042343 | 0.000210638 | 1(Win) | true |
| simdjson (ondemand) | 9680.14 | 0.047922 | 9447.37ms | 7351818 | 640 | 7.71038e+07 | 724291 | 0.291749 | 0.528893 | 2.4948 | 0.256654 | 0.000970091 | 0.0424171 | 7.29314e-05 | 2(Loss) | true |
