
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1417.84 | 0.254809 | 7847.38ms | 7351818 | 30 | 4.76307e+09 | 4.94502e+06 | 0.171222 | 3.55862 | 15.1379 | 3.19719 | 0.010811 | 0.180873 | 0.00144474 | 1(Win) | true |
| simdjson (ondemand) | 937.235 | 0.169979 | 5418.66ms | 7351818 | 30 | 4.85068e+09 | 7.48077e+06 | 0.0215083 | 5.41079 | 25.7051 | 5.14712 | 0.0119587 | 0.430193 | 0.00416217 | 2(Loss) | true |
