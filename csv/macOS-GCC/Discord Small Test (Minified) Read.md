
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1060.42 | 0.188942 | 436.625ms | 4857 | 4890 | 333078 | 4368.07 | 1.09874 | 1(Win) | true |
| simdjson (ondemand) | 885.32 | 0.666035 | 543.322ms | 4857 | 160 | 194290 | 5232 | 0.304878 | 2(Loss) | true |
