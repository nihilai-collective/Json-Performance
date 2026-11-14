
----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16044.2 | 0.0397728 | 1311.04ms | 94370 | 4890 | 24339.4 | 5609.38 | 0.0319045 | 0.317365 | 1.28166 | 0.241708 | 0.000239541 | 7.94419e-06 | 4.08261e-06 | 1(Win) | true |
| Glaze | 4339.3 | 0.0711008 | 2832.37ms | 94370 | 2560 | 556696 | 20740.3 | 0.00961009 | 1.16636 | 4.17651 | 0.677854 | 0.0015444 | 1.08656e-05 | 4.67326e-06 | 2(Loss) | true |
