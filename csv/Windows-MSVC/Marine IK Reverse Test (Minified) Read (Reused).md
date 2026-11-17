
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 761.052 | 0.959605 | 8194.08ms | 1834197 | 30 | 1.45939e+10 | 2.29843e+06 | 0.531137 | 3.25307 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 645.203 | 0.214464 | 9575.03ms | 1834197 | 160 | 5.40917e+09 | 2.71113e+06 | 2.82817 | 3.8372 | -(Loss) | false |
| Glaze | 203.085 | 1.82504 | 6141.81ms | 1834197 | 30 | 7.41313e+11 | 8.61328e+06 | 1.23481 | 12.191 | 3(Loss) | true |
| simdjson (ondemand) | 126.931 | 0.155449 | 9886.37ms | 1834197 | 30 | 1.37675e+10 | 1.37809e+07 | 1.00058 | 19.5052 | 4(Loss) | true |
