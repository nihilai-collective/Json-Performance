
----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 612.304 | 0.181093 | 756.54ms | 4390 | 30 | 4599.57 | 6837.5 | 2.37954 | 1(Win) | true |
| simdjson (ondemand) | 509.82 | 0.58731 | 860.617ms | 4390 | 640 | 1.48871e+06 | 8211.98 | 0.0671206 | 2(Loss) | true |
