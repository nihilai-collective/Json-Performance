
----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2428.6 | 0.0333668 | 839.575ms | 2821 | 640 | 87.4388 | 1107.76 | 0.014526 | 2.20094 | 8.48933 | 1.44845 | 0.000358915 | 3.32329e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2127.22 | 0.098845 | 854.92ms | 2821 | 1280 | 2000.33 | 1264.71 | 0.281859 | 2.49902 | 9.53563 | 1.42822 | 0.000631148 | 6.86813e-05 | 3.2679e-05 | 2(Loss) | true |
