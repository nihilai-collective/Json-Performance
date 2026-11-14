
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1558.34 | 0.0329243 | 7719.55ms | 409725 | 1280 | 8.72377e+06 | 250744 | 0.0588885 | 3.25898 | 15.6445 | 3.01481 | 0.00653146 | 0.00227621 | 1.02222e-05 | 1(Win) | true |
| simdjson (ondemand) | 1160.74 | 0.0337728 | 9912.11ms | 409725 | 1280 | 1.65446e+07 | 336633 | 0.0711067 | 4.37514 | 18.118 | 3.1048 | 0.0126507 | 0.0104854 | 1.42836e-05 | 2(Loss) | true |
