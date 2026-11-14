
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1516.18 | 0.882829 | 185.752ms | 2821 | 1280 | 314099 | 1774.4 | 1.02633 | 1(Win) | true |
| simdjson (ondemand) | 1182.61 | 0.887492 | 235.275ms | 2821 | 2560 | 1.0435e+06 | 2274.9 | 0.321926 | 2(Loss) | true |
