
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15518 | 0.0635401 | 5851.05ms | 7351818 | 640 | 5.27465e+07 | 451813 | 0.164742 | 0.32565 | 1.62913 | 0.0669813 | 0.0011457 | 0.0211473 | 6.34176e-06 | 1(Win) | true |
| simdjson (stage-1) | 13971.2 | 0.0912174 | 6491.67ms | 7351818 | 320 | 6.70542e+07 | 501834 | 0.15245 | 0.365089 | 1.58986 | 0.0660409 | 0.000836977 | 0.0211816 | 0.000157626 | 2(Loss) | true |
