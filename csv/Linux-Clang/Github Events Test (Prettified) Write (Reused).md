
----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15461.5 | 0.18861 | 1231.95ms | 78778 | 4890 | 410720 | 4859.09 | 0.172856 | 0.330397 | 1.12873 | 0.178527 | 2.64054e-05 | 6.99592e-06 | 2.83731e-06 | 1(Win) | true |
| Glaze | 4979.21 | 0.118053 | 2260.64ms | 78778 | 4890 | 1.5515e+06 | 15088.4 | 0.0430852 | 1.01539 | 2.95713 | 0.474155 | 0.000343151 | 2.13668e-05 | 1.1518e-05 | 2(Loss) | true |
