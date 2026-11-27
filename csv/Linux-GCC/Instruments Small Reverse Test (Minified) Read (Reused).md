
----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 652.121 | 0.0418109 | 1414.72ms | 4669 | 1280 | 10432.3 | 6828.03 | 0.0525226 | 7.92272 | 36.2801 | 7.12551 | 0.00805178 | 3.69793e-05 | 7.52972e-06 | 1(Win) | true |
| simdjson (ondemand) | 243.579 | 0.0438279 | 2569.63ms | 4669 | 640 | 41081.8 | 18280.3 | 0.0749402 | 21.1505 | 93.8362 | 19.0831 | 0.0549499 | 3.88199e-05 | 1.13782e-05 | 2(Loss) | true |
