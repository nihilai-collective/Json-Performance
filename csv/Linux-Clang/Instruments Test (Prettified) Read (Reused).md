
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2585.07 | 0.0345502 | 7691.49ms | 183677 | 1280 | 701577 | 67761.4 | 0.152275 | 1.98671 | 9.16416 | 1.73058 | 0.00205054 | 1.96507e-06 | 1.99909e-07 | 1(Win) | true |
| simdjson (ondemand) | 2473.99 | 0.0264546 | 7987.69ms | 183677 | 2560 | 898169 | 70804 | 0.0580883 | 2.05754 | 9.89507 | 1.40204 | 0.00385528 | 5.89945e-06 | 1.71624e-06 | 2(Loss) | true |
