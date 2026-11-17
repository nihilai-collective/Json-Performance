
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1554.65 | 0.0613862 | 6853.92ms | 7351818 | 30 | 2.29924e+08 | 4.50984e+06 | 0.307451 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1232.01 | 0.576582 | 8468.41ms | 7351818 | 80 | 8.61333e+10 | 5.69088e+06 | 8.30242 | -(Loss) | false |
