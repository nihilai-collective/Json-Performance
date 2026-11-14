
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 943.714 | 0.683548 | 5473.48ms | 7351818 | 40 | 1.03159e+11 | 7.42941e+06 | 3.57198 | 3.22057 | -(Win) | false |
| simdjson (ondemand) | 695.022 | 0.562114 | 7357.34ms | 7351818 | 40 | 1.28618e+11 | 1.00878e+07 | 0.208464 | 4.37306 | 2(Loss) | true |
