
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 711.635 | 0.317356 | 8770.88ms | 1834197 | 40 | 2.43406e+09 | 2.45804e+06 | 0.155242 | 3.47893 | 1(Win) | true |
| Jsonifier (two-stage) | 671.473 | 0.384091 | 9275.86ms | 1834197 | 80 | 8.00926e+09 | 2.60506e+06 | 0.787079 | 3.68704 | 2(Loss) | true |
| Glaze | 200.776 | 0.437475 | 6344.04ms | 1834197 | 40 | 5.81076e+10 | 8.71231e+06 | 0.260203 | 12.3311 | 3(Loss) | true |
| simdjson (ondemand) | 132.606 | 0.459437 | 9573.77ms | 1834197 | 40 | 1.46918e+11 | 1.31911e+07 | 0.793982 | 18.6703 | 4(Loss) | true |
