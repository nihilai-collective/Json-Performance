
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2157.64 | 0.0828181 | 8444.24ms | 5212421 | 160 | 5.82494e+08 | 2.30388e+06 | 0.211994 | 2.36315 | 10.8792 | 2.0449 | 0.00958115 | 0.0505479 | 0.000307608 | 1(Win) | true |
| simdjson (ondemand) | 2121.19 | 0.671161 | 8476.31ms | 5212421 | 30 | 7.42158e+09 | 2.34348e+06 | 0.123247 | 2.39224 | 10.8695 | 1.78261 | 0.00988305 | 0.0506084 | 0.000231127 | 2(Loss) | true |
