
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1930.41 | 0.168043 | 8658.09ms | 676745 | 1280 | 4.04019e+08 | 334330 | 0.942689 | 1.28237 | 1(Win) | true |
| simdjson (ondemand) | 1677.64 | 0.0775251 | 9860.25ms | 676745 | 640 | 5.69268e+07 | 384703 | 0.0857641 | 1.47561 | 2(Loss) | true |
