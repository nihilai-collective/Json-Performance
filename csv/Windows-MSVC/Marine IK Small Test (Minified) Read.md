
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 178.524 | 0.101123 | 2490.27ms | 4604 | 4890 | 3.02473e+06 | 24594.6 | 0.0689373 | 13.8531 | 1(Win) | true |
| simdjson (ondemand) | 172.439 | 0.377622 | 2618.89ms | 4604 | 320 | 2.95846e+06 | 25462.5 | 0.00490894 | 14.3419 | 2(Loss) | true |
