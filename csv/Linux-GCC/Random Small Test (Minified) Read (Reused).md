
----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2783.08 | 0.0901359 | 948.159ms | 5094 | 320 | 792.16 | 1745.56 | 0.0849304 | 1.89541 | 8.78426 | 1.44327 | 0.00133122 | 3.92619e-05 | 1.28828e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1794.02 | 0.0718792 | 1046.75ms | 5094 | 1280 | 4849.31 | 2707.89 | 0.0460536 | 2.91411 | 13.8153 | 2.07852 | 0.00216922 | 3.3894e-05 | 4.29427e-06 | 2(Loss) | true |
| Glaze | 1593.06 | 0.133017 | 1082.27ms | 5094 | 320 | 5265.27 | 3049.49 | 0.103095 | 3.27513 | 14.2952 | 2.62898 | 0.00484639 | 3.98753e-05 | 1.16559e-05 | 3(Loss) | true |
| simdjson (reflection) | 1470.19 | 0.119725 | 1122.87ms | 5094 | 80 | 1252.07 | 3304.34 | 0.212525 | 3.54902 | 14.9056 | 2.33608 | 0.00172752 | 4.41696e-05 | 2.45387e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1318.44 | 0.0616721 | 1152.81ms | 5094 | 1280 | 6609.72 | 3684.66 | 0.29088 | 3.94364 | 14.6853 | 2.31508 | 0.003715 | 6.71746e-05 | 2.62257e-05 | 5(Loss) | true |
