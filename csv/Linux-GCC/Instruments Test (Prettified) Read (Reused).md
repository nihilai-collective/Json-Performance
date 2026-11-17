
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2655.91 | 0.0241313 | 7477.86ms | 183677 | 2560 | 648463 | 65954 | 0.0349655 | 1.93523 | 8.42284 | 1.60145 | 0.00189279 | 5.38479e-06 | 2.95823e-06 | 1(Win) | true |
| simdjson (ondemand) | 2568.12 | 0.083722 | 7786.04ms | 183677 | 640 | 2.08708e+06 | 68208.7 | 0.192449 | 1.98206 | 9.19238 | 1.40808 | 0.00330858 | 6.07384e-06 | 2.37339e-06 | 2(Loss) | true |
