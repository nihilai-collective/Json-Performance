
----
### Marine IK Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10367.3 | 0.200584 | 8667.38ms | 7351818 | 160 | 2.94422e+08 | 676284 | 0.283373 | 0.489518 | 2.37653 | 0.241967 | 0.00110275 | 0.0423859 | 1.36148e-05 | 1(Win) | true |
| simdjson (ondemand) | 9522.8 | 0.137365 | 9455.15ms | 7351818 | 40 | 4.09142e+07 | 736258 | 0.270602 | 0.535494 | 2.4948 | 0.256653 | 0.000955274 | 0.042426 | 0.000309641 | 2(Loss) | true |
