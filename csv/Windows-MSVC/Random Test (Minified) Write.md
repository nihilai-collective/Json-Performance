
----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3776.26 | 0.102485 | 5945.35ms | 461466 | 2560 | 3.65188e+07 | 116541 | 0.116108 | 0.80402 | 1(Win) | true |
| Glaze | 3018.44 | 0.134624 | 7524.22ms | 461466 | 640 | 2.4657e+07 | 145800 | 0.394209 | 1.00671 | 2(Loss) | true |
