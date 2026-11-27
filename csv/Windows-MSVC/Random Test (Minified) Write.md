
----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3626.94 | 1.42659 | 6239.6ms | 461466 | 80 | 2.3971e+08 | 121339 | 0.265457 | 0.837071 | 1(Win) | true |
| Glaze | 2861.85 | 0.454531 | 7839.73ms | 461466 | 2560 | 1.2507e+09 | 153778 | 0.18175 | 1.06162 | 2(Loss) | true |
