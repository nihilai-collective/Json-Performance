
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2494.29 | 0.0640844 | 6130.32ms | 124597 | 4890 | 4.55757e+06 | 47638.7 | 0.250421 | 0.992003 | 1(Win) | true |
| Jsonifier | 2261.8 | 0.081189 | 6600.65ms | 124597 | 2560 | 4.65735e+06 | 52535.5 | 0.34566 | 1.09405 | 2(Loss) | true |
| Glaze | 2089.97 | 0.163033 | 7015.2ms | 124597 | 1280 | 1.09976e+07 | 56855 | 0.16563 | 1.18404 | 3(Loss) | true |
| simdjson (ondemand) | 1722.18 | 0.198516 | 8362.25ms | 124597 | 80 | 1.50086e+06 | 68996.6 | 0.0467196 | 1.43697 | 4(Loss) | true |
