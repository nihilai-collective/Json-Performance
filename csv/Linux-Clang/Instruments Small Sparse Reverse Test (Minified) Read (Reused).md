
----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3504.27 | 0.118303 | 842.709ms | 4669 | 40 | 90.3872 | 1270.65 | 0.106358 | 1.51726 | 7.16963 | 1.25958 | 0.00158492 | 2.14179e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2624.97 | 0.139751 | 891.555ms | 4669 | 1280 | 7193.15 | 1696.29 | 0.114963 | 1.99633 | 9.50696 | 1.4637 | 0.00285209 | 2.62703e-05 | 1.25495e-05 | 2(Loss) | true |
