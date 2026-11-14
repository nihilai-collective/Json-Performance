
----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 834.58 | 0.147005 | 6164.01ms | 53331 | 2560 | 2.0546e+07 | 60941.3 | 0.132598 | 1(Win) | true |
| simdjson (ondemand) | 349.692 | 0.0565121 | 7556.45ms | 53331 | 1280 | 8.64731e+06 | 145444 | 0.15699 | 2(Loss) | true |
