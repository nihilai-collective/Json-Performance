
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 22546.9 | 0.117358 | 1965.28ms | 461466 | 2560 | 1.3433e+06 | 19518.8 | 0.0380888 | 0.109653 | 1(Win) | true |
| simdjson (stage-1) | 16370.6 | 0.0674334 | 2700.63ms | 461466 | 2560 | 841277 | 26882.8 | 0.0514738 | 0.151083 | 2(Loss) | true |
