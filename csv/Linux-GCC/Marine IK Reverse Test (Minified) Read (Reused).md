
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 943.536 | 0.0633477 | 6479.01ms | 1834197 | 160 | 2.20676e+08 | 1.8539e+06 | 0.790409 | 2.62391 | 1(Win) | true |
| Jsonifier (two-stage) | 823.552 | 0.197436 | 7268.44ms | 1834197 | 160 | 2.81374e+09 | 2.124e+06 | 0.587102 | 3.0062 | 2(Loss) | true |
| simdjson (reflection) | 724.612 | 0.092482 | 7998.91ms | 1834197 | 30 | 1.49526e+08 | 2.41402e+06 | 1.41566 | 3.41667 | 3(Loss) | true |
| Glaze | 696.306 | 0.141212 | 8659.31ms | 1834197 | 30 | 3.77535e+08 | 2.51215e+06 | 0.145836 | 3.55558 | 4(Loss) | true |
| simdjson (ondemand) | 608.81 | 0.192442 | 9722.84ms | 1834197 | 30 | 9.17167e+08 | 2.87319e+06 | 0.825482 | 4.06658 | 5(Loss) | true |
