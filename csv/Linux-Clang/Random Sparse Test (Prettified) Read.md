
----
### Random Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3503.88 | 0.0574887 | 9813.29ms | 676745 | 2560 | 2.8705e+07 | 184194 | 0.0144323 | 1.4519 | 6.39998 | 1.10306 | 0.00489538 | 0.000667236 | 3.70876e-05 | 1(Win) | true |
| simdjson (ondemand) | 3090.79 | 0.0616289 | 5517.68ms | 676745 | 320 | 5.29944e+06 | 208812 | 0.00741602 | 1.64732 | 7.0671 | 1.09077 | 0.00492403 | 0.00137292 | 5.21799e-05 | 2(Loss) | true |
