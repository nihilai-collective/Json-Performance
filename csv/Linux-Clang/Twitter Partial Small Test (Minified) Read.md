
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6371.53 | 0.346622 | 45.6612ms | 2889 | 1280 | 2875.61 | 432.418 | 0.0803336 | 0.363966 | 1(Win) | true |
| Jsonifier | 6157.83 | 0.182644 | 48.2964ms | 2889 | 40 | 26.7122 | 447.425 | 0.0950783 | 0.377735 | 2(Loss) | true |
| Jsonifier (two-stage) | 5985.12 | 0.339339 | 48.2904ms | 2889 | 1280 | 3123.4 | 460.336 | 0.232981 | 0.389107 | 3(Loss) | true |
| Glaze | 3077.47 | 0.248724 | 92.7631ms | 2889 | 4890 | 24246.6 | 895.269 | 0.08131 | 0.780553 | 4(Loss) | true |
