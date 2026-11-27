
----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12245.6 | 0.0850266 | 3632.96ms | 461466 | 2560 | 2.39038e+06 | 35938.4 | 0.118677 | 1(Win) | true |
| simdjson (reflection) | 8987.26 | 0.109219 | 5030.47ms | 461466 | 640 | 1.83064e+06 | 48968 | 0.434309 | 2(Loss) | true |
| Glaze | 2390.65 | 0.0937154 | 9845.51ms | 461466 | 640 | 1.9048e+07 | 184087 | 0.0269365 | 3(Loss) | true |
