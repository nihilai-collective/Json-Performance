
----
### Random Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14082.1 | 0.454291 | 3135.55ms | 461466 | 160 | 3.22502e+06 | 31251.6 | 0.0580434 | 0.175417 | 1(Win) | true |
| simdjson (reflection) | 10724.8 | 0.253875 | 4249.02ms | 461466 | 640 | 6.94581e+06 | 41034.7 | 0.610031 | 0.230676 | 2(Loss) | true |
| Glaze | 3714.89 | 0.172407 | 6099.25ms | 461466 | 640 | 2.66979e+07 | 118466 | 0.321403 | 0.666281 | 3(Loss) | true |
