
----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 864.076 | 0.0625059 | 302.208ms | 2632 | 160 | 527.509 | 2904.92 | 0.132925 | 1(Win) | true |
| simdjson (ondemand) | 454.057 | 0.10923 | 574.22ms | 2632 | 40 | 1458.45 | 5528.1 | 0.368864 | 2(Loss) | true |
