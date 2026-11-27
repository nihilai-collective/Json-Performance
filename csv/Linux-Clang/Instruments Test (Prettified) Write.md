
----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21537.5 | 0.1144 | 954.266ms | 213963 | 2560 | 300730 | 9474.23 | 0.0200956 | 0.114644 | 1(Win) | true |
| Glaze | 4118.74 | 0.125347 | 4982.53ms | 213963 | 1280 | 4.93613e+06 | 49542.2 | 0.0413649 | 0.600791 | 2(Loss) | true |
