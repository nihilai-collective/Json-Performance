
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5535.51 | 1.20266 | 7316.74ms | 461466 | 640 | 5.85099e+08 | 79502.8 | 0.87754 | 1(Win) | true |
| simdjson (stage-1) | 4754.53 | 0.159434 | 9619.43ms | 461466 | 4890 | 1.06496e+08 | 92561.9 | 0.354861 | 2(Loss) | true |
