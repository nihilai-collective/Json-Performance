
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2308.84 | 0.0225726 | 1097.78ms | 8150 | 4890 | 2823.58 | 3366.39 | 0.0628004 | 2.2576 | 9.35387 | 1.68479 | 0.00259764 | 3.82651e-05 | 3.16158e-06 | 1(Win) | true |
| simdjson (ondemand) | 1994.76 | 0.22961 | 1152.38ms | 8150 | 320 | 25613.2 | 3896.43 | 0.00818125 | 2.60342 | 10.7474 | 1.74258 | 0.00285161 | 0.000116564 | 7.05521e-05 | 2(Loss) | true |
