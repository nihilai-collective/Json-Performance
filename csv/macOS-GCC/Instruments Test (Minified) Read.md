
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2682.83 | 0.228998 | 3892.55ms | 108313 | 30 | 233218 | 38502.4 | 0.088574 | 1(Win) | true |
| Jsonifier (two-stage) | 1640.12 | 0.0439608 | 6431.3ms | 108313 | 4890 | 3.74843e+06 | 62980.2 | 0.1344 | 2(Loss) | true |
| Glaze | 1613.89 | 0.0427031 | 6432.91ms | 108313 | 4890 | 3.65294e+06 | 64004 | 0.102964 | 3(Loss) | true |
| simdjson (reflection) | 1375.04 | 0.0849106 | 7623.75ms | 108313 | 1280 | 5.20794e+06 | 75121.8 | 0.0183668 | 4(Loss) | true |
| simdjson (ondemand) | 1220.24 | 0.141836 | 8889.88ms | 108313 | 1280 | 1.84524e+07 | 84651.4 | 0.270305 | 5(Loss) | true |
