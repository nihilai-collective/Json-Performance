
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3814.16 | 0.0931058 | 3638.12ms | 108313 | 160 | 101727 | 27082.1 | 0.0691664 | 1.3234 | 6.65907 | 1.33399 | 0.00187027 | 4.44314e-06 | 2.53894e-06 | 1(Win) | true |
| Glaze | 2462.84 | 0.0672263 | 5133.54ms | 108313 | 640 | 508802 | 41941.6 | 0.128091 | 2.05125 | 9.37268 | 1.76545 | 0.00275354 | 2.14223e-05 | 1.52481e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2428.89 | 0.0351222 | 5180.96ms | 108313 | 640 | 142787 | 42527.9 | 0.0346087 | 2.08177 | 9.56858 | 1.66868 | 0.00251615 | 8.07844e-06 | 4.80379e-06 | 3(Loss) | true |
| simdjson (reflection) | 1707.75 | 0.108335 | 6982.85ms | 108313 | 160 | 687018 | 60486.2 | 0.0617322 | 2.95485 | 12.7977 | 1.96928 | 0.00246375 | 1.71378e-05 | 1.00403e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1545.42 | 0.0465133 | 7614.73ms | 108313 | 2560 | 2.47436e+06 | 66839.7 | 0.00117821 | 3.2586 | 14.2468 | 2.49171 | 0.00292837 | 1.30265e-05 | 8.60498e-06 | 5(Loss) | true |
