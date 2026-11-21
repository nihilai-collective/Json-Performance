
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1002.43 | 0.586908 | 6793.84ms | 461466 | 640 | 4.249e+09 | 439019 | 0.196419 | 2.46961 | 1(Win) | true |
| Jsonifier (two-stage) | 864.278 | 0.311368 | 7611.83ms | 461466 | 40 | 1.00549e+08 | 509198 | 0.0532166 | 2.86444 | 2(Loss) | true |
| Glaze | 794.802 | 0.127644 | 8305.51ms | 461466 | 320 | 1.59851e+08 | 553708 | 0.857269 | 3.11483 | 3(Loss) | true |
| simdjson (ondemand) | 667.558 | 0.45734 | 9474.31ms | 461466 | 80 | 7.27226e+08 | 659251 | 0.66805 | 3.70857 | 4(Loss) | true |
