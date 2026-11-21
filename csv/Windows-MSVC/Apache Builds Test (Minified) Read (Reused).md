
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1260.49 | 0.269816 | 9427.04ms | 94653 | 160 | 5.97377e+06 | 71613.8 | 0.577578 | 1.96345 | 1(Win) | true |
| simdjson (ondemand) | 1172.26 | 0.350874 | 5063.46ms | 94653 | 30 | 2.18999e+06 | 77003.3 | 0.190831 | 2.11098 | 2(Loss) | true |
| Jsonifier (two-stage) | 1135.52 | 0.295847 | 5029.61ms | 94653 | 160 | 8.84979e+06 | 79495 | 0.0629366 | 2.17956 | 3(Loss) | true |
| Glaze | 1093.36 | 0.132834 | 5321.92ms | 94653 | 640 | 7.6973e+06 | 82560.2 | 0.189045 | 2.26362 | 4(Loss) | true |
