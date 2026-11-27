
----
### Twitter Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1097.39 | 0.111832 | 1051.49ms | 3770 | 80 | 1073.94 | 3276.26 | 0.0751054 | 4.75587 | 19.4886 | 3.59761 | 0.00213528 | 5.96817e-05 | 3.31565e-05 | 1(Win) | true |
| simdjson (ondemand) | 469.385 | 0.0465563 | 1489.05ms | 3770 | 2560 | 32555.3 | 7659.71 | 0.0114553 | 10.9937 | 49.6525 | 8.49417 | 0.0120805 | 8.12334e-05 | 4.46577e-05 | 2(Loss) | true |
