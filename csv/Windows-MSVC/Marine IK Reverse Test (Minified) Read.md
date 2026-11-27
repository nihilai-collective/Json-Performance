
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 266.043 | 0.310672 | 10093.3ms | 1834197 | 80 | 3.33799e+10 | 6.57499e+06 | 0.310384 | 11.4239 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 207.439 | 0.305311 | 6089ms | 1834197 | 30 | 1.98846e+10 | 8.43248e+06 | 3.71467 | 14.6519 | -(Loss) | false |
