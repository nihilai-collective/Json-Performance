
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 738.464 | 0.402122 | 7674.45ms | 461466 | 160 | 9.18878e+08 | 595951 | 0.72629 | 3.35235 | 1(Win) | true |
| Jsonifier (two-stage) | 682.959 | 0.238993 | 8353.44ms | 461466 | 40 | 9.4868e+07 | 644385 | 0.25772 | 3.62487 | 2(Loss) | true |
| Glaze | 662.776 | 0.245855 | 8734.46ms | 461466 | 40 | 1.06602e+08 | 664008 | 0.12622 | 3.73532 | 3(Loss) | true |
| simdjson (ondemand) | 521.725 | 0.169197 | 5372.2ms | 461466 | 40 | 8.14783e+07 | 843525 | 0.727506 | 4.74511 | 4(Loss) | true |
