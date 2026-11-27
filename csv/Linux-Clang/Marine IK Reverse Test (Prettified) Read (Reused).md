
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2870.42 | 0.205297 | 8448.66ms | 7351818 | 80 | 2.01167e+09 | 2.44259e+06 | 0.185124 | 0.862493 | 1(Win) | true |
| Jsonifier | 2649.55 | 0.225385 | 9088.44ms | 7351818 | 80 | 2.84569e+09 | 2.6462e+06 | 0.324978 | 0.93437 | 2(Loss) | true |
| simdjson (ondemand) | 2345.84 | 0.186586 | 10272.5ms | 7351818 | 40 | 1.24397e+09 | 2.9888e+06 | 1.64501 | 1.05531 | 3(Loss) | true |
| Glaze | 2140.06 | 0.147337 | 5272.31ms | 7351818 | 40 | 9.3201e+08 | 3.27618e+06 | 2.02122 | 1.15678 | 4(Loss) | true |
