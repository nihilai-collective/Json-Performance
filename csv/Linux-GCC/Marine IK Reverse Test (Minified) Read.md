
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 406.324 | 0.297693 | 6605.18ms | 1834197 | 40 | 6.56967e+09 | 4.305e+06 | 2.41127 | 6.09317 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 223.561 | 0.303292 | 5545.08ms | 1834197 | 40 | 2.25259e+10 | 7.82438e+06 | 9.5535 | 11.0744 | -(Loss) | false |
