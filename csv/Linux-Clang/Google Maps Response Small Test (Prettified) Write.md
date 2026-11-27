
----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17036.4 | 0.162145 | 791.38ms | 11521 | 2560 | 2799.45 | 644.932 | 0.130088 | 0.315139 | 1.50569 | 0.253711 | 0.000127654 | 9.49353e-06 | 1.59356e-06 | 1(Win) | true |
| Glaze | 4839.38 | 0.0907436 | 955.469ms | 11521 | 2560 | 10866.1 | 2270.39 | 0.0949855 | 1.08033 | 3.86954 | 0.687961 | 0.00116262 | 2.28523e-05 | 6.61157e-06 | 2(Loss) | true |
