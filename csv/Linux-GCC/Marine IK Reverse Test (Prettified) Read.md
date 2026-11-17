
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1364.32 | 0.152914 | 7775.7ms | 7351818 | 80 | 4.9402e+09 | 5.13902e+06 | 0.0250827 | 3.72075 | 15.8823 | 3.37013 | 0.011082 | 0.186145 | 0.00173529 | 1(Win) | true |
| simdjson (ondemand) | 909.773 | 0.197298 | 5462.15ms | 7351818 | 40 | 9.24759e+09 | 7.70659e+06 | 0.870469 | 5.5862 | 26.4499 | 5.32016 | 0.0122538 | 0.435561 | 0.00517814 | 2(Loss) | true |
