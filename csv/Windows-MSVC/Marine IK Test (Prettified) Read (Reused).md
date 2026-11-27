
----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2418.24 | 0.294747 | 10249.8ms | 7351818 | 80 | 5.84223e+09 | 2.89932e+06 | 0.0445562 | 1.02379 | 1(Win) | true |
| Jsonifier | 2368.06 | 0.348823 | 5020.38ms | 7351818 | 30 | 3.19989e+09 | 2.96075e+06 | 0.710006 | 1.04548 | 2(Loss) | true |
| simdjson (ondemand) | 886.694 | 0.272921 | 5872.12ms | 7351818 | 30 | 1.39713e+10 | 7.90717e+06 | 1.09489 | 2.79215 | 3(Loss) | true |
| Glaze | 701.841 | 1.50326 | 7014.99ms | 7351818 | 30 | 6.76557e+11 | 9.98979e+06 | 1.56705 | 3.52756 | 4(Loss) | true |
