
----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13260.4 | 0.238037 | 3313.33ms | 461466 | 640 | 3.99427e+06 | 33188.2 | 0.147129 | 0.186487 | 1(Win) | true |
| Glaze | 2971.2 | 0.0466229 | 7571.12ms | 461466 | 2560 | 1.22082e+07 | 148118 | 0.050765 | 0.833037 | 2(Loss) | true |
