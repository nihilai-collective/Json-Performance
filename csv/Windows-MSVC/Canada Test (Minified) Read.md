
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 409.497 | 0.373611 | 7204.13ms | 2090234 | 80 | 2.64617e+10 | 4.86793e+06 | 1.15555 | 7.42132 | 1(Win) | true |
| simdjson (ondemand) | 391.594 | 0.752785 | 7537.9ms | 2090234 | 30 | 4.40536e+10 | 5.09048e+06 | 0.416489 | 7.76057 | 2(Loss) | true |
