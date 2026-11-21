
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1725.49 | 0.200491 | 125.744ms | 2158 | 80 | 457.468 | 1192.72 | 0.002096 | 1(Win) | true |
| Glaze | 1543.78 | 0.169628 | 164.719ms | 2158 | 160 | 818.171 | 1333.11 | 0.303312 | 2(Loss) | true |
| Jsonifier (two-stage) | 1460.96 | 0.838177 | 146.525ms | 2158 | 320 | 44611.7 | 1408.68 | 0.543857 | 3(Loss) | true |
| simdjson (ondemand) | 970.357 | 1.23952 | 186.296ms | 2158 | 40 | 27644.6 | 2120.9 | 0.135346 | 4(Loss) | true |
