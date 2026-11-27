
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1685.76 | 0.0458954 | 8025.41ms | 264040 | 2560 | 1.20316e+07 | 149373 | 0.156817 | 3.02308 | 10.463 | 1.89313 | 0.0133467 | 8.46685e-05 | 3.58492e-05 | 1(Win) | true |
| simdjson (ondemand) | 1650.71 | 0.0630474 | 8157.54ms | 264040 | 2560 | 2.36795e+07 | 152545 | 0.0339466 | 3.05771 | 11.2479 | 1.83756 | 0.00844572 | 0.000355419 | 5.85553e-05 | 2(Loss) | true |
