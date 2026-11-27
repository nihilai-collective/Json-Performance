
----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1633.03 | 0.13925 | 1004.28ms | 4669 | 40 | 576.644 | 2726.65 | 0.0238331 | 3.26109 | 13.7629 | 2.59756 | 0.00192225 | 1.07089e-05 | 5.35447e-06 | 1(Win) | true |
| simdjson (ondemand) | 1576.19 | 0.189505 | 1014.25ms | 4669 | 40 | 1146.38 | 2824.97 | 0.00265496 | 3.31584 | 15.4588 | 2.2341 | 0.00180445 | 2.14179e-05 | 0 | 2(Loss) | true |
