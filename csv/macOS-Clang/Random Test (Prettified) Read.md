
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6847.6 | 0.300017 | 5373.68ms | 728486 | 40 | 3.70612e+06 | 101457 | 0.391101 | 1(Win) | true |
| simdjson (stage-1) | 5680.9 | 0.361038 | 5962.34ms | 728486 | 40 | 7.79784e+06 | 122294 | 1.30421 | 2(Loss) | true |
