
----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1300.75 | 0.0298058 | 2153.31ms | 18245 | 4890 | 77734.3 | 13376.8 | 0.0295308 | 3.96448 | 17.5237 | 3.52568 | 0.00477077 | 2.60149e-05 | 9.43755e-06 | 1(Win) | true |
| simdjson (ondemand) | 900.6 | 0.0182659 | 2748.58ms | 18245 | 4890 | 60899.8 | 19320.2 | 0.0809911 | 5.72524 | 27.3584 | 5.31444 | 0.00619424 | 2.9512e-05 | 1.14327e-05 | 2(Loss) | true |
