
----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11128 | 0.2067 | 799.284ms | 7376 | 4890 | 8348.31 | 632.127 | 0.552802 | 0.48387 | 1.54338 | 0.28064 | 0.00033708 | 2.096e-05 | 6.04403e-06 | 1(Win) | true |
| Glaze | 2850.81 | 0.407262 | 988.151ms | 7376 | 640 | 64629.8 | 2467.47 | 0.0579078 | 1.80084 | 4.56331 | 0.737799 | 0.000659868 | 3.81304e-05 | 1.2922e-05 | 2(Loss) | true |
