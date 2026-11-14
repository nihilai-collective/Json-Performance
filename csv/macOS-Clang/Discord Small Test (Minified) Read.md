
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1128.39 | 0.122371 | 449.222ms | 4857 | 160 | 4037.34 | 4104.96 | 0.935451 | 1(Win) | true |
| simdjson (ondemand) | 1037.65 | 0.193603 | 476.214ms | 4857 | 30 | 2240.69 | 4463.93 | 0.370492 | 2(Loss) | true |
