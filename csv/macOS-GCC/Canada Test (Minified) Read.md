
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 459.034 | 0.587944 | 6228ms | 2090234 | 80 | 5.21509e+10 | 4.3426e+06 | 5.8824 | -(Win) | false |
| simdjson (ondemand) | 440.775 | 0.952716 | 6683.21ms | 2090234 | 30 | 5.56936e+10 | 4.5225e+06 | 1.72689 | 2(Loss) | true |
