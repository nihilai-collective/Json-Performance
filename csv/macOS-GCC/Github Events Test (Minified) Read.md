
----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8941.68 | 0.304157 | 594.546ms | 53331 | 4890 | 1.46361e+06 | 5688.02 | 1.5812 | 1(Win) | true |
| simdjson (stage-1) | 6146.12 | 2.01033 | 790.238ms | 53331 | 40 | 1.10701e+06 | 8275.2 | 0.742068 | 2(Loss) | true |
