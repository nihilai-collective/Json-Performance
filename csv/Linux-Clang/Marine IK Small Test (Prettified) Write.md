
----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5248.43 | 0.102589 | 1191.81ms | 24579 | 4890 | 102655 | 4466.16 | 0.130071 | 0.972136 | 2.97128 | 0.388625 | 0.00012639 | 1.91195e-05 | 7.97895e-06 | 1(Win) | true |
| Glaze | 3269.26 | 0.116299 | 1466.41ms | 24579 | 2560 | 177999 | 7169.92 | 0.0487298 | 1.55797 | 3.74138 | 0.481592 | 0.000586104 | 4.60568e-05 | 2.7971e-05 | 2(Loss) | true |
