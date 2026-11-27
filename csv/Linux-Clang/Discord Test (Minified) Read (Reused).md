
----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3404.95 | 0.122986 | 1968.93ms | 56369 | 2560 | 965186 | 15788.1 | 0.0271813 | 0.725919 | 1(Win) | true |
| Jsonifier (two-stage) | 2547.55 | 0.280446 | 2534.4ms | 56369 | 320 | 1.12069e+06 | 21101.8 | 0.0241924 | 0.97061 | 2(Loss) | true |
| Glaze | 1900.59 | 0.0794901 | 3220.19ms | 56369 | 4890 | 2.47194e+06 | 28284.7 | 0.101594 | 1.30139 | 3(Loss) | true |
| simdjson (ondemand) | 962.92 | 0.317243 | 6012.61ms | 56369 | 80 | 2.50943e+06 | 55827.8 | 0.0469975 | 2.56996 | 4(Loss) | true |
