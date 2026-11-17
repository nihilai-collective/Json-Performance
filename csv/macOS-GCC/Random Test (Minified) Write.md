
----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10815.6 | 0.191655 | 3972.55ms | 461466 | 4890 | 2.97392e+07 | 40690.2 | 0.296603 | 1(Win) | true |
| simdjson (reflection) | 7340.37 | 0.224529 | 6047.7ms | 461466 | 2560 | 4.63906e+07 | 59954.5 | 0.543852 | 2(Loss) | true |
| Glaze | 1973.62 | 0.423351 | 5592.14ms | 461466 | 640 | 5.70338e+08 | 222985 | 0.900291 | 3(Loss) | true |
