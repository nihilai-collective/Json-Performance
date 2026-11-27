
----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13113.1 | 0.377509 | 3423.26ms | 475954 | 1280 | 2.18565e+07 | 34614.5 | 0.238147 | 0.188626 | 1(Win) | true |
| simdjson (reflection) | 10337.5 | 0.719869 | 4424.59ms | 475954 | 80 | 7.99277e+06 | 43908.7 | 0.461634 | 0.239334 | 2(Loss) | true |
| Glaze | 5640.96 | 0.222358 | 8260.05ms | 475954 | 320 | 1.02442e+07 | 80465.9 | 0.0545054 | 0.438701 | 3(Loss) | true |
