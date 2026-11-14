
----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 683.598 | 0.160588 | 424.907ms | 2821 | 40 | 1597.69 | 3935.53 | 0.0913461 | 1(Win) | true |
| simdjson (ondemand) | 212.186 | 0.0546047 | 1258.1ms | 2821 | 80 | 3834.63 | 12679 | 0.0732057 | 2(Loss) | true |
