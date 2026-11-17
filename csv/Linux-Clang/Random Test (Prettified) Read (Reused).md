
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2261.97 | 0.0874896 | 8580.15ms | 676745 | 320 | 1.99407e+07 | 285325 | 0.0757127 | 2.23683 | 10.1066 | 1.8452 | 0.00467944 | 0.0133962 | 4.71882e-05 | 1(Win) | true |
| simdjson (ondemand) | 1730.03 | 0.0398909 | 5413.47ms | 676745 | 640 | 1.41733e+07 | 373054 | 0.0165511 | 2.92823 | 11.5218 | 1.9132 | 0.0116694 | 0.0217179 | 4.85527e-05 | 2(Loss) | true |
