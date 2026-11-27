
----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 625.922 | 0.0377724 | 1442.79ms | 4669 | 1280 | 9242.02 | 7113.83 | 0.078943 | 8.27209 | 36.471 | 7.24138 | 0.00824086 | 6.87714e-05 | 2.07486e-05 | 1(Win) | true |
| simdjson (ondemand) | 235.509 | 0.0735066 | 2626.91ms | 4669 | 1280 | 247227 | 18906.7 | 0.173866 | 21.8 | 103.734 | 18.71 | 0.0521167 | 8.81814e-05 | 4.51783e-05 | 2(Loss) | true |
