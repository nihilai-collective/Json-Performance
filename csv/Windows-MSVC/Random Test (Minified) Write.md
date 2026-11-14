
----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3816.16 | 0.295939 | 5895.4ms | 461466 | 320 | 3.72717e+07 | 115322 | 0.0620159 | 0.795653 | 1(Win) | true |
| Glaze | 2995.93 | 0.0886806 | 7515.64ms | 461466 | 2560 | 4.34423e+07 | 146895 | 0.106414 | 1.01429 | 2(Loss) | true |
