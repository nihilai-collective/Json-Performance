
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 320.894 | 1.25963 | 8189.97ms | 1834197 | 40 | 1.88588e+11 | 5.4511e+06 | 0.0843967 | 9.47037 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 318.804 | 1.5252 | 8126.92ms | 1834197 | 30 | 2.10096e+11 | 5.48684e+06 | 0.18466 | 9.53352 | 1(Tie) | true |
