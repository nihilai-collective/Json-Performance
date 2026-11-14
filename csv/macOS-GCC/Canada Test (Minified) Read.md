
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 476.121 | 1.08957 | 6416.01ms | 2090234 | 40 | 8.32391e+10 | 4.18675e+06 | 0.43084 | 1(Win) | true |
| simdjson (ondemand) | 456.434 | 0.76671 | 6660.37ms | 2090234 | 30 | 3.3637e+10 | 4.36734e+06 | 0.0322497 | 2(Loss) | true |
