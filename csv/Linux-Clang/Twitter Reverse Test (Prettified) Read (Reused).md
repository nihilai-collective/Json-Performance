
----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 945.129 | 0.0847914 | 9780.47ms | 360584 | 320 | 3.04568e+07 | 363844 | 0.0901067 | 5.36721 | 19.8862 | 3.65239 | 0.0190122 | 0.000545946 | 4.81944e-05 | 1(Win) | true |
| simdjson (ondemand) | 407.621 | 0.190863 | 5499.87ms | 360584 | 40 | 1.03706e+08 | 843627 | 0.0657895 | 12.3478 | 51.8262 | 8.95449 | 0.0488811 | 0.00158756 | 0.00028544 | 2(Loss) | true |
