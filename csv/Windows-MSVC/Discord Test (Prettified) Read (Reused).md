
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1941.49 | 0.038968 | 4609.1ms | 83958 | 2560 | 661164 | 41240.7 | 0.0322146 | 1.56451 | 1(Win) | true |
| Glaze | 1886.04 | 0.0469063 | 4704.75ms | 83958 | 2560 | 1.01514e+06 | 42453.2 | 0.00910846 | 1.61051 | 2(Loss) | true |
| Jsonifier | 1776.3 | 0.027243 | 4987.86ms | 83958 | 4890 | 737414 | 45076 | 0.040028 | 1.71013 | 3(Loss) | true |
| simdjson (ondemand) | 1306.17 | 0.0334154 | 6559.06ms | 83958 | 4890 | 2.05177e+06 | 61300.4 | 0.081663 | 2.32608 | 4(Loss) | true |
