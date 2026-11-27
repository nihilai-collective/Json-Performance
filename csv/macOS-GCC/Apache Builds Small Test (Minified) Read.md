
----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1591.52 | 0.471772 | 161.71ms | 2632 | 4890 | 270719 | 1577.15 | 0.0792913 | 1(Win) | true |
| Jsonifier (two-stage) | 1429.18 | 0.379045 | 177.743ms | 2632 | 4890 | 216714 | 1756.3 | 0.34831 | 2(Loss) | true |
| Glaze | 1268.39 | 0.214795 | 201.735ms | 2632 | 4890 | 88353.9 | 1978.95 | 0.438921 | 3(Loss) | true |
| simdjson (reflection) | 1001.51 | 0.424586 | 266.784ms | 2632 | 4890 | 553735 | 2506.29 | 0.355855 | 4(Loss) | true |
| simdjson (ondemand) | 893.303 | 0.253084 | 283.954ms | 2632 | 4890 | 247294 | 2809.87 | 0.241691 | 5(Loss) | true |
