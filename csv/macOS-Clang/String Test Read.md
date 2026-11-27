
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 2174.48 | 0.29508 | 212.407ms | 4215 | 30 | 892.662 | 1848.6 | 1.77123 | 1(Win) | true |
| simdjson (stage-1) | 1663.34 | 0.0824091 | 260.995ms | 4215 | 30 | 118.989 | 2416.67 | 0 | 2(Loss) | true |
