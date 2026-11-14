
----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 920.519 | 0.304387 | 9945.42ms | 676745 | 40 | 1.82178e+08 | 701120 | 0.633938 | 2.68939 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 404.732 | 0.140478 | 5170.68ms | 676745 | 160 | 8.02887e+08 | 1.59462e+06 | 3.06218 | 6.11701 | -(Loss) | false |
