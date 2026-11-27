
----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16656.5 | 0.12043 | 623.615ms | 108313 | 4890 | 272755 | 6201.49 | 0.020235 | 0.148001 | 1(Win) | true |
| Glaze | 3879.68 | 0.131326 | 2687.93ms | 108313 | 1280 | 1.56488e+06 | 26624.7 | 0.0501577 | 0.637537 | 2(Loss) | true |
