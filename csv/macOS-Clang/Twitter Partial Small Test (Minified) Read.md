
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 3741.06 | 0.0928136 | 77.3235ms | 2889 | 1280 | 598.052 | 736.466 | 0.0687991 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 3740.45 | 0.15815 | 77.462ms | 2889 | 320 | 434.249 | 736.587 | 0.02036 | 1(Tie) | true |
| simdjson (ondemand) | 3510.26 | 0.235002 | 83.9527ms | 2889 | 2560 | 8709.62 | 784.889 | 0.419817 | 3(Loss) | true |
| Glaze | 2226.58 | 0.141599 | 127.83ms | 2889 | 1280 | 3929.58 | 1237.4 | 0.592491 | 4(Loss) | true |
