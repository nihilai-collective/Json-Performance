
----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1671.16 | 0.0824917 | 1001.58ms | 4630 | 4890 | 23230.3 | 2642.18 | 0.117938 | 3.05284 | 7.71728 | 0.433262 | 0.000229189 | 6.32048e-05 | 1.93457e-05 | 1(Win) | true |
| Glaze | 1010.93 | 0.0369032 | 1175.38ms | 4630 | 40 | 103.922 | 4367.77 | 0.00209866 | 5.05109 | 9.27775 | 0.568035 | 0.000215983 | 0.000151188 | 1.07991e-05 | 2(Loss) | true |
