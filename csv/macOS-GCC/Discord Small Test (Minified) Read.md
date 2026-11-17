
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1620.94 | 1.01997 | 339.582ms | 4857 | 160 | 135925 | 2857.6 | 0.334821 | 1(Win) | true |
| Glaze | 1109.19 | 0.728633 | 410.652ms | 4857 | 640 | 592542 | 4176 | 1.30021 | 2(Loss) | true |
| Jsonifier (two-stage) | 994.832 | 0.765807 | 432.898ms | 4857 | 4890 | 6.21705e+06 | 4656.06 | 1.59191 | 3(Loss) | true |
| simdjson (reflection) | 969.402 | 0.716253 | 503.449ms | 4857 | 1280 | 1.49924e+06 | 4778.2 | 0.924774 | 4(Loss) | true |
| simdjson (ondemand) | 798.097 | 0.754166 | 572.209ms | 4857 | 1280 | 2.45227e+06 | 5803.8 | 0.259121 | 5(Loss) | true |
