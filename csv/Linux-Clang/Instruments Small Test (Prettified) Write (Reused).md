
----
### Instruments Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14981.4 | 0.541936 | 784.941ms | 9249 | 640 | 6515.71 | 588.766 | 0.622196 | 0.363391 | 1.31355 | 0.225322 | 0.000109133 | 7.43324e-06 | 1.52043e-06 | 1(Win) | true |
| Glaze | 2955.69 | 0.269731 | 1034.77ms | 9249 | 1280 | 82936.5 | 2984.26 | 0.0933719 | 1.76434 | 3.62255 | 0.590442 | 0.000353586 | 2.21308e-05 | 7.17983e-06 | 2(Loss) | true |
