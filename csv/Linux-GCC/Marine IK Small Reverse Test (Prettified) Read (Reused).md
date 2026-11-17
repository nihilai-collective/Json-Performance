
----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1275.06 | 0.0462985 | 2195.17ms | 18245 | 1280 | 51094.2 | 13646.3 | 0.077485 | 4.03452 | 16.7989 | 3.51483 | 0.00510816 | 2.77473e-05 | 1.42162e-05 | 1(Win) | true |
| simdjson (ondemand) | 978.276 | 0.0480501 | 2633.99ms | 18245 | 640 | 46744.9 | 17786.2 | 0.0905431 | 5.27577 | 26.4497 | 5.34541 | 0.00634497 | 2.25233e-05 | 1.19039e-05 | 2(Loss) | true |
