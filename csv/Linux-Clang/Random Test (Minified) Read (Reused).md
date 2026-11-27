
----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1383.65 | 0.0601388 | 8527.5ms | 409725 | 640 | 1.84596e+07 | 282401 | 0.154891 | 3.66274 | 15.7026 | 2.90969 | 0.0103996 | 0.00537561 | 5.7245e-05 | 1(Win) | true |
| simdjson (ondemand) | 1107.55 | 0.164729 | 5136.04ms | 409725 | 30 | 1.01326e+07 | 352801 | 0.0540162 | 4.55955 | 18.0424 | 3.082 | 0.0157147 | 0.0183827 | 1.2366e-05 | 2(Loss) | true |
