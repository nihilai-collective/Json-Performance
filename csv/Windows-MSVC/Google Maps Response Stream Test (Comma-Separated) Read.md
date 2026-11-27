
----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 665.314 | 0.822807 | 9768.06ms | 4203058 | 80 | 1.96591e+11 | 6.02475e+06 | 4.41374 | 4.5678 | -(Win) | false |
| simdjson (ondemand) | 529.541 | 0.263458 | 5889.43ms | 4203058 | 30 | 1.1931e+10 | 7.56947e+06 | 0.0598098 | 5.73927 | 2(Loss) | true |
