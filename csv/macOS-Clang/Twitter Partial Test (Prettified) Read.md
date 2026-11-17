
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4996.73 | 0.418806 | 6592.91ms | 631514 | 30 | 7.64437e+06 | 120531 | 2.19986 | 1(Win) | true |
| Jsonifier (two-stage) | 4849.96 | 0.195009 | 6471.26ms | 631514 | 1280 | 7.50599e+07 | 124178 | 2.50171 | 2(Loss) | true |
| simdjson (ondemand) | 4226.46 | 1.261 | 7209.66ms | 631514 | 30 | 9.68647e+07 | 142497 | 1.44961 | 3(Loss) | true |
| Glaze | 2403.33 | 0.601299 | 6334.94ms | 631514 | 80 | 1.81639e+08 | 250593 | 1.24853 | 4(Loss) | true |
