
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3904.24 | 0.080796 | 8770.8ms | 699405 | 320 | 6.09697e+06 | 170841 | 0.295271 | 0.778326 | 1(Win) | true |
| Glaze | 2538.24 | 0.097264 | 6677.81ms | 699405 | 640 | 4.18097e+07 | 262783 | 0.0713602 | 1.19733 | 2(Loss) | true |
| simdjson (ondemand) | 1140.27 | 0.308729 | 8171.08ms | 767297 | 160 | 6.28042e+08 | 641737 | 0.179754 | 2.66463 | 3(Loss) | true |
