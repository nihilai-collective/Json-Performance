
----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2403.63 | 0.24265 | 9817.23ms | 7351818 | 40 | 2.0039e+09 | 2.91694e+06 | 0.0765956 | 2.10703 | 8.47845 | 1.67508 | 0.0109162 | 0.0534961 | 0.00501425 | 1(Win) | true |
| simdjson (ondemand) | 2383.51 | 0.124368 | 9930.43ms | 7351818 | 80 | 1.07069e+09 | 2.94157e+06 | 0.147212 | 2.12668 | 8.81426 | 1.39578 | 0.00907 | 0.0536616 | 0.00549119 | 2(Loss) | true |
