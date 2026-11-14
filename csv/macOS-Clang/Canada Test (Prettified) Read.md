
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1103.13 | 0.203605 | 6891.47ms | 5212421 | 40 | 3.36717e+09 | 4.50623e+06 | 0.0359717 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 972.706 | 0.585708 | 7795.15ms | 5212421 | 30 | 2.68782e+10 | 5.11044e+06 | 5.19974 | -(Loss) | false |
