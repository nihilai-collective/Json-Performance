
----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7328.16 | 0.136232 | 6164.98ms | 7351818 | 320 | 5.43634e+08 | 956753 | 1.0951 | 0.694455 | 2.87135 | 0.436869 | 0.00241249 | 0.0635534 | 1.32684e-05 | 1(Win) | true |
| simdjson (ondemand) | 6256.26 | 0.178055 | 7140.03ms | 7351818 | 160 | 6.37075e+08 | 1.12068e+06 | 0.0456798 | 0.811613 | 4.06923 | 0.606507 | 0.000803906 | 0.0848094 | 3.35419e-05 | 2(Loss) | true |
