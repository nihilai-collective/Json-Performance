
----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1593.68 | 0.0248161 | 1306.59ms | 9378 | 4890 | 9483.97 | 5611.87 | 0.330273 | 3.23543 | 14.2305 | 2.76104 | 0.00625643 | 4.14101e-05 | 1.32146e-05 | 1(Win) | true |
| simdjson (ondemand) | 1491.85 | 0.0734406 | 1344.43ms | 9378 | 40 | 775.353 | 5994.93 | 0.0221069 | 3.4772 | 15.3575 | 2.71454 | 0.00424131 | 2.66581e-06 | 0 | 2(Loss) | true |
