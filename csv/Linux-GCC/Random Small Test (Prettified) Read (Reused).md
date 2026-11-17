
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2628.48 | 0.0876684 | 1094.57ms | 8051 | 640 | 4197.16 | 2921.09 | 0.130902 | 1.94619 | 8.74065 | 1.31164 | 0.000541664 | 4.46373e-05 | 6.21041e-06 | 1(Win) | true |
| Jsonifier | 2242.11 | 0.0795345 | 1135.28ms | 8051 | 640 | 4747.63 | 3424.46 | 0.0875738 | 2.28115 | 9.54242 | 1.73829 | 0.00170612 | 3.68743e-05 | 6.98671e-06 | 2(Loss) | true |
| Glaze | 1946.34 | 0.0341039 | 1189.94ms | 8051 | 2560 | 4633.53 | 3944.87 | 0.120505 | 2.62185 | 11.5787 | 2.16818 | 0.00346255 | 3.22165e-05 | 1.00919e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1922.94 | 0.049663 | 1195.95ms | 8051 | 320 | 1258.3 | 3992.86 | 0.232998 | 2.658 | 9.90784 | 1.51509 | 0.00239489 | 2.52298e-05 | 6.21041e-06 | 4(Loss) | true |
| simdjson (reflection) | 1728.66 | 0.0536155 | 1252.7ms | 8051 | 2560 | 14517.8 | 4441.61 | 0.10734 | 2.93531 | 10.116 | 1.55407 | 0.00189054 | 3.63406e-05 | 1.12078e-05 | 5(Loss) | true |
