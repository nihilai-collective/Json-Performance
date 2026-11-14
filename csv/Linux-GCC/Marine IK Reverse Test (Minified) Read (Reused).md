
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 402 | 0.214103 | 6898.12ms | 1834197 | 40 | 3.47172e+09 | 4.35131e+06 | 0.174503 | 6.15873 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 222.899 | 0.143974 | 5852.4ms | 1834197 | 40 | 5.10628e+09 | 7.8476e+06 | 5.33676 | 11.1071 | -(Loss) | false |
