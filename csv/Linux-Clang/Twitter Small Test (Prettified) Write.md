
----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9645.25 | 0.295725 | 778.859ms | 4300 | 80 | 126.467 | 425.163 | 0.0851889 | 0.567238 | 1.38419 | 0.23907 | 0.000235465 | 2.03488e-05 | 8.72093e-06 | 1(Win) | true |
| Glaze | 3131.08 | 0.262067 | 870.566ms | 4300 | 2560 | 30158.6 | 1309.71 | 1.26406 | 1.66447 | 3.75256 | 0.630465 | 0.000240643 | 6.37718e-05 | 2.36192e-05 | 2(Loss) | true |
