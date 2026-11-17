
----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14899.9 | 0.15484 | 795.712ms | 9255 | 4890 | 4114 | 592.37 | 0.181876 | 0.362042 | 1.46818 | 0.280065 | 0.000324613 | 1.99085e-05 | 5.56821e-06 | 1(Win) | true |
| Glaze | 3838.95 | 0.160836 | 972.707ms | 9255 | 2560 | 35005.2 | 2299.13 | 0.208187 | 1.34049 | 4.94165 | 0.853269 | 0.000296799 | 6.09468e-05 | 2.66326e-05 | 2(Loss) | true |
