
----
### Instruments Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 600.602 | 0.124841 | 1466.81ms | 4669 | 30 | 2569.86 | 7413.73 | 0.0368549 | 8.62554 | 37.2804 | 7.4245 | 0.00847433 | 7.85322e-05 | 1.42786e-05 | 1(Win) | true |
| simdjson (ondemand) | 231.925 | 0.138802 | 2631.97ms | 4669 | 320 | 227244 | 19198.9 | 0.000765011 | 22.0991 | 104.543 | 18.8925 | 0.0500522 | 0.000137208 | 7.29546e-05 | 2(Loss) | true |
