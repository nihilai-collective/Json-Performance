
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 222.881 | 0.333538 | 417.366ms | 905 | 4890 | 815733 | 3872.35 | 0.979279 | 1(Win) | true |
| simdjson (ondemand) | 154.327 | 0.496883 | 546.445ms | 905 | 2560 | 1.97679e+06 | 5592.5 | 0.616648 | 2(Loss) | true |
