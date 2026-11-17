
----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15683.4 | 0.142682 | 797.16ms | 11812 | 160 | 168.044 | 718.263 | 0.152913 | 0.3407 | 1.63021 | 0.257365 | 8.46597e-05 | 6.34948e-06 | 0 | 1(Win) | true |
| simdjson (reflection) | 10305.7 | 0.129589 | 838.023ms | 11812 | 80 | 160.515 | 1093.06 | 0.0377523 | 0.518808 | 2.37242 | 0.355401 | 0.000104766 | 1.2699e-05 | 1.05825e-06 | 2(Loss) | true |
| Glaze | 3654.8 | 0.147938 | 1056.9ms | 11812 | 4890 | 101669 | 3082.19 | 0.228613 | 1.39977 | 4.61895 | 0.71512 | 0.000126799 | 7.07229e-05 | 4.3005e-05 | 3(Loss) | true |
