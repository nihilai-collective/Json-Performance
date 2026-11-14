
----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16327.2 | 0.172361 | 1215.48ms | 78778 | 4890 | 307589 | 4601.43 | 0.00517878 | 0.314169 | 1.09159 | 0.183579 | 2.63171e-05 | 4.92726e-05 | 3.41593e-05 | 1(Win) | true |
| Glaze | 4645.32 | 0.13889 | 2372.05ms | 78778 | 4890 | 2.46734e+06 | 16172.9 | 0.0621915 | 1.08966 | 3.01834 | 0.488296 | 0.000347984 | 2.87676e-05 | 1.26472e-05 | 2(Loss) | true |
