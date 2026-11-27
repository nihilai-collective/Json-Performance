
----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1316.81 | 0.0226761 | 2151.08ms | 18245 | 4890 | 43902.4 | 13213.6 | 0.160308 | 3.90108 | 16.6266 | 3.51335 | 0.00484178 | 3.04983e-05 | 1.54117e-05 | 1(Win) | true |
| simdjson (ondemand) | 969.765 | 0.0794415 | 2624.23ms | 18245 | 320 | 65012.9 | 17942.3 | 0.0392036 | 5.29167 | 26.4867 | 5.35084 | 0.00602391 | 3.57975e-05 | 1.90121e-05 | 2(Loss) | true |
