
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1185.37 | 0.0739356 | 4604.97ms | 56369 | 4890 | 5.4978e+06 | 45350.9 | 0.000109575 | 1(Win) | true |
| simdjson (ondemand) | 919.727 | 0.18299 | 5948.43ms | 56369 | 160 | 1.83037e+06 | 58449.6 | 0.101181 | 2(Loss) | true |
