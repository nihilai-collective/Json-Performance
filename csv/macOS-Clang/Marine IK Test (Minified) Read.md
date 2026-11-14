
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 367.036 | 1.15718 | 7284.13ms | 1834197 | 30 | 9.12424e+10 | 4.76581e+06 | 3.03006 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 360.085 | 1.58337 | 7071.2ms | 1834197 | 30 | 1.77488e+11 | 4.85781e+06 | 0.145937 | 1(Tie) | true |
