
----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1484.98 | 0.253717 | 6564.76ms | 409725 | 640 | 2.85249e+08 | 263131 | 0.229919 | 1(Win) | true |
| simdjson (ondemand) | 1105.81 | 0.455145 | 9521.56ms | 409725 | 40 | 1.03464e+08 | 353357 | 0.554755 | 2(Loss) | true |
