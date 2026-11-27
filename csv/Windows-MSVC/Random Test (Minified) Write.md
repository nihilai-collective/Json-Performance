
----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3144.02 | 0.638337 | 7183.31ms | 461466 | 640 | 5.10961e+08 | 139976 | 0.602709 | 0.786881 | 1(Win) | true |
| Glaze | 2568.36 | 0.492791 | 8977.41ms | 461466 | 30 | 2.13902e+07 | 171350 | 0.496569 | 0.963759 | 2(Loss) | true |
