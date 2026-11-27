
----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 922.171 | 0.0272714 | 1553ms | 7932 | 4890 | 24471.7 | 8202.97 | 0.0835313 | 5.59537 | 23.7068 | 4.54841 | 0.00629306 | 7.09507e-05 | 4.12246e-05 | 1(Win) | true |
| simdjson (ondemand) | 398.371 | 0.220292 | 2632.19ms | 7932 | 80 | 139984 | 18988.7 | 0.0918782 | 12.9524 | 60.7317 | 10.8781 | 0.0306181 | 8.82501e-05 | 3.78215e-05 | 2(Loss) | true |
