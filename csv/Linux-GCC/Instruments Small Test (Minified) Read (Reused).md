
----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1726.38 | 0.0562873 | 983.578ms | 4669 | 4890 | 10306.3 | 2579.21 | 0.165813 | 3.01444 | 12.1305 | 2.43436 | 0.00173147 | 0.000168321 | 0.000108359 | 1(Win) | true |
| simdjson (ondemand) | 1619.59 | 0.055092 | 1001.97ms | 4669 | 2560 | 5872.95 | 2749.29 | 0.134881 | 3.22687 | 14.2652 | 2.25316 | 0.00141224 | 9.31175e-05 | 6.12417e-05 | 2(Loss) | true |
