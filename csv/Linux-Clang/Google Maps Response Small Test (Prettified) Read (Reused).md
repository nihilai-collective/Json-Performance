
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3571.29 | 0.0930285 | 1017.37ms | 9378 | 2560 | 13894.5 | 2504.3 | 0.0499828 | 1.42503 | 6.85434 | 1.06654 | 0.00151539 | 1.81192e-05 | 2.74912e-06 | 1(Win) | true |
| Jsonifier | 2876.13 | 0.113191 | 1073.9ms | 9378 | 2560 | 31715.1 | 3109.59 | 0.194889 | 1.77422 | 7.61058 | 1.58851 | 0.00337738 | 2.77828e-05 | 8.03909e-06 | 2(Loss) | true |
| Glaze | 2588.4 | 0.0729054 | 1102.7ms | 9378 | 2560 | 16244.9 | 3455.25 | 0.0996582 | 1.97564 | 9.00811 | 1.74579 | 0.00300387 | 1.39122e-05 | 2.29093e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2315.26 | 0.0817197 | 1151.05ms | 9378 | 2560 | 25510.2 | 3862.88 | 0.111999 | 2.19016 | 9.51823 | 1.46758 | 0.00143862 | 2.37007e-05 | 5.49824e-06 | 4(Loss) | true |
