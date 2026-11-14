
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 522.088 | 0.795606 | 5739.02ms | 2090234 | 30 | 2.76835e+10 | 3.81813e+06 | 1.68865 | 1(Win) | true |
| simdjson (ondemand) | 494.313 | 0.288931 | 6335.08ms | 2090234 | 80 | 1.08609e+10 | 4.03267e+06 | 0.421243 | 2(Loss) | true |
