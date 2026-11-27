
----
### Random Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1509.63 | 0.0851181 | 6087.23ms | 676745 | 320 | 4.23745e+07 | 427519 | 0.0847098 | 3.3654 | 16.1205 | 3.14294 | 0.0075642 | 0.0192578 | 4.9497e-05 | 1(Win) | true |
| simdjson (ondemand) | 801.301 | 0.0744283 | 5409.29ms | 676745 | 320 | 1.14997e+08 | 805433 | 0.0694814 | 6.34109 | 26.948 | 5.27578 | 0.0199123 | 0.0228077 | 6.28006e-05 | 2(Loss) | true |
