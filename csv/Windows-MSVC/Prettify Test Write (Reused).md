
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4680.16 | 0.443598 | 7436.63ms | 699405 | 80 | 3.19746e+07 | 142518 | 1.04758 | 0.528879 | 1(Win) | true |
| Glaze | 3447.9 | 0.219154 | 5020.34ms | 699405 | 160 | 2.87585e+07 | 193452 | 0.0245599 | 0.717959 | 2(Loss) | true |
| simdjson (ondemand) | 1470.55 | 0.390051 | 6130.36ms | 767297 | 80 | 3.01371e+08 | 497605 | 0.176535 | 1.6832 | 3(Loss) | true |
