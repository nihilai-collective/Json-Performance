
----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2634.87 | 0.193558 | 7584.68ms | 676745 | 640 | 1.43859e+08 | 244944 | 0.0806198 | 1.92938 | 9.28253 | 1.67059 | 0.00447974 | 0.0189032 | 8.23104e-05 | 1(Win) | true |
| simdjson (ondemand) | 1880.95 | 0.0812406 | 10056.2ms | 676745 | 1280 | 9.94604e+07 | 343121 | 0.185867 | 2.69767 | 10.9022 | 1.91788 | 0.00864343 | 0.0225988 | 6.13749e-05 | 2(Loss) | true |
