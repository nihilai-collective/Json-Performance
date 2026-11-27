
----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 959.929 | 0.0578435 | 9717.61ms | 360584 | 640 | 2.74804e+07 | 358234 | 0.133973 | 5.3493 | 20.1395 | 3.68097 | 0.0204986 | 0.000913288 | 0.000100969 | 1(Win) | true |
| simdjson (ondemand) | 447.125 | 0.174867 | 10041.1ms | 360584 | 80 | 1.44698e+08 | 769091 | 0.274734 | 11.2557 | 45.8448 | 9.22381 | 0.0519967 | 0.000369331 | 7.48439e-05 | 2(Loss) | true |
