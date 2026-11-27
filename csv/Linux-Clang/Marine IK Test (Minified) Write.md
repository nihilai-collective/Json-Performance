
----
### Marine IK Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1430.44 | 0.0469027 | 8468.85ms | 1922245 | 30 | 1.08392e+07 | 1.28156e+06 | 0.055069 | 1.73076 | 1(Win) | true |
| Glaze | 627.727 | 0.36907 | 8489.16ms | 1833577 | 40 | 4.22799e+09 | 2.78566e+06 | 1.09272 | 3.94386 | 2(Loss) | true |
