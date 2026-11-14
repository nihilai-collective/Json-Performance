
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 253.681 | 0.474537 | 10223.5ms | 1834197 | 80 | 8.56537e+10 | 6.89538e+06 | 0.763337 | 11.9797 | 1(Win) | true |
| simdjson (ondemand) | 194.16 | 0.496218 | 6285.3ms | 1834197 | 40 | 7.99429e+10 | 9.00922e+06 | 0.103677 | 15.6533 | 2(Loss) | true |
