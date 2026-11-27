
----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1972.13 | 0.0792827 | 7680.51ms | 124597 | 1280 | 2.92087e+06 | 60252.2 | 0.0533551 | 1(Win) | true |
| Jsonifier (two-stage) | 1774.12 | 0.0179322 | 8362.15ms | 124597 | 40 | 5770.02 | 66977 | 0.0114578 | 2(Loss) | true |
| Glaze | 1725.06 | 0.161692 | 8411.27ms | 124597 | 320 | 3.96948e+06 | 68881.5 | 0.173442 | 3(Loss) | true |
| simdjson (ondemand) | 1343.52 | 0.127603 | 5399.05ms | 124597 | 320 | 4.07565e+06 | 88443 | 0.079416 | 4(Loss) | true |
