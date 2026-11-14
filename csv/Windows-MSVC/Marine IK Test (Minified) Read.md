
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 219.427 | 0.742707 | 5652.06ms | 1834197 | 40 | 1.40219e+11 | 7.97178e+06 | 1.63148 | 11.2828 | 1(Win) | true |
| simdjson (ondemand) | 213.738 | 0.526396 | 5932.07ms | 1834197 | 40 | 7.4236e+10 | 8.18398e+06 | 0.976903 | 11.5833 | 2(Loss) | true |
