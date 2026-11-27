
----
### Canada Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5200.53 | 0.0709153 | 7748.86ms | 6661989 | 320 | 2.40183e+08 | 1.22168e+06 | 0.116033 | 0.983729 | 2.9578 | 0.261231 | 7.53637e-05 | 0.027805 | 0.000140718 | 1(Win) | true |
| Glaze | 3947.57 | 0.188258 | 5027.57ms | 6661897 | 40 | 3.67203e+08 | 1.60942e+06 | 0.0461093 | 1.29056 | 4.22891 | 0.468988 | 8.30282e-05 | 0.02448 | 7.09933e-05 | 2(Loss) | true |
