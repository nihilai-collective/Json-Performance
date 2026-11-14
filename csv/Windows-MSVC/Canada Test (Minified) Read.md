
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 192.02 | 0.604616 | 7741.36ms | 2090234 | 30 | 1.18189e+11 | 1.03812e+07 | 3.78114 | 12.8931 | -(Win) | false |
| simdjson (ondemand) | 175.027 | 0.668501 | 8034ms | 2090234 | 30 | 1.73902e+11 | 1.13891e+07 | 0.590192 | 14.1451 | 2(Loss) | true |
