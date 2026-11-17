
----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1217.88 | 0.0355935 | 6422.18ms | 65103 | 1280 | 421451 | 50979.8 | 0.098116 | 4.22582 | 15.0573 | 2.96163 | 0.0121972 | 2.37484e-05 | 1.28762e-05 | 1(Win) | true |
| simdjson (ondemand) | 601.931 | 0.0483895 | 5992.68ms | 65103 | 2560 | 6.37752e+06 | 103147 | 0.151444 | 8.53761 | 31.4571 | 5.55668 | 0.0479903 | 4.92069e-05 | 3.35826e-05 | 2(Loss) | true |
