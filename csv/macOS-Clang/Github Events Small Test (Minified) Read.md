
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1288.04 | 0.851986 | 119.353ms | 1691 | 40 | 4551.46 | 1252.03 | 0.0592023 | 1(Win) | true |
| Jsonifier (two-stage) | 1146.38 | 0.574259 | 170.664ms | 1691 | 1280 | 83532.1 | 1406.74 | 0.0576242 | 2(Loss) | true |
| Glaze | 1028.58 | 0.282756 | 158.587ms | 1691 | 640 | 12578.1 | 1567.85 | 0.0680135 | 3(Loss) | true |
| simdjson (ondemand) | 804.216 | 0.828747 | 194.074ms | 1691 | 640 | 176753 | 2005.26 | 0.0619068 | 4(Loss) | true |
