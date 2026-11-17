
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2075.39 | 0.319793 | 240.817ms | 4857 | 30 | 1528.26 | 2231.87 | 0.876849 | 1(Win) | true |
| Glaze | 1291.52 | 0.312413 | 390.698ms | 4857 | 40 | 5021.74 | 3586.47 | 0.304615 | 2(Loss) | true |
| Jsonifier (two-stage) | 1158.74 | 0.204014 | 402.013ms | 4857 | 2560 | 170264 | 3997.43 | 0.0060289 | 3(Loss) | true |
| simdjson (ondemand) | 620.139 | 0.106356 | 783.537ms | 4857 | 80 | 5048.66 | 7469.29 | 0.0349643 | 4(Loss) | true |
