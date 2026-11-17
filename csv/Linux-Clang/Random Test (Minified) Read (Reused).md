
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1613.64 | 0.162121 | 8765.02ms | 461466 | 160 | 3.12798e+07 | 272730 | 0.052371 | 1.53411 | 1(Win) | true |
| Jsonifier (two-stage) | 1477.77 | 0.600576 | 9635.73ms | 461466 | 40 | 1.27956e+08 | 297806 | 0.4798 | 1.67518 | 2(Loss) | true |
| Glaze | 1310.86 | 0.094573 | 5265.23ms | 461466 | 320 | 3.22591e+07 | 335725 | 0.16526 | 1.88853 | 3(Loss) | true |
| simdjson (ondemand) | 939.163 | 0.148275 | 6724.84ms | 461466 | 160 | 7.72416e+07 | 468596 | 0.0617208 | 2.63599 | 4(Loss) | true |
