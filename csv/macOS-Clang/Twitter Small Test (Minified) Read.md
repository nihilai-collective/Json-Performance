
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2326.27 | 0.118088 | 122.167ms | 2889 | 1280 | 2503.79 | 1184.37 | 0.253876 | 1(Win) | true |
| Glaze | 1909.22 | 0.161118 | 148.198ms | 2889 | 2560 | 13839.3 | 1443.09 | 0.0164551 | 2(Loss) | true |
| Jsonifier (two-stage) | 1845.99 | 0.131552 | 153.268ms | 2889 | 4890 | 18851.2 | 1492.51 | 0.0380679 | 3(Loss) | true |
| simdjson (ondemand) | 847.609 | 0.1005 | 332.187ms | 2889 | 80 | 853.747 | 3250.51 | 0.049583 | 4(Loss) | true |
